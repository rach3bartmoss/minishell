NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror -lreadline -I

SOURCES = main.c

OBJ = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)

$(OBJ)
