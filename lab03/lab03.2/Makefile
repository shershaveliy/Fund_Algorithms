CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
INCLUDE = -I.

HEAP_SRC = include/vector.h
TEST_SRCS = src/test_int.c src/test_string.c src/test_double.c
TEST_EXECS = test_int.exe test_string.exe test_double.exe

all: $(TEST_EXECS)

test_int.exe: src/test_int.c $(HEAP_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ src/test_int.c

test_string.exe: src/test_string.c $(HEAP_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ src/test_string.c

test_double.exe: src/test_double.c $(HEAP_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ src/test_double.c

test: all
	@echo === Запуск всех тестов ===
	@test_int.exe
	@echo.
	@test_string.exe
	@echo.
	@test_double.exe

clean:
	del /Q $(TEST_EXECS) *.o 2>nul

help:
	@echo Доступные команды:
	@echo   make all     - собрать все тесты
	@echo   make test    - собрать и запустить все тесты
	@echo   make clean   - удалить скомпилированные файлы
	@echo   make help    - показать эту справку

.PHONY: all test clean help