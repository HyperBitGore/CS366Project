#ifndef ITEM_H
#define ITEM_H

#define MAX_NAME 50

/* Different types of items in the game */
typedef enum {
	ITEM_HEALING,
	ITEM_WEAPON,
	ITEM_ARMOR,
} ItemType; 

/* BAsic item structure */
typedef struct {
	char name[MAX_NAME];
	ItemType type; 
	int value; 

	/*Name of item, type of item (armor, weapon, potions). Value of item, 
	 * weapon = damage
	 * armor = defense bonus
	 * potion = healing */ 
}Item; 

#endif

