#include "menu.h"

autok* beolvasas(int* autokszama) {
    FILE *fp;
    char line[100];  //max 100 karakterenként olvasunk be sorokként

    fp = fopen("autok.txt", "r"); // megnyitás
    if (fp == NULL) {
        perror("Fajl megnyitasa sikertelen");
        return 0;    /* ha hiba nem folytathatjuk! */
    }
    fgets(line,100, fp);
    *autokszama= atoi(line);
    printf("%d\n",*autokszama);

    autok* autoadatok=(autok*) malloc(sizeof(autok)*(*autokszama));
    for (int i = 0; i < *autokszama; ++i) {
        fgets(line,100, fp);
        masolo(line,autoadatok[i].nev);
        printf("%s\n",autoadatok[i].nev);
        fgets(line,100, fp);
        autoadatok[i].osszkiadas=atoi(line);
        fgets(line,100, fp);
        autoadatok[i].maxkm=atoi(line);
        fgets(line,100, fp);
        autoadatok[i].adatszam=atoi(line);

        autoadatok[i].adatok=(adat*) malloc(sizeof(adat)*autoadatok[i].adatszam);

        for (int j = 0; j < autoadatok[i].adatszam; ++j) {
            fgets(line,100, fp);
            masolo(line,autoadatok[i].adatok[j].kiadas);
            fgets(line,100, fp);
            autoadatok[i].adatok[j].osszeg=atoi(line);
            fgets(line,100, fp);
            autoadatok[i].adatok[j].kmallas=atoi(line);
            fgets(line,100, fp);
            masolo(line,autoadatok[i].adatok[j].megjegyzes);
        }
    }
    fclose(fp);
    return autoadatok;
}

int kezdokepernyo(){
    int autokszama=0;

    printf("\nCarNote\n");
    printf("Fomenu\n");
    printf("Valaszd ki az autot!\n");
    autok* autoadatok = beolvasas(&autokszama);
    printf("\n(h) Auto hozzaadasa\n");
    printf("(t) Auto eltavolitasa\n");
    printf("(k) Kilepes\n");

    char bekertbetu[4];
    scanf("%s",bekertbetu);
    getchar();
    if(bekertbetu[0]=='h'){
        autoadatok = autohozzadas(&autokszama,autoadatok);
    }
    if(bekertbetu[0]=='k'){
        felszabadito(autokszama,autoadatok);
        return 1;
    }
    if(bekertbetu[0]=='t'){
        autoadatok = autotorles(&autokszama,autoadatok);
    }
    int melyikauto;
    if ((melyikauto=atoi(bekertbetu))>0 && melyikauto<=autokszama){
        int again = 0;
        for(;again == 0; autoadatok = szervizkezelo(melyikauto-1,autokszama,autoadatok, &again));
    }
    felszabadito(autokszama,autoadatok);
    return 0;
}

autok* autohozzadas(int* autokszama,autok* autoadatok){

    char bekertautoneve[30];
    printf("\nAdd meg az auto nevet:\n");
    fgets(bekertautoneve, 30, stdin);
    autoadatok = autotenylegeshozzaadas(bekertautoneve,autokszama,autoadatok);
    //clrscr();
    return autoadatok;
}
autok* autotenylegeshozzaadas(char* nev,int* autokszama,autok* autoadatok){
    (*autokszama)++;
    autok* seged=autoadatok;
    autoadatok=(autok*)realloc(seged,sizeof(autok)*(*autokszama));
    if(!autoadatok){printf("hiba"); exit(1);}
    masolo(nev,autoadatok[(*autokszama)-1].nev);
    autoadatok[(*autokszama)-1].maxkm=0;
    autoadatok[(*autokszama)-1].osszkiadas=0;
    autoadatok[(*autokszama)-1].adatszam=0;
    autoadatok[(*autokszama)-1].adatok=0;
    fajlkiiras(*autokszama,autoadatok);
    return autoadatok;
}

autok* autotorles(int* autokszama,autok* autoadatok){
    int sorszam;
    printf("\nAdd meg a torlendo sorszamot:\n");
    scanf("%d",&sorszam);
    autoadatok = autotenylegestorlese(sorszam-1,autokszama,autoadatok);
    fajlkiiras(*autokszama,autoadatok);
    return autoadatok;

}
autok* autotenylegestorlese(int index,int* autokszama,autok* autoadatok){

    autok* seged=(autok*) malloc(sizeof(autok)*((*autokszama)-1));
    int j=0;
    for (int i = 0; i < *autokszama; ++i) {
        if(index==i){continue;}
        masolo(autoadatok[i].nev,seged[j].nev);
        seged[j].maxkm=autoadatok[i].maxkm;
        seged[j].osszkiadas=autoadatok[i].osszkiadas;
        seged[j].adatszam=autoadatok[i].adatszam;
        seged[j].adatok=(adat*)malloc(sizeof(adat)*seged[j].adatszam ); //pointer
        for (int k = 0; k < seged[j].adatszam; ++k) {
            masolo(autoadatok[i].adatok[k].kiadas,seged[j].adatok[k].kiadas);
            seged[j].adatok[k].osszeg=autoadatok[i].adatok[k].osszeg;
            seged[j].adatok[k].kmallas=autoadatok[i].adatok[k].kmallas;
            masolo(autoadatok[i].adatok[k].megjegyzes,seged[j].adatok[k].megjegyzes);
        }
        j++;
    }
    felszabadito(*autokszama,autoadatok);
    (*autokszama)--;
    autoadatok=seged;
    seged=NULL;
    return autoadatok;
}