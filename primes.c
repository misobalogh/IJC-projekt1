/***************************************************************
* File Name: primes.c
* Description: riesnie IJC-DU1, priklad a)
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 21.3.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include <stdio.h>
#include <time.h>
#include "eratosthenes.h"

#ifdef USE_INLINE

extern bitset_index_t bitset_size(bitset_t name);

extern unsigned int bitset_getbit(bitset_t name, bitset_index_t index);

#endif // USE_INLINE

#define N 230000000UL      // najvacsie cislo po ktore hladame prvocisla
#define LAST_N_PRIMES 10UL // poslednych n prvocisel

void print_last_n(bitset_t array)
{
    unsigned long printed = 0;
    unsigned long primes_to_print[LAST_N_PRIMES] = {0};

    for (unsigned long i = bitset_size(array) - 1; printed < LAST_N_PRIMES && i > 0; i--)
    {
        // ak je cislo prvocislo (bit nastaveny na 0), ulozi ich do listu primes_to_print
        if (bitset_getbit(array, i) == 0)
        {
            primes_to_print[printed] = i;
            printed++;
        }
    }

    // vypise poslednych 10 prvocisel v opacnom poradi
    for (unsigned long j = LAST_N_PRIMES; j > 0; j--)
    {
        // kontrola aby sa nevypisovali nuly, ak by bolo poslednych N ktore chceme vypisat viac ako najdenych prvocisel
        if (primes_to_print[j - 1] != 0)
        {
            printf("%ld\n", primes_to_print[j - 1]);
        }
    }
}

int main()
{
    clock_t start = clock();

    bitset_create(numbers, N);

    Eratosthenes(numbers);
    print_last_n(numbers);

    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}
