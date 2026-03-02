#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

const unsigned int x = 1920;
const unsigned int y = 1080;
Color bg = {55, 53, 62, 255};
Color fg = {211,218, 217, 200};
void DrawCountDown(unsigned int sec){
  Font RetroF = LoadFontEx("assets/fonts/Transcity DEMO.otf", 200, 0, 0);
  Font DreamerTM = LoadFontEx("assets/fonts/DreamerTM-Regular.ttf",  120, 0, 0);
  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(bg);
    char buf[99];
    sprintf(buf, "%02d:%02d", sec/60, sec%60);

    const char* dreamerText = buf; 
    Vector2 dreamerSize = MeasureTextEx(DreamerTM, dreamerText, (float)DreamerTM.baseSize, 20);
    DrawTextEx(DreamerTM, dreamerText, 
	       (Vector2){ (float)(x/2 - dreamerSize.x/2), (float)(y/2 - 300) }, 
	       (float)DreamerTM.baseSize, 20, fg);
    

    const char* retroText = "Be Right Back";
    Vector2 retroSize = MeasureTextEx(RetroF, retroText, (float)RetroF.baseSize, 2);
    DrawTextEx(RetroF, retroText, 
	       (Vector2){ (float)(x/2 - retroSize.x/2), (float)(y/2 - 100) }, 
	       (float)RetroF.baseSize, 2, fg);
    sleep(1);
    sec--;
    EndDrawing();
  }  
  UnloadFont(DreamerTM);
}

void DrawTimer(){
  Font RetroF = LoadFontEx("assets/fonts/Transcity DEMO.otf", 200, 0, 0);
  Font DreamerTM = LoadFontEx("assets/fonts/DreamerTM-Regular.ttf",  120, 0, 0);
  unsigned int sec =0;
  while(!WindowShouldClose()){
    BeginDrawing();

    ClearBackground(bg);
    char buf[99];
    sprintf(buf, "%02d:%02d", sec/60, sec%60);
    const char* dreamerText = buf; 
    Vector2 dreamerSize = MeasureTextEx(DreamerTM, dreamerText, (float)DreamerTM.baseSize, 20);
    DrawTextEx(DreamerTM, dreamerText, 
	       (Vector2){ (float)(x/2 - dreamerSize.x/2), (float)(y/2 - 300) }, 
	       (float)DreamerTM.baseSize, 20, fg);
    
  const char* retroText = "Be Right Back";
  Vector2 retroSize = MeasureTextEx(RetroF, retroText, (float)RetroF.baseSize, 2);
  DrawTextEx(RetroF, retroText, 
	     (Vector2){ (float)(x/2 - retroSize.x/2), (float)(y/2 - 100) }, 
	     (float)RetroF.baseSize, 2, fg);
  

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
