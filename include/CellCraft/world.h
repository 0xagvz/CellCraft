#ifndef _WORLD_H
#define _WORLD_H

#include <stdint.h>
#include "player.h"

int worldGetBlock(int32_t x, int32_t y, int32_t z);
void worldGenerateChunk(int32_t chunk_x, int32_t chunk_z, size_t from, size_t to);

#endif
