#ifndef OVERPRINTF_H
#define OVERPRINTF_H

#include <stdio.h>
#include <stdarg.h>

int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);

int handle_custom_specifier(const char **format, va_list args, char *buffer);
int handle_standard_specifier(const char **format, va_list args, char *buffer);

#endif