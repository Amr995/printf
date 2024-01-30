<<<<<<< HEAD
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"

/**
 * _printf - Custom printf function
 * @format: Format string
 *
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%' && (*(format + 1) == 'c' || *(format + 1)
				       == 's' ||
				       *(format + 1) == 'd' || *(format + 1)
				       == 'i' ||
				       *(format + 1) == 'r'))
		{
			count += handle_format(args, *++format);
		}
		else if (*format == '%' && *(format + 1) == '%')
		{
			write(1, "%", 1);
			count++;
			format++;
		}
		else
		{
			write(1, format, 1);
			count++;
		}

		format++;
	}

	va_end(args);
	return (count);
}

/**
 * handle_format - Handles format specifiers
 * @args: Variable argument list
 * @specifier: Format specifier
 *
 * Return: Number of characters printed
 */
int handle_format(va_list args, char specifier)
{
	int count = 0;

	switch (specifier)
	{
	case 'c':
		count += write_char(args);
		break;
	case 's':
	case 'r': /* Treat %r like %s */
		count += write_str(args);
		break;
	case 'd':
	case 'i':
		count += write_int(args);
		break;
	}

	return (count);
}

/**
 * write_char - Writes a character to standard output
 * @args: Variable argument list
 *
 * Return: Number of characters printed
 */
int write_char(va_list args)
{
	char c = va_arg(args, int);

	write(1, &c, 1);

	return (1);
}

/**
 * write_str - Writes a string to standard output
 * @args: Variable argument list
 *
 * Return: Number of characters printed
 */
int write_str(va_list args)
{
	char *str = va_arg(args, char *);
	int count = 0;

	if (str == NULL)
		str = "(null)";

	while (*str)
	{
		write(1, str, 1);
		str++;
		count++;
	}

	return (count);
}

/**
 * write_int - Writes an integer to standard output
 * @args: Variable argument list
 *
 * Return: Number of characters printed
 */
int write_int(va_list args)
{
	int num = va_arg(args, int);
	char buffer[12]; /* Assuming a 32-bit int */

    /* Convert integer to string */
	int length = sprintf(buffer, "%d", num);

    /* Write the string to standard output */
	write(1, buffer, length);

	return (length);
=======
#include "main.h"
/**
 * _printf - is a function that selects the correct function to print.
 * @format: identifier to look for.
 * Return: the length of the string.
 */
int _printf(const char * const format, ...)
{
	convert_match m[] = {
		{"%s", printf_string}, {"%c", printf_char},
		{"%%", printf_37},
		{"%i", printf_int}, {"%d", printf_dec}, {"%r", printf_srev},
		{"%R", printf_rot13}, {"%b", printf_bin}, {"%u", printf_unsigned},
		{"%o", printf_oct}, {"%x", printf_hex}, {"%X", printf_HEX},
		{"%S", printf_exclusive_string}, {"%p", printf_pointer}
	};

	va_list args;
	int i = 0, j, len = 0;

	va_start(args, format);
	if (format == NULL || (format[0] == '%' && format[1] == '\0'))
		return (-1);

Here:
	while (format[i] != '\0')
	{
		j = 13;
		while (j >= 0)
		{
			if (m[j].id[0] == format[i] && m[j].id[1] == format[i + 1])
			{
				len += m[j].f(args);
				i = i + 2;
				goto Here;
			}
			j--;
		}
		_putchar(format[i]);
		len++;
		i++;
	}
	va_end(args);
	return (len);
>>>>>>> ef5a6fed72ba2562c3c397765984573b537b7ebe
}
