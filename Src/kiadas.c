#include "kiadas.h"

autok* szervizkezelo(int index,int autokszama,autok* autoadatok, int* again){

    printf("%s %d km %d ft\n",autoadatok[index].nev,autoadatok[index].maxkm,autoadatok[index].osszkiadas);
    printf("Kiadas\tOsszeg\tKmallas\tMegjegyzes\n");
    for (int i = 0; i < autoadatok[index].adatszam; ++i) {
        printf("%s\t%d\t%d\t%s\n",autoadatok[index].adatok[i].kiadas,autoadatok[index].adatok[i].osszeg,autoadatok[index].adatok[i].kmallas,autoadatok[index].adatok[i].megjegyzes);
    }
    printf("(h) Kiadas hozzadasa\n");
    printf("(t) Kiadas torlese\n");
    printf("(v) Vissza\n");

    char bekertbetu[4];
    scanf("%s",bekertbetu);
    getchar();
    if(bekertbetu[0]=='h'){
        autoadatok = tenylegeshozzadas(index,autokszama,autoadatok);
    }
    if(bekertbetu[0]=='t'){
        int torlendo;
        printf("Melyik elemet szeretned torolni?\n");
        scanf("%d",&torlendo);
        autoadatok = tenylegestorles(index,torlendo-1,autokszama,autoadatok);
    }
    if(bekertbetu[0]=='v')
        *again = 1;
    else
        *again = 0;
    return autoadatok;
}

autok* tenylegeshozzadas(int index,int autokszama,autok* autoadatok){
    autoadatok[index].adatszam++;
    int i=0;
    if(!autoadatok[index].adatok)
        autoadatok[index].adatok=(adat*) malloc(sizeof(adat));
    else{
        adat* seged=autoadatok[index].adatok;
        autoadatok[index].adatok=(adat*) realloc(seged,autoadatok[index].adatszam*sizeof(adat));
        if(!autoadatok[index].adatok){
            printf("Hiba"); exit(1);
        }
        i=autoadatok[index].adatszam-1;
    }

    char kiadasok[100]; int kiadasokint;
    //kiadastipusa
printf("Add meg a kiadas tipusat:\n");
    scanf("%s",kiadasok);getchar();
    masolo(kiadasok,autoadatok[index].adatok[i].kiadas);
    //osszege
    printf("Add meg a kiadas osszeget:\n");
    scanf("%d",&kiadasokint);
    autoadatok[index].adatok[i].osszeg=kiadasokint;
    //km allas
    printf("Add meg az aktualis km allast:\n");
    scanf("%d",&kiadasokint);
    autoadatok[index].adatok[i].kmallas=kiadasokint;
    //megjegyzes
    printf("Adj meg tetszoleges megjegyzest:\n");
    scanf("%s",kiadasok);getchar();
    masolo(kiadasok,autoadatok[index].adatok[i].megjegyzes);
    autoadatok = adatkiszamitas(index,autoadatok);
    fajlkiiras(autokszama,autoadatok);
    return autoadatok;
}

autok* tenylegestorles(int index,int torlendoindex,int autokszama,autok* autoadatok){
    adat* seged=(adat*) malloc(sizeof(adat*)*(autoadatok[index].adatszam-1));
    int j=0;
    for (int i = 0; i < autoadatok[index].adatszam; ++i) {
        if(torlendoindex==i){continue;}
        masolo(autoadatok[index].adatok[i].kiadas,seged[j].kiadas);
        seged[j].osszeg=autoadatok[index].adatok[i].osszeg;
        seged[j].kmallas=autoadatok[index].adatok[i].kmallas;
        masolo(autoadatok[index].adatok[i].megjegyzes,seged[j].megjegyzes);
        j++;
    }
    free(autoadatok[index].adatok);
    autoadatok[index].adatszam--;
    autoadatok[index].adatok=seged;
    seged=NULL;
    autoadatok = adatkiszamitas(index,autoadatok);
    fajlkiiras(autokszama,autoadatok);
    return autoadatok;
}

autok* adatkiszamitas(int index,autok* autoadatok){
    int maxkmallas=0; int osszkiadas=0;
    for (int i = 0; i < autoadatok[index].adatszam; ++i) {
        osszkiadas+=autoadatok[index].adatok[i].osszeg;
        if (maxkmallas<autoadatok[index].adatok[i].kmallas){maxkmallas=autoadatok[index].adatok[i].kmallas;}
    }
    autoadatok[index].osszkiadas=osszkiadas;
    autoadatok[index].maxkm=maxkmallas;
    return autoadatok;
}