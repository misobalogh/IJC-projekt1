/***************************************************************
* File Name: error.h
* Description: riesnie IJC-DU1, priklad b)
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 21.3.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "ppm.h"
#include "eratosthenes.h"
#include "bitset.h"

#define START_PRIME 101
#define LSB(_byte) (_byte & 1)
#define MAX_MESSAGE_SIZE 1000

// funckia pouzita zo stranky: https://www.cl.cam.ac.uk/~mgk25/ucs/utf8_check.c
unsigned char *utf8_check(unsigned char *s)
{
    while (*s)
    {
        if (*s < 0x80)
            s++;
        else if ((s[0] & 0xe0) == 0xc0)
        {
            if ((s[1] & 0xc0) != 0x80 ||
                (s[0] & 0xfe) == 0xc0)
                return s;
            else
                s += 2;
        }
        else if ((s[0] & 0xf0) == 0xe0)
        {
            if ((s[1] & 0xc0) != 0x80 ||
                (s[2] & 0xc0) != 0x80 ||
                (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) ||
                (s[0] == 0xed && (s[1] & 0xe0) == 0xa0) ||
                (s[0] == 0xef && s[1] == 0xbf &&
                 (s[2] & 0xfe) == 0xbe))
                return s;
            else
                s += 3;
        }
        else if ((s[0] & 0xf8) == 0xf0)
        {
            if ((s[1] & 0xc0) != 0x80 ||
                (s[2] & 0xc0) != 0x80 ||
                (s[3] & 0xc0) != 0x80 ||
                (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) ||
                (s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4)
                return s;
            else
                s += 4;
        }
        else
            return s;
    }

    return NULL;
}
/***************************************************************/

void print_secret_message(bitset_t bitset, int start_index, struct ppm *image)
{

    int size = bitset_size(bitset);
    if (start_index >= size)
    {
        error_exit("print_secret_message: Počáteční index %d je mimo pole velikosti %u", start_index, size);
        return;
    }

    char byte = 0;
    unsigned int bit_index = 0;
    int num_of_chars = 0;
    unsigned char message[MAX_MESSAGE_SIZE];
    int proper_termination = 0;

    for (unsigned int i = start_index; i < bitset_size(bitset); i++)
    {
        // ak je cislo prvocislo, zapise jeho lsb do prislusneho bitu charu
        if (bitset_getbit(bitset, i) == 0)
        {
            byte |= LSB(image->data[i + 1]) << bit_index;
            bit_index++;
            continue;
        }

        // ak je nacitanych 8 bitov, prida znak do spravy
        if (bit_index == CHAR_BIT)
        {
            if (byte == '\0')
            {
                proper_termination = 1;
                break;
            }
            message[num_of_chars] = byte;
            num_of_chars++;
            byte = 0;
            bit_index = 0;
        }
    }

    if (!proper_termination)
    {
        error_exit("Správa není ukončená znakem \\0");
    }

    if (utf8_check(message) != NULL)
    {
        error_exit("Správa nie je vo formáte UTF-8");
        return;
    }
    printf("%s\n", message);
}

int main(int argc, char *argv[])
{
    // kontrola argumentov
    if (argc != 2)
    {
        error_exit("Nesprávný počet argumentů (%d)\nPočet požadovaných argumentů: 1", argc - 1);
        return 1;
    }

    // nacitanie obrazku
    char *filename = argv[1];
    struct ppm *image = ppm_read(filename);
    if (image == NULL)
    {
        error_exit("Chyba v načtení obrázku");
        return 1;
    }

    // velkost obrazovych dat
    unsigned long size = BYTES_PER_PIXEL * image->xsize * image->ysize;

    bitset_alloc(bitset, size);

    // najdenie pixelov, ktore su prvocisla
    Eratosthenes(bitset);

    print_secret_message(bitset, START_PRIME, image);

    // uvolnenie alokovanej pamate
    bitset_free(bitset);
    ppm_free(image);

    return 0;
}