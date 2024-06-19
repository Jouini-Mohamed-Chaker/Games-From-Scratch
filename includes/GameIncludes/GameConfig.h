#ifndef GAMECONFIG_H
#define GAMECONFIG_H

namespace GameConfig {
  // Screen dimensions
  const int screenWidth = 1280;
  const int screenHeight = 800;

  // Ball configuration
  const int CircleRadius = 20;
  const int BallSpeed = 11;
  const int InitialCircleX = screenWidth / 2;
  const int InitialCircleY = screenHeight / 2;

  // Paddle configuration
  const int RectWidth = 20;
  const int RectHeight = 150;
  const int RectSpeed = 8;
  const int padding = 15;
  const int InitialPlayerX = padding;
  const int InitialPlayerY = screenHeight / 2 - RectHeight / 2;
  const int InitialBotX = screenWidth - padding - RectWidth;
  const int InitialBotY = InitialPlayerY;

  // Background configuration
  const int BGCircleRadius = 150;

  // Line configuration
  const int LineStartX = screenWidth / 2;
  const int LineStartY = 0;
  const int LineEndX = LineStartX;
  const int LineEndY = screenHeight;

  // Text configuration
  const int PlayerTextPosX = screenWidth / 4;
  const int PlayerTextPosY = 50;
  const int BotTextPosX = 3 * screenWidth / 4;
  const int BotTextPosY = PlayerTextPosY;
  const int FontSize = 45;
}

#endif // GAMECONFIG_H


