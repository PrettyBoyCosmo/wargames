// series 6
// created by : bluecosmo

// imports
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// my solution
int factorial(int n) {

    if (n == 1) {
        return n;
    }

    return n * factorial(n - 1);
}

int main() {

    char terms_buffer[MAX];
    int term, sum;

    printf("[~] Enter number of terms : \n");
    fgets(terms_buffer, MAX, stdin);

    if (sscanf(terms_buffer, "%d", &term)) {
        sum = 0;

        for (int i = 1; i <= term; i++) {
            sum += factorial(i);
            printf("[*] Current i = %d, Factor = %d, Sum = %d\n", i, factorial(i), sum);
        }
    }

    else {
        printf("[!] ERROR: No number detected\n");
    }

    return EXIT_SUCCESS;
}
