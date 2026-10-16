#ifndef _RECIPES_H
#define _RECIPES_H

#include <stdint.h>
#include "blocks/items.h"
#include "storage.h"

typedef enum
{
    RECIPE_SHAPED,
    RECIPE_SHAPELESS,
} recipe_type_t;

typedef struct
{
    recipe_type_t type;
    int32_t ingredients[9];
    int32_t result_item;
    int16_t result_count;
} recipe_t;

static const recipe_t recipes[] = {
    // Oak log -> 4 oak planks
    { RECIPE_SHAPELESS, {MINECRAFT_OAK_LOG_ITEM}, MINECRAFT_OAK_PLANKS_ITEM, 4 },
    // 2 oak planks (vertical) -> 4 sticks
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_AIR_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_AIR_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,        MINECRAFT_AIR_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_STICK_ITEM, 4,
    },
    // Crafting table
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_AIR_ITEM,
            MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,        MINECRAFT_AIR_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_CRAFTING_TABLE_ITEM, 1,
    },
    // Chest
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_OAK_PLANKS_ITEM,
            MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_AIR_ITEM,        MINECRAFT_OAK_PLANKS_ITEM,
            MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_OAK_PLANKS_ITEM, MINECRAFT_OAK_PLANKS_ITEM,
        },
        MINECRAFT_CHEST_ITEM, 1,
    },
    // Furnace
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_COBBLESTONE_ITEM,
            MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_AIR_ITEM,         MINECRAFT_COBBLESTONE_ITEM,
            MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_COBBLESTONE_ITEM,
        },
        MINECRAFT_FURNACE_ITEM, 1,
    },
    // White bed
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_WHITE_WOOL_ITEM,  MINECRAFT_WHITE_WOOL_ITEM,  MINECRAFT_WHITE_WOOL_ITEM,
            MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_OAK_PLANKS_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_WHITE_BED_ITEM, 1,
    },
    // Wooden pickaxe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_OAK_PLANKS_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_WOODEN_PICKAXE_ITEM, 1,
    },
    // Stone pickaxe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_COBBLESTONE_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_STONE_PICKAXE_ITEM, 1,
    },
    // Iron pickaxe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_IRON_PICKAXE_ITEM, 1,
    },
    // Golden pickaxe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_GOLDEN_PICKAXE_ITEM, 1,
    },
    // Diamond pickaxe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_DIAMOND_PICKAXE_ITEM, 1,
    },
    // Wooden axe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_AIR_ITEM,
            MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_WOODEN_AXE_ITEM, 1,
    },
    // Stone axe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_AIR_ITEM,
            MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_STONE_AXE_ITEM, 1,
    },
    // Iron axe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_IRON_AXE_ITEM, 1,
    },
    // Golden axe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_GOLDEN_AXE_ITEM, 1,
    },
    // Diamond axe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_DIAMOND_AXE_ITEM, 1,
    },
    // Wooden sword
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_WOODEN_SWORD_ITEM, 1,
    },
    // Stone sword
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_STONE_SWORD_ITEM, 1,
    },
    // Iron sword
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_IRON_SWORD_ITEM, 1,
    },
    // Golden sword
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_GOLDEN_SWORD_ITEM, 1,
    },
    // Diamond sword
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_DIAMOND_SWORD_ITEM, 1,
    },
    // Wooden shovel
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_WOODEN_SHOVEL_ITEM, 1,
    },
    // Stone shovel
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_STONE_SHOVEL_ITEM, 1,
    },
    // Iron shovel
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_IRON_SHOVEL_ITEM, 1,
    },
    // Golden shovel
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_GOLDEN_SHOVEL_ITEM, 1,
    },
    // Diamond shovel
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
            MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_DIAMOND_SHOVEL_ITEM, 1,
    },
    // Wooden hoe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_OAK_PLANKS_ITEM,  MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_WOODEN_HOE_ITEM, 1,
    },
    // Stone hoe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_COBBLESTONE_ITEM, MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_STONE_HOE_ITEM, 1,
    },
    // Iron hoe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_IRON_HOE_ITEM, 1,
    },
    // Golden hoe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,        MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_GOLDEN_HOE_ITEM, 1,
    },
    // Diamond hoe
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_STICK_ITEM,       MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_DIAMOND_HOE_ITEM, 1,
    },
    // Leather helmet
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_LEATHER_ITEM,     MINECRAFT_LEATHER_ITEM,     MINECRAFT_LEATHER_ITEM,
            MINECRAFT_LEATHER_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_LEATHER_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_LEATHER_HELMET_ITEM, 1,
    },
    // Leather chestplate
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_LEATHER_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_LEATHER_ITEM,
            MINECRAFT_LEATHER_ITEM,     MINECRAFT_LEATHER_ITEM,     MINECRAFT_LEATHER_ITEM,
            MINECRAFT_LEATHER_ITEM,     MINECRAFT_LEATHER_ITEM,     MINECRAFT_LEATHER_ITEM,
        },
        MINECRAFT_LEATHER_CHESTPLATE_ITEM, 1,
    },
    // Leather leggings
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_LEATHER_ITEM,     MINECRAFT_LEATHER_ITEM,     MINECRAFT_LEATHER_ITEM,
            MINECRAFT_LEATHER_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_LEATHER_ITEM,
            MINECRAFT_LEATHER_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_LEATHER_ITEM,
        },
        MINECRAFT_LEATHER_LEGGINGS_ITEM, 1,
    },
    // Leather boots
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_LEATHER_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_LEATHER_ITEM,
            MINECRAFT_LEATHER_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_LEATHER_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_LEATHER_BOOTS_ITEM, 1,
    },
    // Iron helmet
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_IRON_INGOT_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_IRON_HELMET_ITEM, 1,
    },
    // Iron chestplate
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_IRON_INGOT_ITEM,
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,
        },
        MINECRAFT_IRON_CHESTPLATE_ITEM, 1,
    },
    // Iron leggings
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_IRON_INGOT_ITEM,
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_IRON_INGOT_ITEM,
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_IRON_INGOT_ITEM,
        },
        MINECRAFT_IRON_LEGGINGS_ITEM, 1,
    },
    // Iron boots
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_IRON_INGOT_ITEM,
            MINECRAFT_IRON_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_IRON_INGOT_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_IRON_BOOTS_ITEM, 1,
    },
    // Golden helmet
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_GOLD_INGOT_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_GOLDEN_HELMET_ITEM, 1,
    },
    // Golden chestplate
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_GOLD_INGOT_ITEM,
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,
        },
        MINECRAFT_GOLDEN_CHESTPLATE_ITEM, 1,
    },
    // Golden leggings
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_GOLD_INGOT_ITEM,
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_GOLD_INGOT_ITEM,
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_GOLD_INGOT_ITEM,
        },
        MINECRAFT_GOLDEN_LEGGINGS_ITEM, 1,
    },
    // Golden boots
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_GOLD_INGOT_ITEM,
            MINECRAFT_GOLD_INGOT_ITEM,  MINECRAFT_AIR_ITEM,         MINECRAFT_GOLD_INGOT_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_GOLDEN_BOOTS_ITEM, 1,
    },
    // Diamond helmet
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_DIAMOND_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_DIAMOND_HELMET_ITEM, 1,
    },
    // Diamond chestplate
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_DIAMOND_ITEM,
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,
        },
        MINECRAFT_DIAMOND_CHESTPLATE_ITEM, 1,
    },
    // Diamond leggings
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,     MINECRAFT_DIAMOND_ITEM,
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_DIAMOND_ITEM,
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_DIAMOND_ITEM,
        },
        MINECRAFT_DIAMOND_LEGGINGS_ITEM, 1,
    },
    // Diamond boots
    {
        RECIPE_SHAPED,
        {
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_DIAMOND_ITEM,
            MINECRAFT_DIAMOND_ITEM,     MINECRAFT_AIR_ITEM,         MINECRAFT_DIAMOND_ITEM,
            MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,         MINECRAFT_AIR_ITEM,
        },
        MINECRAFT_DIAMOND_BOOTS_ITEM, 1,
    },
};

static int32_t get_crafted_item(player_t *currentPlayer, inventory_slots_t slots[9], size_t *count)
{
    (void)currentPlayer;
    if (slots == NULL)
    {
        return MINECRAFT_AIR_ITEM;
    }
    if (count == NULL)
    {
        return MINECRAFT_AIR_ITEM;
    }

    *count = 0;

    static const size_t num_recipes = sizeof(recipes) / sizeof(recipes[0]);

    for (size_t r = 0; r < num_recipes; r++)
    {
        const recipe_t *recipe = &recipes[r];

        if (recipe->type == RECIPE_SHAPED)
        {
            int p_min_row = 3, p_max_row = -1, p_min_col = 3, p_max_col = -1;
            int g_min_row = 3, g_max_row = -1, g_min_col = 3, g_max_col = -1;
            for (int i = 0; i < 9; i++)
            {
                int row = i / 3, col = i % 3;
                if (recipe->ingredients[i] != MINECRAFT_AIR_ITEM)
                {
                    if (row < p_min_row)
                    {
                        p_min_row = row;
                    }
                    if (row > p_max_row)
                    {
                        p_max_row = row;
                    }
                    if (col < p_min_col)
                    {
                        p_min_col = col;
                    }
                    if (col > p_max_col)
                    {
                        p_max_col = col;
                    }
                }
                if (slots[i].item_id != MINECRAFT_AIR_ITEM)
                {
                    if (row < g_min_row)
                    {
                        g_min_row = row;
                    }
                    if (row > g_max_row)
                    {
                        g_max_row = row;
                    }
                    if (col < g_min_col)
                    {
                        g_min_col = col;
                    }
                    if (col > g_max_col)
                    {
                        g_max_col = col;
                    }
                }
            }

            if (g_max_row == -1 ||
                (p_max_row - p_min_row) != (g_max_row - g_min_row) ||
                (p_max_col - p_min_col) != (g_max_col - g_min_col))
            {
                continue;
            }

            int height = p_max_row - p_min_row + 1;
            int width = p_max_col - p_min_col + 1;
            int match = 1;
            for (int dr = 0; dr < height && match; dr++)
            {
                for (int dc = 0; dc < width && match; dc++)
                {
                    int32_t p_item = recipe->ingredients[(p_min_row + dr) * 3 + (p_min_col + dc)];
                    int32_t g_item = slots[(g_min_row + dr) * 3 + (g_min_col + dc)].item_id;
                    if (p_item != g_item)
                    {
                        match = 0;
                    }
                }
            }

            if (match)
            {
                *count = (size_t)recipe->result_count;
                return recipe->result_item;
            }
        }
        else
        {
            int32_t grid_items[9];
            int grid_count = 0;
            int min_row = 3, max_row = -1, min_col = 3, max_col = -1;
            for (int i = 0; i < 9; i++)
            {
                if (slots[i].item_id != MINECRAFT_AIR_ITEM)
                {
                    grid_items[grid_count++] = slots[i].item_id;
                    int row = i / 3, col = i % 3;
                    if (row < min_row)
                    {
                        min_row = row;
                    }
                    if (row > max_row)
                    {
                        max_row = row;
                    }
                    if (col < min_col)
                    {
                        min_col = col;
                    }
                    if (col > max_col)
                    {
                        max_col = col;
                    }
                }
            }

            for (int row = min_row; row <= max_row && grid_count != -1; row++)
            {
                int row_has_item = 0;
                for (int col = 0; col < 3 && !row_has_item; col++)
                {
                    if (slots[row * 3 + col].item_id != MINECRAFT_AIR_ITEM)
                    {
                        row_has_item = 1;
                    }
                }
                if (!row_has_item)
                {
                    grid_count = -1;
                }
            }

            for (int col = min_col; col <= max_col && grid_count != -1; col++)
            {
                int col_has_item = 0;
                for (int row = 0; row < 3 && !col_has_item; row++)
                {
                    if (slots[row * 3 + col].item_id != MINECRAFT_AIR_ITEM)
                    {
                        col_has_item = 1;
                    }
                }
                if (!col_has_item)
                {
                    grid_count = -1;
                }
            }

            if (grid_count == -1)
            {
                continue;
            }

            int needed_count = 0;
            int32_t needed[9];
            for (int i = 0; i < 9 && recipe->ingredients[i] != MINECRAFT_AIR_ITEM; i++)
            {
                needed[needed_count++] = recipe->ingredients[i];
            }

            if (grid_count != needed_count)
            {
                continue;
            }

            int used[9] = {0};
            int match = 1;
            for (int n = 0; n < needed_count && match; n++)
            {
                int found = 0;
                for (int g = 0; g < grid_count && !found; g++)
                {
                    if (!used[g] && grid_items[g] == needed[n])
                    {
                        used[g] = 1;
                        found = 1;
                    }
                }
                if (!found)
                {
                    match = 0;
                }
            }

            if (match)
            {
                *count = (size_t)recipe->result_count;
                return recipe->result_item;
            }
        }
    }

    return MINECRAFT_AIR_ITEM;
}

#endif