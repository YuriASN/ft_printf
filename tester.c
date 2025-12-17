#include "ft_printf_bonus.h"
#include <stdio.h>

int	main(){
	char	*str = "Will justiify.";
	int		nbr = 1234;
	int		r_origina;
	int		r_mine;
							// 1
	r_origina = printf("This is the original printf: |%#17x|\n", nbr);
	r_mine = ft_printf("This is the ft vers. printf: |%#17x|\n", nbr);
	printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);

							// 2
	r_origina = printf("This is the original printf: |%#017x|\n", nbr);
	r_mine = ft_printf("This is the ft vers. printf: |%#017x|\n", nbr);
	printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);

							// 3
	r_origina = printf("This is the original printf: |%-17x|\n", nbr);
	r_mine = ft_printf("This is the ft vers. printf: |%-17x|\n", nbr);
	printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);

							// 4
	r_origina = printf("This is the original printf: |%.17d|\n", nbr);
	r_mine = ft_printf("This is the ft vers. printf: |%.17d|\n", nbr);
	printf("Returns are\norgi: %d\nmine: %d\n\n", r_origina, r_mine);
}
