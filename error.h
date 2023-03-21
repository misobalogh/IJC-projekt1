/***************************************************************
* File Name: error.h
* Description: riesnie IJC-DU1, priklad b), hlavickovy subor pre error.c
* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
* Faculty: FIT VUT
* Date: 21.3.2023

* Comments: prekladane pomocou gcc 9.4.0
***************************************************************/

#ifndef ERROR_H
#define ERROR_H

#include <stdarg.h>

void warning(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif // ERROR_H