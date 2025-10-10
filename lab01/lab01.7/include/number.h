#ifndef NUMBER_H
#define NUMBER_H

int find_min_base(const char* number);
char* remove_leading_zeros(const char* number);
long long convert_to_decimal(const char* num_str, int base);
int is_valid_number_for_base(const char* number, int base);

#endif