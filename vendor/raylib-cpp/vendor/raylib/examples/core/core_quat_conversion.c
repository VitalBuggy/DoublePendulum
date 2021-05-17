/*******************************************************************************************
*
*   raylib [core] example - quat conversions
*
*   Welcome to raylib!
*
*	generally you should really stick to eulers OR quats...
*   This tests that various conversions are equivilant.
*
*   You can find all basic examples on [C:\raylib\raylib\examples] directory and
*   raylib official webpage: [www.raylib.com]
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#ifndef PI2
	#define PI2 PI*2
#endif

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - quat conversions");
    
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type

    Mesh msh = GenMeshCylinder(.2, 1, 32); 
    Model mod = LoadModelFromMesh(msh);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

	Quaternion q1;
	Matrix m1,m2,m3,m4;
	Vector3 v1,v2;
	
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if (!IsKeyDown(KEY_SPACE)) {
            v1.x += 0.01;
            v1.y += 0.03;
            v1.z += 0.05;
        }
            
        if (v1.x > PI2) v1.x-=PI2;
        if (v1.y > PI2) v1.y-=PI2;
        if (v1.z > PI2) v1.z-=PI2;
        
        q1 = QuaternionFromEuler(v1.x, v1.y, v1.z);
        m1 = MatrixRotateZYX(v1);
        m2 = QuaternionToMatrix(q1);

        q1 = QuaternionFromMatrix(m1);
        m3 = QuaternionToMatrix(q1);
        
        v2 = QuaternionToEuler(q1);       
        v2.x*=DEG2RAD; v2.y*=DEG2RAD; v2.z*=DEG2RAD; 
        
        m4 = MatrixRotateZYX(v2);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode3D(camera);

                mod.transform = m1;
                DrawModel(mod, (Vector3){-1,0,0},1.0,RED);
                mod.transform = m2;
                DrawModel(mod, (Vector3){1,0,0},1.0,RED);
                mod.transform = m3;
                DrawModel(mod, (Vector3){0,0,0},1.0,RED);
                mod.transform = m4;
                DrawModel(mod, (Vector3){0,0,-1},1.0,RED);


                DrawGrid(10, 1.0f);
 
            EndMode3D();
        
            if (v2.x<0) v2.x+=PI2;
            if (v2.y<0) v2.y+=PI2;
            if (v2.z<0) v2.z+=PI2;
            
            Color cx,cy,cz;
            cx=cy=cz=BLACK;
            if (v1.x == v2.x) cx = GREEN;
            if (v1.y == v2.y) cy = GREEN;
            if (v1.z == v2.z) cz = GREEN;
            
            DrawText(TextFormat("%2.3f",v1.x),20,20,20,cx);
            DrawText(TextFormat("%2.3f",v1.y),20,40,20,cy);
            DrawText(TextFormat("%2.3f",v1.z),20,60,20,cz);

        
            DrawText(TextFormat("%2.3f",v2.x),200,20,20,cx);
            DrawText(TextFormat("%2.3f",v2.y),200,40,20,cy);
            DrawText(TextFormat("%2.3f",v2.z),200,60,20,cz);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
