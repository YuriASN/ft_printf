NAME = libftprintf.a

SRC = ft_printf.c	printf_utils.c
BONUS = ft_printf_bonus.c	printf_utils_bonus.c	bonus_flags.c	get_conversions.c \
		bonus_utils.c		justify_right.c			dot_flag.c

OBJ = $(SRC:.c=.o)
BNOBJ= $(BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

.PHONY: all bonus libft clean fclean re rebonus

all: $(NAME)

$(NAME): libft $(OBJ)
	@ar rcs $(NAME) libft/*o $(OBJ)
	@echo "\e[0;32mPrintf compiled!\e[0m"

bonus: libft $(BNOBJ)
	@ar rcs $(NAME) libft/*o $(BNOBJ)
	@echo "\e[0;32mPrintf bonus compiled!\e[0m"

libft:
	@echo "LIBFT:\e[0;33m Ensuring submodule is initialized...\e[0m"
	@git submodule update --init --recursive --force libft
	@echo "LIBFT:\e[0;32m Libft ready.\e[0m"
	@$(MAKE) -C libft/ --no-print-directory;

# Regra padrão para compilar .c -> .o
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

clean:
	@/bin/rm -f *.o
	@echo "\e[0;33mPrintf clean done!\e[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) fclean -Clibft/ --no-print-directory
	@echo "\e[0;31mPrintf fclean done!\e[0m"

re: fclean all

rebonus: fclean bonus