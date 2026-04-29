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

int main() {
  printf("Hello World!\n");

  size_t screenWidth = 1920;
  size_t screenHeight = 1080;

  InitWindow(screenWidth, screenHeight, "breakout");
  SetTargetFPS(60);

  size_t block_count = 60;
  size_t block_width = 40;
  size_t block_height = 30;
  size_t curr_y_offset = 0;
  size_t curr_x_offset = 0;
  Block *blocks = malloc(block_count * sizeof(Block));
  for (size_t i = 0; i < block_count; i++) {
    if (curr_x_offset > screenWidth - 100) {
      curr_x_offset = 0;
      curr_y_offset += block_height + 10;
    } else {
      curr_x_offset += block_width + 10;
    }
    Block a = {
        .rect = {.x = curr_x_offset,
                 .y = curr_y_offset,
                 .width = block_width,
                 .height = block_height},
        .active = true,
    };

    blocks[i] = a;
  }

  Rectangle player = {.x = (float)screenWidth / 2,
                      .y = (float)screenHeight - 40,
                      .height = 20,
                      .width = 250};

  float speed = 30;

  Vector2 ball = {.x = (float)screenWidth / 2,
                  .y = (float)screenHeight / 2 - 100};
  int ball_radius = 30;
  float ball_speed_x = 500;
  float ball_speed_y = 500;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    ball.x += ball_speed_x * dt;
    ball.y += ball_speed_y * dt;

    if (IsKeyDown(KEY_RIGHT))
      player.x += speed;

    if (IsKeyDown(KEY_LEFT))
      player.x -= speed;

    if (CheckCollisionCircleRec(ball, ball_radius, player)) {
      ball_speed_y *= -1;
    }

    bool ball_is_touching_botton = ball.y + ball_radius > screenHeight;
    bool ball_is_touching_top = ball.y - ball_radius < 0;
    bool ball_is_touching_left = ball.x - ball_radius < 0;
    bool ball_is_touching_right = ball.x + ball_radius > screenWidth;

    if (ball_is_touching_left || ball_is_touching_right) {
      ball_speed_x *= -1;
      ball.x = clamp(ball.x, ball_radius, screenWidth - ball_radius);
    }
    if (ball_is_touching_top) {
      ball_speed_y *= -1;
      ball.y = clamp(ball.y, ball_radius, screenHeight - ball_radius);
    }
    if (ball_is_touching_botton) {
      return 0;
    }

    if (player.x < 0)
      player.x = 0;
    if (player.x + player.width > screenWidth)
      player.x = screenWidth - player.width;

    for (size_t i = 0; i < block_count; i++) {
      if (!blocks[i].active) {
        continue;
      }
      if (CheckCollisionCircleRec(ball, ball_radius, blocks[i].rect)) {
        blocks[i].active = false;
        ball_speed_y *= -1;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (size_t i = 0; i < block_count; i++) {
      if (!blocks[i].active) {
        continue;
      }
      DrawRectangleRec(blocks[i].rect, RED);
    }

    DrawRectangleRec(player, BLUE);
    DrawCircleV(ball, ball_radius, RED);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
