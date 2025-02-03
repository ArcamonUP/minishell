# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/02 15:36:26 by kbaridon          #+#    #+#              #
#    Updated: 2025/02/03 12:20:51 by kbaridon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN=\033[0;32m
ORANGE=\033[38;5;214m
CC = cc
CFLAGS = -Wall -Wextra -Werror
OTHERFLAGS = -lreadline
SRCDIR = src
LIBFT = libft
INCDIR = includes
NAME = minishell
HEADERS = $(INCDIR)/minishell.h $(INCDIR)/pipex.h $(LIBFT)/libft.h

SRC =	pipe/pipex.c pipe/pipex_init.c pipe/pipex_utils.c pipe/pipex_bonus.c	\
		minishell.c

OBJS = $(addprefix $(SRCDIR)/, $(SRC:.c=.o))

all:	$(NAME)

$(NAME):	$(OBJS)
	@$(MAKE) --no-print-directory -C $(LIBFT)
	@echo "$(ORANGE)Compiling libft..."
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
	@echo "$(ORANGE)Cleaning minishell's objects..."
	@echo "$(GREEN)Cleaning of objects completed !"

fclean:	clean
	@$(MAKE) --no-print-directory fclean -C $(LIBFT)
	@rm -rf $(NAME)
	@echo "$(ORANGE)Cleaning executables..."
	@echo "$(GREEN)Cleaning of executables completed !"

re: fclean all

.PHONY: all clean fclean re
