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
  size_t screenWidth = 1500;
  size_t screenHeight = 1100;

  InitWindow(screenWidth, screenHeight, "breakout");
  SetTargetFPS(60);

  // we use simple array, but treat it
  // in terms of rows and cols
  size_t cols = 30;
  size_t rows = 10;
  size_t block_count = cols * rows;
  size_t block_width = 60;
  size_t block_height = 20;

  Block *blocks = malloc(block_count * sizeof(Block));

  for (size_t i = 0; i < block_count; i++) {
    // remainder from div gives what col we are in
    size_t col = i % cols;
    // skipping remainder gives what row we are in
    size_t row = i / cols;
    Block a = {
        .rect = {.x = col * (block_width + 10),
                 .y = row * (block_height + 10),
                 .width = block_width,
                 .height = block_height},
        .active = true,
    };

    blocks[i] = a;
  }

  size_t player_width = 250;
  size_t player_height = 20;
  Rectangle player = {.x = (float)screenWidth / 2,
                      .y = (float)screenHeight - 40,
                      .height = player_height,
                      .width = player_width};

  float speed = 30;

  Vector2 ball = {.x = (float)screenWidth / 2, .y = (float)screenHeight - 150};
  int ball_radius = 30;
  float ball_speed_x = 580;
  float ball_speed_y = 580;

  while (!WindowShouldClose()) {
    float prev_player_x = player.x;
    float prev_ball_x = ball.x;
    float dt = GetFrameTime();
    ball.x += ball_speed_x * dt;
    ball.y += ball_speed_y * dt;

    bool player_is_moving_right = IsKeyDown(KEY_RIGHT);
    bool player_is_moving_left = IsKeyDown(KEY_LEFT);

    if (player_is_moving_right)
      player.x += speed;

    if (player_is_moving_left)
      player.x -= speed;

    float player_vel_x = player.x - prev_player_x;
    float ball_vel_x = ball.x - prev_ball_x;

    if (CheckCollisionCircleRec(ball, ball_radius, player)) {
      ball_speed_y *= -1;
      ball.y = player.y - ball_radius;
      if (player_vel_x < 0 && ball_vel_x > 0) {
        ball_speed_x *= -1;
      }

      if (player_vel_x > 0 && ball_vel_x < 0) {
        ball_speed_x *= -1;
      }
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

  free(blocks);
  CloseWindow();

  return 0;
}
