#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include "converting.h"

//+1
int increment(int value){
    int carry = 1;
    while (carry != 0){
        int tempCarry = value & carry;
        value = value ^ carry;
        carry = tempCarry << 1;
    }
    return value;
}
//-1
int decrement(int value){
    return ~increment(~value);
}

int changeSign(int value){
    return increment(~value);
}

int isZero(int value){
    return (value == 0) ? 1 : 0;
}

void swapChars(char* a, char* b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

void reverseArray(char* array, int length){
    int start = 0;
    int end = decrement(length); // начальная позиция lenght - 1
    
    while (start < end){
        swapChars(&array[start], &array[end]);
        start = increment(start);
        end = decrement(end);
    }
}

void decimalToBase2R(int number, int r, char* result){
    if (r < 1 || r > 5){
        result[0] = '\0';
        return;
    }
    
    if (isZero(number)){
        result[0] = '0';
        result[1] = '\0';
        return;
    }
    
    char symbols[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    int position = 0;
    int isNegative = 0;
    int originalNumber = number;
    
    // Обработка отрицательных чисел
    if (number < 0){
        // в общем случае инвертируем все биты, + 1
        // для int_min в начале сдвиг вправо на 1 бит
        isNegative = 1;
        if (number == INT_MIN){
            result[position] = '0';
            position = increment(position);
            number = number >> r;
        }
        number = changeSign(number);
    }
    
    // Маска для битов
    int bitMask = ~(INT_MAX << r);
    
    while (!isZero(number)){
        //Берем r крайних битов в двоичном представлении;
        //преобразуем в число с помощью массива; сдвиг вправо на r битов
        int currentBits = number & bitMask;
        result[position] = symbols[currentBits];
        position = increment(position);
        number = number >> r;
    }
    
    if (isNegative){
        result[position] = '-';
        position = increment(position);
    }
    
    reverseArray(result, position);
    result[position] = '\0';
}