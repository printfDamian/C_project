
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cache.h"

int main()
{
    Cache *caches = NULL;
    int size = 0;
    char code[10];
    char option[256];

    int uniqueSize;
    Cache *uniqueCaches = getUniqueCaches(caches, size, &uniqueSize);
    do
    {
        printf(
            "Menu:\n"
            "Load\n"
            "List\n"
            "foundDP\n"
            "Search\n"
            "Edit cache\n"
            "Clear caches\n"
            "Caches Stats\n"
            "Age Stats\n"
            "Sort\n"
            "state count\n"
            "Matrix 81\n"
            "save\n"
            "Exit\n");

        fgets(option, sizeof(option), stdin); // Ler opção do utilizador
        // remover enter do fim da string

        // passar a string para lowercase
        toLower(option);

        option[strlen(option) - 1] = '\0';
        if (strcmp(option, "load") == 0)
        {
            if (caches == NULL)
            {
                char filename[256];
                printf("Enter the name of the file to be read: ");
                fgets(filename, sizeof(filename), stdin); // Use fgets instead of scanf
                filename[strlen(filename) - 1] = '\0';    // Remove the newline at the end
                caches = load(filename, &size);
                if (caches != NULL && size > 0)
                {
                    printf("Successfully loaded %d caches.\n", size);
                }
                else
                {
                    printf("Failed to load caches.\n");
                }
            }
            else
            {
                printf("Caches already loaded. type clear to clear the caches\n");
            }
        }
        else if (strcmp(option, "list") == 0)
        {
            if (caches != NULL)
            {
                int uniqueSize;
                Cache *uniqueCaches = getUniqueCaches(caches, size, &uniqueSize);
                list(uniqueCaches, uniqueSize);
                printf("Listed %d unique caches.\n", uniqueSize);
                free(uniqueCaches);
            }
            else
            {
                printf("No caches loaded. type load to load the caches\n");
            }
        }
        else if (strcmp(option, "founddp") == 0)
        {
            if (caches != NULL)
            {
                int uniqueSize;
                Cache *uniqueCaches = getUniqueCaches(caches, size, &uniqueSize);
                displayFoundPercentage(uniqueCaches, uniqueSize);
                printf("Listed %d unique caches.\n", uniqueSize);
                free(uniqueCaches);
            }
            else
            {
                printf("No caches loaded. type load to load the caches\n");
            }
        }
        else if (strcmp(option, "search") == 0)
        {
            if (caches != NULL)
            {
                printf("Code: ");
                fgets(code, sizeof(code), stdin);
                code[strlen(code) - 1] = '\0';
                search(caches, size, code);
            }
            else
            {
                printf("No caches loaded. type load to load the caches\n");
            }
        }
        else if (strcmp(option, "edit") == 0)
        {
            if (caches != NULL)
            {
                printf("Code: ");
                fgets(code, sizeof(code), stdin);
                code[strlen(code) - 1] = '\0';
                edit(caches, size, code);
            }
            else
            {
                printf("No caches loaded. type load to load the caches\n");
            }
        }
        else if (strcmp(option, "clear") == 0)
        {
            clear(&caches, &size);
        }
        else if (strcmp(option, "caches stats") == 0)
        {
            if (caches != NULL)
            {
                int uniqueSize;
                Cache *uniqueCaches = getUniqueCaches(caches, size, &uniqueSize);
                printf("Caches stats\n");
                centerStats(uniqueCaches, uniqueSize);
            }
            else
            {
                printf("No caches loaded. type load to load the caches\n");
            }
        }
        else if (strcmp(option, "age stats") == 0)
        {
            if (caches != NULL)
            {
                int uniqueSize;
                Cache *uniqueCaches = getUniqueCaches(caches, size, &uniqueSize);
                ageStats(uniqueCaches, uniqueSize);
            }
            else
            {
                printf("No caches loaded. type load to load the caches\n");
            }
        }
        else if (strcmp(option, "sort") == 0)
        {
            if (caches != NULL)
            {
                int uniqueSize;
                Cache *uniqueCaches = getUniqueCaches(caches, size, &uniqueSize);
                sort(uniqueCaches, uniqueSize);
                list(uniqueCaches, uniqueSize);
            }
            else
            {
                printf("No caches loaded. type load to load the caches\n");
            }
        }
        else if (strcmp(option, "state count") == 0)
        {
            if (caches != NULL)
            {
                int uniqueSize;
                Cache *uniqueCaches = getUniqueCaches(caches, size, &uniqueSize);
                stateCount(uniqueCaches, uniqueSize);
                free(uniqueCaches);
            }
            else
            {
                printf("No caches loaded. type load to load the caches\n");
            }
        }
        else if (strcmp(option, "matrix81") == 0)
        {
            if (caches != NULL)
            {
                int uniqueSize;
                Cache *uniqueCaches = getUniqueCaches(caches, size, &uniqueSize);
                calculateMatrix81(uniqueCaches, uniqueSize);
                free(uniqueCaches);
            }
            else
            {
                printf("No caches loaded. type load to load the caches\n");
            }
        }
        else if (strcmp(option, "save") == 0)
        {
            if (caches != NULL)
            {   
                int uniqueSize;
                Cache *uniqueCaches = getUniqueCaches(caches, size, &uniqueSize);
                save(uniqueCaches, uniqueSize);
                free(uniqueCaches);
            }
            else
            {
                printf("No caches loaded. type load to load the caches\n");
            }
        }
        else if (strcmp(option, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("Invalid option\n");
        }
    } while (1);
}