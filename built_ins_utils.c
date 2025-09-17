/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:20:34 by dopereir          #+#    #+#             */
/*   Updated: 2025/09/09 16:22:08 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_child_builtin(t_command *cmd, t_env **env, t_parse_data *pd)
{
	if (cmd->input_file)
		set_input(cmd);
	if (cmd->output_file)
		set_output(cmd);
	return (run_parent_built(cmd, env, pd));

}
