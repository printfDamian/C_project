#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

int main()
{
    Cache* caches = NULL;
    int size = 0;

    int option = 0;
    do
    {
        printf("menu\n");
        printf("1. Ler ficheiro\n");
        printf("2. Mostrar informação\n");
        printf("3. sair\n");

        scanf("%d", &option);
        
        switch (option)
        {
        case 1:
            caches = readCSV(&size);
            break;
        case 2: 
            if (caches != NULL) {
                displayCaches(caches, size);
            } else {
                printf("No caches loaded. Please load the file first.\n");
            }
            break;
        case 3:
            free(caches); // Free the memory allocated for caches
            break;
        default: printf("Opção inválida\n");
            break;
        }
    } while (option != 3);
    return 0;
}