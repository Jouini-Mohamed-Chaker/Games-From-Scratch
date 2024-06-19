#include "raylib.h"
#include "GameConfig.h"

using namespace std;
using namespace GameConfig;

//************************Global variables ********************************

int PlayerScore = 0;
int BotScore = 0;

Color Green = Color{38,185,154,255};
Color DarkGreen = Color{20,160,133,255};
Color LightGreen = Color{129,204,184,255};
Color Yellow = Color{243,213,91,255};

//*********************Classes ****************************************

class Ball {
public:
  float x, y;
  int vx, vy;
  int radius = CircleRadius;

  void draw() {
    DrawCircle(x, y, CircleRadius, Yellow);
  }

  void update() {
    x += vx;
    y += vy;

    if ((y + radius >= screenHeight) || (y - radius <= 0)) {
      vy *= -1;
    }
  }
};

class Paddle {
public:
  float x, y;
  float width = RectWidth, height = RectHeight;
  const int vy = RectSpeed;

  void draw() {
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
  }

  void update() {
    if (IsKeyDown(KEY_UP)) {
      y -= vy;
    }
    if (IsKeyDown(KEY_DOWN)) {
      y += vy;
    }

    LimitMovement();
  }

protected:
  void LimitMovement() {
    if (y < padding) {
      y = padding;
    }
    if (y + height > screenHeight - padding) {
      y = screenHeight - height - padding;
    }
  }
};

class Bot : public Paddle {
public:
  void update(int ball_y) {
    if ((y + height / 2 > ball_y)) {
      y -= vy;
    }
    if ((y + height / 2 <= ball_y)) {
      y += vy;
    }
    LimitMovement();
  }
};

//*************************** MAIN *************************************

int main(void) {

  Paddle player;
  Bot bot;
  Ball ball;

  InitWindow(screenWidth, screenHeight, "Pong Game");
  SetTargetFPS(60);

  // Ball
  ball.x = InitialCircleX;
  ball.y = InitialCircleY;
  ball.vx = ball.vy = BallSpeed;

  // Player
  player.x = InitialPlayerX;
  player.y = InitialPlayerY;
  bot.x = InitialBotX;
  bot.y = InitialBotY;

  while (WindowShouldClose() == false) {
    BeginDrawing();
    ClearBackground(DarkGreen);

    // Update
    ball.update();
    player.update();
    bot.update(ball.y);

    // Check Collision
    // Collide with player paddle
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
      ball.vx *= -1;
      ball.x = player.x + player.width + ball.radius;  // Ensure ball moves away from paddle
    }
    // Collide with bot paddle
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{bot.x, bot.y, bot.width, bot.height})) {
      ball.vx *= -1;
      ball.x = bot.x - ball.radius;  // Ensure ball moves away from paddle
    }

    // Scoring
    if (ball.x - ball.radius <= 0) {
      BotScore++;
      ball.vx *= -1;
      ball.x = ball.radius; // Move the ball slightly away from the edge
    }
    if (ball.x + ball.radius >= screenWidth) {
      PlayerScore++;
      ball.vx *= -1;
      ball.x = screenWidth - ball.radius; // Move the ball slightly away from the edge
    }

    // Drawing
    DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, Green);
    DrawCircle(InitialCircleX, InitialCircleY, BGCircleRadius, LightGreen);

    ball.draw();
    player.draw();
    bot.draw();

    DrawLine(LineStartX, LineStartY, LineEndX, LineEndY, WHITE);

    DrawText(TextFormat("%i", PlayerScore), PlayerTextPosX, PlayerTextPosY, FontSize, WHITE);
    DrawText(TextFormat("%i", BotScore), BotTextPosX, BotTextPosY, FontSize, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

