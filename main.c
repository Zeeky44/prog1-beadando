#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"




REKORD *parser(char *s){
    REKORD *rekord = malloc(sizeof(REKORD));
    char *tp;
    strcpy(rekord->datum, strtok(s, ";"));
    strcpy(rekord->ido, strtok(NULL, ";"));
    tp = strtok(NULL, ";");
    if(strstr(tp, "gyorshajtas")) {
        rekord->sebesseg = atoi(tp + 12);
        tp[11] = '\0';
    }
    strcpy(rekord->tipus, tp);

    strcpy(rekord->rendszam, strtok(NULL, ";"));
    //printf("\n||%s %s %d %s %s||\n", rekord->datum, rekord->ido, rekord->sebesseg, rekord->tipus, rekord->rendszam);
    return rekord;
}

REKORD **getRecords(int i, FILE *fp){
    REKORD **tomb = NULL;
    char sor[100];

    if(fgets(sor, 99, fp) != NULL){
        if(sor[strlen(sor)-1] == '\n')
            sor[strlen(sor)-1] = 0;
        tomb = getRecords(i+1, fp);
        tomb[i] = parser(sor);
    }
    else{
        tomb = malloc(sizeof(REKORD *) * (i+1));
        tomb[i] = NULL;
    }
    return tomb;
}

ELLENORZO_PONT *readFile(char *fileName){
    ELLENORZO_PONT *EP = malloc(sizeof(ELLENORZO_PONT));
    FILE *fp = fopen(fileName, "r");
    char elso[100];
    fgets(elso, 100, fp);
    if(elso[strlen(elso)] == '\n')
        elso[strlen(elso)] = 0;
    strcpy(EP->nev, elso);
    fscanf(fp, "%d\n", &EP->megengedett);
    EP->rekordok = getRecords(0, fp);
    fclose(fp);
    //printf("||%s %s %s %d %s||\n", EP->rekordok[0]->datum, EP->rekordok[0]->ido, EP->rekordok[0]->rendszam, EP->rekordok[0]->sebesseg, EP->rekordok[0]->tipus);
    return EP;
}

int _getBirsag(int megengedett, int ment, int kat){
    int i;
    int seb =  ment - megengedett;
    if(seb < 0) return 0;
    for(i = 0; tullepes[kat][i] < seb; i++);
    return tullepesbirsag[i-1];
}

int getSebBirsag(int megengedett, int ment){
    if(megengedett <= 50) _getBirsag(megengedett, ment, 0);
    else if( megengedett <= 100) _getBirsag(megengedett, ment, 1);
    else return  _getBirsag(megengedett, ment, 2);
}

int getBirsag(REKORD *r, int megengedett){
    if(strcmp(r->tipus, sertesek[0]) == 0)
        return getSebBirsag(megengedett, r->sebesseg);

    int i;
    for(i = 1; i < 7; i++)
        if(strcmp(r->tipus, sertesek[i]) == 0)
            return birsagok[i];

    return 0;
}


void stat(ELLENORZO_PONT **data){
    int darab = 0, osszeg = 0, i,j,k;
    for(i = 0; data[i]; i++){
        for(j = 0; data[i]->rekordok[j]; j++){
            darab++;
            osszeg += getBirsag(data[i]->rekordok[j], data[i]->megengedett);
        }
    }
    printf("A honap soran %d birsag kerult kiszabasra, osszesen %d forint ertekben.\n", darab, osszeg);
}


int main(int argc, char **argv)
{

    //printf("|%d|", tullepes[0][0] );


    ELLENORZO_PONT *pontok[argc];
    int i,j,k;
    for(i = 0; i < argc-1; i++){
        pontok[i] = readFile(argv[i+1]);
    }
    pontok[i] = NULL;
    /*
    //printf("%s", pontok[0]->rekordok[0]->datum);

    for(i = 0; i < argc-1; i++){
        for(j = 0;pontok[i]->rekordok[j] != NULL; j++){
            printf("%s;%s;%s;%d;%s\n", pontok[i]->rekordok[j]->datum, pontok[i]->rekordok[j]->ido, pontok[i]->rekordok[j]->tipus, pontok[i]->rekordok[j]->sebesseg , pontok[i]->rekordok[j]->rendszam);
        }
    }*/
    stat(pontok);


    return 0;
}
