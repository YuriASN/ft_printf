#include "ft_printf_bonus.h"
#include <stdio.h>
#include <limits.h>
//make fclean; rm ./comp.out;  make bonus
//cc tester.c libftprintf.a -o comp.out && echo && echo && echo && ./comp.out b
int	main(int argc, char **argv){
	char	*str = "Will justiify.";
	int		nbr = 1234;
	int		r_origina;
	int		r_mine;

	if (argc == 1 || (argc > 1 && argv[1][0] == 'm'))
	{							// c
		r_origina = printf("This is the original printf: |%c|\n", 'a');
		r_mine = ft_printf("This is the ft vers. printf: |%c|\n", 'a');
		printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);
								// p
		r_origina = printf("This is the original printf: |%p|\n", (void *)ULONG_MAX);
		r_mine = ft_printf("This is the ft vers. printf: |%p|\n", (void *)ULONG_MAX);
		printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);
	}
	else if (argc > 1 && argv[1][0] == 'b')
	{
								// 1
		r_origina = printf("This is the original printf: |%d|\n", -1);
		r_mine = ft_printf("This is the ft vers. printf: |%d|\n", -1);
		printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);

								// 2
		r_origina = printf("This is the original printf: |%-2d|\n", -1);
		r_mine = ft_printf("This is the ft vers. printf: |%-2d|\n", -1);
		printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);

								// 3
		r_origina = printf("This is the original printf: |%-17x|\n", nbr);
		r_mine = ft_printf("This is the ft vers. printf: |%-17x|\n", nbr);
		printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);

								// 4
		r_origina = printf("This is the original printf: |%.17d|\n", nbr);
		r_mine = ft_printf("This is the ft vers. printf: |%.17d|\n", nbr);
		printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);
								// 5
		r_origina = printf("This is the original printf: |%09u %010u %011u %012u %013u %014u %015u|\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
		r_mine = ft_printf("This is the ft vers. printf: |%09u %010u %011u %012u %013u %014u %015u|\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
		printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);
	}
}
