#ifndef CHARACTER_H
#define CHARACTER_H

#include "item.h"

/* Maximum number of items in inventory */
#define INVENTORY_SIZE 20

/* Character structure */
typedef struct {
    char name[MAX_NAME];

    /* Basic stats */
    int hp;
    int maxHp;
    int attack;
    int defense;

    /* Inventory */
    Item inventory[INVENTORY_SIZE];
    int inventoryCount;

    /* Equipped weapon */
    Item weapon;
    int hasWeapon;

    /* Equipped armor */
    Item armor;
    int hasArmor;

} Character;

/* Function prototypes */

void initCharacter(Character *player, char name[]);

void printCharacter(Character *player);

int addItem(Character *player, Item item);

void showInventory(Character *player);

void useItem(Character *player, int index);

void equipItem(Character *player, int index);

int getAttack(Character *player);

int getDefense(Character *player);

void takeDamage(Character *player, int damage);

int isAlive(Character *player);

void basicAttack(Character *attacker, Character *defender);

void startCombat(Character *player, Character *enemy);
#endif
