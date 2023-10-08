#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POKEMON 100
#define FILENAME "pokedex_data.bin"

typedef struct {
    char name[50];
    int id;
    char type[20];
} Pokemon;

typedef struct {
    Pokemon pokemons[MAX_POKEMON];
    int count;
} Pokedex;

void savePokedex(Pokedex *pokedex) {
    FILE *file = fopen(FILENAME, "wb");
    if (file != NULL) {
        fwrite(pokedex, sizeof(Pokedex), 1, file);
        fclose(file);
    } else {
        printf("Error: Could not save Pokedex data to file.\n");
    }
}

ytutyutyutyuyu

void loadPokedex(Pokedex *pokedex) {
    FILE *file = fopen(FILENAME, "rb");
    if (file != NULL) {
        fread(pokedex, sizeof(Pokedex), 1, file);
        fclose(file);
    }
}

void addPokemon(Pokedex *pokedex, char name[], int id, char type[]) {
    if (pokedex->count < MAX_POKEMON) {
        strcpy(pokedex->pokemons[pokedex->count].name, name);
        pokedex->pokemons[pokedex->count].id = id;
        strcpy(pokedex->pokemons[pokedex->count].type, type);
        pokedex->count++;
        printf("Pokemon added successfully!\n");
        savePokedex(pokedex);
    } else {
        printf("Pokedex is full, cannot add more Pokemon.\n");
    }
}

void displayPokemon(Pokedex *pokedex) {
    printf("Pokedex Entries:\n");
    for (int i = 0; i < pokedex->count; i++) {
        printf("ID: %d, Name: %s, Type: %s\n",
               pokedex->pokemons[i].id,
               pokedex->pokemons[i].name,
               pokedex->pokemons[i].type);
    }
}

void searchPokemon(Pokedex *pokedex, int id) {
    for (int i = 0; i < pokedex->count; i++) {
        if (pokedex->pokemons[i].id == id) {
            printf("ID: %d, Name: %s, Type: %s\n",
                   pokedex->pokemons[i].id,
                   pokedex->pokemons[i].name,
                   pokedex->pokemons[i].type);
            return;
        }
    }
    printf("Pokemon with ID %d not found.\n", id);
}

void editPokemon(Pokedex *pokedex, int id, char name[], char type[]) {
    for (int i = 0; i < pokedex->count; i++) {
        if (pokedex->pokemons[i].id == id) {
            strcpy(pokedex->pokemons[i].name, name);
            strcpy(pokedex->pokemons[i].type, type);
            printf("Pokemon with ID %d edited successfully!\n", id);
            savePokedex(pokedex);
            return;
        }
    }
    printf("Pokemon with ID %d not found.\n", id);
}

void deletePokemon(Pokedex *pokedex, int id) {
    for (int i = 0; i < pokedex->count; i++) {
        if (pokedex->pokemons[i].id == id) {
            for (int j = i; j < pokedex->count - 1; j++) {
                pokedex->pokemons[j] = pokedex->pokemons[j + 1];
            }
            pokedex->count--;
            printf("Pokemon with ID %d deleted successfully!\n", id);
            savePokedex(pokedex);
            return;
        }
    }
    printf("Pokemon with ID %d not found.\n", id);
}

int main() {
    Pokedex pokedex;
    pokedex.count = 0;

    loadPokedex(&pokedex);

    int choice;
    int id;
    char name[50];
    char type[20];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Pokemon\n");
        printf("2. Display Pokemon\n");
        printf("3. Search Pokemon\n");
        printf("4. Edit Pokemon\n");
        printf("5. Delete Pokemon\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Pokemon details:\n");
                printf("ID: ");
                scanf("%d", &id);
                printf("Name: ");
                scanf("%s", name);
                printf("Type: ");
                scanf("%s", type);
                addPokemon(&pokedex, name, id, type);
                break;
            case 2:
                displayPokemon(&pokedex);
                break;
            case 3:
                printf("Enter Pokemon ID to search: ");
                scanf("%d", &id);
                searchPokemon(&pokedex, id);
                break;
            case 4:
                printf("Enter Pokemon ID to edit: ");
                scanf("%d", &id);
                printf("Enter new name: ");
                scanf("%s", name);
                printf("Enter new type: ");
                scanf("%s", type);
                editPokemon(&pokedex, id, name, type);
                break;
            case 5:
                printf("Enter Pokemon ID to delete: ");
                scanf("%d", &id);
                deletePokemon(&pokedex, id);
                break;
            case 6:
                savePokedex(&pokedex);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}
