#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "face.h"


Game::Game(sf::RenderWindow *window)
{
	this->window = window;
	window->setTitle(title);

	if (!this->font.loadFromFile("C:/Windows/Fonts/SegoeUI.ttf")) {
		if (!this->font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
			window->close();
		}
	}
	this->status = MENU;

	this->bgColor = sf::Color::Black;
	this->pointColor = sf::Color(30, 30, 30);

	this->snakeColor = sf::Color(0, 173, 31);
	this->snakeColorSecond = sf::Color(71, 224, 71);
	defaultPalette[0] = snakeColor;
	defaultPalette[1] = snakeColorSecond;

	this->foodColor = sf::Color::Red;

	this->scaleX = this->window->getSize().x / N;
	this->scaleY = this->window->getSize().y / M;

	for (int i = 0; i<3; i++)
		this->snake.push_front(Vector2s(N / 2, M / 2));

	this->food.push_front(Vector2s(rand() % N, rand() % M));

	this->movement = Vector2s(1, 0);

	// Girls
	
	sf::Image *img;
	
	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[0].img = img;
	characters[0].size = 2;
	characters[0].palette = new sf::Color[2];
	characters[0].palette[0] = sf::Color(10, 10, 10);
	characters[0].palette[1] = sf::Color(30, 30, 30);

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[1].img = img;

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[2].img = img;

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[3].img = img;

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[4].img = img;
	characters[4].size = 2;
	characters[4].palette = new sf::Color[2];
	characters[4].palette[0] = sf::Color(205, 87, 10);
	characters[4].palette[1] = sf::Color(235, 107, 30);

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[5].img = img;

	// Boys
	img = new sf::Image;
	img->create(face.width,	face.height, &face.pixel_data[0]);
	characters[6].img = img;
	characters[6].size = 2;
	characters[6].palette = new sf::Color[2];
	characters[6].palette[0] = sf::Color(255, 50, 50);
	characters[6].palette[1] = sf::Color(255, 100, 0);

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[7].img = img;
	characters[7].img = img;
	characters[7].size = 2;
	characters[7].palette = new sf::Color[2];
	characters[7].palette[0] = sf::Color(50, 50, 255);
	characters[7].palette[1] = sf::Color(100, 100, 255);

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[8].img = img;
	characters[8].size = 6;
	characters[8].palette = new sf::Color[6];
	characters[8].palette[0] = sf::Color(254, 32, 32);
	characters[8].palette[1] = sf::Color(255, 165, 0);
	characters[8].palette[2] = sf::Color(0, 128, 0);
	characters[8].palette[3] = sf::Color(64, 224, 208);
	characters[8].palette[4] = sf::Color(148, 0, 211);
	characters[8].palette[5] = sf::Color(255, 105, 180);
	characters[8].motto = L"Gdybym nie przgra³, to bym wygra³";

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[9].img = img;

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[10].img = img;

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[11].img = img;

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[12].img = img;

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[13].img = img;

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[14].img = img;

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[15].img = img;

	img = new sf::Image;
	img->create(face.width, face.height, &face.pixel_data[0]);
	characters[16].img = img;
	characters[16].size = 2;
	characters[16].palette = new sf::Color[2];
	characters[16].palette[0] = sf::Color(175, 57, 10);
	characters[16].palette[1] = sf::Color(205, 77, 30);
	
}

/*
____                                 ____                   _                    _
/ ___|   __ _   _ __ ___     ___     / ___|   ___    _ __   | |_   _ __    ___   | |
| |  _   / _` | | '_ ` _ \   / _ \   | |      / _ \  | '_ \  | __| | '__|  / _ \  | |
| |_| | | (_| | | | | | | | |  __/   | |___  | (_) | | | | | | |_  | |    | (_) | | |
\____|  \__,_| |_| |_| |_|  \___|    \____|  \___/  |_| |_|  \__| |_|     \___/  |_|
*/

int Game::getSpeed()
{
	return 100;
}

void Game::gameRestart()
{
	food.clear();
	snake.clear();
	for (int i = 0; i<3; i++)
		this->snake.push_front(Vector2s(N / 2, M / 2));
	gameTime = sf::microseconds(0);
	clockBonus.restart();
	bonus = NONE;
}


void Game::countGameTime()
{
	gameTime += clockGameTime.getElapsedTime();
	clockGameTime.restart();
}

void Game::updateFoodTime()
{
	timeFoodRespawn += sf::seconds(clockFoodRespawn.getElapsedTime().asSeconds());
	clockFoodRespawn.restart();
}

void Game::eaten()
{
	for (int j = 0; j < this->food.size(); j++) {
		if (snake[0] == food[j]) {
			if (chanceBonus == COLORIZE_BOARD) {
				clockBonus.restart();
				bonus = COLORIZE_BOARD;
			}
			if (chanceBonus == REVERSE_CONTROL) {
				clockBonus.restart();
				bonus = REVERSE_CONTROL;
			}
			food.clear();
			if (chanceBonus == BONUSFOOD) {
				for (int i = 0; i < 10; i++) {
					this->snake.push_back(this->snake[snake.size() - 1]);
				}
			}
			else {
				this->snake.push_back(this->snake[snake.size() - 1]);
			}
		}
	}
}

bool Game::eatenYourself(Vector2s part)
{
	for (int i = 0; i < this->snake.size(); i++)
	{
		if (this->snake[i] == part) {
			return true;
		}
	}
	return false;
}

void Game::changeMovement()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && this->lastMovement != Vector2s(0, 1)) {
		this->movement = Vector2s(0, -1);
		return;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && this->lastMovement != Vector2s(0, -1)) {
		this->movement = Vector2s(0, 1);
		return;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && this->lastMovement != Vector2s(1, 0)) {
		this->movement = Vector2s(-1, 0);
		return;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && this->lastMovement != Vector2s(-1, 0)) {
		this->movement = Vector2s(1, 0);
		return;
	}
}

void Game::drawSnake()
{
	if (I >= 0) {
		imgTxt.loadFromImage(*characters[I].img);
		imgSpr = new sf::Sprite;
		(*imgSpr).setColor(sf::Color::White);
		(*imgSpr).setTexture(imgTxt, false);

		(*imgSpr).setOrigin((*characters[I].img).getSize().x / 2, (*characters[I].img).getSize().y / 2);
		(*imgSpr).setPosition(sf::Vector2f(this->snake[0].x * scaleX + scaleX / 2 - 2, this->snake[0].y * scaleY + scaleY / 2 - 2));
	}

	for (int i = 0; i < this->snake.size(); i++) {
		sf::RectangleShape rect(sf::Vector2f(scaleX - 1, scaleY - 1));
		//sf::CircleShape rect(scaleX / 2);
		rect.move(sf::Vector2f(this->snake[i].x * scaleX, this->snake[i].y * scaleY));
		rect.setFillColor(defaultPalette[i % 2]);
		if (I != -1) {
			if (characters[I].palette != NULL) {
				rect.setFillColor(characters[I].palette[i % characters[I].size]);
			}
		}
		window->draw(rect);
	}

	if (I >= 0) {
		window->draw(*imgSpr);
		delete(imgSpr);
	}
}

void Game::drawFood()
{
	for (int i = 0; i < this->food.size(); i++) {
		sf::RectangleShape rect(sf::Vector2f(scaleX - 1, scaleY - 1));
		//sf::CircleShape rect(scaleX / 2);
		rect.move(sf::Vector2f(this->food[i].x * scaleX, this->food[i].y * scaleY));
		rect.setFillColor(foodColor);
		if (chanceBonus == COLORIZE_BOARD) {
			rect.setFillColor(sf::Color(255, 215, 0));
		}
		if (chanceBonus == REVERSE_CONTROL || chanceBonus == BONUSFOOD) {
			rect.setFillColor(sf::Color::Blue);
		}
		window->draw(rect);
	}
}

void Game::drawBoard()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			sf::RectangleShape rect(sf::Vector2f(scaleX - 1, scaleY - 1));
			rect.move(sf::Vector2f(i*scaleX, j*scaleY));
			rect.setFillColor(sf::Color(20, 20, 20));
			window->draw(rect);
		}
	}
}


/*
_____                          _
| ____| __   __   ___   _ __   | |_   ___
|  _|   \ \ / /  / _ \ | '_ \  | __| / __|
| |___   \ V /  |  __/ | | | | | |_  \__ \
|_____|   \_/    \___| |_| |_|  \__| |___/

*/

void Game::drawBoardBonus()
{
	if (clockBoard.getElapsedTime().asMilliseconds() > 1200) {
		clockBoard.restart();
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			sf::RectangleShape rect(sf::Vector2f(scaleX - 1, scaleY - 1));
			rect.move(sf::Vector2f(i*scaleX, j*scaleY));
			rect.setFillColor(defaultPalette[((int)(clockBoard.getElapsedTime().asMilliseconds() / 100) + i) % 2]);
			if (I != -1) {
				if (characters[I].palette != NULL) {
					rect.setFillColor(characters[I].palette[((int)(clockBoard.getElapsedTime().asMilliseconds() / 100) + i) % characters[I].size]);
				}
			}
			sf::Color rectColor = rect.getFillColor();
			rectColor.a = 95;
			rect.setFillColor(rectColor);
			window->draw(rect);
		}
	}
}

void Game::showCharactersMenu()
{
	sf::Text _Gheader("Girls: ", font, 30);
	_Gheader.setStyle(sf::Text::Bold);
	_Gheader.setFillColor(sf::Color(255, 105, 180));
	_Gheader.setOrigin(sf::Vector2f(_Gheader.getLocalBounds().width / 2, _Gheader.getLocalBounds().height / 2));
	_Gheader.setPosition(sf::Vector2f(window->getSize().x / 2, _Gheader.getLocalBounds().height));
	window->draw(_Gheader);

	for (int i = 0; i < 6; i++) {
		sf::Texture texture;
		texture.loadFromImage(*characters[i].img);

		if (i == I) {
			sf::RectangleShape rectangle(sf::Vector2f((*characters[i].img).getSize().x, (*characters[i].img).getSize().y));
			rectangle.setPosition(sf::Vector2f(20, 4.5 * _Gheader.getLocalBounds().height));
			rectangle.setOrigin(sf::Vector2f(0, (*characters[i].img).getSize().y / 2));
			rectangle.move(sf::Vector2f(75 * i, 0));
			rectangle.setFillColor(sf::Color::Transparent);
			rectangle.setOutlineThickness(2);
			rectangle.setOutlineColor(snakeColorSecond);
			window->draw(rectangle);
		}

		sf::Sprite sprite;
		sprite.setPosition(sf::Vector2f(20, 4.5 * _Gheader.getLocalBounds().height));
		sprite.setOrigin(sf::Vector2f(0, (*characters[i].img).getSize().y / 2));
		sprite.setTexture(texture);
		sprite.move(sf::Vector2f(75 * i, 0));
		window->draw(sprite);

		if (sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left) && clockButton.getElapsedTime().asMilliseconds() >= 500) {
			I = i;
			status = MENU;
			clockButton.restart();
		}
	}

	sf::Text _Bheader("Boys: ", font, 30);
	_Bheader.setStyle(sf::Text::Bold);
	_Bheader.setFillColor(sf::Color(0, 0, 255));
	_Bheader.setOrigin(sf::Vector2f(_Bheader.getLocalBounds().width / 2, _Bheader.getLocalBounds().height / 2));
	_Bheader.setPosition(sf::Vector2f(window->getSize().x / 2, 11 * _Bheader.getLocalBounds().height / 2));
	window->draw(_Bheader);

	for (int i = 6; i < 17; i++) {
		sf::Texture texture;
		texture.loadFromImage(*characters[i].img);

		short int y = ((i - 6) - ((i - 6) % 6)) / 6;
		short int x = (i - 6) % 6;

		if (i == I) {
			sf::RectangleShape rectangle(sf::Vector2f((*characters[i].img).getSize().x, (*characters[i].img).getSize().y));
			rectangle.setPosition(sf::Vector2f(20, 230));
			rectangle.setOrigin(sf::Vector2f(0, (*characters[i].img).getSize().y / 2));
			rectangle.move(sf::Vector2f(x * 75, y * 100));
			rectangle.setFillColor(sf::Color::Transparent);
			rectangle.setOutlineThickness(2);
			rectangle.setOutlineColor(snakeColorSecond);
			window->draw(rectangle);
		}

		sf::Sprite sprite;
		sprite.setPosition(sf::Vector2f(20, 4.5 * _Gheader.getLocalBounds().height));
		sprite.setOrigin(sf::Vector2f(0, (*characters[i].img).getSize().y / 2));
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f(20, 230));
		sprite.move(sf::Vector2f(x * 75, y * 100));

		window->draw(sprite);

		if (sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left) && clockButton.getElapsedTime().asMilliseconds() >= 500) {
			I = i;
			status = MENU;
			clockButton.restart();
		}
	}

	sf::Text _nonFace("Non Face", font, 30);
	_nonFace.setStyle(sf::Text::Bold);
	_nonFace.setFillColor(sf::Color::White);
	_nonFace.setOrigin(sf::Vector2f(_nonFace.getLocalBounds().width / 2, _nonFace.getLocalBounds().height / 2));
	_nonFace.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y - _nonFace.getLocalBounds().height * 2));
	if (_nonFace.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)))
	{
		_nonFace.setFillColor(snakeColor);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clockButton.getElapsedTime().asMilliseconds() >= 500) {
			I = -1;
			status = MENU;
			clockButton.restart();
		}
	}
	window->draw(_nonFace);
}

/*
__  __
|  \/  |   ___   _ __    _   _   ___
| |\/| |  / _ \ | '_ \  | | | | / __|
| |  | | |  __/ | | | | | |_| | \__ \
|_|  |_|  \___| |_| |_|  \__,_| |___/

*/

void Game::showMenu()
{
	sf::Text header(title, font, 50);
	header.setStyle(sf::Text::Bold);
	header.setFillColor(snakeColor);
	header.setOrigin(sf::Vector2f(header.getLocalBounds().width / 2, header.getLocalBounds().height / 2));
	header.setPosition(sf::Vector2f(window->getSize().x / 2, header.getLocalBounds().height));
	window->draw(header);

	std::string itemsName[] = { "Play", "Characters" , "Exit" };
	sf::Text item[3];
	for (int i = 0; i < 3; i++) {
		item[i].setFont(font);
		item[i].setCharacterSize(40);
		item[i].setString(itemsName[i]);
		item[i].setOrigin(sf::Vector2f(item[i].getLocalBounds().width / 2, item[i].getLocalBounds().height / 2));
		item[i].setPosition(sf::Vector2f(window->getSize().x / 2, i * 52 + 200));
		item[i].setFillColor(sf::Color::White);
		if (item[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
			item[i].setFillColor(snakeColorSecond);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clockButton.getElapsedTime().asMilliseconds() >= 500) {
				if (i == 0) {
					gameRestart();
					status = GAME;
					gameTime = sf::microseconds(0);
				}
				if (i == 1) {
					status = CHARACTERS;
				}
				if (i == 2) {
					status = EXIT;
				}
				clockButton.restart();
			}
		}
		window->draw(item[i]);
	}
}

void Game::showPause()
{
	sf::Text header("Pause", font, 50);
	header.setStyle(sf::Text::Bold);
	header.setFillColor(snakeColorSecond);
	header.setOutlineColor(snakeColor);
	header.setOutlineThickness(1);
	header.setOrigin(sf::Vector2f(header.getLocalBounds().width / 2, header.getLocalBounds().height / 2));
	header.setPosition(sf::Vector2f(window->getSize().x / 2, header.getLocalBounds().height));
	window->draw(header);

	sf::Text text("Score: " + std::to_string(score), font, 20);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color(150, 150, 150));
	text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2));
	text.setPosition(sf::Vector2f(window->getSize().x / 2, 2.5*header.getLocalBounds().height));
	window->draw(text);

	sf::Text text2("Press ESC to return", font, 25);
	text2.setStyle(sf::Text::Bold);
	text2.setFillColor(sf::Color(211, 211, 211));
	text2.setOrigin(sf::Vector2f(text2.getLocalBounds().width / 2, text2.getLocalBounds().height / 2));
	text2.setPosition(sf::Vector2f(window->getSize().x / 2, 3.5*header.getLocalBounds().height));
	window->draw(text2);

	sf::Text item;
	item.setFont(font);
	item.setCharacterSize(50);
	item.setString("Menu");
	item.setOrigin(sf::Vector2f(item.getLocalBounds().width / 2, item.getLocalBounds().height / 2));
	item.setPosition(sf::Vector2f(window->getSize().x / 2, 42 + 200));
	item.setFillColor(sf::Color::White);
	if (item.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
		item.setFillColor(snakeColorSecond);
		item.setOutlineColor(snakeColor);
		item.setOutlineThickness(1);
	}
	if (item.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)) && clockButton.getElapsedTime().asMilliseconds() >= 500
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		snake.clear();
		for (int i = 0; i<3; i++)
			this->snake.push_front(Vector2s(N / 2, M / 2));
		status = MENU;
		clockButton.restart();
	}
	window->draw(item);
}

void Game::showGameOver()
{
	// BONUS STOP
	bonus = NONE;

	// GAMEOVER
	sf::Text gameover("Game Over", font, 50);
	if (I != -1 && characters[I].motto.size() > 0) {
		gameover.setScale(sf::Vector2f(0.5, 0.5));
		gameover.setString(characters[I].motto);
	}
	gameover.setStyle(sf::Text::Bold);
	gameover.setFillColor(sf::Color(0, 170, 0));
	gameover.setOrigin(sf::Vector2f(gameover.getLocalBounds().width / 2, gameover.getLocalBounds().height / 2));
	gameover.setPosition(sf::Vector2f(window->getSize().x / 2, gameover.getLocalBounds().height));
	window->draw(gameover);

	// SCORE
	score = snake.size();
	sf::Text score("Your Score: " + std::to_string(score), font, 30);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color(0, 170, 0));
	score.setOrigin(sf::Vector2f(score.getLocalBounds().width / 2, score.getLocalBounds().height / 2));
	score.setPosition(sf::Vector2f(window->getSize().x / 2, 5 * score.getLocalBounds().height));
	window->draw(score);

	// HIGHSCORE
	sf::Text highscore("Your Highscore: " + std::to_string(highscore), font, 30);
	highscore.setStyle(sf::Text::Bold);
	highscore.setFillColor(sf::Color(100, 220, 100));
	highscore.setOrigin(sf::Vector2f(highscore.getLocalBounds().width / 2, highscore.getLocalBounds().height / 2));
	highscore.setPosition(sf::Vector2f(window->getSize().x / 2, highscore.getLocalBounds().height + score.getLocalBounds().height * 5.5));
	window->draw(highscore);

	// MENUS
	std::string itemsName[] = { "Retry", "Menu", "Exit" };
	sf::Text item[3];
	for (int i = 0; i < 3; i++) {
		item[i].setFont(font);
		item[i].setCharacterSize(40);
		item[i].setString(itemsName[i]);
		item[i].setOrigin(sf::Vector2f(item[i].getLocalBounds().width / 2, item[i].getLocalBounds().height / 2));
		item[i].setPosition(sf::Vector2f(window->getSize().x / 2, i * 42 + 200));
		item[i].setFillColor(sf::Color::White);
		item[i].setOutlineColor(sf::Color::Black);
		item[i].setOutlineThickness(1);
		if (item[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
			item[i].setFillColor(sf::Color::Green);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clockButton.getElapsedTime().asMilliseconds() >= 500) {
				if (i == 0) {
					gameRestart();
					status = GAME;
					clockButton.restart();
				}
				if (i == 1) {
					status = MENU;
					clockButton.restart();
				}
				if (i == 2) {
					status = EXIT;
					clockButton.restart();
				}
			}
		}
		window->draw(item[i]);
	}
}

/*
_   _   _   _   ____
| | | | | | | | |  _ \
| |_| | | | | | | | | |
|  _  | | |_| | | |_| |
|_| |_|  \___/  |____/

*/

void Game::showScore()
{
	highscore = snake.size() > highscore ? snake.size() : highscore;
	score = snake.size();
	sf::Text score("Score: " + std::to_string(snake.size()), font, 30);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(snakeColorSecond);
	score.setOrigin(sf::Vector2f(0, 0));
	score.setPosition(sf::Vector2f(10, 10));
	window->draw(score);
}

void Game::showGameTime()
{
	sf::Text time;
	time.setString("Game time: " + std::to_string((short int)ceil(gameTime.asSeconds())) + " seconds");
	time.setFont(font);
	time.setCharacterSize(20);
	time.setFillColor(sf::Color::White);
	time.setOrigin(sf::Vector2f(time.getLocalBounds().width, 0));
	time.setPosition(sf::Vector2f(window->getSize().x - 5, 5));
	window->draw(time);
}

void Game::showFoodTime()
{
	float width = timeFoodRespawn.asMilliseconds() / (float)(respawnTime * 1000);
	sf::RectangleShape timeBar(sf::Vector2f(width * window->getSize().x, 5));
	timeBar.setFillColor(foodColor);
	timeBar.setOrigin(sf::Vector2f(0, timeBar.getSize().y));
	timeBar.setPosition(sf::Vector2f(0, window->getSize().y));
	window->draw(timeBar);
}

void Game::showBonusTime()
{
	float width = clockBonus.getElapsedTime().asMilliseconds() / (float)(bonusTime * 1000);
	sf::RectangleShape timeBar(sf::Vector2f(width * window->getSize().x, 5));
	timeBar.setFillColor(sf::Color::Green);
	timeBar.setOrigin(sf::Vector2f(0, timeBar.getSize().y));
	timeBar.setPosition(sf::Vector2f(0, window->getSize().y - 5));
	window->draw(timeBar);
}

/*
____                   _                    _
/ ___|   ___    _ __   | |_   _ __    ___   | |
| |      / _ \  | '_ \  | __| | '__|  / _ \  | |
| |___  | (_) | | | | | | |_  | |    | (_) | | |
\____|  \___/  |_| |_|  \__| |_|     \___/  |_|
*/

void Game::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && clockButton.getElapsedTime().asMilliseconds() >= 500
		&& (status == GAME || status == PAUSE)) {
		status = (status == GAME) ? PAUSE : GAME;
		clockButton.restart();
		return;
	}

	if (status != GAME) {
		return;
	}


	if (clockBonus.getElapsedTime().asSeconds() > bonusTime) {
		bonus = NONE;
	}

	// Food respawn
	if (food.size() == 0 || timeFoodRespawn.asSeconds() > respawnTime) {
		if (rand() % 100 < 20) {
			chanceBonus = (rand() % 2 == 0) ? COLORIZE_BOARD : ((rand() % 2 == 0) ? REVERSE_CONTROL : BONUSFOOD);
			foodColor = (chanceBonus == COLORIZE_BOARD) ? sf::Color(215, 215, 0) : sf::Color::Blue;
		}
		else {
			chanceBonus = NONE;
			foodColor = sf::Color::Red;
		}
		food.clear();
		food.push_front(Vector2s(rand() % N, rand() % M));
		timeFoodRespawn = sf::seconds(0);
	}

	changeMovement();

	if (clock.getElapsedTime().asMilliseconds() >= getSpeed()) {
		eaten();
		if (movement != lastMovement && bonus == REVERSE_CONTROL) {
			movement = -movement;
		}
		lastMovement = movement;

		// Ctrl + Z
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			snake.push_back(Vector2s(N / 2, M / 2));
		}

		Vector2s _new;
		_new = snake[0];
		_new += this->movement;

		//PASS THROUGH THE WALL
		if (_new.x < 0 || _new.x >= N || _new.y < 0 || _new.y >= M) {
			status = GAMEOVER;
			return;
		}

		_new.x = (_new.x < 0) ? N - _new.x - 2 : _new.x % N;
		_new.y = (_new.y < 0) ? M - _new.y - 2 : _new.y % M;

		if (eatenYourself(_new)) {
			status = GAMEOVER;
		}
		else {
			snake.push_front(_new);
			snake.pop_back();
		}

		clock.restart();
		return;
	}
	else {
		return;
	}
}

void Game::display()
{
	if (status == GAME) {
		window->clear(bgColor);
		if (bonus != COLORIZE_BOARD)drawBoard();
		else drawBoardBonus();
		drawFood();
		drawSnake();
		showScore();
		countGameTime();
		showGameTime();
		if (bonus != NONE) {
			showBonusTime();
		}
		showFoodTime();
		updateFoodTime();
	}
	else {
		clockGameTime.restart();
		clockFoodRespawn.restart();
	}
	if (status == MENU) {
		window->clear(bgColor);
		drawBoard();
		showMenu();
	}
	if (status == GAMEOVER) {
		window->clear(bgColor);
		drawBoard();
		drawFood();
		drawSnake();
		showGameOver();
		showFoodTime();
		showGameTime();
	}
	if (status == CHARACTERS) {
		window->clear(bgColor);
		drawBoard();
		showCharactersMenu();
	}
	if (status == PAUSE) {
		window->clear(bgColor);
		drawBoard();
		drawFood();
		drawSnake();
		showPause();
		showGameTime();
		showFoodTime();
	}
	if (status == EXIT) {
		window->close();
	}
	window->display();
}


Game::~Game()
{
}
