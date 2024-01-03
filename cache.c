#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h" // Include the header file

// Function to load caches from a file
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

// Function to clear loaded caches
void clearCaches(Cache *caches, int *size) {
    free(caches);
    *size = 0;
}

// Function to display all caches
void listCaches(Cache *caches, int size) {
    for (int i = 0; i < size; i++) {
        displayCache(caches[i]);
    }
}

// Function to display the percentage of times each cache was found
void displayFoundPercentage(Cache *caches, int size) {
    for (int i = 0; i < size; i++) {
        float percentage = (float)caches[i].founds / (caches[i].founds + caches[i].not_founds) * 100;
        printf("Cache code: %s, Found percentage: %.2f%%\n", caches[i].code, percentage);
    }
}

// Function to search for a cache by code
void searchCache(Cache *caches, int size, char *code) {
    for (int i = 0; i < size; i++) {
        if (strcmp(caches[i].code, code) == 0) {
            displayCache(caches[i]);
            return;
        }
    }
    printf("Cache not found\n");
}

// Function to edit a cache
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
    printf("Code: %s\n", cache.code);
    printf("Name: %s\n", cache.name);
    printf("State: %s\n", cache.state);
    printf("Owner: %s\n", cache.owner);
    printf("Latitude: %.2f\n", cache.latitude);
    printf("Longitude: %.2f\n", cache.longitude);
    printf("Kind: %s\n", cache.kind);
    printf("Size: %s\n", cache.size);
    printf("Difficulty: %.2f\n", cache.difficulty);
    printf("Terrain: %.2f\n", cache.terrain);
    printf("Status: %s\n", cache.status);
    printf("Hidden Date: %s\n", cache.hidden_date);
    printf("Founds: %d\n", cache.founds);
    printf("Not Founds: %d\n", cache.not_founds);
    printf("Favourites: %d\n", cache.favourites);
    printf("Altitude: %d\n", cache.altitude);
}