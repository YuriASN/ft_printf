NAME = libftprintf.a

SRC = ft_printf.c	printf_utils.c
BONUS = ft_printf_bonus.c	printf_utils_bonus.c	utils_bonus.c	get_conversions.c

OBJ = $(SRC:.c=.o)
BNOBJ= $(BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

.PHONY: all bonus libft clean fclean re rebonus

all: $(NAME)

$(NAME): libft $(OBJ)
	@ar rcs $(NAME) libft/*o $(OBJ)
	@echo "\e[0;32mPrintf compiled!\nDon't forget to link Libft when creating a program.\e[0m"

bonus: libft $(BNOBJ)
	@ar rcs $(NAME) libft/*o $(BNOBJ)
	@echo "\e[0;32mPrintf bonus compiled!\nDon't forget to link Libft when creating a program.\e[0m"

libft:
	@if [ ! -d libft ]; then \
		echo "LIBFT:	\e[0;31mLibft directory missing! Cloning the submodule now...\e[0m"; \
		git submodule update --init; \
		echo "LIBFT:	\e[0;32mSubmodule cloned.\e[0m"; \
	fi
	@if [ `ls -A libft/ && wc -l` == "0" ]; then \
		echo "LIBFT:	\e[0;31mLibft directory is empty! Downloading submodule archives now...\e[0m"; \
		git submodule foreach git checkout main && git submodule foreach git fetch  && git submodule foreach git reset --hard origin/main; \
		echo "LIBFT:	\e[0;32mSubmodule ready.\e[0m"; \
	fi
	$(MAKE) -C libft/ --no-print-directory;

# Regra padrão para compilar .c -> .o
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

clean:
	@/bin/rm -f *.o
#	@$(MAKE) clean -Clibft/ --no-print-directory
	@echo "\e[0;33mPrintf clean done!\e[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) fclean -Clibft/ --no-print-directory
	@echo "\e[0;31mPrintf fclean done!\e[0m"

re: fclean all

rebonus: fclean bonus