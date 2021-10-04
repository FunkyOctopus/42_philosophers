# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olgerret <olgerret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/21 13:34:53 by olgerret          #+#    #+#              #
#    Updated: 2021/10/02 12:47:24 by olgerret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libft_philosophers.a

FLAGS = -Wall -Wextra -Werror

SRC = ft_main.c ft_philosophers.c ft_free_functions.c \
	ft_helpers.c ft_input_handling.c

all: $(NAME)

$(NAME): *.c
	$(CC) $(FLAGS) -c $(SRC)
	ar rc $(NAME) *.o
	$(CC) $(FLAGS) -L. -lft_philosophers -o philo

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
