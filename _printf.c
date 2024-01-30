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
}
