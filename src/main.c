#include <raylib.h>
#include "screen.h"

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particles");
  SetTargetFPS(FPS);
  init();

  while (!WindowShouldClose()) {
    update();
    BeginDrawing();
    draw();
    EndDrawing();
  }

  CloseWindow();
  cleanup();

  return 0;
}
