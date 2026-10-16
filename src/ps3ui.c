#include "ps3ui.h"

#if defined(__PPU__) || defined(__PS3__) || defined(__CELLOS_LV2__) || defined(CELLCRAFT_PS3)

#include <stdio.h>
#include <string.h>
#include <tiny3d.h>
#include <libfont.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "CellCraft.h"
#include "player.h"
#include "config.h"

#define PS3UI_FONT_W 16
#define PS3UI_FONT_H 16
#define PS3UI_MAX_PLAYERS_SHOWN 10

static int ui_active = 0;
static FT_Library ft_lib = NULL;
static FT_Face ft_face = NULL;

static void ps3ui_ttf_callback(u8 chr, u8 *bitmap, short *w, short *h, short *y_correction)
{
    int cell_w = *w;
    int cell_h = *h;
    memset(bitmap, 0, (size_t)(cell_w * cell_h));
    *w = 0;
    *h = 0;
    *y_correction = 0;
    if (ft_face == NULL) return;
    if (FT_Load_Char(ft_face, (unsigned long)chr, FT_LOAD_RENDER)) return;
    {
        FT_GlyphSlot g = ft_face->glyph;
        int gw = g->bitmap.width;
        int gh = g->bitmap.rows;
        int top, left, x, y;
        if (gw > cell_w) gw = cell_w;
        if (gh > cell_h) gh = cell_h;
        top = cell_h - g->bitmap_top;
        if (top < 0) top = 0;
        if (top + gh > cell_h) gh = cell_h - top;
        left = g->bitmap_left;
        if (left < 0) left = 0;
        if (left >= cell_w) return;
        if (left + gw > cell_w) gw = cell_w - left;
        for (y = 0; y < gh; y++)
        {
            for (x = 0; x < gw; x++)
            {
                bitmap[(top + y) * cell_w + (left + x)] = g->bitmap.buffer[y * g->bitmap.pitch + x];
            }
        }
        *w = (short)(g->advance.x >> 6);
        if (*w < 1) *w = 1;
        if (*w > cell_w) *w = (short)cell_w;
        *h = (short)gh;
        *y_correction = (short)top;
    }
}

int ps3ui_init(void)
{
    static const char *font_paths[] = {
        "/dev_flash/data/font/SCE-PS3-SR-R-LATIN2.TTF",
        "/dev_flash/data/font/SCE-PS3-VR-R-LATIN.TTF",
        "/dev_flash/data/font/SCE-PS3-NB-R-LATIN.TTF",
        NULL};
    u8 *tex_mem;
    int i;

    if (tiny3d_Init(1024 * 1024) != 0) return 0;
    tex_mem = tiny3d_AllocTexture(256 * 1024);
    if (tex_mem == NULL) return 0;
    if (FT_Init_FreeType(&ft_lib)) return 0;
    for (i = 0; font_paths[i] != NULL; i++)
    {
        if (FT_New_Face(ft_lib, font_paths[i], 0, &ft_face) == 0) break;
    }
    if (ft_face == NULL) return 0;
    FT_Set_Pixel_Sizes(ft_face, 0, PS3UI_FONT_H);
    ResetFont();
    AddFontFromTTF(tex_mem, 32, 127, PS3UI_FONT_W, PS3UI_FONT_H, ps3ui_ttf_callback);
    SetFontColor(0xffffffff, 0x0);
    ui_active = 1;
    return 1;
}

void ps3ui_draw(void)
{
    float y;
    int n;
    player_t *p;

    if (!ui_active) return;
    tiny3d_Clear(0xff000000, TINY3D_CLEAR_ALL);
    tiny3d_Project2D();

    SetFontColor(0x00ff00ff, 0x0);
    y = DrawFormatString(64.0f, 48.0f, "CellCraft PS3  (proto %d)", PROTOCOL_VERSION);
    (void)y;
    SetFontColor(0xffffffff, 0x0);
    y = 96.0f;
    y = DrawFormatString(64.0f, y, "Status: LISTENING *:%d   tick: %u", PORT, (unsigned)main_tick) + 28.0f;
    n = 0;
    for (p = playerGetHead(); p != NULL && n < PS3UI_MAX_PLAYERS_SHOWN; p = p->next, n++)
    {
        if (!p->active) continue;
        y = DrawFormatString(64.0f, y, "- %s", p->name) + 24.0f;
    }
    DrawFormatString(64.0f, y, "Players online: %u", (unsigned)playerGetActiveCount());
    SetFontColor(0x808080ff, 0x0);
    DrawFormatString(64.0f, 464.0f, "Made by 0xagvz");

    tiny3d_Flip();
}

void ps3ui_end(void)
{
    if (ft_face != NULL)
    {
        FT_Done_Face(ft_face);
        ft_face = NULL;
    }
    if (ft_lib != NULL)
    {
        FT_Done_FreeType(ft_lib);
        ft_lib = NULL;
    }
    ui_active = 0;
}

#else

int ps3ui_init(void)
{
    return 0;
}
void ps3ui_draw(void)
{
}
void ps3ui_end(void)
{
}

#endif
