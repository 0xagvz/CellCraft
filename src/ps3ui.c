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

#include <malloc.h>
#include "logo_png.h"
#include <png.h>

#define PS3UI_SCREEN_W          848.0f
#define PS3UI_SCREEN_H          512.0f
#define PS3UI_FONT_W            16
#define PS3UI_FONT_H            16
#define PS3UI_MAX_PLAYERS_SHOWN 10
#define PS3UI_RAM_LIMIT         (256u * 1024u * 1024u)

/* Colors */
#define UI_BG           0x080D16FFu
#define UI_PANEL        0x111A2AFFu
#define UI_ROW          0x172238FFu
#define UI_ROW_ALT      0x131E30FFu
#define UI_BORDER       0x26334AFFu
#define UI_ACCENT       0x39D0C8FFu
#define UI_GREEN        0x48DE93FFu
#define UI_AMBER        0xF3BC5BFFu
#define UI_TEXT         0xEAF0FFFFu
#define UI_MUTED        0x91A0BAFFu
#define UI_BAR_BG       0x25314BFFu
#define UI_BADGE_BG     0x15382FFFu

static int ui_active = 0;
static FT_Library ft_lib = NULL;
static FT_Face ft_face = NULL;

static u8 *logo_tex_mem = NULL;
static u32 logo_offset = 0;
static int logo_w = 0;
static int logo_h = 0;

static int percentageOfRamUsed(void)
{
    struct mallinfo info = mallinfo();
    size_t used = (size_t)info.uordblks;

    if (PS3UI_RAM_LIMIT == 0u)
        return 0;

    if (used > PS3UI_RAM_LIMIT)
        used = PS3UI_RAM_LIMIT;

    return (int)(((double)used / (double)PS3UI_RAM_LIMIT) * 100.0);
}

typedef struct
{
    const unsigned char *data;
    size_t pos;
    size_t size;
} png_mem_reader_t;

static png_mem_reader_t png_reader;

static void png_read_from_memory(png_structp png_ptr, png_bytep out, png_size_t len)
{
    if (png_reader.pos + len > png_reader.size)
    {
        png_error(png_ptr, "unexpected end of PNG data");
    }
    memcpy(out, png_reader.data + png_reader.pos, len);
    png_reader.pos += len;
}

static int ps3ui_load_logo(void)
{
    png_structp png_ptr;
    png_infop info_ptr;
    int color_type;
    int bit_depth;
    png_uint_32 width;
    png_uint_32 height;
    png_bytepp rows;
    unsigned char *dst;
    png_size_t rowbytes;
    int y;
    int x;

    png_reader.data = logo_png;
    png_reader.pos = 0;
    png_reader.size = logo_png_size;

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)
        return 0;
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return 0;
    }
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return 0;
    }

    png_set_read_fn(png_ptr, NULL, png_read_from_memory);
    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    if (bit_depth == 16)
        png_set_strip_16(png_ptr);
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    rows = (png_bytepp)malloc((size_t)height * sizeof(png_bytep));
    if (rows == NULL)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return 0;
    }
    for (y = 0; y < (int)height; y++)
    {
        rows[y] = (png_bytep)malloc(rowbytes);
        if (rows[y] == NULL)
        {
            for (x = 0; x < y; x++)
                free(rows[x]);
            free(rows);
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            return 0;
        }
    }
    png_read_image(png_ptr, rows);
    png_read_end(png_ptr, NULL);

    logo_tex_mem = tiny3d_AllocTexture((u32)(width * height * 4));
    if (logo_tex_mem == NULL)
    {
        for (y = 0; y < (int)height; y++)
            free(rows[y]);
        free(rows);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return 0;
    }
    logo_offset = tiny3d_TextureOffset(logo_tex_mem);
    logo_w = (int)width;
    logo_h = (int)height;

    dst = (unsigned char *)logo_tex_mem;
    for (y = 0; y < (int)height; y++)
    {
        unsigned char *src = rows[y];
        for (x = 0; x < (int)width; x++)
        {
            unsigned char r = src[x * 4 + 0];
            unsigned char g = src[x * 4 + 1];
            unsigned char b = src[x * 4 + 2];
            unsigned char a = src[x * 4 + 3];
            dst[(y * (int)width + x) * 4 + 0] = a;
            dst[(y * (int)width + x) * 4 + 1] = r;
            dst[(y * (int)width + x) * 4 + 2] = g;
            dst[(y * (int)width + x) * 4 + 3] = b;
        }
    }

    for (y = 0; y < (int)height; y++)
        free(rows[y]);
    free(rows);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    return 1;
}

static void ps3ui_rect(float x, float y, float w, float h, float z, u32 color)
{
    tiny3d_SetPolygon(TINY3D_QUADS);
    tiny3d_VertexPos(x,     y,     z);
    tiny3d_VertexColor(color);
    tiny3d_VertexPos(x + w, y,     z);
    tiny3d_VertexPos(x + w, y + h, z);
    tiny3d_VertexPos(x,     y + h, z);
    tiny3d_End();
}

static void ps3ui_panel(float x, float y, float w, float h)
{
    ps3ui_rect(x, y, w, h, 64000.0f, UI_PANEL);
    ps3ui_rect(x, y, w, 1.0f, 63000.0f, UI_BORDER);
}

static void ps3ui_ttf_callback(u8 chr, u8 *bitmap, short *w, short *h,
                               short *y_correction)
{
    int cell_w = *w;
    int cell_h = *h;

    memset(bitmap, 0, (size_t)(cell_w * cell_h));
    *w = 0;
    *h = 0;
    *y_correction = 0;

    if (ft_face == NULL)
        return;

    if (FT_Load_Char(ft_face, (unsigned long)chr, FT_LOAD_RENDER))
        return;

    {
        FT_GlyphSlot g = ft_face->glyph;
        int gw = (int)g->bitmap.width;
        int gh = (int)g->bitmap.rows;
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
                bitmap[(top + y) * cell_w + (left + x)] =
                    g->bitmap.buffer[y * g->bitmap.pitch + x];
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
        NULL
    };
    u8 *tex_mem;
    int i;

    if (tiny3d_Init(1024 * 1024) != 0)
        return 0;

    tex_mem = tiny3d_AllocTexture(256 * 1024);
    if (tex_mem == NULL)
        return 0;

    if (FT_Init_FreeType(&ft_lib))
        return 0;

    for (i = 0; font_paths[i] != NULL; i++)
    {
        if (FT_New_Face(ft_lib, font_paths[i], 0, &ft_face) == 0)
            break;
    }

    if (ft_face == NULL)
        return 0;

    FT_Set_Pixel_Sizes(ft_face, 0, PS3UI_FONT_H);
    ResetFont();
    AddFontFromTTF(tex_mem, 32, 127, PS3UI_FONT_W, PS3UI_FONT_H,
                   ps3ui_ttf_callback);
    SetFontColor(UI_TEXT, 0x00000000u);
    SetFontSize(16, 16);

    ps3ui_load_logo();

    ui_active = 1;
    return 1;
}

void ps3ui_draw(void)
{
    player_t *p;
    unsigned int total_players;
    unsigned int tick;
    int ram_percent;
    int shown = 0;
    float row_y;
    const float left_x = 32.0f;
    const float left_w = 500.0f;
    const float right_x = 548.0f;
    const float right_w = 268.0f;

    if (!ui_active)
        return;

    total_players = (unsigned int)playerGetActiveCount();
    tick = (unsigned int)main_tick;
    ram_percent = percentageOfRamUsed();

    tiny3d_Clear(0xff000000, TINY3D_CLEAR_ALL);
    tiny3d_Project2D();

    /* Background */
    ps3ui_rect(0.0f, 0.0f, PS3UI_SCREEN_W, PS3UI_SCREEN_H,
               65535.0f, UI_BG);
    ps3ui_panel(left_x, 24.0f, 784.0f, 72.0f);

    if (logo_offset != 0)
    {
        tiny3d_SetTexture(0, logo_offset, (u32)logo_w, (u32)logo_h,
                          (u32)(logo_w * 4), TINY3D_TEX_FORMAT_A8R8G8B8,
                          TEXTURE_LINEAR);
        tiny3d_AlphaTest(1, 0, TINY3D_ALPHA_FUNC_GREATER);
        tiny3d_SetPolygon(TINY3D_QUADS);
        tiny3d_VertexPos(52.0f, 36.0f, 0.0f);
        tiny3d_VertexTexture(0.0f, 0.0f);
        tiny3d_VertexPos(92.0f, 36.0f, 0.0f);
        tiny3d_VertexTexture(1.0f, 0.0f);
        tiny3d_VertexPos(92.0f, 76.0f, 0.0f);
        tiny3d_VertexTexture(1.0f, 1.0f);
        tiny3d_VertexPos(52.0f, 76.0f, 0.0f);
        tiny3d_VertexTexture(0.0f, 1.0f);
        tiny3d_End();
        tiny3d_AlphaTest(0, 0, TINY3D_ALPHA_FUNC_ALWAYS);
    }

    SetFontColor(UI_TEXT, 0x00000000u);
    SetFontSize(24, 24);
    DrawFormatString(100.0f, 34.0f, "CELLCRAFT");

    SetFontSize(12, 12);
    SetFontColor(UI_GREEN, 0x00000000u);
    DrawFormatString(670.0f, 52.0f, "SERVER ONLINE");

    /* PLayers */
    ps3ui_panel(left_x, 112.0f, left_w, 326.0f);
    SetFontSize(15, 15);
    SetFontColor(UI_TEXT, 0x00000000u);
    DrawFormatString(50.0f, 128.0f, "CONNECTED PLAYERSS");

    SetFontSize(12, 12);
    SetFontColor(UI_GREEN, 0x00000000u);
    DrawFormatString(405.0f, 132.0f, "ONLINE %u", total_players);

    row_y = 168.0f;
    for (p = playerGetHead(); p != NULL && shown < PS3UI_MAX_PLAYERS_SHOWN;
         p = p->next)
    {
        const char *name;
        u32 row_color;

        if (!p->active)
            continue;

        name = (p->name[0] != '\0') ? p->name : "Unknown";
        row_color = (shown % 2 == 0) ? UI_ROW : UI_ROW_ALT;

        SetFontSize(13, 13);
        SetFontColor(UI_MUTED, 0x00000000u);
        DrawFormatString(61.0f, row_y + 3.0f, "%02d", shown + 1);

        SetFontColor(UI_TEXT, 0x00000000u);
        DrawFormatString(94.0f, row_y + 3.0f, "%.24s", name);

        shown++;
        row_y += 24.0f;
    }

    if (shown == 0)
    {
        SetFontSize(14, 14);
        SetFontColor(UI_MUTED, 0x00000000u);
        DrawFormatString(64.0f, 188.0f, "No players connected");
        SetFontSize(12, 12);
        DrawFormatString(64.0f, 212.0f, "Waiting for incoming connections...");
    }
    else if (total_players > (unsigned int)shown)
    {
        SetFontSize(11, 11);
        SetFontColor(UI_MUTED, 0x00000000u);
        DrawFormatString(50.0f, 414.0f, "+ %u more player(s) not shown",
                         total_players - (unsigned int)shown);
    }

    /* Server status */
    ps3ui_panel(right_x, 112.0f, right_w, 135.0f);
    SetFontSize(15, 15);
    SetFontColor(UI_TEXT, 0x00000000u);
    DrawFormatString(566.0f, 128.0f, "SERVER STATUS");

    SetFontSize(12, 12);
    SetFontColor(UI_MUTED, 0x00000000u);
    DrawFormatString(566.0f, 190.0f, "PORT");
    SetFontColor(UI_TEXT, 0x00000000u);
    DrawFormatString(704.0f, 190.0f, "%d", PORT);

    SetFontColor(UI_MUTED, 0x00000000u);
    DrawFormatString(566.0f, 214.0f, "MAIN TICK");
    SetFontColor(UI_TEXT, 0x00000000u);
    DrawFormatString(704.0f, 214.0f, "%u", tick);

    /* Memory */
    ps3ui_panel(right_x, 260.0f, right_w, 178.0f);
    SetFontSize(15, 15);
    SetFontColor(UI_TEXT, 0x00000000u);
    DrawFormatString(566.0f, 276.0f, "MEMORY USAGE");

    SetFontSize(25, 25);
    SetFontColor(ram_percent >= 90 ? UI_AMBER : UI_ACCENT, 0x00000000u);
    DrawFormatString(566.0f, 310.0f, "%d%%", ram_percent);

    SetFontSize(11, 11);
    SetFontColor(UI_MUTED, 0x00000000u);
    DrawFormatString(646.0f, 321.0f, "ALLOCATED");

    ps3ui_rect(566.0f, 347.0f, 234.0f, 10.0f,
               62000.0f, UI_BAR_BG);
    if (ram_percent > 0)
    {
        float fill_w = 234.0f * (float)ram_percent / 100.0f;
        u32 fill_color = (ram_percent >= 90) ? UI_AMBER : UI_ACCENT;
        ps3ui_rect(566.0f, 347.0f, fill_w, 10.0f,
                   60000.0f, fill_color);
    }

    /* Footer */
    ps3ui_rect(32.0f, 458.0f, 784.0f, 1.0f, 61000.0f, UI_BORDER);
    SetFontSize(11, 11);
    SetFontColor(UI_MUTED, 0x00000000u);
    DrawFormatString(718.0f, 474.0f, "0xagvz");

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
