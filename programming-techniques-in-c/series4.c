// series 4
// created by : bluecosmo

// NOTE:
// sum = -1 + 2 - 3 + 4 - 5 + 6 - ... n terms
// idx =  1   2   3   4   5   6   ... n places

// imports
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main() {

    // variables
    char terms_buffer[MAX]; 
    int num_of_terms, sum;

    printf("[~] Enter number of terms :\n");
    fgets(terms_buffer, MAX, stdin);

    if (sscanf(terms_buffer, "%d", &num_of_terms)) {
        
        sum = 0;

        for (int i = 1; i <= num_of_terms; i++) {
            sum = i * pow(-1, i);
            printf("[+] Current i = %d and sum = %d\n", i, sum);
        }
    }
    else {
        printf("[!] ERROR:\n");
    }

    printf("[+] Final sum is %d\n", sum);


    return EXIT_SUCCESS;
}
