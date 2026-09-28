#include <stdio.h>

/*
    Task:
    Write a function `int is_prime(int n)` that returns 1 if n is prime,
    0 otherwise.

    In main():
      - Ask user for an integer n (>= 2)
      - If invalid, print an error
      - Otherwise, print all prime numbers up to n
*/

int is_prime(int n) {
    // TODO: check if n is prime using loop up to sqrt(n)
    int i;
    if (n < 2) {
        return 0;
    }
    for (i = 2; i * i <= n; i++){
        if (n % i ==0){
            return 0;
        }
    }
    return 1; // placeholder
}

int main(void) {
    int n;
    int i;

    printf("Enter an integer n (>= 2): ");
    scanf("%d", &n);

    // TODO: validate input and print all primes up to n
    if (n < 2) {
        printf("Needs a integer greater or equal to 2.\n");
    } else {
        printf("Prime numbers to %d: ", n);
        for (i = 2; i <= n; i++) {
            printf ("%d ", i);
        }
    }
    printf("\n");
    return 0;
}

