#include "UserInterface.h"

UserInterface::UserInterface():
	coinSpinAnimation(6, 32, 32, 0),
	heartLoseAnimation(6, 17, 17, 0)
{
	//load font
	textFont.loadFromFile("Assets/rainyhearts.ttf");

	//load textures
	heartTexture.loadFromFile("Assets/HUD/heart_animated_1.png");
	coinTexture.loadFromFile("Assets/HUD/coin_rot_anim.png");

	//create coin text
	sf::Text* coinText = new sf::Text();
	coinText->setFont(textFont);
	coinText->setString("0 / 10");
	coinText->setOutlineColor(sf::Color::Black);
	coinText->setOutlineThickness(1.f);
	coinText->setCharacterSize(32.f);
	coinText->setPosition(55.f, 14.f);
	uiText.push_back(coinText); //save into vector

	//create coin sprite
	sf::Sprite* coinSprite = new sf::Sprite();
	coinSprite->setTexture(coinTexture);
	coinSprite->setTextureRect({0,0,32,32});
	coinSprite->setScale({ 1.25f, 1.25f });
	coinSprite->setPosition(10.f, 15.f);
	uiSprites.push_back(coinSprite);

	for (size_t i = 0; i < 3; i++) //3 hearts
	{
		//create heart sprites
		sf::Sprite* heart = new sf::Sprite();
		heart->setTexture(heartTexture);
		heart->setTextureRect({ 0,0,17,17 });
		heart->setScale({ 2.75f,  2.75f });
		heart->setPosition(35.f + 17 * 2.75f * i, 650.f);
		uiSprites.push_back(heart);
	}

	//create ending text
	endText.setFont(textFont);
	endText.setString("You collected all the coins and completed the game! \n            Press 'R' to restart the game");
	endText.setOutlineColor(sf::Color::Black);
	endText.setOutlineThickness(1.f);
	endText.setCharacterSize(32.f);
	endText.setPosition(325.f, 300.f);
}
void UserInterface::Update(float deltaTime)
{
	coinSpinAnimation.PlayAnimation(*uiSprites[0], deltaTime);

	//losing a heart animation
	if(_heartLost)
	{
		if (heartLoseAnimation.GetAnimationStep() == 6)
		{
			_heartLost = false;
			heartLoseAnimation.ResetAnimation();
		}

		heartLoseAnimation.PlayAnimation(*uiSprites[_heartSpriteIndex], deltaTime);
	}
}

void UserInterface::Draw(sf::RenderWindow& window)
{
	for (sf::Text* text : uiText)
	{
		window.draw(*text);
	}

	for(sf::Sprite* sprite : uiSprites)
	{
		window.draw(*sprite);
	}

	if(gameCompleted)
	{
		window.draw(endText);
	}
}

void UserInterface::UpdateHearts(int hitPoints)
{
	_heartSpriteIndex = hitPoints + 1;
	_heartLost = true;
}

void UserInterface::UpdateCoinsText(int current, int max)
{
	uiText[0]->setString(std::to_string(current) + " / " + std::to_string(max));
}

void UserInterface::ResetUI()
{
	for (sf::Sprite* sprite : uiSprites)
	{
		sprite->setTextureRect({ 0,0,17,17 });
	}

	_heartLost = false;
	heartLoseAnimation.ResetAnimation();
}

UserInterface::~UserInterface()
{
	for (auto sprite : uiSprites)
	{
		delete sprite;
	}

	for (auto text : uiText)
	{
		delete text;
	}
}

