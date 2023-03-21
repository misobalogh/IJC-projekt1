/***************************************************************
* File Name: eratosthenes.c
* Description: riesnie IJC-DU1, priklad a), implementacia funkcie eratosthenes
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 21.3.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include <math.h>
#include "eratosthenes.h"
#include "error.h"

void Eratosthenes(bitset_t array)
{
    // cisla 0 a 1 nie su prvocisla
    bitset_setbit(array, 0, 1);
    bitset_setbit(array, 1, 1);

    unsigned long size = bitset_size(array);

    // index nastaveny na 2 -> 0 a 1 nie su prvocisla
    for (bitset_index_t i = 2; i <= sqrt(size); i++)
    {
        // ak bit na pozicii i == 0, je to prvocislo
        if (bitset_getbit(array, i) == 0)
        {
            // všechny nasobky i nie su prvocisla
            for (bitset_index_t j = i + i; j < size; j += i)
            {
                bitset_setbit(array, j, 1);
            }
        }
    }
}
