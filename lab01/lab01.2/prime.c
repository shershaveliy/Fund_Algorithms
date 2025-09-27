#include "prime.h"

bool prime(int x) {
    if(x < 2) {
        return false;
    }
    else if(x == 2) {
        return true;
    }
    else if(x % 2 == 0){
        return false;
    }
    else{
        for(int i = 3; i * i <= x; i += 2){
            if(x % i == 0){
                return false;
                break;
            }
        }
    }
    return true;
}

int find_prime(int n) {
    if (n == 1) return 2;
    
    int count = 1;
    int x_prime = 1;
    
    while (count < n) {
        x_prime += 2;
        if (prime(x_prime)) {
            count++;
        }
    }
    return x_prime;
}