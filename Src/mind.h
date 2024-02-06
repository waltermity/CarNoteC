#pragma once
#include <stdio.h>
#include <stdlib.h>
#define clrscr() printf("\e[1;1H\e[2J")
#include "debugmalloc.h"

typedef struct adat{
    char kiadas[100];
    int osszeg;
    int kmallas;
    char megjegyzes[100];
}adat;

typedef struct autok {
    char nev[100]; // max 100 karakter
    adat* adatok;
    int maxkm;
    int osszkiadas;
    int adatszam;
}autok;

void masolo(char amibol[], char amibe[]);
void felszabadito(int autokszama,autok* autoadatok);
void fajlkiiras(int autokszama,autok* autoadatok);