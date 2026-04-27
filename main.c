#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "map.h"
#include "character.h"

int main() {
        map* m1;
        Character player;
        char* input;
        int run;

        m1 = loadMap("map1.txt");

        if (m1 == NULL) {
                printf("Map failed to load.\n");
                return 1;
        }

        input = malloc(1024);
        run = 1;

        srand(time(NULL));
        interactSetup();
        initCharacter(&player, "Hero");

        while (run) {
                char tile;

                system("clear");
                renderMap(m1);

                printf("\nCommands: d, a, w, s, stats, inv, use, equip, help, quit\n");
                printf("Enter command: ");
                scanf("%s", input);

                if (strcmp(input, "d") == 0){
			playerMovement(m1, "right");
		}else if (strcmp(input, "a") ==0){
			playerMovement(m1, "left");
		}else if (strcmp(input, "w") ==0){
                        playerMovement(m1, "up");
		}else if (strcmp(input, "s") ==0){
                        playerMovement(m1, "down");

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
                        printf("w = up\n");
			printf("s = down\n");
			printf("a = left\n");
			printf("d = right\n");
                        printf("stats - show player stats\n");
                        printf("inv - show inventory\n");
                        printf("use - use healing item\n");
                        printf("equip - equip weapon or armor\n");
                        printf("quit - exit game\n");

                        printf("\nMap Symbols:\n");
                        printf("# = wall\n");
                        printf("> = next map\n");
                        printf("< = previous map\n");
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

                if (tile == '>' || tile == '<') {
                        m1 = interact(m1);
                        continue;
                }

                if (tile == 'T') {
                        Item treasure;
                        int randomTreasure;

                        randomTreasure = rand() % 3;

                        if (randomTreasure == 0) {
                                treasure = (Item){"Potion", ITEM_HEALING, 25};
                        } else if (randomTreasure == 1) {
                                treasure = (Item){"Large Potion", ITEM_HEALING, 50};
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

                else if (tile == 'W') {
                        Item weapon;
                        int randomWeapon;

                        randomWeapon = rand() % 5;

                        if (randomWeapon == 0) {
                                weapon = (Item){"Stick", ITEM_WEAPON, 5};
                        } else if (randomWeapon == 1) {
                                weapon = (Item){"Paper Sword", ITEM_WEAPON, 10};
                        } else if (randomWeapon == 2) {
                                weapon = (Item){"Stone Sword", ITEM_WEAPON, 15};
                        } else if (randomWeapon == 3) { 
				weapon = (Item){"Steel Blade", ITEM_WEAPON, 18};
			} else {
				weapon = (Item){"Battle Axe", ITEM_WEAPON, 25};
			}
                        printf("You found %s!\n", weapon.name);
                        addItem(&player, weapon);

                        m1->arr[m1->py * m1->width + m1->px] = ' ';

                        printf("Press enter to continue...");
                        getchar();
                        getchar();
                }

                else if (tile == 'A') {
                        Item armor;
                        int randomArmor;

                        randomArmor = rand() % 5;

                        if (randomArmor == 0) {
                                armor = (Item){"Paper Armor", ITEM_ARMOR, 3};
                        } else if (randomArmor == 1) {
                                armor = (Item){"Wizard Robes", ITEM_ARMOR, 6};
                        } else if (randomArmor == 2) {
                                armor = (Item){"Iron Armor", ITEM_ARMOR, 10};
                        } else if (randomArmor ==3) {
				armor = (Item){"Knight Armor", ITEM_ARMOR, 15};
			} else {
				armor = (Item){"Power Armor", ITEM_ARMOR, 20};
			}

                        printf("You found %s!\n", armor.name);
                        addItem(&player, armor);

                        m1->arr[m1->py * m1->width + m1->px] = ' ';

                        printf("Press enter to continue...");
                        getchar();
                        getchar();
                }else if (tile == 'B') {
		       Character boss;
	       	
		       initCharacter(&boss, "Big Bad Boss Man");
		       boss.hp = 170;
		       boss.maxHp = 170;
		       boss.attack = 22; 
	   	       boss.defense = 7;

		       startCombat(&player, &boss); 
			if (!isAlive(&player)) {
 				run = 0; 
			} else {
				printf("\n=================================\n");
				printf("CONGRATULATIONS!\n");
				printf("You defeated the final boss!\n");
				printf("You beat the game!\n");
				printf("=================================\n");
			
				printf("Press enter to end");
                        	getchar();
                        	getchar();
				run = 0;
			}
			m1->arr[m1->py * m1->width + m1->px] = ' ';

		}else if (tile == 'E') {
                        Character enemy;
                        int randomEnemy;

                        randomEnemy = rand() % 5;

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

                        } else if (randomEnemy == 2) {
                                initCharacter(&enemy, "Orc");
                                enemy.hp = 80;
                                enemy.maxHp = 80;
                                enemy.attack = 15;
                                enemy.defense = 4;
                        } else if (randomEnemy == 3){ 
				initCharacter(&enemy, "Skeleton");
                                enemy.hp = 60;
                                enemy.maxHp = 60;
                                enemy.attack = 12;
                                enemy.defense = 3;
			} else {
				initCharacter(&enemy, "Troll");
                                enemy.hp = 90;
                                enemy.maxHp = 90;
                                enemy.attack = 17;
                                enemy.defense = 5;
			}
                        startCombat(&player, &enemy);

                        if (!isAlive(&player)) {
                                run = 0;
                        }

                        m1->arr[m1->py * m1->width + m1->px] = ' ';

                        
                }
        }

        free(input);
        return 0;
}
