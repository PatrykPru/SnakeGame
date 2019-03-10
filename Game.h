#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

class Game
{
	typedef sf::Vector2 <short int> Vector2s;

private:
	// GENERAL
	short int N = 25, M = 25;
	sf::RenderWindow *window = NULL;
	std::string title = "Snake 2.2";

	// Font
	sf::Font font;

	// Colors
	sf::Color bgColor;
	sf::Color pointColor;
	sf::Color snakeColor;
	sf::Color snakeColorSecond;

	sf::Color foodColor;
	// Game
	std::deque <Vector2s> snake;
	std::deque <Vector2s> food;
	Vector2s movement;
	Vector2s lastMovement;

	// Statistics
	short int highscore;
	short int score;

	// FPS time
	sf::Clock clock;

	// Count Game Time
	sf::Clock clockGameTime;
	sf::Time gameTime = sf::milliseconds(0);

	// Button delay
	sf::Clock clockButton;

	// Food respawn speed
	sf::Clock clockFoodRespawn;
	sf::Time timeFoodRespawn = sf::milliseconds(0);
	short int respawnTime = 7; /*in seconds*/

							   // Game status
	enum GameStatus { MENU, GAME, GAMEOVER, CHARACTERS, PAUSE, EXIT, };
	GameStatus status;

	// Events
	enum Bonus { NONE, COLORIZE_BOARD, REVERSE_CONTROL, BONUSFOOD };
	Bonus bonus = NONE;
	Bonus chanceBonus = NONE;
	sf::Clock clockBonus;
	short int bonusTime = 4;
	sf::Clock clockBoard;

	// Faces
	struct Character { sf::Image *img = NULL; unsigned int size; sf::Color *palette = NULL; std::wstring motto = L""; };
	int I = -1;
	Character characters[18];
	sf::Texture imgTxt;
	sf::Sprite *imgSpr;

	// Color palette
	sf::Color defaultPalette[2];

protected:
	// GENERAL
	float scaleX = 0;
	float scaleY = 0;

	// Game Control
	int getSpeed();
	void gameRestart();
	void countGameTime();
	void updateFoodTime();
	void eaten();
	bool eatenYourself(Vector2s);
	void changeMovement();
	void drawSnake();
	void drawFood();
	void drawBoard();

	// Events
	void drawBoardBonus();

	// Menus
	void showMenu();
	void showCharactersMenu();
	void showPause();
	void showGameOver();

	// HUD
	void showScore();
	void showGameTime();
	void showFoodTime();
	void showBonusTime();

public:
	Game(sf::RenderWindow *);

	// Control
	void update();
	void display();
	~Game();
};
