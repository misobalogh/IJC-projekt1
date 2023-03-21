/***************************************************************
* File Name: bitset.h
* Description: riesnie IJC-DU1, priklad a)
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 21.3.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include <limits.h> // CHAR_BIT
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include <assert.h>

#ifndef BITSET_H
#define BITSET_H

// Typ bitového pola pre predavanie parametru do funkcie odkazom
typedef unsigned long bitset_t[];

// Typ indexu do bitového pola
typedef unsigned long bitset_index_t;

// pocet bitov v jednom UL
#define UL_BITS (sizeof(unsigned long) * CHAR_BIT)

// minimalna velkost pola pre ulozenie "size" bitov do pola zvacsene o 1, na zapis velkosti pola na prvy index
#define bitset_min_size_of_bytes(size) ((size / UL_BITS) + (size % UL_BITS ? 1 : 0) + 1)


#define bitset_create(name, size)                                               \
    static_assert(size > 0, "bitset_create: Veilkost nesmi byt menší než 0\n"); \
    bitset_index_t name[bitset_min_size_of_bytes(size)] = {[0] = size}

#define bitset_alloc(name, size)                                                          \
    assert(size > 0);                                                                     \
    bitset_index_t *name = calloc(bitset_min_size_of_bytes(size), sizeof(unsigned long)); \
    if (name == NULL)                                                                     \
    {                                                                                     \
        error_exit("bitset_alloc: Chyba alokace paměti\n");                               \
    }                                                                                     \
    name[0] = size


#ifndef USE_INLINE

#define bitset_free(name) free(name)

// velkost pola v bitoch, ktora je ulozena na prvej pozici pola
#define bitset_size(name) name[0]

// nastavi bit v poli "name" na pozicii "index" na bit "expression" (0/1)
#define bitset_setbit(name, index, expression)                                  \
    do                                                                          \
    {                                                                           \
        unsigned long segment_of_array = index / UL_BITS + 1;                   \
        bitset_index_t bitset_index = (index + UL_BITS) % UL_BITS;              \
        if (segment_of_array > bitset_size(name) - 1)                           \
        {                                                                       \
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",           \
                       (unsigned long)index, (unsigned long)bitset_size(name)); \
        }                                                                       \
        if (expression == 1)                                                    \
        {                                                                       \
            name[segment_of_array] |= 1UL << bitset_index;                      \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            name[segment_of_array] &= ~(1UL << bitset_index);                   \
        }                                                                       \
    } while (0)


// hodnota bitu na pozicii "index" v poli "name"
#define bitset_getbit(name, index)                                                                                                       \
    ((index / UL_BITS > bitset_size(name) - 1) > bitset_size(name) ? error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",           \
                                                                            (unsigned long)index, (unsigned long)bitset_size(name)), 0   \
                                                                   : ((name[(index + UL_BITS) / UL_BITS] >> ((UL_BITS + index) % UL_BITS)) & 1))

#else  // USE_INLINE

inline void bitset_free(bitset_t name)
{
    free(name);
}

inline bitset_index_t bitset_size(bitset_t name)
{
    return name[0];
}

inline unsigned int bitset_getbit(bitset_t name,bitset_index_t index)
{
    if (index / UL_BITS > bitset_size(name) - 1)
        {
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(name));
            return 0;
        }
    return (name[(index + UL_BITS) / UL_BITS] >> ((UL_BITS + index) % UL_BITS)) & 1;
}

inline void bitset_setbit(bitset_t name,bitset_index_t index, unsigned int expression)
{
    unsigned long segment_of_array = index / UL_BITS + 1;
    bitset_index_t bitset_index = (index + UL_BITS) % UL_BITS;
    if (segment_of_array > bitset_size(name) - 1)
    {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",
                   (unsigned long)index, (unsigned long)bitset_size(name));
    }
    if (expression == 1)
    {
        name[segment_of_array] |= 1UL << bitset_index;
    }
    else
    {
        name[segment_of_array] &= ~(1UL << bitset_index);
    }
}

#endif // USE_INLINE

#endif // BITSET_H