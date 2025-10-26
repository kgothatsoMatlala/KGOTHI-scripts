#include <iostream>
#include "raylib.h"

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrames){
    //update runningTime
    data.runningTime+= deltaTime;
    if(data.runningTime >= data.updateTime){
        data.runningTime = 0.0;
        //update animation frame
        data.rec.x = data.frame*data.rec.width;
        data.frame++;
        if(data.frame > maxFrames){
            data.frame = 0;
        }
    }
    return data;
}

int main(){
    int winheight = 600;
    int winwidth = 1200;
    InitWindow(winwidth, winheight, "King");

    //king variables
    Texture2D king0 = LoadTexture("Textures/The King.png");
    Texture2D king1 = LoadTexture("Textures/The King-Dance.png");
    Texture2D king2 = LoadTexture("Textures/The King-Dance3.png");
    Texture2D kings[3] ={
        king0, king1, king2
    };

    
    AnimData kingDatas[3]{};
    
    for(int i = 0; i < 3; ++i){
        kingDatas[i].rec.height = kings[i].height;
        kingDatas[i].rec.x = 0;
        kingDatas[i].rec.y = 0;

        kingDatas[i].pos.x = winwidth/2 - kingDatas[i].rec.width/2;
        kingDatas[i].pos.y = winheight- kingDatas[i].rec.height;

        kingDatas[i].frame = 0;
        kingDatas[i].updateTime = 1.0/12.0;
        kingDatas[i].runningTime = 0.0;
    }
    kingDatas[0].rec.width = kings[0].width;
    kingDatas[1].rec.width = kings[1].width/6;
    kingDatas[2].updateTime = 1.0/6.0;
    kingDatas[2].rec.width = kings[2].width/4;

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        //delta Time (time since last frame)
        const float dT{GetFrameTime()};
        if(IsKeyDown(KEY_S)){
            kingDatas[1] = updateAnimData(kingDatas[1], dT, 6);
            DrawTextureRec(kings[1], kingDatas[1].rec, kingDatas[1].pos, WHITE);
        }
        else if(IsKeyDown(KEY_W)){
            kingDatas[2] = updateAnimData(kingDatas[2], dT, 5);
            DrawTextureRec(kings[2], kingDatas[2].rec, kingDatas[2].pos, WHITE);
        }
        else{
            DrawTextureRec(kings[0], kingDatas[0].rec, kingDatas[0].pos, WHITE);
        }
        
        EndDrawing();
    }
    UnloadTexture(king0);
    UnloadTexture(king1);
    UnloadTexture(king2);

    return 0;
}