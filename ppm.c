/***************************************************************
* File Name: error.h
* Description: riesnie IJC-DU1, priklad b), implementacia funkcii z ppm.h
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 21.3.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
#include "error.h"

#define MAGIC_NUMBER "P6"
#define MAX_DIMENSION 16000
#define MAX_COLOR_VALUE 255

struct ppm *ppm_read(const char *filename)
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        warning("ppm_read: Soubor %s se nepodařilo otevřít", filename);
        return NULL;
    }

    // kontrola varianty P6
    char variant[3];
    if (fscanf(fp, "%2s", variant) != 1 || strcmp(variant, MAGIC_NUMBER) != 0)
    {
        warning("ppm_read: Soubor %s není varianty P6", filename);
        fclose(fp);
        return NULL;
    }

    // kontrola formatu rozmerov suboru
    unsigned xsize, ysize, maxval;
    if (fscanf(fp, "%u%u%u", &xsize, &ysize, &maxval) != 3)
    {
        warning("ppm_read: Neplatné rozměry v souboru %s", filename);
        fclose(fp);
        return NULL;
    }

    // kontrola rozmerov suboru
    if (xsize > MAX_DIMENSION || ysize > MAX_DIMENSION || maxval > MAX_COLOR_VALUE)
    {
        warning("ppm_read: Rozměry souboru %s překračují maximální povolené rozměry", filename);
        fclose(fp);
        return NULL;
    }

    // alokacia miesta v pamati
    size_t size = BYTES_PER_PIXEL * xsize * ysize;
    struct ppm *image = malloc(sizeof(*image) + size);
    if (image == NULL)
    {
        warning("ppm_read: Chyba alokace paměti", filename);
        fclose(fp);
        return NULL;
    }

    image->xsize = xsize;
    image->ysize = ysize;

    // kontrola spravnosti citania suboru
    if (fread(image->data, sizeof(char), size, fp) != size)
    {
        warning("ppm_read: Neočekávaný konec souboru %s", filename);
        fclose(fp);
        free(image);
        return NULL;
    }

    fclose(fp);

    return image;
}

void ppm_free(struct ppm *p)
{
    free(p);
}

