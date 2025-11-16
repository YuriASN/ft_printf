# FT_PRINTF

### This project was done to reimplement printf().  
This primarily teached me how to handle a variable number of arguments, introducing **variadic functions** in C.  

This repository has submodule dependencies. To clone the dependencies with it do:
`git clone --recurse-submodules -j8 https://github.com/YuriASN/ft_printf.git`  

The libft lib has to be linked along with printf when a program is created. As an example you have the command bellow.  
`cc -W -W -W main.c -L. -lftprintf -Llibft -lft -o program`  

The flags that ft_printf will support are:  
	•%c Prints a single character.  
	•%s Prints a string (as defined by the common C convention).  
	•%p The void * pointer argument has to be printed in hexadecimal format.  
	•%d Prints a decimal (base 10) number.  
	•%i Prints an integer in base 10.  
	•%u Prints an unsigned decimal (base 10) number.  
	•%x Prints a number in hexadecimal (base 16) lowercase format.  
	•%X Prints a number in hexadecimal (base 16) uppercase format.  
	•%% Prints a percent sign.  

And more with the **bonus**:  
	•%# Used with x or X specifiers the value is preceeded with 0x or 0X respectively for values different than zero.  
	•% (space) If no sign is going to be written, a blank space is inserted before the value.  
	•%+ Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign.  

These must work with combinations of any of the 3 flags.  
	•%- Left-justify within the given field width; Right justification is the default.  
	•%0 Left-pads the number with zeroes (0) instead of spaces when padding is specified.  
	•%.For integer specifiers (d, i, o, u, x, X): precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0.  