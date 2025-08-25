// series 7
// created by : bluecosmo

// imports
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int factorial(int n) {
    if (n == 1)
        return n;

    return n * factorial(n - 1);
}

int main() {

    // variables
    char terms_buffer[MAX];
    int num_of_terms, sum;

    printf("[~] Enter number of terms : ");
    fgets(terms_buffer, MAX, stdin);

    if (sscanf(terms_buffer, "%d", &num_of_terms)) {
        sum = 0;
        for (int i = 1; i <= num_of_terms; i++) {
            sum += factorial(i*2);
            printf("[*] Current i = %d, Factor = %d, Sum = %d\n", i, factorial(i*2), sum);
        }
    }

    else {
        printf("[!] ERROR: No number detected\n");
    }


    return EXIT_SUCCESS;
}
