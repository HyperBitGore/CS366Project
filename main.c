#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "map.h"
#include "character.h"

int main() {
        map* m1 = loadMap("map1.txt");

        Character player;
        char* input = malloc(1024);
        int run = 1;

        srand(time(NULL));
        initCharacter(&player, "Hero");

        while (run) {
                char tile;

                system("clear");
                renderMap(m1);

                printf("\nCommands: right, left, up, down, stats, inv, use, equip, help, quit\n");
                printf("Enter command: ");
                scanf("%s", input);

                /* Command handling */
                if (strcmp(input, "right") == 0) {
                        m1->px += 1;

                } else if (strcmp(input, "left") == 0) {
                        m1->px -= 1;

                } else if (strcmp(input, "up") == 0) {
                        m1->py -= 1;

                } else if (strcmp(input, "down") == 0) {
                        m1->py += 1;

                } else if (strcmp(input, "stats") == 0) {
                        printCharacter(&player);

                        printf("Press enter to continue...");
                        getchar();
                        getchar();
                        continue;

                } else if (strcmp(input, "inv") == 0) {
                        showInventory(&player);

                        printf("Press enter to continue...");
                        getchar();
                        getchar();
                        continue;

                } else if (strcmp(input, "use") == 0) {
                        int slot;

                        showInventory(&player);
                        printf("Enter item number to use: ");
                        scanf("%d", &slot);

                        useItem(&player, slot - 1);

                        printf("Press enter to continue...");
                        getchar();
                        getchar();
                        continue;

                } else if (strcmp(input, "equip") == 0) {
                        int slot;

                        showInventory(&player);
                        printf("Enter item number to equip: ");
                        scanf("%d", &slot);

                        equipItem(&player, slot - 1);

                        printf("Press enter to continue...");
                        getchar();
                        getchar();
                        continue;

                } else if (strcmp(input, "help") == 0) {
                        printf("\nCommands:\n");
                        printf("right, left, up, down\n");
                        printf("stats - show player stats\n");
                        printf("inv - show inventory\n");
                        printf("use - use healing item\n");
                        printf("equip - equip weapon or armor\n");
                        printf("quit - exit game\n");

                        printf("\nMap Symbols:\n");
                        printf("T = treasure\n");
                        printf("W = weapon\n");
                        printf("A = armor\n");
                        printf("E = enemy\n");

                        printf("\nPress enter to continue...");
                        getchar();
                        getchar();
                        continue;

                } else if (strcmp(input, "quit") == 0) {
                        run = 0;
                        continue;
                }

                tile = m1->arr[m1->py * m1->width + m1->px];

                /* Treasure or items */
                if (tile == 'T') {
                        Item treasure;
                        int randomTreasure = rand() % 3;

                        if (randomTreasure == 0) {
                                treasure = (Item){"Potion", ITEM_HEALING, 25};
                        } else if (randomTreasure == 1) {
                                treasure = (Item){"Hi-Potion", ITEM_HEALING, 50};
                        } else {
                                treasure = (Item){"Mega Potion", ITEM_HEALING, 75};
                        }

                        printf("You found %s!\n", treasure.name);
                        addItem(&player, treasure);

                        m1->arr[m1->py * m1->width + m1->px] = ' ';

                        printf("Press enter to continue...");
                        getchar();
                        getchar();
                }

                /* Weapons */
                else if (tile == 'W') {
                        Item weapon;
                        int randomWeapon = rand() % 3;

                        if (randomWeapon == 0) {
                                weapon = (Item){"Iron Sword", ITEM_WEAPON, 5};
                        } else if (randomWeapon == 1) {
                                weapon = (Item){"Steel Sword", ITEM_WEAPON, 10};
                        } else {
                                weapon = (Item){"Magic Blade", ITEM_WEAPON, 15};
                        }

                        printf("You found %s!\n", weapon.name);
                        addItem(&player, weapon);

                        m1->arr[m1->py * m1->width + m1->px] = ' ';

                        printf("Press enter to continue...");
                        getchar();
                        getchar();
                }

                /* Armors */
                else if (tile == 'A') {
                        Item armor;
                        int randomArmor = rand() % 3;

                        if (randomArmor == 0) {
                                armor = (Item){"Leather Armor", ITEM_ARMOR, 3};
                        } else if (randomArmor == 1) {
                                armor = (Item){"Iron Armor", ITEM_ARMOR, 6};
                        } else {
                                armor = (Item){"Knight Armor", ITEM_ARMOR, 10};
                        }

                        printf("You found %s!\n", armor.name);
                        addItem(&player, armor);

                        m1->arr[m1->py * m1->width + m1->px] = ' ';

                        printf("Press enter to continue...");
                        getchar();
                        getchar();
                }

                /* Enemies */
                else if (tile == 'E') {
                        Character enemy;
                        int randomEnemy = rand() % 3;

                        if (randomEnemy == 0) {
                                initCharacter(&enemy, "Slime");
                                enemy.hp = 30;
                                enemy.maxHp = 30;
                                enemy.attack = 6;
                                enemy.defense = 1;

                        } else if (randomEnemy == 1) {
                                initCharacter(&enemy, "Goblin");
                                enemy.hp = 50;
                                enemy.maxHp = 50;
                                enemy.attack = 10;
                                enemy.defense = 2;

                        } else {
                                initCharacter(&enemy, "Orc");
                                enemy.hp = 80;
                                enemy.maxHp = 80;
                                enemy.attack = 15;
                                enemy.defense = 4;
                        }

                        startCombat(&player, &enemy);

                        if (!isAlive(&player)) {
                                run = 0;
                        }

                        m1->arr[m1->py * m1->width + m1->px] = ' ';

                        printf("Press enter to continue...");
                        getchar();
                        getchar();
                }
        }

        free(input);
        return 0;
}
