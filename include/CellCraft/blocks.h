#ifndef _BLOCKS_H
#define _BLOCKS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "blocks/block_states.h"
#include "config.h"

#define BLOCKS_INITAL_CAPACITY 16

typedef struct Block
{
    int32_t default_state;
    union
    {
#if (ENDIAN)
        struct
        {
            uint8_t x;
            uint8_t z;
            int16_t y; // TODO: is it possible to optimize the range here while keeping it packed?
        } c;
#else

        struct
        {
            int16_t y; // TODO: is it possible to optimize the range here while keeping it packed?
            uint8_t z;
            uint8_t x;

        } c;
#endif
        uint32_t coord_hash;
    };
} Block;
typedef struct Blocks
{
    size_t size;
    size_t count;
    Block *block;
} Blocks;

void blocksInit();
void blocksCleanup();
bool blocksUpdate(blocksDefaultState state, int32_t x, int16_t y, int32_t z);
Blocks *blocksGet(int32_t chunk_x, int32_t chunk_z);
int32_t blocksGetBlock(int32_t x, int16_t y, int32_t z);
#endif
