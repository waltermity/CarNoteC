#pragma once
#include "mind.h"
#include "kiadas.h"

autok* beolvasas(int* autokszama);
int kezdokepernyo();
autok* autohozzadas(int* autokszama,autok* autoadatok);
autok* autotenylegeshozzaadas(char*nev,int* autokszama,autok* autoadatok);
autok* autotorles(int* autokszama,autok* autoadatok);
autok* autotenylegestorlese(int index,int* autokszama,autok* autoadatok);