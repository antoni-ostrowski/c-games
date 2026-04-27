#include "raylib.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

float clamp(float value, float min, float max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

typedef struct {
  Rectangle rect;
  bool active;
} Block;

Block block_create() {
  Block a = {
      .rect = {.x = GetRandomValue(0, 1920),
               .y = GetRandomValue(0, 40),
               .width = 10,
               .height = 10},
      .active = true,
  };
  return a;
}

int main() {
  printf("Hello World!\n");

  int32_t screenWidth = 1920;
  int32_t screenHeight = 1080;

  InitWindow(screenWidth, screenHeight, "breakout");
  SetTargetFPS(60);

  size_t block_count = 50;
  Block *blocks = malloc(block_count * sizeof(Block));
  for (size_t i = 0; i < block_count; i++) {
    blocks[i] = block_create();
  }

  Rectangle player = {.x = (float)screenWidth / 2,
                      .y = (float)screenHeight / 2,
                      .height = 20,
                      .width = 250};

  float speed = 30;
  int32_t score = 0;

  Vector2 ball = {.x = (float)screenWidth / 2,
                  .y = (float)screenHeight / 2 - 100};
  int ball_radius = 30;
  float ball_speed_x = 300;
  float ball_speed_y = 300;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    ball.x += ball_speed_x * dt;
    ball.y += ball_speed_y * dt;

    if (IsKeyDown(KEY_RIGHT))
      player.x += speed;

    if (IsKeyDown(KEY_LEFT))
      player.x -= speed;

    if (IsKeyPressed(KEY_R)) {
      for (size_t i = 0; i < block_count; i++) {
        blocks[i] = block_create();
      }
      score = 0;
    }

    if (CheckCollisionCircleRec(ball, ball_radius, player)) {
      ball_speed_y *= -1;
    }

    if (ball.x - ball_radius < 0 || ball.x + ball_radius > screenWidth) {
      ball_speed_x *= -1;
      ball.x = clamp(ball.x, ball_radius, screenWidth - ball_radius);
    }
    if (ball.y - ball_radius < 0 || ball.y + ball_radius > screenHeight) {
      ball_speed_y *= -1;
      ball.y = clamp(ball.y, ball_radius, screenHeight - ball_radius);
    }

    if (player.x < 0)
      player.x = 0;
    if (player.x + player.width > screenWidth)
      player.x = screenWidth - player.width;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (size_t i = 0; i < block_count; i++) {
      if (!blocks[i].active) {
        continue;
      }
      if (CheckCollisionRecs(player, blocks[i].rect)) {
        blocks[i].active = false;
        score++;
      }
      DrawRectangleRec(blocks[i].rect, RED);
    }

    DrawRectangleRec(player, BLUE);
    char scoreText[32];
    snprintf(scoreText, sizeof(scoreText), "%d; R for reset", score);
    DrawText(scoreText, 0, 0, 60, BLACK);
    DrawCircleV(ball, ball_radius, RED);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
