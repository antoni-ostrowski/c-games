#include "raylib.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Rectangle rect;
  bool active;
} Block;

Block block_create() {
  Block a = {
      .rect = {.x = GetRandomValue(0, 1920),
               .y = GetRandomValue(0, 1080),
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

  size_t block_count = 3000;
  Block *blocks = malloc(block_count * sizeof(Block));
  for (size_t i = 0; i < block_count; i++) {
    blocks[i] = block_create();
  }

  Rectangle player = {.x = (float)screenWidth / 2,
                      .y = (float)screenHeight / 2,
                      .height = 60,
                      .width = 60};
  float speedAmount = 20;
  int32_t score = 0;

  while (!WindowShouldClose()) {

    if (IsKeyDown(KEY_RIGHT))
      player.x += speedAmount;

    if (IsKeyDown(KEY_LEFT))
      player.x -= speedAmount;

    if (IsKeyDown(KEY_DOWN))
      player.y += speedAmount;

    if (IsKeyDown(KEY_UP))
      player.y -= speedAmount;

    if (IsKeyPressed(KEY_R)) {
      for (size_t i = 0; i < block_count; i++) {
        blocks[i] = block_create();
      }
      score = 0;
    }

    if (IsKeyDown(KEY_U)) {
      player.height += 8;
      player.width += 8;
    }
    if (IsKeyDown(KEY_D)) {
      player.height -= 8;
      player.width -= 8;
    }

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

    if (player.x < 0)
      player.x = 0;
    if (player.x + player.width > screenWidth)
      player.x = screenWidth - player.width;
    if (player.y < 0)
      player.y = 0;
    if (player.y + player.height > screenHeight)
      player.y = screenHeight - player.height;

    DrawRectangleRec(player, BLUE);
    char scoreText[32];
    snprintf(scoreText, sizeof(scoreText), "%d; R for reset; U/D for size",
             score);
    DrawText(scoreText, 0, 0, 60, BLACK);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
