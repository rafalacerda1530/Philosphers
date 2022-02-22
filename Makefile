# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 19:41:29 by rarodrig          #+#    #+#              #
#    Updated: 2022/02/21 21:17:40 by rarodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_SRC = ./src/
PATH_UTILS = ./utils/
PATH_OBJ = ./obj/

HEADERS = includes/philo.h

CC = clang
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
LEAK = -fsanitize=address

FILE =	$(PATH_SRC)philosophers.c $(PATH_UTILS)utils.c $(PATH_UTILS)utils_dinner.c\

OBJ = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(FILE))

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	@echo done!!
	@$(CC) $(CFLAGS) $(OBJ) $(LEAK) -pthread -g -o philo

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJ)
	$(CC) $(CFLAGS) -g -I. -c $< -o $@

clean:
	@$(RM) $(PATH_OBJ)
	@echo obj removed!

fclean: clean
	@$(RM) $(NAME)
	@echo clean everything

re: fclean all