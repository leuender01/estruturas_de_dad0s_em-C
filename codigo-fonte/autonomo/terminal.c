#include <stdio.h>
#include <raylib.h>


#define WIDHT 1000
#define HEIGHT 500

int main(void)
{
    
    
    InitWindow(WIDHT, HEIGHT, "PRIMEIRA TELA");
    SetTargetFPS(60);

    Vector2 position = {0};
    Vector2 positioncube = {WIDHT / 2, HEIGHT / 2};
    Vector2 sizecube = {50, 50};

    Rectangle quadrado = {(int)(WIDHT / 2),(int)( HEIGHT / 2), 50, 50};

    Camera2D camera = {0};
    camera.target = (Vector2){positioncube.x + 20, positioncube.y + 20};
    camera.offset = (Vector2){positioncube.x, positioncube.y};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;




    int time = 19;
    while(!WindowShouldClose())
    {
        if(time <= 19){
            time++;
        }else{
            positioncube.y = HEIGHT / 2;
        }
        ClearBackground(BLACK);
        if(IsKeyDown(KEY_UP) && (positioncube.y == HEIGHT / 2)){
            positioncube.y += -20;
            time = 0;
        }
        if(IsKeyDown(KEY_RIGHT)) positioncube.x += 2;
        if(IsKeyDown(KEY_LEFT)) positioncube.x += -2;
        camera.target = (Vector2){positioncube.x + 20, positioncube.y + 20};

        BeginDrawing();
        
            BeginMode2D(camera);
                DrawRectangle(-6000, 250 + sizecube.y, 13000, 8000, DARKGRAY);

                DrawRectangleV(positioncube, sizecube, RED);

            DrawRectangleRec(quadrado, YELLOW);
            EndMode2D();

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
