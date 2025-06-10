/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:56:17 by dopereir          #+#    #+#             */
/*   Updated: 2025/06/09 22:14:42 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

//turns t_command struct into a doubly linked list
//parse through tokens and create meaning modules of data

//use dup2 to redirect the fd 1(stdout) to target fd.

/*
for example:

in input ls -la > text.txt

we have three commands in the linked list

t_commands cmd[3]:

cmd[0] = ls
		args[0] = -la
		input_file = 0 (stdin default);
		output_file = cmd[1]->output_file;
		*filename = text.txt

cmd[1] = >
		args[0] = null
		input_file = cmd[0]->input_file #0(stdin)
		output_file = cmd[2]->fd #to obtain this fd must use open(cmd[2]->filename)

cmd[2] = test.txt
			args[0] = null
			char	*filename = "test.txt"
			input_file = cmd[1]->input_file
			output_file = cmd[1]->output_file


			###int dup2(int oldfd, int newfd);
			int fd = open(command->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			uses the dup2
			dup2(fd, STDOUT_FILENO)


			dup2 takes the oldfd and duplicates, subs the newfd to the old one.
*/

//this function can be called at execute func
void	redirections(t_command **commands, int n_cmds)
{
	int	i;
	int	fd_target;
	int	saved_stdout;
	pid_t	pid;

	i = 0;
	while (i < n_cmds)
	{
		if (commands[i]->type == T_REDIR_OUT) //pay attention, we must return error when the file doest have permission
		{
			saved_stdout = dup(STDOUT_FILENO);
			fd_target = open(commands[i+1]->filename, O_WRONLY | O_CREAT, 0664);
			if (fd_target < 0)
			{
				perror("Error at open() function call");
				exit(EXIT_FAILURE);
			}
			dup2(fd_target, STDOUT_FILENO);
			close(fd_target);
			//exec and fork
			pid = fork();
			if (pid == 0)
				execve(commands[i-1]->path, commands[i-1]->argv, NULL);
			else
				wait(NULL);
			close(fd_target);
			dup2(saved_stdout, STDOUT_FILENO);
			break ;
		}
		i++;
	}
}

int	main(void)
{
	t_command	*commands[3];

	commands[0] = malloc(sizeof(t_command));
	commands[1] = malloc(sizeof(t_command));
	commands[2] = malloc(sizeof(t_command));

	commands[0]->name = "echo";
	commands[0]->path = "/bin/echo";
	//commands[0]->argv = malloc(3 * sizeof(char *));
	commands[0]->argv[0] = "ls";
	commands[0]->argv[1] = "-la";
	commands[0]->argv[2] = NULL;

	commands[1]->name = ">";
	commands[1]->type = T_REDIR_OUT;

	commands[2]->filename = "test.txt";

	redirections(commands, 3);
}

/*t_parse_data	*create_node(t_command *cmd_data)
{
	t_parse_data	*new_node;

	new_node = malloc(sizeof(t_parse_data));

	new_node->data = cmd_data;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}*/
