#ifndef BRACKETS_H
#define BRACKETS_H

int check_brackets(const char *str);
int is_open_bracket(char c);
int is_close_bracket(char c);
char get_matching_open_bracket(char close_bracket);

#endif