#include "screen.h"
#include <raylib.h>

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particles");
  SetTargetFPS(FPS);
  init();

  while (!WindowShouldClose()) {
    update();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw();
    EndDrawing();
  }

  CloseWindow();
  cleanup();

  return 0;
}
