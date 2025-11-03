# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysantos- <ysantos-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/05 21:41:21 by ysantos-          #+#    #+#              #
#    Updated: 2025/11/03 22:50:54 by ysantos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c	printf_utils.c
BONUS = ft_printf_bonus.c	printf_utils_bonus.c	utils_bonus.c

OBJ = $(SRC:.c=.o)
BNOBJ= $(BONUS:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) -c $(SRC)
	ar rcs $(NAME) $(OBJ)
	ranlib $(NAME)

bonus:
	$(CC) $(FLAGS) -c $(BONUS)
	ar rcs $(NAME) $(BNOBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY all bonus clean fclean re rebonus