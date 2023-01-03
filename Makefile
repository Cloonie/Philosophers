# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 17:05:11 by mliew             #+#    #+#              #
#    Updated: 2023/01/03 21:50:32 by mliew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	gcc
RM			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror
# CFLAGS		+=	-pthread
# CFLAGS		+=	-g -fsanitize=thread

FILES		=	philo	\
				libft	\

SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/

all:
	mkdir -p $(OBJS_DIR)
	make $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@echo Removing object files...
	@$(RM) $(OBJS_DIR)

fclean: clean
	@echo Removing program file...
	@$(RM) $(NAME)

re:	fclean all