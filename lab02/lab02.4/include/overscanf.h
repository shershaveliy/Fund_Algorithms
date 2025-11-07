
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
int handle_custom_specifier_scan(const char **format, va_list args, FILE *stream, const char **str, bool is_stream);

int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(const char *str, const char *format, ...);

