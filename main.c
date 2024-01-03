#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

int main()
{
    Cache *caches = NULL;
    int size = 0;
    char code[10];

    int option = 0;
    do
    {
        printf("menu \n");
        printf("1. Load \n");
        printf("2. List \n");
        printf("3. foundDP \n");
        printf("4. Search \n");
        printf("5. Edit cache\n");
        printf("6. Clear caches\n");
        printf("7. Caches Stats\n");
        printf("8. Exit\n");

        scanf("%d", &option);

        switch (option)
        {
        case 1:
            if (caches == NULL)
            {
                caches = loadCaches("caches_all.csv", &size);
            }
            else
            {
                printf("Caches already loaded. Select option 6 to clear caches.\n");
            }
            break;
        case 2:
            if (caches != NULL)
            {
                listCaches(caches, size);
            }
            else
            {
                printf("No caches loaded. Select option 1 to load caches.\n");
            }
            break;
        case 3:
            if (caches != NULL)
            {
                displayFoundPercentage(caches, size);
            }
            else
            {
                printf("No caches loaded. Select option 1 to load caches.\n");
            }
            break;
        case 4:
            printf("Enter cache code: ");
            scanf("%s", code);
            searchCache(caches, size, code);
            break;
        case 5:
            printf("Enter cache code: ");
            scanf("%s", code);
            editCache(caches, size, code);
            break;
        case 6:
            clearCaches(caches, &size);
            break;
        case 7:
            if (caches != NULL)
            {
                centerStats(caches, size);
            }
            else
            {
                printf("No caches loaded. Select option 1 to load caches.\n");
            }
            break;
        case 8:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option\n");
            break;
        }
    } while (option != 8);

    printf("Press any key to continue...\n");
    return 0;
}