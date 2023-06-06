#include <raylib.h>
#include <iostream>

// forward declaration
void drawSquare(Color &color, Vector2 &pos);
bool checkmateOccured();
bool isDraw();
void displayEnd();

namespace Consts {
  const int screen_width = 800;
  const int screen_height = 800;
  const int SIZE = 8;
}

typedef enum GameScreen { GAMEPLAY, ENDING } GameScreen;
GameScreen currentScreen = GAMEPLAY;

// --------------
// Main game loop
// --------------

void handleGame() {

  //Initialization
  InitWindow(Consts::screen_width, Consts::screen_height, "Chess");
  SetTargetFPS(60);
  Image pieces = LoadImage("/home/johannes/Chess/Assets/Pieces.png");
  Texture2D piecesTexture = LoadTextureFromImage(pieces);

  //game loop starts here
  while (!WindowShouldClose()) {

    switch(currentScreen) {
      case GAMEPLAY: [[likely]]
        if (checkmateOccured() || isDraw() || IsKeyPressed(KEY_SPACE)) {
          currentScreen = ENDING;
        }
        break;
      case ENDING:
		if (IsKeyPressed(KEY_ENTER)) {
		  currentScreen = GAMEPLAY;
		}
        break;
      default: break;
    };
 
	// ----------------------------
	// DRAW
	// ----------------------------
	BeginDrawing();
	ClearBackground(RAYWHITE);

	int color = 0;

	switch (currentScreen) {

	case GAMEPLAY:

	  for (int i = 0; i < Consts::SIZE; ++i) {
		const Color colors[2] = {WHITE, LIGHTGRAY};
		for (int j = 0; j < 8; ++j) {
		  DrawRectangleRec((Rectangle) { j*100.0f, i*100.0f, 100, 100 }, colors[color]);
		  color = !color;
		}
		color = !color;
	  }
	  
	  DrawTexture(piecesTexture, Consts::screen_width / 2 - pieces.width, Consts::screen_height / 2 - pieces.height, BLACK);
	  break;
	case ENDING:
	  displayEnd();
	  break;
	}
	EndDrawing();
  }
  CloseWindow();
}


bool checkmateOccured() {
  return false;
}

bool isDraw() {
  return false;
}
void displayEnd() {
  std::size_t fontSize{40};
  ClearBackground(RAYWHITE);

  DrawRectangle(Consts::screen_width / 2 - 100, Consts::screen_height / 2 - 25, 200, 50, RED);
  DrawText("Continue", Consts::screen_width / 2 - 75, Consts::screen_height / 2 - 16, fontSize - 5, BLACK);
  DrawRectangle(Consts::screen_width / 2 - 100, Consts::screen_height / 2 + 50, 200, 50, RED);
  DrawText("Quit", Consts::screen_width / 2 - 33, Consts::screen_height / 2 + 58, fontSize - 5, BLACK);

  DrawText("THE END. Press enter to continue!", 50, 100, fontSize, BLACK);
  DrawText("Escape to quit!", 50, 150, fontSize, BLACK);
}

