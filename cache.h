#ifndef CACHE_H /*caso o cache.h já esteja a ser defenido por outros ficehiros não fará o define do mesmo novamente */
#define CACHE_H
// atributos da cache
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

// funções de manipulação da cache
Cache *load(char *filename, int *size);
void clear(Cache **caches, int *size);
void list(Cache *caches, int size);
void displayFoundPercentage(Cache *caches, int size);
void search(Cache *caches, int size, char *code);
void edit(Cache *caches, int size, char *code);
void display(Cache cache);
void displayP(Cache cache, float percentage);
void centerStats(Cache *caches, int size);


Cache *getUniqueCaches(Cache *caches, int size, int *uniqueSize);

#endif
