# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 17:05:11 by mliew             #+#    #+#              #
#    Updated: 2022/12/29 18:05:06 by mliew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
HEADER			= includes/
SOURCE_DIR		= source/
FILE_NAMES		= philo
SOURCES			= $(addsuffix .c, $(addprefix $(SOURCE_DIR), $(FILE_NAMES)))
OBJECTS			= $(addsuffix .o, $(addprefix $(SOURCE_DIR), $(FILE_NAMES)))

SANITIZE		=	-fsanitize=address -g3

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror $(SOURCES) -c objects/ -I $(HEADER) #$(SANITIZE)
	gcc -Wall -Wextra -Werror $(OBJECTS) -o $(NAME) -I $(HEADER) #$(SANITIZE)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re:	fclean all