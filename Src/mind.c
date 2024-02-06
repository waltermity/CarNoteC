#include "mind.h"


void fajlkiiras(int autokszama,autok* autoadatok){
    FILE *fp= fopen("autok.txt","w");
    fprintf(fp,"%d\n",autokszama);
    for (int i = 0; i < autokszama; ++i) {
        fprintf(fp,"%s\n",autoadatok[i].nev);
        fprintf(fp,"%d\n",autoadatok[i].maxkm);
        fprintf(fp,"%d\n",autoadatok[i].osszkiadas);
        fprintf(fp,"%d\n",autoadatok[i].adatszam);
        for (int j = 0; j < autoadatok[i].adatszam; ++j) {
            fprintf(fp,"%s\n",autoadatok[i].adatok[j].kiadas);
            fprintf(fp,"%d\n",autoadatok[i].adatok[j].osszeg);
            fprintf(fp,"%d\n",autoadatok[i].adatok[j].kmallas);
            fprintf(fp,"%s\n",autoadatok[i].adatok[j].megjegyzes);
        }

    }
    fclose(fp);
}

void masolo(char amibol[], char amibe[]){
    int i=0;
    while(amibol[i]!='\n' && amibol[i]!='\0'){
        amibe[i]=amibol[i];
        i++;
    }
    amibe[i]='\0';

}

void felszabadito(int autokszama,autok* autoadatok){
    for (int i = 0; i < autokszama; ++i) {
        free(autoadatok[i].adatok);
    }
    free(autoadatok);
}