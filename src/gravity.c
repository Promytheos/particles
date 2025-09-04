#include "screen.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#define G 0.06f
#define STARTING_PLANETS 1
#define MAX_PLANETS 50
#define MIN_RADIUS 1.0f
#define MAX_RADIUS 10.0f
#define MIN_VELOCITY -10.0f
#define MAX_VELOCITY 10.0f
#define MIN_DENSITY 0.2f
#define MAX_DENSITY 3.0f
#define FONT_SIZE 19
#define SOFTENING 3.0f
#define DAMPING 0.5f
#define TITLE "Planets Sim"

struct Planet {
  Vector2 position;
  float radius;
  Vector2 velocity;
  float mass;
  float density;
  Vector2 gravityVector;
};

struct Planet *planets;
int num_planets;
struct Planet create_planet(float x, float y);
float getRandomValuef(float min, float max);

void init() {
  planets = malloc(sizeof(struct Planet) * MAX_PLANETS);
  num_planets = STARTING_PLANETS;

  for (int i = 0; i < num_planets; i++) {
    struct Planet planet =
        create_planet(getRandomValuef(SCREEN_LEFT, SCREEN_RIGHT),
                      getRandomValuef(SCREEN_TOP, SCREEN_BOTTOM));

    planets[i] = planet;
  }
}

float getRandomValuef(float min, float max) {
  float multiplier = max - min;
  return min + multiplier * ((float)rand() / RAND_MAX);
}

struct Planet create_planet(float x, float y) {
  float radius = getRandomValuef(MIN_RADIUS, MAX_RADIUS);
  float density = getRandomValuef(MIN_DENSITY, MAX_DENSITY);
  float velocityX = getRandomValuef(-3.0, 3.0);
  float velocityY = getRandomValuef(-3.0, 3.0);
  struct Planet planet = {.position = {x, y},
                          .radius = radius,
                          .velocity = {velocityX, velocityY},
                          .density = density,
                          .gravityVector = Vector2Zero(),
                          .mass =
                              (4.0f / 3.0f) * PI * pow(radius, 3) * density};

  return planet;
}

float calculateGravityBetween(struct Planet *planet_a,
                              struct Planet *planet_b) {
  return G * planet_a->mass * planet_b->mass /
         pow(fmaxf(Vector2Distance(planet_a->position, planet_b->position),
                   SOFTENING + planet_a->radius + planet_b->radius),
             2);
}

void update() {
  if (IsMouseButtonPressed(0)) {
    Vector2 mousePos = GetMousePosition();
    if (num_planets < MAX_PLANETS) {
      planets[num_planets] = create_planet(mousePos.x, mousePos.y);
      num_planets++;
    }
  }

  for (int i = 0; i < num_planets; i++) {
    struct Planet *planet_i = &planets[i];
    Vector2 netForce = Vector2Zero();
    for (int j = 0; j < num_planets; j++) {
      struct Planet *planet_j = &planets[j];
      if (i != j) {
        float gravityForce = calculateGravityBetween(planet_i, planet_j);
        Vector2 distanceVector = {planet_j->position.x - planet_i->position.x,
                                  planet_j->position.y - planet_i->position.y};
        float distanceMag =
            fmaxf(Vector2Length(distanceVector),
                  SOFTENING + planet_i->radius + planet_j->radius);
        Vector2 gravityVector =
            Vector2Scale(distanceVector, gravityForce / distanceMag);
        netForce = Vector2Add(netForce, gravityVector);
      }
    }
    planet_i->gravityVector = netForce;

    Vector2 acceleration = {netForce.x / planet_i->mass,
                            netForce.y / planet_i->mass};
    planet_i->velocity.x += acceleration.x;
    planet_i->velocity.y += acceleration.y;
  }
  // update positions
  for (int i = 0; i < num_planets; i++) {
    struct Planet *planet = &planets[i];
    if (planet->position.x >= SCREEN_RIGHT - planet->radius) {
      planet->position.x = SCREEN_RIGHT - planet->radius;
      planet->velocity.x = -planet->velocity.x;
      planet->velocity.x *= DAMPING;
    }

    if (planet->position.x <= SCREEN_LEFT + planet->radius) {
      planet->position.x = SCREEN_LEFT + planet->radius;
      planet->velocity.x = -planet->velocity.x;
      planet->velocity.x *= DAMPING;
    }

    if (planet->position.y <= SCREEN_TOP + planet->radius) {
      planet->position.y = SCREEN_TOP + planet->radius;
      planet->velocity.y = -planet->velocity.y;
      planet->velocity.y *= DAMPING;
    }

    if (planet->position.y >= SCREEN_BOTTOM - planet->radius) {
      planet->position.y = SCREEN_BOTTOM - planet->radius;
      planet->velocity.y = -planet->velocity.y;
      planet->velocity.y *= DAMPING;
    }
    planet->position.x += planet->velocity.x;
    planet->position.y += planet->velocity.y;
  }
}

void draw() {
  int textWidth = MeasureText(TITLE, FONT_SIZE);
  DrawText(TITLE, (SCREEN_WIDTH / 2 - textWidth), SCREEN_TOP, FONT_SIZE, BLACK);
  for (int i = 0; i < num_planets; i++) {
    struct Planet *planet = &planets[i];
    DrawCircleV(planet->position, planet->radius, BLACK);
    DrawLine(planet->position.x, planet->position.y,
             planet->position.x + planet->gravityVector.x,
             planet->position.y + planet->gravityVector.y, GRAY);
  }
}

void cleanup() { free(planets); }
