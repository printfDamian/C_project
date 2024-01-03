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

Cache* loadCaches(char *filename, int *size);
void clearCaches(Cache *caches, int *size);
void listCaches(Cache *caches, int size);
void displayFoundPercentage(Cache *caches, int size);
void searchCache(Cache *caches, int size, char *code);
void editCache(Cache *caches, int size, char *code);
void displayCache(Cache cache);
#endif