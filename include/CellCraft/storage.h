#ifndef _STORAGE_H
#define _STORAGE_H

#include "player.h"
#include <stdint.h>

#define INVENTORY_SIZE 46

typedef struct player_t player_t;
typedef struct storage_t storage_t;
typedef struct inventory_slots_t inventory_slots_t;

struct inventory_slots_t
{
    int16_t count;
    int32_t item_id;
};

struct storage_t
{
    char name[18];
    inventory_slots_t inventory_slots[INVENTORY_SIZE];
    storage_t *next;
};

void storageInventoryUpdate(player_t *currentPlayer);
void storageInventoryUpdateSlot(player_t *currentPlayer, int16_t slot, int16_t count, int32_t item_id);
void storageInventoryGetSlot(player_t *currentPlayer, int16_t slot, inventory_slots_t *selected_slot);
void storageInventoryInsertItem(player_t *currentPlayer, int32_t item_id, int16_t count);
storage_t *storageInventoryGet(player_t *currentPlayer);
void storageInventoryCleanup();

#endif