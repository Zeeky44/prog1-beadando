
char *sertesek[] = { "gyorshajtas",
                    "vasuti_atjaro",
                    "piros_lampa",
                    "leallosav",
                    "behajtasi_tilalom",
                    "kotelezo_haladas",
                    "korlatozott_zona"
                };

int birsagok[] = { 0, 60000, 50000, 100000, 30000, 50000, 30000 };

int tullepes[3][8] = {
                { 15, 25, 35, 45, 55, 65, 75, 1000},
                { 15, 30, 45, 60, 75, 90, 105, 1000},
                { 20, 35,50, 65, 80, 95, 110, 1000},
            };

int  tullepesbirsag[] = { 30000, 45000, 60000, 90000, 130000, 200000, 300000 };

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


