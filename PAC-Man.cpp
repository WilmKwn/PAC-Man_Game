#include "pch.h"

#include "SFML/Graphics.hpp"

#include <iostream>

int main()
{
	bool topEaten = false, bottomEaten = false, left0Eaten = false, left1Eaten = false, right0Eaten = false, right1Eaten = false;

	bool gameOver = false, win = false;

	bool blueBounce = false, redBounce = false, orangeBounce = false, purpleBounce = false;

	float pacman_speed = 0.1f;

	sf::Color bgColor = sf::Color(0, 0, 170);

	int dotX = 45;
	int dotY = 50;

	int score = 0;
	bool scoreUp = true;

	bool moveUp = false, moveDown = false, moveRight = false, moveLeft = false, animate = false, faceRight = false, faceLeft = false , faceUp = false, faceDown = false;
	bool notLeft = false, notRight = false, notUp = false, notDown = false;

	sf::Text gameOverText;
	sf::Font textFont;
	textFont.loadFromFile("Fonts/candal.ttf");
	gameOverText.setFont(textFont);
	gameOverText.setString("GAME OVER!");
	gameOverText.setCharacterSize(50);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setPosition(220, 320);

	sf::Text winText;
	textFont.loadFromFile("Fonts/candal.ttf");
	winText.setFont(textFont);
	winText.setString("YOU WIN!");
	winText.setCharacterSize(50);
	winText.setFillColor(sf::Color::White);
	winText.setPosition(250, 320);

	sf::RenderWindow window(sf::VideoMode(736, 736), "PAC-MAN");

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Textures/pac-man-background2.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(23, 23);

	sf::Texture pac_dots;
	pac_dots.loadFromFile("Textures/pac-dots.png");
	sf::Sprite pac_dots_sprite_top[13];
	for (int i = 0; i < 13; i++)
	{
		pac_dots_sprite_top[i].setTexture(pac_dots);
		pac_dots_sprite_top[i].setScale(3, 3);
		pac_dots_sprite_top[i].setPosition(dotX + (dotX*i), dotY);
		pac_dots_sprite_top[i].setColor(sf::Color::White);
	}
	pac_dots_sprite_top[0].setColor(bgColor);
	sf::Sprite pac_dots_sprite_bottom[13];
	for (int i = 0; i < 13; i++)
	{
		pac_dots_sprite_bottom[i].setTexture(pac_dots);
		pac_dots_sprite_bottom[i].setScale(3, 3);
		pac_dots_sprite_bottom[i].setPosition(dotX + (dotX*i), dotY*12);
		pac_dots_sprite_bottom[i].setColor(sf::Color::White);
	}
	pac_dots_sprite_bottom[0].setColor(bgColor);
	sf::Sprite pac_dots_sprite_left0[10];
	for (int i = 0; i < 10; i++)
	{
		pac_dots_sprite_left0[i].setTexture(pac_dots);
		pac_dots_sprite_left0[i].setScale(3, 3);
		pac_dots_sprite_left0[i].setPosition(dotX, (dotY*2) + (dotY*i));
		pac_dots_sprite_left0[i].setColor(sf::Color::White);
	}
	sf::Sprite pac_dots_sprite_left1[10];
	for (int i = 0; i < 10; i++)
	{
		pac_dots_sprite_left1[i].setTexture(pac_dots);
		pac_dots_sprite_left1[i].setScale(3, 3);
		pac_dots_sprite_left1[i].setPosition(dotX*4, (dotY * 2) + (dotY*i));
		pac_dots_sprite_left1[i].setColor(sf::Color::White);
	}
	sf::Sprite pac_dots_sprite_right0[10];
	for (int i = 0; i < 10; i++)
	{
		pac_dots_sprite_right0[i].setTexture(pac_dots);
		pac_dots_sprite_right0[i].setScale(3, 3);
		pac_dots_sprite_right0[i].setPosition(dotX * 13, (dotY * 2) + (dotY*i));
		pac_dots_sprite_right0[i].setColor(sf::Color::White);
	}
	sf::Sprite pac_dots_sprite_right1[10];
	for (int i = 0; i < 10; i++)
	{
		pac_dots_sprite_right1[i].setTexture(pac_dots);
		pac_dots_sprite_right1[i].setScale(3, 3);
		pac_dots_sprite_right1[i].setPosition(dotX * 10, (dotY * 2) + (dotY*i));
		pac_dots_sprite_right1[i].setColor(sf::Color::White);
	}

	sf::ConvexShape leftRect;
	leftRect.setFillColor(sf::Color::Black);
	leftRect.setPointCount(4);
	leftRect.setPoint(0, sf::Vector2f(138, 138));
	leftRect.setPoint(1, sf::Vector2f(185, 138));
	leftRect.setPoint(2, sf::Vector2f(185, 599));
	leftRect.setPoint(3, sf::Vector2f(138, 599));

	sf::ConvexShape rightRect;
	rightRect.setFillColor(sf::Color::Black);
	rightRect.setPointCount(4);
	rightRect.setPoint(0, sf::Vector2f(551, 138));
	rightRect.setPoint(1, sf::Vector2f(598, 138));
	rightRect.setPoint(2, sf::Vector2f(598, 599));
	rightRect.setPoint(3, sf::Vector2f(551, 599));

	sf::ConvexShape Rect1;
	Rect1.setFillColor(sf::Color::Black);
	Rect1.setPointCount(4);
	Rect1.setPoint(0, sf::Vector2f(275, 138));
	Rect1.setPoint(1, sf::Vector2f(460, 138));
	Rect1.setPoint(2, sf::Vector2f(460, 184));
	Rect1.setPoint(3, sf::Vector2f(275, 184));

	sf::ConvexShape Rect2;
	Rect2.setFillColor(sf::Color::Black);
	Rect2.setPointCount(4);
	Rect2.setPoint(0, sf::Vector2f(275, 437));
	Rect2.setPoint(1, sf::Vector2f(460, 437));
	Rect2.setPoint(2, sf::Vector2f(460, 483));
	Rect2.setPoint(3, sf::Vector2f(275, 483));

	sf::ConvexShape Rect3;
	Rect3.setFillColor(sf::Color::Black);
	Rect3.setPointCount(4);
	Rect3.setPoint(0, sf::Vector2f(275, 552));
	Rect3.setPoint(1, sf::Vector2f(460, 552));
	Rect3.setPoint(2, sf::Vector2f(460, 598));
	Rect3.setPoint(3, sf::Vector2f(275, 598));

	sf::ConvexShape RectMiddle;
	RectMiddle.setFillColor(sf::Color::Black);
	RectMiddle.setPointCount(4);
	RectMiddle.setPoint(0, sf::Vector2f(275, 253));
	RectMiddle.setPoint(1, sf::Vector2f(460, 253));
	RectMiddle.setPoint(2, sf::Vector2f(460, 368));
	RectMiddle.setPoint(3, sf::Vector2f(275, 368));

	sf::Texture playerTextureRight;
	sf::Texture playerTextureLeft;
	sf::Texture playerTextureUp;
	sf::Texture playerTextureDown;
	playerTextureRight.loadFromFile("Textures/pac-man.png");
	playerTextureLeft.loadFromFile("Textures/pac-man-left.png");
	playerTextureUp.loadFromFile("Textures/pac-man-up.png");
	playerTextureDown.loadFromFile("Textures/pac-man-down.png");

	sf::IntRect rect[3];
	rect[0] = sf::IntRect(0, 0, 32, 32);
	rect[1] = sf::IntRect(32, 0, 32, 32);
	rect[2] = sf::IntRect(64, 0, 32, 32);

	sf::Sprite playerSprite;
	playerSprite.setTexture(playerTextureLeft);
	playerSprite.setTextureRect(rect[0]);
	playerSprite.setScale(1.5, 1.5);
	playerSprite.setPosition(325, 380);

	sf::Texture blueGhost;
	blueGhost.loadFromFile("Textures/blueGhost.png");
	sf::Texture redGhost;
	redGhost.loadFromFile("Textures/redGhost.png");
	sf::Texture orangeGhost;
	orangeGhost.loadFromFile("Textures/orangeGhost.png");
	sf::Texture purpleGhost;
	purpleGhost.loadFromFile("Textures/purpleGhost.png");

	sf::Sprite blueGhostSprite;
	blueGhostSprite.setTexture(blueGhost);
	blueGhostSprite.setScale(1.5, 1.5);
	blueGhostSprite.setPosition(80,80);

	sf::Sprite redGhostSprite;
	redGhostSprite.setTexture(redGhost);
	redGhostSprite.setScale(1.5, 1.5);
	redGhostSprite.setPosition(80, 610);

	sf::Sprite orangeGhostSprite;
	orangeGhostSprite.setTexture(orangeGhost);
	orangeGhostSprite.setScale(1.5, 1.5);
	orangeGhostSprite.setPosition(610, 80);

	sf::Sprite purpleGhostSprite;
	purpleGhostSprite.setTexture(purpleGhost);
	purpleGhostSprite.setScale(1.5, 1.5);
	purpleGhostSprite.setPosition(610, 610);


	sf::Clock clock;
	int imageCount = 0;
	float timer = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W) {
					moveUp = true; moveDown = moveRight = moveLeft = false;
					animate = true;
					faceUp = true; faceRight = faceLeft = faceDown = false;
				}
				else if (event.key.code == sf::Keyboard::S) {
					moveDown = true; moveUp = moveRight = moveLeft = false;
					animate = true;
					faceDown = true; faceRight = faceLeft = faceUp = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					moveRight = true; moveUp = moveDown = moveLeft = false;
					animate = true;
					faceRight = true; faceLeft = faceUp = faceDown = false;
				}
				else if (event.key.code == sf::Keyboard::A) {
					moveLeft = true; moveUp = moveDown = moveRight = false;
					animate = true;
					faceLeft = true; faceRight = faceUp = faceDown = false;
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::W) {
					faceUp = false;
				}
				else if (event.key.code == sf::Keyboard::S) {
					faceDown = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					faceRight = false;
				}
				else if (event.key.code == sf::Keyboard::A) {
					faceLeft = false;
				}
			}
		}
		if (!gameOver || !win)
		{
			if (animate)
			{
				timer = clock.getElapsedTime().asSeconds();
				if (timer > 0.1f)
				{
					if (imageCount < 2)
						imageCount++;
					else
						imageCount = 0;
					clock.restart();
				}
			}
			else
				playerSprite.setTextureRect(rect[0]);
			playerSprite.setTextureRect(rect[imageCount]);

			if (playerSprite.getPosition().x <= 185 && playerSprite.getPosition().x >= 138 && playerSprite.getPosition().y + 47 >= 138 && playerSprite.getPosition().y <= 599) {
				notLeft = true; notRight = notUp = notDown = false;
			}
			else if (playerSprite.getPosition().x + 47 >= 138 && playerSprite.getPosition().x + 47 <= 185 && playerSprite.getPosition().y + 47 >= 138 && playerSprite.getPosition().y <= 599) {
				notRight = true; notLeft = notUp = notDown = false;
			}
			else if (playerSprite.getPosition().x <= 598 && playerSprite.getPosition().x >= 551 && playerSprite.getPosition().y + 47 >= 138 && playerSprite.getPosition().y <= 599) {
				notLeft = true; notRight = notUp = notDown = false;
			}
			else if (playerSprite.getPosition().x + 47 >= 551 && playerSprite.getPosition().x + 47 <= 598 && playerSprite.getPosition().y + 47 >= 138 && playerSprite.getPosition().y <= 599) {
				notRight = true; notLeft = notUp = notDown = false;
			}
			else if (playerSprite.getPosition().y <= 184 && playerSprite.getPosition().y >= 138 && playerSprite.getPosition().x + 32 >= 275 && playerSprite.getPosition().x <= 460) {
				notUp = true; notLeft = notRight = notDown = false;
			}
			else if (playerSprite.getPosition().y + 47 >= 138 && playerSprite.getPosition().y + 47 <= 184 && playerSprite.getPosition().x + 32 >= 275 && playerSprite.getPosition().x + 32 <= 460) {
				notDown = true; notLeft = notRight = notUp = false;
			}
			else if (playerSprite.getPosition().y <= 184 && playerSprite.getPosition().y >= 138 && playerSprite.getPosition().x + 32 >= 275 && playerSprite.getPosition().x <= 460) {
				notUp = true; notLeft = notRight = notDown = false;
			}
			else if (playerSprite.getPosition().y + 47 >= 138 && playerSprite.getPosition().y + 47 <= 184 && playerSprite.getPosition().x + 32 >= 275 && playerSprite.getPosition().x + 32 <= 460) {
				notDown = true; notLeft = notRight = notUp = false;
			}
			else if (playerSprite.getPosition().y <= 483 && playerSprite.getPosition().y >= 437 && playerSprite.getPosition().x + 32 >= 275 && playerSprite.getPosition().x <= 460) {
				notUp = true; notLeft = notRight = notDown = false;
			}
			else if (playerSprite.getPosition().y + 47 >= 437 && playerSprite.getPosition().y + 47 <= 483 && playerSprite.getPosition().x + 32 >= 275 && playerSprite.getPosition().x + 32 <= 460) {
				notDown = true; notLeft = notRight = notUp = false;
			}
			else if (playerSprite.getPosition().y <= 598 && playerSprite.getPosition().y >= 552 && playerSprite.getPosition().x + 32 >= 275 && playerSprite.getPosition().x <= 460) {
				notUp = true; notLeft = notRight = notDown = false;
			}
			else if (playerSprite.getPosition().y + 47 >= 552 && playerSprite.getPosition().y + 47 <= 598 && playerSprite.getPosition().x + 32 >= 275 && playerSprite.getPosition().x + 32 <= 460) {
				notDown = true; notLeft = notRight = notUp = false;
			}
			else if (playerSprite.getPosition().y <= 368 && playerSprite.getPosition().y >= 253 && playerSprite.getPosition().x + 32 >= 275 && playerSprite.getPosition().x <= 460) {
				notUp = true; notLeft = notRight = notDown = false;
			}
			else if (playerSprite.getPosition().y + 47 >= 253 && playerSprite.getPosition().y + 47 <= 368 && playerSprite.getPosition().x + 32 >= 275 && playerSprite.getPosition().x + 32 <= 460) {
				notDown = true; notLeft = notRight = notUp = false;
			}
			else if (playerSprite.getPosition().y + 47 >= 138 && playerSprite.getPosition().y <= 599 && playerSprite.getPosition().x + 32 >= 138 && playerSprite.getPosition().x + 32 <= 185) {
				notDown = true; notLeft = notRight = notUp = false;
			}
			else
			{
				notLeft = false;
				notRight = false;
				notUp = false;
				notDown = false;
			}

			sf::Vector2f pacman_movement(0, 0);
			if (moveUp && playerSprite.getPosition().y > 80 && !notUp) {
				pacman_movement.y -= pacman_speed;
			}
			else if (moveDown && playerSprite.getPosition().y < 615 && !notDown) {
				pacman_movement.y += pacman_speed;
			}
			if (moveLeft && playerSprite.getPosition().x > 80 && !notLeft) {
				pacman_movement.x -= pacman_speed;
			}
			else if (moveRight && playerSprite.getPosition().x < 615 && !notRight) {
				pacman_movement.x += pacman_speed;
			}
			playerSprite.move(pacman_movement);

			if (faceRight) playerSprite.setTexture(playerTextureRight);
			else if (faceLeft) playerSprite.setTexture(playerTextureLeft);
			else if (faceUp) playerSprite.setTexture(playerTextureUp);
			else if (faceDown) playerSprite.setTexture(playerTextureDown);

			for (int i = 0; i < 13; i++)
			{
				if (pac_dots_sprite_top[i].getPosition().x + 32 <= playerSprite.getPosition().x + 32 && pac_dots_sprite_top[i].getPosition().x + 32 >= playerSprite.getPosition().x && pac_dots_sprite_top[i].getPosition().y <= playerSprite.getPosition().y && pac_dots_sprite_top[i].getPosition().y + 47 >= playerSprite.getPosition().y)
					pac_dots_sprite_top[i].setColor(bgColor);
			}
			for (int i = 0; i < 13; i++)
			{
				if (pac_dots_sprite_bottom[i].getPosition().x + 32 <= playerSprite.getPosition().x + 32 && pac_dots_sprite_bottom[i].getPosition().x + 32 >= playerSprite.getPosition().x && pac_dots_sprite_bottom[i].getPosition().y <= playerSprite.getPosition().y && pac_dots_sprite_bottom[i].getPosition().y + 47 >= playerSprite.getPosition().y)
					pac_dots_sprite_bottom[i].setColor(bgColor);
			}
			for (int i = 0; i < 10; i++)
			{
				if (pac_dots_sprite_left0[i].getPosition().x <= playerSprite.getPosition().x + 32 && pac_dots_sprite_left0[i].getPosition().x >= playerSprite.getPosition().x - 47 && pac_dots_sprite_left0[i].getPosition().y <= playerSprite.getPosition().y + 32 && pac_dots_sprite_left0[i].getPosition().y + 32 >= playerSprite.getPosition().y)
					pac_dots_sprite_left0[i].setColor(bgColor);
			}

			for (int i = 0; i < 10; i++)
			{
				if (pac_dots_sprite_left1[i].getPosition().x <= playerSprite.getPosition().x + 32 && pac_dots_sprite_left1[i].getPosition().x >= playerSprite.getPosition().x - 47 && pac_dots_sprite_left1[i].getPosition().y <= playerSprite.getPosition().y + 32 && pac_dots_sprite_left1[i].getPosition().y + 32 >= playerSprite.getPosition().y)
					pac_dots_sprite_left1[i].setColor(bgColor);
			}
			for (int i = 0; i < 10; i++)
			{
				if (pac_dots_sprite_right0[i].getPosition().x <= playerSprite.getPosition().x + 32 && pac_dots_sprite_right0[i].getPosition().x >= playerSprite.getPosition().x - 47 && pac_dots_sprite_right0[i].getPosition().y <= playerSprite.getPosition().y + 32 && pac_dots_sprite_right0[i].getPosition().y + 32 >= playerSprite.getPosition().y)
					pac_dots_sprite_right0[i].setColor(bgColor);
			}
			for (int i = 0; i < 10; i++)
			{
				if (pac_dots_sprite_right1[i].getPosition().x <= playerSprite.getPosition().x + 32 && pac_dots_sprite_right1[i].getPosition().x >= playerSprite.getPosition().x - 47 && pac_dots_sprite_right1[i].getPosition().y <= playerSprite.getPosition().y + 32 && pac_dots_sprite_right1[i].getPosition().y + 32 >= playerSprite.getPosition().y)
					pac_dots_sprite_right1[i].setColor(bgColor);
			}
			
			for (int i = 0; i < 13; i++)
			{
				if (pac_dots_sprite_top[i].getColor() == bgColor)
					topEaten = true;
				else
					topEaten = false;
			}
			for (int i = 0; i < 13; i++)
			{
				if (pac_dots_sprite_bottom[i].getColor() == bgColor)
					bottomEaten = true;
				else
					bottomEaten = false;
			}
			for (int i = 0; i < 10; i++)
			{
				if (pac_dots_sprite_left0[i].getColor() == bgColor)
					left0Eaten = true;
				else
					left0Eaten = false;
			}
			for (int i = 0; i < 10; i++)
			{
				if (pac_dots_sprite_left1[i].getColor() == bgColor)
					left1Eaten = true;
				else
					left1Eaten = false;
			}
			for (int i = 0; i < 10; i++)
			{
				if (pac_dots_sprite_right0[i].getColor() == bgColor)
					right0Eaten = true;
				else
					right0Eaten = false;
			}
			for (int i = 0; i < 10; i++)
			{
				if (pac_dots_sprite_right1[i].getColor() == bgColor)
					right1Eaten = true;
				else
					right1Eaten = false;
			}

			if (topEaten && bottomEaten && left0Eaten && left1Eaten && right0Eaten && right1Eaten)
				win = true;

			if (blueGhostSprite.getPosition().x >= 615)
				blueBounce = true;
			else if (blueGhostSprite.getPosition().x <= 80)
				blueBounce = false;

			if (redGhostSprite.getPosition().y <= 80)
				redBounce = true;
			else if (redGhostSprite.getPosition().y >= 615)
				redBounce = false;

			if (orangeGhostSprite.getPosition().y >= 615)
				orangeBounce = true;
			else if (orangeGhostSprite.getPosition().y <= 80)
				orangeBounce = false;

			if (purpleGhostSprite.getPosition().x <= 80)
				purpleBounce = true;
			else if (purpleGhostSprite.getPosition().x >= 615)
				purpleBounce = false;

			if (!gameOver)
			{
				if (!blueBounce)
					blueGhostSprite.move(0.1f, 0);
				else
					blueGhostSprite.move(-0.1f, 0);
				if (!redBounce)
					redGhostSprite.move(0, -0.1f);
				else
					redGhostSprite.move(-0, 0.1f);
				if (!orangeBounce)
					orangeGhostSprite.move(0, 0.1f);
				else
					orangeGhostSprite.move(0, -0.1f);
				if (!purpleBounce)
					purpleGhostSprite.move(-0.1f, 0);
				else
					purpleGhostSprite.move(0.1f, 0);
			}

			if (playerSprite.getPosition().x >= blueGhostSprite.getPosition().x && playerSprite.getPosition().x <= blueGhostSprite.getPosition().x + 47 && playerSprite.getPosition().y+20 >= blueGhostSprite.getPosition().y && playerSprite.getPosition().y <= blueGhostSprite.getPosition().y+32) {
				gameOver = true; win = false;
			}
			else if (playerSprite.getPosition().x >= purpleGhostSprite.getPosition().x && playerSprite.getPosition().x <= purpleGhostSprite.getPosition().x + 47 && playerSprite.getPosition().y+32 >= purpleGhostSprite.getPosition().y && playerSprite.getPosition().y <= purpleGhostSprite.getPosition().y+32) {
				gameOver = true; win = false;
			}
			else if (playerSprite.getPosition().x+32 >= redGhostSprite.getPosition().x && playerSprite.getPosition().x <= redGhostSprite.getPosition().x + 32 && playerSprite.getPosition().y <= redGhostSprite.getPosition().y + 32 && playerSprite.getPosition().y + 32 >= redGhostSprite.getPosition().y) {
				gameOver = true; win = false;
			}
			else if (playerSprite.getPosition().x >= orangeGhostSprite.getPosition().x && playerSprite.getPosition().x <= orangeGhostSprite.getPosition().x + 32 && playerSprite.getPosition().y <= orangeGhostSprite.getPosition().y + 32 && playerSprite.getPosition().y + 32 >= orangeGhostSprite.getPosition().y) {
				gameOver = true; win = false;
			}

			window.clear();

			window.draw(backgroundSprite);

			for (int i = 0; i < 13; i++)
			{
				window.draw(pac_dots_sprite_top[i]);
				window.draw(pac_dots_sprite_bottom[i]);
			}
			for (int i = 0; i < 10; i++)
			{
				window.draw(pac_dots_sprite_left0[i]);
				window.draw(pac_dots_sprite_right0[i]);
				window.draw(pac_dots_sprite_left1[i]);
				window.draw(pac_dots_sprite_right1[i]);
			}
			window.draw(leftRect);
			window.draw(rightRect);
			window.draw(Rect1);
			window.draw(Rect2);
			window.draw(Rect3);
			window.draw(RectMiddle);
			window.draw(playerSprite);
			window.draw(blueGhostSprite);
			window.draw(redGhostSprite);
			window.draw(orangeGhostSprite);
			window.draw(purpleGhostSprite);

			if (win)
			{
				gameOver = false;
				window.clear();
				window.draw(winText);
			}
			else if (gameOver)
			{
				window.clear();
				window.draw(gameOverText);
			}

			window.display();
		}
	}
	return 0;
}