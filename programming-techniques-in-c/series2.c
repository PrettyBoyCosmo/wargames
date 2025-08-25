// series 2
// created by : bluecosmo

// NOTE:
// sum = 2 + 4 + 6 + 8 + ... + 2^n terms
// idx = 1   2   3   4   ...   n places

// imports
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main() {

    int num_of_terms, sum;
    char terms_buffer[MAX];

    // get number of terms
    printf("[~] Enter number of terms : ");
    fgets(terms_buffer, MAX, stdin);

    // if num inputted
    if (sscanf(terms_buffer, "%d", &num_of_terms)) {
        sum = 0;

        // video solution
        for (int i = 1; i <= num_of_terms; i++) {
            sum += 2*i;
            printf("[+] Current i = %d and sum = %d...\n", 2*i, sum);
        }

        // my original solution
        /* for (int i = 2; i <= (2 * num_of_terms); i += 2) { */
        /*     sum += i; */
        /*     printf("[+] Current i = %d and sum = %d...\n", i, sum); */
        /* } */

        printf("[+] Final sum is %d\n", sum);
    }

    // exception
    else {
        printf("[!] ERROR: Number not found\n");
    }

    return EXIT_SUCCESS;
}
