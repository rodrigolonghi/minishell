# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 23:44:29 by rfelipe-          #+#    #+#              #
#    Updated: 2022/05/12 21:29:07 by acarneir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
FLAGS = -g -Wall -Wextra -Werror
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck -q ./minishell

LIBFT_DIR = ./libft
LIBFT = libft/libft.a

INCLUDE_DIR = ./includes
INCLUDE = $(INCLUDE_DIR)/minishell.h

OBJ_DIR = ./objs
OBJ_BUILTINS = ./objs/builtins
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_DIR = ./src
BUILTINS = ./src/builtins
SRC = $(SRC_DIR)/minishell.c \
	$(BUILTINS)/exit_prompt.c \
	$(BUILTINS)/pwd_prompt.c

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "Minishell compiled!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_BUILTINS)
	@$(CC) -c $(FLAGS) -I$(INCLUDE_DIR) -o $@ $<

$(LIBFT):
	@echo "Compiling project...\n"
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Deleting EVERYTHING...\n"
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
	@rm -rf $(CHECKER)
	@echo "Project cleaned up!"

re: fclean all

valgrind: all
	@$(VALGRIND)
