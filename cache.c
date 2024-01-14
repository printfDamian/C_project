#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "cache.h"

// converter para lowercase
void toLower(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}
// carregar a cache do ficheiro
Cache *load(char *filename, int *size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }

    Cache *caches = malloc(sizeof(Cache) * 1600); // tamanho predefinido
    *size = 0; // variavel para contar o numero de estruturas vindas da cache

    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%[^;];%[^;];%[^;];%[^;];%f;%f;%[^;];%[^;];%f;%f;%[^;];%[^;];%d;%d;%d;%d",
                   caches[*size].code, caches[*size].name, caches[*size].state, caches[*size].owner, &caches[*size].latitude, &caches[*size].longitude,
                   caches[*size].kind, caches[*size].size, &caches[*size].difficulty, &caches[*size].terrain, caches[*size].status, caches[*size].hidden_date,
                   &caches[*size].founds, &caches[*size].not_founds, &caches[*size].favourites, &caches[*size].altitude) == 16)
        {
            (*size)++;
        }
    }

    fclose(file);
    return caches;
}

bool isUnique(Cache cache, Cache *uniqueCaches, int uniqueSize) {
    for (int i = 0; i < uniqueSize; i++) {
        if (strcmp(uniqueCaches[i].code, cache.code) == 0) {
            return false;
        }
    }
    return true;
}
// retornar as caches Unicas
Cache *getUniqueCaches(Cache *caches, int size, int *uniqueSize) {
    Cache *uniqueCaches = malloc(size * sizeof(Cache));
    *uniqueSize = 0;

    for (int i = 1; i < size; i++) {
        if (isUnique(caches[i], uniqueCaches, *uniqueSize)) {
            uniqueCaches[*uniqueSize] = caches[i];
            (*uniqueSize)++;
        }
    }

    return uniqueCaches;
}

// limpar cache
void clear(Cache **caches, int *size) /* **caches em vez de *caches porque é um ponteiro para um ponteiro de caches*/   
{
    free(*caches);
    *caches = NULL;
    *size = 0;
}



void displayFoundPercentage(Cache *caches, int size)
{
    for (int i = 0; i < size; i++)
    {
        int isDuplicate = 0;
        for (int j = 0; j < i; j++)
        {
            if (strcmp(caches[i].code, caches[j].code) == 0)
            {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate)
        {
            float percentage = (float)caches[i].founds / (caches[i].founds + caches[i].not_founds) * 100;
            displayP(caches[i], percentage);
        }
    }
}


void search(Cache *caches, int size, char *code)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(caches[i].code, code) == 0)
        {
            display(caches[i]);
            return;
        }
    }
    printf("Cache not found\n");
}

void edit(Cache *caches, int size, char *code)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(caches[i].code, code) == 0)
        {
            printf("Enter new owner: ");
            scanf("%s", caches[i].owner);
            printf("Enter new status: ");
            scanf("%s", caches[i].status);
            printf("Enter new hidden_date: ");
            scanf("%s", caches[i].hidden_date);
            printf("Enter new altitude: ");
            scanf("%d", &caches[i].altitude);
            return;
        }
    }
    printf("Cache not found\n");
}
void list(Cache *caches, int size) {
    for (int i = 0; i < size; i++) {
        display(caches[i]);
    }
}
void display(Cache cache)
{
    printf("| %s | %s | %s | %s | %.2f | %.2f | %s | %s | %.2f | %.2f | %s | %s | %d | %d | %d | %d |\n",
           cache.code, cache.name, cache.state, cache.owner, cache.latitude, cache.longitude,
           cache.kind, cache.size, cache.difficulty, cache.terrain, cache.status,
           cache.hidden_date, cache.founds, cache.not_founds, cache.favourites, cache.altitude);
}
void displayP(Cache cache, float percentage)
{
    // foundP no inicio do print
    printf("found percentage: %.2f%% | %s | %s | %s | %s | %.2f | %.2f | %s | %s | %.2f | %.2f | %s | %s | %d | %d | %d | %d\n",
           percentage,cache.code, cache.name, cache.state, cache.owner, cache.latitude, cache.longitude,
           cache.kind, cache.size, cache.difficulty, cache.terrain, cache.status,
           cache.hidden_date, cache.founds, cache.not_founds, cache.favourites, cache.altitude);
}

void centerStats(Cache *caches, int size)
{
    double sumLat = 0, sumLong = 0, sumLatSq = 0, sumLongSq = 0;
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (caches[i].altitude < -90 || caches[i].latitude > 90)
        { // checar se a latitude é válida
            sumLat += caches[i].latitude;
            sumLong += caches[i].longitude;
            sumLatSq += caches[i].latitude * caches[i].latitude;
            sumLongSq += caches[i].longitude * caches[i].longitude;
            count++;
        }
    }
    double avgLat = sumLat / count;
    double avgLong = sumLong / count;
    double stdDevLat = sqrt(sumLatSq / count - avgLat * avgLat);
    double stdDevLong = sqrt(sumLongSq / count - avgLong * avgLong);
    printf("Average Latitude: %.2f, Standard Deviation: %.2f\n", avgLat, stdDevLat);
    printf("Average Longitude: %.2f, Standard Deviation: %.2f\n", avgLong, stdDevLong);
}

/* para de pois fazer */
// diferença entre a data de hoje e a data de criação da cache

void ageStats(Cache *caches, int size)
{
    int oldestIndex = 0;
    int newestIndex = 0;
    char *oldestDate = caches[0].hidden_date;
    char *newestDate = caches[0].hidden_date;

    for (int i = 1; i < size; i++)
    {
        if (strcmp(caches[i].hidden_date, oldestDate) < 0)
        {
            oldestIndex = i;
            oldestDate = caches[i].hidden_date;
        }
        if (strcmp(caches[i].hidden_date, newestDate) > 0)
        {
            newestIndex = i;
            newestDate = caches[i].hidden_date;
        }
    }

    int monthDifference = month_difference(oldestDate, newestDate);

    printf("Oldest Cache: %s | Newest Cache: %s | Month Difference: %d\n",
           caches[oldestIndex].code, caches[newestIndex].code, monthDifference);
}

int month_difference(char *date1, char *date2) {
    struct tm tm1 = {0}, tm2 = {0};
    sscanf(date1, "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    sscanf(date2, "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);

    // Ajustar o ano e o mês para o formato do struct tm (ano começa em 1900 e mês começa em 0)
    tm1.tm_year -= 1900;
    tm1.tm_mon--;
    tm2.tm_year -= 1900;
    tm2.tm_mon--;

    int years = tm2.tm_year - tm1.tm_year;
    int months = tm2.tm_mon - tm1.tm_mon;

    return years * 12 + months;
}


int compare_by_altitude(const void *a, const void *b) {
    Cache *cacheA = (Cache *)a;
    Cache *cacheB = (Cache *)b;
    return cacheB->altitude - cacheA->altitude;
}

int compare_by_state(const void *a, const void *b) {
    Cache *cacheA = (Cache *)a;
    Cache *cacheB = (Cache *)b;
    int stateComparison = strcmp(cacheA->state, cacheB->state);
    if (stateComparison == 0) {
        return cacheB->founds - cacheA->founds;
    } else {
        return stateComparison;
    }
}

int compare_by_date(const void *a, const void *b) {
    Cache *cacheA = (Cache *)a;
    Cache *cacheB = (Cache *)b;
    return strcmp(cacheB->hidden_date, cacheA->hidden_date);
}

void sort(Cache *caches, int size) {
    char choice[20];
    printf("Choose the sorting method:\nAltitude - By altitude (descending order)\nState - By state (A-Z, tiebreaker by founds in descending order)\nDate - By hidden_date (most recent to oldest)\n");
    scanf("%s", choice);
    toLower(choice);

    if (strcasecmp(choice, "altitude") == 0) {
        qsort(caches, size, sizeof(Cache), compare_by_altitude);
    } else if (strcasecmp(choice, "state") == 0) {
        qsort(caches, size, sizeof(Cache), compare_by_state);
    } else if (strcasecmp(choice, "date") == 0) {
        qsort(caches, size, sizeof(Cache), compare_by_date);
    } else {
        printf("Invalid choice\n");
    }
}
// contar e mostrar o numero de caches por estado
void stateCount(Cache *caches, int size)
{
}
