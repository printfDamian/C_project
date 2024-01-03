#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h" 

// carregar a cache do ficheiro
Cache *loadCaches(char *filename, int *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    Cache *caches = malloc(sizeof(Cache) * 1600);
    *size = 0;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
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

// limpar cache
void clearCaches(Cache *caches, int *size) {
    free(caches);
    *size = 0;
}

// mostrar todas as caches
void listCaches(Cache *caches, int size) {
    for (int i = 0; i < size; i++) {
        int isDuplicate = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(caches[i].code, caches[j].code) == 0) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            displayCache(caches[i]);
        }
    }
}

// Function to display the percentage of times each cache was found
void displayFoundPercentage(Cache *caches, int size) {
    for (int i = 0; i < size; i++) {
        int isDuplicate = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(caches[i].code, caches[j].code) == 0) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            float percentage = (float)caches[i].founds / (caches[i].founds + caches[i].not_founds) * 100;
            displayCacheP(caches[i],percentage);
        }
    }
}

// Pesquisar cache com o código
void searchCache(Cache *caches, int size, char *code) {
    for (int i = 0; i < size; i++) {
        if (strcmp(caches[i].code, code) == 0) {
            displayCache(caches[i]);
            return;
        }
    }
    printf("Cache not found\n");
}

// Editar a cache
void editCache(Cache *caches, int size, char *code) {
    for (int i = 0; i < size; i++) {
        if (strcmp(caches[i].code, code) == 0) {
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
void displayCache(Cache cache) {
    printf("| %s | %s | %s | %s | %.2f | %.2f | %s | %s | %.2f | %.2f | %s | %s | %d | %d | %d | %d |\n",
           cache.code, cache.name, cache.state, cache.owner, cache.latitude, cache.longitude,
           cache.kind, cache.size, cache.difficulty, cache.terrain, cache.status,
           cache.hidden_date, cache.founds, cache.not_founds, cache.favourites, cache.altitude);
}
void displayCacheP(Cache cache,float percentage) {
    printf("| %s | %s | %s | %s | %.2f | %.2f | %s | %s | %.2f | %.2f | %s | %s | %d | %d | %d | %d | found percentage: %.2f%%\n",
           cache.code, cache.name, cache.state, cache.owner, cache.latitude, cache.longitude,
           cache.kind, cache.size, cache.difficulty, cache.terrain, cache.status,
           cache.hidden_date, cache.founds, cache.not_founds, cache.favourites, cache.altitude,percentage);
}
