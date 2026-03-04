#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FRAME_DELAY 20
#define MIN_FRAME_DELAY 1

const unsigned int x = 1920;
const unsigned int y = 1080;
Color bg = {55, 53, 62, 255};
Color fg = {211, 218, 217, 220};

void DrawScreen(int sec) {

  /* ======================FONTS=================================== */
  Font RetroF = LoadFontEx("assets/fonts/Transcity DEMO.otf", 200, 0, 0);
  Font DreamerTM = LoadFontEx("assets/fonts/DreamerTM-Regular.ttf", 120, 0, 0);
  const char *retroText = "Be Right Back";
  Vector2 retroSize =
      MeasureTextEx(RetroF, retroText, (float)RetroF.baseSize, 2);
  /* =============================================================== */

  /* =========================Audios================================ */
  // TODO: Must Randomly Start at Some Point and Loop
  InitAudioDevice();
  Music song = LoadMusicStream("assets/aux/background.mp3");
  PlayMusicStream(song);

  /* =============================================================== */

  /* =================== GIFS======================================= */

  /* =============================================================== */

  float timer = 0.0f;
  /* Start Rendering the Timer */
  if (sec == -1) {
    sec = 0;

    /* Rendering the Window */
    while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(bg);
      UpdateMusicStream(song);
      char buf[99];
      sprintf(buf, "%02d:%02d", sec / 60, sec % 60);

      const char *dreamerText = buf;
      Vector2 dreamerSize =
          MeasureTextEx(DreamerTM, dreamerText, (float)DreamerTM.baseSize, 20);
      DrawTextEx(
          DreamerTM, dreamerText,
          (Vector2){(float)(x / 2 - dreamerSize.x / 2), (float)(y / 2 - 300)},
          (float)DreamerTM.baseSize, 20, fg);
      DrawTextEx(
          RetroF, retroText,
          (Vector2){(float)(x / 2 - retroSize.x / 2), (float)(y / 2 - 100)},
          (float)RetroF.baseSize, 2, fg);

      /* Increase sec when timer increases  */
      timer += GetFrameTime();
      if (timer >= 1.0f) {
        sec++;
        timer -= 1.0f;
      }
      EndDrawing();
    }
    CloseAudioDevice();
    return;
  }

  /* Rendering the Countdown */
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(bg);
    char buf[99];
    UpdateMusicStream(song);
    sprintf(buf, "%02d:%02d", sec / 60, sec % 60);
    const char *dreamerText = buf;
    Vector2 dreamerSize =
        MeasureTextEx(DreamerTM, dreamerText, (float)DreamerTM.baseSize, 20);
    DrawTextEx(
        DreamerTM, dreamerText,
        (Vector2){(float)(x / 2 - dreamerSize.x / 2), (float)(y / 2 - 300)},
        (float)DreamerTM.baseSize, 20, fg);

    DrawTextEx(
        RetroF, retroText,
        (Vector2){(float)(x / 2 - retroSize.x / 2), (float)(y / 2 - 100)},
        (float)RetroF.baseSize, 2, fg);
    /* Increase sec when timer increases  */
    timer += GetFrameTime();
    if (timer >= 1.0f) {
      sec--;
      timer -= 1.0f;
    }

    EndDrawing();
  }
  UnloadFont(DreamerTM);
}

int main(int argc, char *argv[]) {
  /* Help Menu */
  if (argc < 2) {
    printf("USAGE: holdup [hold | timer] [5]\n");
    exit(1);
  }

  InitWindow(x, y, "Hol' up");
  SetTargetFPS(60);
  /* Checks for the Arguments */
  if (strcmp(argv[1], "hold") == 0 || strcmp(argv[1], "hol") == 0) {
    if (argc == 2) {
      printf("Usage: holdup hold [time in min] -> eg: holdup hold 5\n");
      exit(1);
    }
    DrawScreen((atoi(argv[2]) * 60));
  }

  if (strcmp(argv[1], "timer") == 0) {
    DrawScreen(-1);
  }

  CloseWindow();
  return 0;
}
