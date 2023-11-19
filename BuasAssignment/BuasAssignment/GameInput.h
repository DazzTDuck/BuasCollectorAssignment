#pragma once
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>


namespace Input
{
	extern void InitializeInputs();
	extern void InputHandler(sf::RenderWindow& window, sf::Event& event);
	extern std::map<sf::Keyboard::Key, bool> inputs;

	extern bool GetInput(sf::Keyboard::Key);
};

