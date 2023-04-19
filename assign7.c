#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INVENTORY_FILE "inventory.dat"

typedef struct
{
    char itemName[64];
    char simpleName[16];
    int currentQuantity;
    int maxQuantity;
    char body[128];
} Item;

void create(FILE *invFile);
void read(FILE *invFile);
void update(FILE *invFile);
void delete(FILE *invFile);
void showMenu();

int main()
{
    while (true)
    {
        showMenu();
        FILE *invFile = fopen(INVENTORY_FILE, "rb+");
        if (invFile == NULL)
        {
            invFile = fopen(INVENTORY_FILE, "wb+");
        }

        char choice;
        if (scanf("%c", &choice) != 1)
            return 1;

        switch (choice)
        {
        case 'C':
        case 'c':
            create(invFile);
            break;

        case 'R':
        case 'r':
            read(invFile);
            break;

        case 'U':
        case 'u':
            update(invFile);
            break;

        case 'D':
        case 'd':
            delete (invFile);
            break;
        }
        fclose(invFile);
    }
    return 0;
}

void showMenu()
{
    printf("\nEnter one of the following actions or press CTRL-D to exit.\n");
    printf("C - create a new item\n");
    printf("R - read an existing item\n");
    printf("U - update an existing item\n");
    printf("D - delete an existing item\n");
}

void create(FILE *invFile)
{
    Item item;
    int seekPos;
    int itemNumber;
    int readCount;

    scanf("%d", &itemNumber);
    getchar();

    seekPos = itemNumber * sizeof(Item);
    fseek(invFile, seekPos, SEEK_SET);
    readCount = fread(&item, sizeof(Item), 1L, invFile);

    if (readCount == 1)
    {
        printf("ERROR: item already exists\n");
        return;
    }

    else
    {
        fgets(item.simpleName, 16, stdin);
        item.simpleName[strcspn(item.simpleName, "\n")] = '\0';

        fgets(item.itemName, 64, stdin);
        item.itemName[strcspn(item.itemName, "\n")] = '\0';

        scanf("%d", &item.currentQuantity);
        getchar();

        scanf("%d", &item.maxQuantity);
        getchar();

        fgets(item.body, 128, stdin);
        item.body[strcspn(item.body, "\n")] = '\0';

        seekPos = itemNumber * sizeof(Item);
        fseek(invFile, seekPos, SEEK_SET);
        fwrite(&item, sizeof(Item), 1L, invFile);
    }
}

void read(FILE *invFile)
{
    int itemNumber;
    Item item;
    int seekPos;
    int readCount;

    printf("Enter an item number: ");
    scanf("%d", &itemNumber);
    getchar();

    seekPos = itemNumber * sizeof(Item);
    fseek(invFile, seekPos, SEEK_SET);
    readCount = fread(&item, sizeof(Item), 1L, invFile);

    if (readCount == 1)
    {
        printf("Item Name: %s\nSimple Name: %s\nItem Number: %d\nQty: %d/%d\nDescription: %s\n\n", item.itemName, item.simpleName, itemNumber, item.currentQuantity, item.maxQuantity, item.body);
    }
    else
    {
        printf("ERROR: item not found\n");
    }
}

void update(FILE *invFile)
{
    printf("updated\n");
}

void delete(FILE *invFile)
{
    printf("deleted\n");
}