#ifndef SCREEN_H
#define SCREEN_H

#define SCREEN_WIDTH 2160
#define SCREEN_HEIGHT 1080
#define SCREEN_TOP 0
#define SCREEN_BOTTOM SCREEN_HEIGHT
#define SCREEN_RIGHT SCREEN_WIDTH
#define SCREEN_LEFT 0
#define FPS 60

void init(void);
void update(void);
void draw(void);
void cleanup(void);

#endif
