#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>

int _putchar(char c);
int _printf(const char *format, ...);
int handle_format(va_list args, char specifier);
int write_char(va_list args);
int write_str(va_list args);
int write_rev_str(va_list args);
int write_int(va_list args);
void print_buffer(char buffer[], int *buffer_index);

#endif /* MAIN_H */
