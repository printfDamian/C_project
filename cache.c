#include <stdio.h>
#include <stdlib.h>
#include "cache.h" // Include the header file

Cache *readCSV(int *size)
{
    printf("About to open the file\n");

    FILE *file = fopen("caches_all.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }
    else
    {
        printf("File opened successfully\n");
    }

    Cache *caches = malloc(sizeof(Cache) * 1000); // Allocate memory for 1000 caches
    *size = 0;                                    // Initialize size to 0

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        printf("Current line: %s\n", line); // Print the current line

        if (sscanf(line, "%[^;];%[^;];%[^;];%[^;];%f;%f;%[^;];%[^;];%f;%f;%[^;];%[^;];%d;%d;%d;%d",
                   caches[*size].code, caches[*size].name, caches[*size].state, caches[*size].owner, &caches[*size].latitude, &caches[*size].longitude,
                   caches[*size].kind, caches[*size].size, &caches[*size].difficulty, &caches[*size].terrain, caches[*size].status, caches[*size].hidden_date,
                   &caches[*size].founds, &caches[*size].not_founds, &caches[*size].favourites, &caches[*size].altitude) == 16)
        {
            printf("Read cache: %s\n", caches[*size].code); // Print the code of the cache that was just read
            (*size)++;                                      // Increase size by 1
        }
    }

    fclose(file);
    return caches; // Return the pointer to the array
}
void displayCaches(Cache caches[], int size)
{   
    printf("Size of caches: %d\n", size);
    printf("About to iterate over caches\n");
    for (int i = 0; i < size; i++)
    {
        printf("About to display cache %d\n", i);
        printf("Cache code: %s\n", caches[i].code); // Print the code of the cache
        
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

        printf("Finished displaying cache %d\n", i);
    }
    printf("Finished iterating over caches\n");
}