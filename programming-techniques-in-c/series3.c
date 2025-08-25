// series 3
// created by : bluecosmo

// NOTE:
// sum = 1 + 3 + 5 + 7 + ... + n terms
// idx = 1   2   3   4   ...   n places

// imports
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main() {

    int num_of_terms, sum;
    char terms_buffer[MAX];

    printf("[~] Enter number of terms : ");
    fgets(terms_buffer, MAX, stdin);

    if (sscanf(terms_buffer, "%d", &num_of_terms)) {
        sum = 0;

        // video solution
        for (int i = 1; i <= num_of_terms; i++) {
            sum += 2*i - 1;
            printf("[+] Current i = %d and sum = %d\n", 2*i - 1, sum);
        }

        // my solution
        /* for (int i = 1; i <= num_of_terms; i++)  { */
        /*     sum += i + i - 1; */
        /*     printf("[+] Current i = %d and sum = %d\n", i + i - 1, sum); */
        /* } */
    }

    else {
        printf("[!] ERROR\n");
    }
    
    return EXIT_SUCCESS;
}
