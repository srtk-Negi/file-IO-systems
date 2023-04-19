#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char itemName[64];
    char simpleName[16];
    int currentQuantity;
    int maxQuantity;
    char body[128];
} Item;

int main()
{
    int itemNum;
    Item newItem;

    printf("Enter item number: ");
    scanf("%d", &itemNum);

    FILE *fp = fopen("inventory.dat", "rb+");
    if (fp == NULL)
    {
        printf("Null");
        fp = fopen("inventory.dat", "wb+");
    }
    fseek(fp, itemNum * sizeof(Item), SEEK_SET);

    fread(&newItem, sizeof(Item), 1L, fp);
    if (newItem.itemName[0] != '\0')
    {
        printf("ERROR: item already exists\n");
        fclose(fp);
        exit(1);
    }

    printf("Enter simple name: ");
    scanf("%s", newItem.simpleName);

    printf("Enter item name: ");
    scanf(" %[^\n]s", newItem.itemName);

    printf("Enter current quantity: ");
    scanf("%d", &newItem.currentQuantity);

    printf("Enter maximum quantity: ");
    scanf("%d", &newItem.maxQuantity);

    printf("Enter description: ");
    scanf(" %[^\n]s", newItem.body);

    fseek(fp, itemNum * sizeof(Item), SEEK_SET);
    fwrite(&newItem, sizeof(Item), 1, fp);

    fclose(fp);
    exit(0);
}
