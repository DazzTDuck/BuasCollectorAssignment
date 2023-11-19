#include "GameInput.h"
#include <SFML/Window/Event.hpp>

using namespace sf;

void Input::InitializeInputs()
{
	for (int i = Keyboard::Key::A; i != Keyboard::KeyCount; i++)
		inputs[static_cast<Keyboard::Key>(i)] = false;
}

void Input::InputHandler(RenderWindow& window, Event& event)
{
	switch (event.type)
	{
		case Event::KeyPressed:
			Input::inputs[event.key.code] = true;
			break;
		case Event::KeyReleased:
			Input::inputs[event.key.code] = false;
			break;
	}
}

bool Input::GetInput(Keyboard::Key key)
{
	return inputs.at(key); 
}

std::map<Keyboard::Key, bool> Input::inputs; //define map

