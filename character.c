#include <stdio.h>
#include <string.h>
#include "character.h"

/* Set up a new character with default starting stats */
void initCharacter(Character *player, char name[]) {
    strcpy(player->name, name);

    player->hp = 100;
    player->maxHp = 100;
    player->attack = 10;
    player->defense = 2;

    player->inventoryCount = 0;

    player->hasWeapon = 0;
    player->hasArmor = 0;
}

/* Return total attack including weapon bonus */
int getAttack(Character *player) {
    if (player->hasWeapon) {
        return player->attack + player->weapon.value;
    }
    return player->attack;
}

/* Return total defense including armor bonus */
int getDefense(Character *player) {
    if (player->hasArmor) {
        return player->defense + player->armor.value;
    }
    return player->defense;
}

/* Add item to inventory */
int addItem(Character *player, Item item) {
    if (player->inventoryCount >= INVENTORY_SIZE) {
        printf("Inventory is full!\n");
        return 0;
    }

    player->inventory[player->inventoryCount] = item;
    player->inventoryCount++;

    return 1;
}

/* Show all items in inventory */
void showInventory(Character *player) {
    int i;

    printf("\n--- Inventory ---\n");

    if (player->inventoryCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    for (i = 0; i < player->inventoryCount; i++) {
        printf("%d. %s\n", i + 1, player->inventory[i].name);
    }
}

/* Equip a weapon or armor */
void equipItem(Character *player, int index) {
    if (index < 0 || index >= player->inventoryCount) {
        printf("Invalid inventory slot.\n");
        return;
    }

    if (player->inventory[index].type == ITEM_WEAPON) {
        player->weapon = player->inventory[index];
        player->hasWeapon = 1;
        printf("%s equipped %s!\n", player->name, player->weapon.name);
    }
    else if (player->inventory[index].type == ITEM_ARMOR) {
        player->armor = player->inventory[index];
        player->hasArmor = 1;
        printf("%s equipped %s!\n", player->name, player->armor.name);
    }
    else {
        printf("That item cannot be equipped.\n");
    }
}

/* Use healing items like potions */
void useItem(Character *player, int index) {
    int i;

    if (index < 0 || index >= player->inventoryCount) {
        printf("Invalid inventory slot.\n");
        return;
    }

    if (player->inventory[index].type == ITEM_HEALING) {
        printf("%s used %s!\n", player->name, player->inventory[index].name);

        player->hp += player->inventory[index].value;

        if (player->hp > player->maxHp) {
            player->hp = player->maxHp;
        }

        /* Remove used item from inventory */
        for (i = index; i < player->inventoryCount - 1; i++) {
            player->inventory[i] = player->inventory[i + 1];
        }

        player->inventoryCount--;
    }
    else {
        printf("That item cannot be used.\n");
    }
}

/* Take damage after defense is applied */
void takeDamage(Character *player, int damage) {
    int finalDamage;

    finalDamage = damage - getDefense(player);

    if (finalDamage < 1) {
        finalDamage = 1;
    }

    player->hp -= finalDamage;

    if (player->hp < 0) {
        player->hp = 0;
    }

    printf("%s took %d damage!\n", player->name, finalDamage);
}

/* Check if character is still alive */
int isAlive(Character *player) {
    return player->hp > 0;
}

/* Basic attack action */
void basicAttack(Character *attacker, Character *defender) {
    printf("%s attacks %s!\n", attacker->name, defender->name);
    takeDamage(defender, getAttack(attacker));
}

/* player-controlled combat loop */
void startCombat(Character *player, Character *enemy) {
    int choice;
    int slot;

    printf("\nA %s appeared!\n", enemy->name);

    while (isAlive(player) && isAlive(enemy)) {
        printf("\n--- Combat ---\n");
        printf("%s HP: %d / %d\n", player->name, player->hp, player->maxHp);
        printf("%s HP: %d / %d\n", enemy->name, enemy->hp, enemy->maxHp);

        printf("\nChoose an action:\n");
        printf("1. Attack\n");
        printf("2. Use item\n");
        printf("3. View stats\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            basicAttack(player, enemy);
        }
        else if (choice == 2) {
            showInventory(player);

            printf("Enter item number to use: ");
            scanf("%d", &slot);

            useItem(player, slot - 1);
        }
        else if (choice == 3) {
            printCharacter(player);
            continue;
        }
        else {
            printf("Invalid choice.\n");
            continue;
        }

        if (!isAlive(enemy)) {
            printf("\nYou defeated the %s!\n", enemy->name);
            break;
        }

        printf("\n%s's turn!\n", enemy->name);
        basicAttack(enemy, player);

        if (!isAlive(player)) {
            printf("\nYou were defeated!\n");
            break;
        }
    }
}

/* Print all player stats */
void printCharacter(Character *player) {
    printf("\n=== %s ===\n", player->name);
    printf("HP: %d / %d\n", player->hp, player->maxHp);
    printf("Attack: %d\n", getAttack(player));
    printf("Defense: %d\n", getDefense(player));

    if (player->hasWeapon) {
        printf("Weapon: %s (+%d ATK)\n",
               player->weapon.name,
               player->weapon.value);
    }
    else {
        printf("Weapon: None\n");
    }

    if (player->hasArmor) {
        printf("Armor: %s (+%d DEF)\n",
               player->armor.name,
               player->armor.value);
    }
    else {
        printf("Armor: None\n");
    }
}
