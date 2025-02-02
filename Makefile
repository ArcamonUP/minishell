# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/02 15:36:26 by kbaridon          #+#    #+#              #
#    Updated: 2025/02/02 16:16:12 by kbaridon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src
LIBFT = libft
INCDIR = includes
NAME = minishell
HEADERS = $(INCDIR)/minishell.h $(LIBFT)/libft.h

SRC = minishell.c

OBJS = $(addprefix $(SRCDIR)/, $(SRC:.c=.o))

all:	$(NAME)

$(NAME):	$(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT)/libft.a -o $(NAME)

$(SRCDIR)/%.o:	$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(LIBFT) -I $(INCDIR) -c $< -o $@

$(OBJS):	$(HEADERS)

clean:
	$(MAKE) clean -C $(LIBFT)
	rm -rf $(OBJS)

fclean:	clean
	$(MAKE) fclean -C $(LIBFT)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re