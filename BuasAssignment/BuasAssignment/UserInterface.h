#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Animations.h"

class UserInterface
{
public:
	UserInterface();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void UpdateHearts(int hitPoints);
	void UpdateCoinsText(int current, int max);
	void ResetUI();

	sf::Font textFont;

	std::vector<sf::Sprite*> uiSprites;
	std::vector<sf::Text*> uiText;

	sf::Texture heartTexture;
	sf::Texture coinTexture;

	Animations coinSpinAnimation;
	Animations heartLoseAnimation;

	~UserInterface();

private:

	bool _heartLost = false;
	int _heartSpriteIndex = 0;
};

