#include <stdio.h>
#include <stdlib.h>
#include "cache.h" // Include the header file


Cache* readCSV(int* size) {
    FILE *file = fopen("caches_all.csv", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir ficheiro\n");
        return NULL;
    }

    Cache* caches = malloc(sizeof(Cache) * 1000); // Allocate memory for 1000 caches
    *size = 0; // Initialize size to 0

    while (fscanf(file, "%[^;];%[^;];%[^;];%[^;];%f;%f;%[^;];%[^;];%f;%f;%[^;];%[^;];%d;%d;%d;%d\n",
                  caches[*size].code, caches[*size].name, caches[*size].state, caches[*size].owner, &caches[*size].latitude, &caches[*size].longitude,
                  caches[*size].kind, caches[*size].size, &caches[*size].difficulty, &caches[*size].terrain, caches[*size].status, caches[*size].hidden_date,
                  &caches[*size].founds, &caches[*size].not_founds, &caches[*size].favourites, &caches[*size].altitude) == 16)
    {
        (*size)++; // Increase size by 1
    }

    fclose(file);
    return caches; // Return the pointer to the array
}
void displayCaches(Cache caches[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Code: %s\n", caches[i].code);
        printf("Name: %s\n", caches[i].name);
        printf("State: %s\n", caches[i].state);
        printf("Owner: %s\n", caches[i].owner);
        printf("Latitude: %f\n", caches[i].latitude);
        printf("Longitude: %f\n", caches[i].longitude);
        printf("Kind: %s\n", caches[i].kind);
        printf("Size: %s\n", caches[i].size);
        printf("Difficulty: %f\n", caches[i].difficulty);
        printf("Terrain: %f\n", caches[i].terrain);
        printf("Status: %s\n", caches[i].status);
        printf("Hidden Date: %s\n", caches[i].hidden_date);
        printf("Founds: %d\n", caches[i].founds);
        printf("Not Founds: %d\n", caches[i].not_founds);
        printf("Favourites: %d\n", caches[i].favourites);
        printf("Altitude: %d\n", caches[i].altitude);
        printf("\n");
    }
}