/***************************************************************
* File Name: error.c
* Description: riesnie IJC-DU1, priklad b), implementacia funkcii na vypisanie chybovych hlaseni
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 21.3.2023

* Comments: prekladane pomocou gcc 9.4.0, funkcie boli pouzite aj pre ulohu a)
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void warning(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Warning:");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}

void error_exit(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Error:");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(1);
}