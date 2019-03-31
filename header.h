
/*
Debrecen 33. sz. fout 104+545 kilometerszelveny
70
2019-03-05;16:29;gyorshajtas 88;FHP487
2019-03-11;07:11;piros_lampa;NRE054
2019-03-14;12:44;kotelezo_haladas;KDD687
2019-03-18;11:21;gyorshajtas 119;PSN548
2019-03-26;13:08;gyorshajtas 97;NDL547
*/


typedef struct{
    char datum[11];
    char ido[6];
    char tipus[15];
    int sebesseg;
    char rendszam[7];
}REKORD;

typedef struct {
    char nev[100];
    int megengedett;
    REKORD **rekordok;
    //maybe NULLable
    int rekordszam;
}ELLENORZO_PONT;
