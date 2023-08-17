#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Hay 736 colores en el archivo PALETTES.DAT
#define PALETTE_COLORS 736

// Estructura de un color
typedef struct _color {
  uint8_t r, g, b; 
} color_t;

color_t colors[PALETTE_COLORS];

// Programa que convierte el archivo PALETTES.DAT a un archivo de paleta de GIMP
int main(int argc, char** argv)
{
  FILE* file = fopen("PALETTES.DAT", "rb");
  if (!file)
    return 1;

  fread(colors, sizeof(color_t), PALETTE_COLORS, file);
  fclose(file);

  fprintf(stdout, "GIMP Palette\nName: LOV.PAL\nColumns: 16\n#\n");
  for (uint32_t index = 0; index < PALETTE_COLORS; index++) {
    fprintf(stdout, "%d\t%d\t%d\tIndex %d\n", colors[index].r << 2, colors[index].g << 2, colors[index].b << 2, index);
  }
  return 0;
}
