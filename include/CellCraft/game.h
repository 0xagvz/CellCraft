#ifndef _GAME_H
#define _GAME_H

#include "config.h"
#include "wrapper.h"

typedef struct player_t player_t;
typedef struct game_player_data_t game_player_data_t;
typedef struct game_data_t game_data_t;
typedef struct inventory_slots_t inventory_slots_t;

struct game_player_data_t
{
    // Chunk events
    uint8_t chunk_load_event : 1;
    uint8_t chunk_spawn_event : 1;
    uint8_t action_item_event : 2;
    // Block events
    uint8_t block_update_event : 1;
    uint8_t block_ack_event : 1;
    // Inventory events
    uint8_t full_inventory_update_event : 1;
    uint8_t inventory_crafting_event : 1;
    // Crafting
    uint8_t crafting_table_event : 1;
    inventory_slots_t *crafting_menu;
    // Inventory slot
    int16_t inventory_slot;
    // Block actions
    int32_t block_state;
    uint8_t block_face;
    int32_t block_x, block_y, block_z;
    uint32_t block_sequence;
    // Chunk
    int32_t chunk_x, chunk_z, chunk_lx, chunk_lz;
};

struct game_data_t
{
    size_t time;
};

void gamePreload();
void gameCleanup();
void gamePlayerSpawned(player_t *currentPlayer);
void gamePlayerLeft(player_t *currentPlayer);
void gameGlobalTick();
void gamePlayerGlobalTick(player_t *currentPlayer);
void gamePlayerGlobalTickOthers(player_t *currentPlayer);
void gamePlayerLocalTick(player_t *currentPlayer);

#endif
