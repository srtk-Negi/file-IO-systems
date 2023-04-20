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

Item item;
Item newItem;
Item oldItem;

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
        FILE *invFile;

        char choice;
        if (scanf("%c", &choice) != 1)
            return 1;
        getchar();

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

        default:
            printf("ERROR: invalid option\n");
        }
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
    invFile = fopen(INVENTORY_FILE, "rb+");
    if (invFile == NULL)
    {
        invFile = fopen(INVENTORY_FILE, "wb+");
    }

    int seekPos = 0;
    int itemNumber = 0;

    scanf("%d", &itemNumber);
    getchar();

    seekPos = itemNumber * sizeof(Item);
    fseek(invFile, seekPos, SEEK_SET);
    fread(&item, sizeof(Item), 1L, invFile);

    if (item.simpleName[0] != '\0')
    {
        printf("\nERROR: item already exists\n");
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

        fseek(invFile, seekPos, SEEK_SET);
        fwrite(&item, sizeof(Item), 1L, invFile);

        item.simpleName[0] = '\0';
        item.itemName[0] = '\0';
        item.currentQuantity = 0;
        item.maxQuantity = 0;
        item.body[0] = '\0';
    }
    fclose(invFile);
}

void read(FILE *invFile)
{
    invFile = fopen(INVENTORY_FILE, "rb+");
    if (invFile == NULL)
    {
        invFile = fopen(INVENTORY_FILE, "wb+");
    }

    int itemNumber = 0;
    int seekPos = 0;

    printf("\nEnter an item number: ");
    scanf("%d", &itemNumber);
    getchar();

    seekPos = itemNumber * sizeof(Item);
    fseek(invFile, seekPos, SEEK_SET);
    fread(&item, sizeof(Item), 1L, invFile);

    if (item.simpleName[0] != '\0')
    {
        printf("\nItem Name: %s\nSimple Name: %s\nItem Number: %d\nQty: %d/%d\nDescription: %s\n\n", item.itemName, item.simpleName, itemNumber, item.currentQuantity, item.maxQuantity, item.body);

        item.simpleName[0] = '\0';
        item.itemName[0] = '\0';
        item.currentQuantity = 0;
        item.maxQuantity = 0;
        item.body[0] = '\0';
    }
    else
    {
        printf("\nERROR: item not found\n");
    }
    fclose(invFile);
}

void update(FILE *invFile)
{
    invFile = fopen(INVENTORY_FILE, "rb+");
    if (invFile == NULL)
    {
        invFile = fopen(INVENTORY_FILE, "wb+");
    }
    int itemNumber = 0;
    int seekPos = 0;
    int readCount = 0;
    char numInput[10];

    printf("\nEnter an item number: ");
    scanf("%d", &itemNumber);
    getchar();

    seekPos = itemNumber * sizeof(Item);
    fseek(invFile, seekPos, SEEK_SET);
    fread(&oldItem, sizeof(Item), 1L, invFile);

    if (oldItem.simpleName[0] == '\0')
    {
        printf("\nERROR: item not found\n");
    }
    else
    {
        printf("Simple name: ");
        fgets(newItem.simpleName, 16, stdin);
        newItem.simpleName[strcspn(newItem.simpleName, "\n")] = '\0';
        if (newItem.simpleName[0] == '\0')
        {
            strcpy(newItem.simpleName, oldItem.simpleName);
        }

        printf("Item name: ");
        fgets(newItem.itemName, 64, stdin);
        newItem.itemName[strcspn(newItem.itemName, "\n")] = '\0';
        if (newItem.itemName[0] == '\0')
        {
            strcpy(newItem.itemName, oldItem.itemName);
        }

        printf("Current quantity: ");
        fgets(numInput, 9, stdin);
        numInput[strcspn(numInput, "\n")] = '\0';
        readCount = sscanf(numInput, "%d", &newItem.currentQuantity);
        if (readCount != 1)
        {
            newItem.currentQuantity = oldItem.currentQuantity;
        }

        printf("Max quantity: ");
        fgets(numInput, 9, stdin);
        numInput[strcspn(numInput, "\n")] = '\0';
        readCount = sscanf(numInput, "%d", &newItem.maxQuantity);
        if (readCount != 1)
        {
            newItem.maxQuantity = oldItem.maxQuantity;
        }

        printf("Description: ");
        fgets(newItem.body, 128, stdin);
        newItem.body[strcspn(newItem.body, "\n")] = '\0';
        if (newItem.body[0] == '\0')
        {
            strcpy(newItem.body, oldItem.body);
        }

        fseek(invFile, seekPos, SEEK_SET);
        fwrite(&newItem, sizeof(Item), 1L, invFile);

        newItem.simpleName[0] = '\0';
        newItem.itemName[0] = '\0';
        newItem.currentQuantity = 0;
        newItem.maxQuantity = 0;
        newItem.body[0] = '\0';

        oldItem.simpleName[0] = '\0';
        oldItem.itemName[0] = '\0';
        oldItem.currentQuantity = 0;
        oldItem.maxQuantity = 0;
        oldItem.body[0] = '\0';
    }
    fclose(invFile);
}

void delete(FILE *invFile)
{
    invFile = fopen(INVENTORY_FILE, "rb+");
    if (invFile == NULL)
    {
        invFile = fopen(INVENTORY_FILE, "wb+");
    }
    int itemNumber = 0;
    int seekPos = 0;

    printf("\nEnter an item number: ");
    scanf("%d", &itemNumber);
    getchar();

    seekPos = itemNumber * sizeof(Item);
    fseek(invFile, seekPos, SEEK_SET);
    fread(&item, sizeof(Item), 1L, invFile);

    if (item.simpleName[0] != '\0')
    {
        printf("\n%s was successfully deleted.\n", item.simpleName);
        item.simpleName[0] = '\0';
        item.itemName[0] = '\0';
        item.currentQuantity = 0;
        item.maxQuantity = 0;
        item.body[0] = '\0';
        fseek(invFile, seekPos, SEEK_SET);
        fwrite(&item, sizeof(Item), 1L, invFile);
    }
    else
    {
        printf("\nERROR: item not found\n");
    }
    fclose(invFile);
}