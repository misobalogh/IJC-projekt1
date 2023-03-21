/***************************************************************
* File Name: error.h
* Description: riesnie IJC-DU1, priklad b)
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 21.3.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/
#ifndef PPM_H
#define PPM_H

#define BYTES_PER_PIXEL 3

struct ppm
{
        unsigned xsize;
        unsigned ysize;
        char data[]; // RGB bajty, celkem 3*xsize*ysize
};

// načte obsah PPM souboru do touto funkcí dynamicky alokované struktury
struct ppm *ppm_read(const char *filename);

// uvolní paměť dynamicky alokovanou v ppm_read
void ppm_free(struct ppm *p);

#endif // PPM_H