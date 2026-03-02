#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

const unsigned int x = 1920;
const unsigned int y = 1080;


void DrawCountDown(unsigned int sec){
Font DreamerTM = LoadFont("assets/fonts/DreamerTM-Regular.ttf");
  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(BLACK);
    char buf[99];
    sprintf(buf, "%02d:%02d", sec/60, sec%60);
    DrawTextEx(DreamerTM, buf, (Vector2){ 100.0f, 100.0f}, 100.0f,30,MAROON );

    sleep(1);
    sec--;
    EndDrawing();
  }  
  UnloadFont(DreamerTM);
}

void DrawTimer(){
  unsigned int sec =0;
  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(BLACK);
    char buf[99];
    sprintf(buf, "%02d:%02d", sec/60, sec%60);
    DrawText(buf, x/2.5, y/3, 120, RAYWHITE);
    sleep(1);
    sec++;
    EndDrawing();
  }  
}

int main(int argc, char* argv[]){
  if(argc < 2){
    printf("USAGE: holdup [hold | timer] [5]\n");
    exit(1);
  }
    
  InitWindow(x,y, "Hol' up");
  SetTargetFPS(60);

  
  if (strcmp(argv[1], "hold") == 0){
      if (argc == 2) {
	printf("Usage: holdup hold [time in min] -> eg: holdup hold 5\n");
	exit(1);
      }

      DrawCountDown((atoi(argv[2]) * 60));
  }

  if(strcmp(argv[1], "timer") == 0){
    DrawTimer();    
  }

  CloseWindow();
  

  return 0;
}
