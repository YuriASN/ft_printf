This project has been created as part of the 42 curriculum by ysantos-

## Description

The ft_printf is a copy of printf() but with less options. It writes a string to standard output transforming arguments to string replacing its specifiers.  
It writes to stdout the string that might contain specifiers that will be replaced by values that are passed as additional parameters.  
The specifiers always come after a % as for example `%[flag][width][precision]specifier`.  

On this project we learn variadic arguments, since an unknown number of arguments can be passed as a parameter. And handling many conversions to *char\** to display those arguments on stdout.

| Specifier | Output |
| :---- | :---- |
| %c | Prints a single character. |
| %s | Prints a string (as defined by the common C convention). |
| %p | The void * pointer argument has to be printed in hexadecimal format. |
| %d | Prints a decimal (base 10) number. |
| %i | Prints an integer in base 10. |
| %u | Prints an unsigned decimal (base 10) number. |
| %x | Prints a number in hexadecimal (base 16) lowercase format.|
| %X | Prints a number in hexadecimal (base 16) uppercase format.|
| %% | Prints a percent sign. |

The flags provided by the bonus part can have combinations of  `-0.` and the field minimum width (number) under all conversions. In addition, it also handle all the following flags: `#(space)+`.  

| Flags | Description |
| :---- | :---- |
| - | Left-justify within the given field width; Right justification is the default. |
| + | Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers. |
| (space) | If no sign is going to be written, a blank space is inserted before the value. |
| # | Used with x or X specifiers the value is preceeded with 0x or 0X respectively for values different than zero. |
| 0 | Left-pads the number with zeroes (0) instead of spaces when padding is specified (see width sub-specifier). |
|**Width**|
| (number) | Right-justifies given argument leaving the width of the full size of number passed. |
|**Precision**|
| .(number) | For integer specifiers (d, i, u, x, X): precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0. For string specifiers this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered. |

## Instructions

### Install

Requirements:  
	- C language compiler ex.: GCC (GNU Compiler Collection)  
	- Make  

Clone the repository from [github](https://github.com/YuriASN/ft_printf).  
```git clone https://github.com/YuriASN/ft_printf```  
*As the bonus has the option for flags, width and precision, I would recommend to use the bonus version, but it's up to you.*  
After making the library with the `make` or `make bonus` command, you need to link it to your program as  
```cc main.c ft_printf.a -o my_prog.out```.  

### Usage

Link the library on your **.c** or **.h** file as `PATH/ft_printf.h` or `PATH/ft_printf_bonus.h` depending on the version you want to use.  
The function prototype is `ft_printf(char \*str, ...)`, Pass a string as argument and for each specifier, you add a argument for it, for example:  
`ft_printf("Hello %s! We're %d.", "world", 42);`  
Where **%s** is replaced by **world**, and **%d** by **42**: `Hello world! We're 42.`. 

## Resources

Some functions were already created by me, on the [Libft](https://github.com/YuriASN/Libft_2.0) project, done previously at 42.  
External functions:  
| Function | Description |
| :----- | :---- |
| **write(fd, buffer, n)** | Writes up to amount of `n` bytes from the `buffer` to the file referred to by the `fd` file descriptor. |
| **va_start(va_list ap)** | Macro initializes `ap` for subsequent use by **va_arg()** and **va_end()**, and must be called first. |
| **va_arg(va_list ap, type)** |  Has the type and value of the next argument in  the  call.   The  argument ap is the va_list `ap` initialized by **va_start()**.  Each call to **va_arg()** modifies ap so that the next call returns the next argument.  The argument `type`  is a type name specified so that the type of a pointer to an object that has the specified type can be obtained simply by adding a * to type. |
| **va_end(ap)** | Each  invocation  of **va_start()** must be matched by a corresponding invocation of **va_end()** in the same function.  After the call **va_end(ap)** the variable `ap` is undefined. |
| **va_copy(va_list dest, va_list src)** |  Copies the (previously initialized) variable argument list `src` to  `dest`. The  behavior is as if **va_start()** were applied to `dest` with the same last argument, followed by the same number of **va_arg()** invocations that was used to reach the current state of src. |
  
## Algorithm and Data Structure

The `ft_printf` loop scans the format string character by character. When it sees a `%`, it parses the conversion and prints accordingly:

1. **Parsing**  
   Reads flags (`-0#(space)+`), width, optional precision, and the final specifier. The parsed data is stored in a few of individual local variables.
2. **Dispatch**  
   Dispatch can change accordingly to the flag(s) used. Mostly changing the order of Emission.
   It uses the specifier to route to the proper handler (`c, s, p, d, i, u, x, X, %`)with being written or the data being converted. In case of a `s` right justification for example, it just gets the length of it, to know how much space needs to be put before.
3. **Conversion**  
   Each number handler converts the argument to a temporary buffer (base 10 or 16), applies sign, prefix (`0x/0X`), precision trimming, and zero/space padding.
4. **Emission**  
   Writes to `stdout` in chunks: prefix, padding, and payload, in the order provided by the flag. Counts bytes written to return the final length.

### Core data structures
- **Individual flag variables**: keeps flags, width, precision, specifier, and a “precision set” boolean. Centralizes parsing results and avoids recomputation.
- **Temporary conversion buffer**: local fixed-size arrays (*char nbr_c[20]*) for numeric to-string conversion, preventing dynamic allocation.

### Complexity
- **Time**: The function only reads the string once and handle each flag, width, precision and specifier only once. Characters of the string are printed directly unless a `%` is found, indicating a specifier. Things that slow down the function are:  
  - Reading the flags and width or precision specifiers. It'll depend of the number of characters that were used for them.  
  - Number conversions as it divides by its base repeatedly.  
  - Strings with right justification (*number flag*), as it copies the arg to get the string length and with it calculate the amount of spaces to be written before.  
- **Space**: Uses small amount of memory space only buffering (*char nbr_c[20]*) for the number decimal or hex conversion. All the other specifiers have its arguments passed straight to output without buffering.
