#include "screen.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#define ACCELERATION 0.1f
#define RADIUS 5.0f
#define PARTICLE_COUNT 1
#define FONT_SIZE 19
#define TITLE "Particle Sim"
#define DAMPING 0.9f

struct Particle {
  Vector2 position;
  Vector2 velocity;
  Vector2 acceleration;
  float radius;
};

struct Particle *particles;

void init() {
  particles = malloc(sizeof(struct Particle) * PARTICLE_COUNT);

  for (int i = 0; i < PARTICLE_COUNT; i++) {
    struct Particle particle = {
        .position = {GetRandomValue(SCREEN_LEFT, SCREEN_RIGHT),
                     GetRandomValue(SCREEN_TOP, SCREEN_BOTTOM)},
        .velocity = {0, 0},
        .radius = RADIUS,
        .acceleration = {0, 0}};
    particles[i] = particle;
  }
}

void update() {
  Vector2 mousePos = GetMousePosition();
  for (int i = 0; i < PARTICLE_COUNT; i++) {
    struct Particle *particle = &particles[i];
    Vector2 particlePos = particle->position;

    if (IsMouseButtonDown(0)) {
      Vector2 direction = {mousePos.x - particlePos.x,
                           mousePos.y - particlePos.y};
      float length =
          sqrt(direction.x * direction.x + direction.y * direction.y);

      if (length > 0) {
        particle->acceleration.x = (direction.x / length) * ACCELERATION;
        particle->acceleration.y = (direction.y / length) * ACCELERATION;
      }
    } else {
      particle->acceleration.x = 0;
      particle->acceleration.y = 0;
    }

    if (particlePos.x >= SCREEN_RIGHT - particle->radius) {
      particle->position.x = SCREEN_RIGHT - particle->radius;
      particle->velocity.x = -particle->velocity.x;
      particle->velocity.x *= DAMPING;
    }

    if (particlePos.x <= SCREEN_LEFT + particle->radius) {
      particle->position.x = SCREEN_LEFT + particle->radius;
      particle->velocity.x = -particle->velocity.x;
      particle->velocity.x *= DAMPING;
    }

    if (particlePos.y <= SCREEN_TOP + particle->radius) {
      particle->position.y = SCREEN_TOP + particle->radius;
      particle->velocity.y = -particle->velocity.y;
      particle->velocity.y *= DAMPING;
    }

    if (particlePos.y >= SCREEN_BOTTOM - particle->radius) {
      particle->position.y = SCREEN_BOTTOM - particle->radius;
      particle->velocity.y = -particle->velocity.y;
      particle->velocity.y *= DAMPING;
    }

    particle->velocity.x += particle->acceleration.x;
    particle->velocity.y += particle->acceleration.y;

    particle->position.x += particle->velocity.x;
    particle->position.y += particle->velocity.y;
  }
}

void draw() {
  Vector2 mousePos = GetMousePosition();
  int textWidth = MeasureText(TITLE, FONT_SIZE);
  DrawText(TITLE, (SCREEN_WIDTH - textWidth) / 2, SCREEN_TOP, FONT_SIZE, BLACK);
  for (int i = 0; i < PARTICLE_COUNT; i++) {
    struct Particle *particle = &particles[i];
    if (IsMouseButtonDown(0)) {
      DrawLine(mousePos.x, mousePos.y, particle->position.x,
               particle->position.y, GRAY);
    }

    DrawCircle(particle->position.x, particle->position.y, particle->radius,
               BLACK);
  }
}

void cleanup() { free(particles); }
