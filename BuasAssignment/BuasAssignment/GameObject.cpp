#include "GameObject.h"
#include "Game.h"
#include "MathFunctions.h"
#include <iostream>

GameObject::GameObject(Game* game):
	_collider(),
	_sprite(),
	_defaultTexture()
	{
		this->_game = game;

		_defaultTexture.loadFromFile("Assets/Assets/Props-Rocks.png");

		_sprite.setTexture(_defaultTexture);
		_sprite.setTextureRect({176, 0, 16, 16}); //a rock as the default object
		_sprite.setPosition(objectPosition);
		_sprite.setScale(objectScale);
		spriteOrigin = _sprite.getOrigin();
		
		//make collider shape & resize it
		_collider.setSize(_sprite.getGlobalBounds().getSize());
		_collider.setOutlineColor(sf::Color::White);
		_collider.setOutlineThickness(colliderDrawThickness);
		_collider.setFillColor(sf::Color::Transparent);
	}


void GameObject::Start()
{
}


void GameObject::Update(float deltaTime)
{
	//Add gravity force
	ApplyForce(sf::Vector2f(0.f, GRAVITY * objectMass * static_cast<float>(!_grounded)), deltaTime);

	if(_grounded && _velocity.y > 0) //stop player if colliding with something
	{
		SetVelocityY(0.f);
	}

	objectPosition += _velocity; //update position with velocity

	//collision check
	_grounded = false;

	//make collider follow sprite
	_collider.setPosition(objectPosition);

	for (auto tileObject : _game->activeTiles)
	{
		sf::FloatRect tileBounds = tileObject->GetSprite()->getGlobalBounds();
		//make bounds smaller on the Y axis so objects fall a bit into it, so it looks better visually
		tileBounds.top -= -4;
		tileBounds.height -= 4;

		if(!_grounded)
			_grounded = MathFunctions::IsPointInBounds(_pointR, tileBounds) ||
				MathFunctions::IsPointInBounds(_pointL, tileBounds);

		if (MathFunctions::AreBoundsColliding(_collider.getGlobalBounds(), tileBounds, _overlapCollision))
		{
			if(MathFunctions::SqrMagnitude(_overlapCollision) > _minSqrCollisionOverlap)
			{
				//add overlap to player to set it to the correct position
				objectPosition -= _overlapCollision;
				_collider.setPosition(objectPosition);
			}
		}
	}

	//update sprite position and scale
	_sprite.setPosition(objectPosition);
	_sprite.setScale(objectScale);
	_sprite.setOrigin(spriteOrigin);

	//set ground collision points
	_pointL = (objectPosition + sf::Vector2f(5.f, _collider.getGlobalBounds().height + 1));
	_pointR = (objectPosition + sf::Vector2f(_collider.getGlobalBounds().width - 5.f, _collider.getGlobalBounds().height + 1));
}

void GameObject::Draw(sf::RenderWindow& window)
{
	if(drawCollider)
		window.draw(_collider);

	window.draw(_sprite);
}

void GameObject::ApplyForce(sf::Vector2f force, float deltaTime, bool onlyColliding)
{
	if (onlyColliding && !_grounded)
		return;

	//value makes sure the speed will never go faster than a certain amount
	float speedPercent = 1 - MathFunctions::Clamp01(_velocity.y / maxVelocity);

	_acceleration = force / objectMass * deltaTime * speedPercent;

	_velocity += _acceleration;
}


sf::Vector2f GameObject::GetVelocity() const
{
	return _velocity;
}

void GameObject::AddVelocity(sf::Vector2f velocity)
{
	_velocity += velocity;
}


void GameObject::SetVelocity(sf::Vector2f velocity)
{
	_velocity = velocity;
}

void GameObject::SetVelocityX(float x)
{
	_velocity.x = x;
}

void GameObject::SetVelocityY(float y)
{
	_velocity.y = y;
}

///Flips sprite on scale and re-alines origin to match same position, based on the velocity X
void GameObject::FlipSprite(float originalScaleX)
{
	float newScaleX = objectScale.x;
	float widthOrigin = 0;

	if (_velocity.x > 0)
		newScaleX = originalScaleX;

	if (_velocity.x < 0)
	{
		newScaleX = -originalScaleX;
		widthOrigin = _sprite.getLocalBounds().width / 1.75f; // division to center sprite after flipping
	}

	if (objectScale.x != newScaleX)
	{
		spriteOrigin = { widthOrigin, 0.f };
		objectScale = { newScaleX, objectScale.y };
	}
}

void GameObject::CheckOutOfBounds(sf::RenderWindow& window)
{
	
}

GameObject::~GameObject() = default;
