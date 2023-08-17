#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define PALETTE_COLORS  736

#define CHARACTERS      120
#define TEXTNIBS        3840
#define PIXELS_WIDTH    16
#define PIXELS_HEIGHT   8
#define PIXELS          64

typedef struct _color {
  uint8_t r, g, b;
} color_t;

color_t colors[PALETTE_COLORS];
uint8_t widths[CHARACTERS] = {
  4, 4, 5, 7, 6, 7, 7, 4, 4, 4, 8, 6, 3, 6, 2, 7, 7, 6, 7, 7, 7, 7, 7, 7,
  7, 7, 2, 3, 7, 6, 4, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 6, 8, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7, 4, 7, 8, 3, 7, 7, 7, 7, 7, 7, 7,
  7, 3, 7, 7, 6, 8, 7, 7, 7, 8, 7, 7, 7, 7, 7, 8, 7, 7, 7, 7, 5, 7, 7, 0,
  3, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 0, 4, 0, 0, 4, 7, 7, 8, 7, 7, 7, 7, 0,
};
uint8_t textnibs[TEXTNIBS];
uint8_t pixels[PIXELS];

void put_pixel(uint8_t x, uint8_t y, uint8_t color) {
  pixels[y * PIXELS_WIDTH + x] = color;
}

void print_character(uint8_t *textnibs, uint8_t char_code) {
  const uint8_t height = 8;
  const uint8_t bytes_per_char = 32;

  uint8_t cx = 0;
  uint8_t cy = 0;
  uint8_t index = char_code - 32;
  for (uint8_t y = 0; y < height; y++) {
    // ÑAAAAAARGH!
    uint32_t offset = index * bytes_per_char + y * 4;
    uint16_t cy = y;
    uint8_t width = widths[index];
    while (width > 0) {
      uint8_t current = textnibs[offset];
      uint8_t first_nibble = (current & 0xf0) >> 4;
      if (first_nibble != 0) {
        put_pixel(cx, cy, first_nibble);
      }

      cx++;
      width--;
      if (width > 0) {
        uint8_t second_nibble = current & 0x0f;
        if (second_nibble != 0) {
          put_pixel(cx, cy, second_nibble);
        }
        cx++;
        width--;
      }

      offset++;
    }

    cx = 0;
  }

  fprintf(stdout, "P3\n# (%c) textnibs.dat\n16 8\n255\n", char_code);
  for (uint8_t y = 0; y < PIXELS_HEIGHT; y++) {
    for (uint8_t x = 0; x < PIXELS_WIDTH; x++) {
      uint32_t offset = y * PIXELS_WIDTH + x;
      uint32_t pixel = pixels[offset];
      fprintf(stdout, "%d %d %d ", colors[pixel].r << 2, colors[pixel].g << 2, colors[pixel].b << 2);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char** argv)
{
  FILE* file = fopen("PALETTES.DAT", "rb");
  if (!file)
    return 1;

  fread(colors, sizeof(color_t), PALETTE_COLORS, file);
  fclose(file);

  file = fopen("TEXTNIBS.DAT", "rb");
  if (!file)
    return 1;

  fread(textnibs, sizeof(uint8_t), TEXTNIBS, file);
  fclose(file);

  print_character(textnibs, argv[1][0]);

  return 0;
}
