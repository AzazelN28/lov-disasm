#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAP_WIDTH 85
#define MAP_HEIGHT 128
#define MAP_STRIDE 256

uint8_t map[MAP_STRIDE * MAP_HEIGHT];

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "rb");
  if (!file)
    return 1;

  fread(map, 1, MAP_STRIDE * MAP_HEIGHT, file);
  fclose(file);

  fprintf(stdout, "P2\n%d %d\n3\n", MAP_WIDTH, MAP_HEIGHT);
  for (int y = 0; y < MAP_HEIGHT; ++y) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
      uint8_t tile = map[y * MAP_STRIDE + x];
      uint8_t collision = tile & 0x03;
      fprintf(stdout, "%d ", collision);
    }
    fprintf(stdout, "\n");
  }

  return 0;
}
