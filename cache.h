#ifndef CACHE_H
#define CACHE_H

typedef struct
{
    char code[10];
    char name[50];
    char state[50];
    char owner[50];
    float latitude;
    float longitude;
    char kind[50];
    char size[50];
    float difficulty;
    float terrain;
    char status[50];
    char hidden_date[50];
    int founds;
    int not_founds;
    int favourites;
    int altitude;
} Cache;

Cache* readCSV(int* size);
void displayCaches(Cache caches[], int size);

#endif