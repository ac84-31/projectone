#include "CS3113/cs3113.h"
#include <string>
#include <math.h>

/**
* Author: Alaya Chowdhury
* Assignment: Simple 2D Scene
* Date due: 2025-09-27, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

// Global variables
constexpr int   SCREEN_WIDTH  = 1600 / 2;
constexpr int   SCREEN_HEIGHT = 1000 / 2;
constexpr int   FPS           = 60;
constexpr float BASE_SIZE     = 100.0f;
constexpr float MAX_AMP       = 0.25f;
constexpr float RADIUS        = 200.0f;
AppStatus gAppStatus     = RUNNING;
float     gPreviousTicks = 0.0f;
float     gPulseTime     = 0.0f;
float     gOrbitAngle    = 0.0f;

constexpr char objectone[]   = "assets/pyramid.jpeg";
constexpr char objecttwo[]   = "assets/program.jpeg";
constexpr char objectthree[] = "assets/sewing.jpeg";

// Pulsing 
Texture2D obj1Texture;
float     obj1Scale   = 1.0f;
float     obj1Rotation = 0.0f;
Vector2   obj1Position = {60.0f, SCREEN_HEIGHT / 2.0f + 180.0f};

// Rotating 
Texture2D obj2Texture;
float     obj2Scale   = 1.0f;
float     obj2Rotation = 0.0f;
Vector2   obj2Position = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

// Orbiting 
Texture2D obj3Texture;
float     obj3Scale   = 1.0f;
float     obj3Rotation = 0.0f;
Vector2   obj3Position = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

void initialise() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project One");
    SetTargetFPS(FPS);

    obj1Texture = LoadTexture(objectone);
    obj2Texture = LoadTexture(objecttwo);
    obj3Texture = LoadTexture(objectthree);

    gPreviousTicks = GetTime();
}

void processInput() {
    if (WindowShouldClose()) {
        gAppStatus = TERMINATED;
    }
}

void update() {
    float currentTicks = GetTime();
    float deltaTime = currentTicks - gPreviousTicks;
    gPreviousTicks = currentTicks;

    gPulseTime += deltaTime;

    // pulsing
    obj1Scale = 1.0f + MAX_AMP * cos(gPulseTime * 2.0f);

    // rotating
    obj2Rotation += 60.0f * deltaTime;

    // orbiting
    gOrbitAngle += 1.5f * deltaTime;
    obj3Position.x = SCREEN_WIDTH / 2 + cos(gOrbitAngle) * RADIUS;
    obj3Position.y = SCREEN_HEIGHT / 2 + sin(gOrbitAngle) * RADIUS;
}

void render() {
    BeginDrawing();
    ClearBackground(ColorFromHex("#000000"));

    // pulsing
    Rectangle textureArea = { 0.0f, 0.0f, (float)obj1Texture.width, (float)obj1Texture.height };
    Rectangle destinationArea = {
        obj1Position.x,
        obj1Position.y,
        BASE_SIZE * obj1Scale,
        BASE_SIZE * obj1Scale
    };
    // Origin inside the source texture (centre of the texture)
    Vector2 origin = {
        destinationArea.width / 2.0f,
        destinationArea.height / 2.0f
    };
    DrawTexturePro(obj1Texture, textureArea, destinationArea, origin, obj1Rotation, WHITE);

    // rotating
    textureArea = { 0.0f, 0.0f, (float)obj2Texture.width, (float)obj2Texture.height };
    destinationArea = {
        obj2Position.x,
        obj2Position.y,
        BASE_SIZE * obj2Scale,
        BASE_SIZE * obj2Scale
    };
    // Origin inside the source texture (centre of the texture)
    origin = {
        destinationArea.width / 2.0f,
        destinationArea.height / 2.0f
    };
    DrawTexturePro(obj2Texture, textureArea, destinationArea, origin, obj2Rotation, WHITE);

    // orbiting
    textureArea = { 0.0f, 0.0f, (float)obj3Texture.width, (float)obj3Texture.height };
    destinationArea = {
        obj3Position.x,
        obj3Position.y,
        BASE_SIZE * obj3Scale,
        BASE_SIZE * obj3Scale
    };
    // Origin inside the source texture (centre of the texture)
    origin = {
        destinationArea.width / 2.0f,
        destinationArea.height / 2.0f
    };
    DrawTexturePro(obj3Texture, textureArea, destinationArea, origin, obj3Rotation, WHITE);

    EndDrawing();
}

void shutdown() {
    CloseWindow();
}

int main(void) {
    initialise();

    while (gAppStatus == RUNNING) {
        processInput();
        update();
        render();
    }

    shutdown();
    return 0;
}
