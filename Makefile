# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achu <achu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/02 15:36:26 by kbaridon          #+#    #+#              #
#    Updated: 2025/03/28 18:05:19 by achu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN=\033[0;32m
ORANGE=\033[38;5;214m
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
OTHERFLAGS = -lreadline
SRCDIR = src
LIBFT = libft
INCDIR = includes
NAME = minishell
HEADERS = $(INCDIR)/minishell.h $(LIBFT)/libft.h $(INCDIR)/pipex.h

SRC =	function/ft_cd.c \
		function/ft_echo.c \
		function/ft_env.c \
		function/ft_export.c \
		function/ft_pwd.c \
		function/ft_unset.c \
		exec/exec_and_or.c \
		exec/exec_redir.c \
		exec/exec.c \
		pipe/pipex_utils.c \
		pipe/pipex_init.c \
		pipe/pipex_lib.c \
		pipe/pipex.c \
		token/get_tokenize.c \
		token/tokenize_utils.c \
		token/tokenize.c \
		token/parser_utils.c \
		token/parser.c \
		wildcard/wild_tokenize.c \
		wildcard/wild_checker.c \
		wildcard/wildcard.c \
		checker_utils.c \
		checker.c \
		basics.c \
		custom_split.c \
		utils.c \
		init.c \
		init_redir.c \
		utils_lstfd.c \
		free.c \
		minishell.c

OBJS = $(addprefix $(SRCDIR)/, $(SRC:.c=.o))

all:	$(NAME)

$(NAME):	$(OBJS)
	@if [ ! -f $(LIBFT)/libft.a ]; then \
	echo "$(ORANGE)Compiling libft..."; \
	$(MAKE) --no-print-directory -C $(LIBFT); \
	fi
	@$(CC) $(CFLAGS) $(OBJS) $(OTHERFLAGS) $(LIBFT)/libft.a -o $(NAME)
	@echo "$(ORANGE)Compiling minishell..."
	@echo "$(GREEN)Compilation completed !"

$(SRCDIR)/%.o:	$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I $(LIBFT) -I $(INCDIR) -c $< -o $@

$(OBJS):	$(HEADERS)

clean:
	@$(MAKE) --no-print-directory clean -C $(LIBFT)
	@echo "$(ORANGE)Cleaning libft..."
	@rm -rf $(OBJS)
	@echo "$(ORANGE)Cleaning minishell..."
	@echo "$(GREEN)Cleaning of objects completed !"

fclean:	clean
	@$(MAKE) --no-print-directory fclean -C $(LIBFT)
	@rm -rf $(NAME)
	@echo "$(ORANGE)Cleaning executables..."
	@echo "$(GREEN)Cleaning of executables completed !"

re: fclean all

.PHONY: all clean fclean re
