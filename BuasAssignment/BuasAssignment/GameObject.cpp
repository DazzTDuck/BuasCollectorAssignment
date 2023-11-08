#include "GameObject.h"

#include "Game.h"
#include "MathFunctions.h"

GameObject::GameObject(const std::string& spriteFile):
	_texture(),
	_sprite(),
	_collider()
	{
		_texture.loadFromFile(spriteFile);
		_sprite.setTexture(_texture);
		_sprite.setTextureRect(sf::IntRect(22, 16, 35, 48));
		_sprite.setPosition(objectPosition);
		_sprite.setScale(objectScale);
		spriteOrigin = _sprite.getOrigin();
		

	//make collider shape & resize it
		_collider.setSize(_sprite.getGlobalBounds().getSize() - sf::Vector2f{30.f, 0.f});
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
	ApplyForce(sf::Vector2f(0.f, GRAVITY * objectMass * static_cast<float>(!_colliding)), deltaTime);

	if(_colliding && _velocity.y > 0) //stop player if colliding with something
	{
		SetVelocityY(0.f);
	}

	objectPosition += _velocity; //update position with velocity

	//update sprite position and scale
	_sprite.setPosition(objectPosition);
	_sprite.setScale(objectScale);
	_sprite.setOrigin(spriteOrigin);

	if (drawCollider)
		_collider.setPosition(objectPosition);

	FlipSprite(2.f);

	_colliding = false;

	//collision checking by distance
	for (auto tiles : game->activeTiles)
	{
		if(MathFunctions::GetSqrDistance(objectPosition, tiles->GetSprite()->getPosition()) < _collisionDistance)
		{
			if (_collider.getGlobalBounds().intersects(tiles->GetSprite()->getGlobalBounds()))
			{
				_colliding = true;
				break;
			}
		}
	}
}

void GameObject::Draw(sf::RenderWindow& window)
{
	if(drawCollider)
		window.draw(_collider);

	window.draw(_sprite);
}

void GameObject::ApplyForce(sf::Vector2f force, float deltaTime, bool onlyColliding)
{
	if (onlyColliding && !_colliding)
		return;

	//value makes sure the speed will never go faster than a certain amount
	float speedPercent = 1 - MathFunctions::Clamp01(_velocity.y / maxVelocity);

	_acceleration = force / objectMass * deltaTime * speedPercent;

	_velocity += _acceleration;
}

void GameObject::CheckOutOfBounds(sf::RenderWindow& window)
{
	sf::FloatRect bounds = _sprite.getGlobalBounds();

	//keep object from moving out of bounds
	if (objectPosition.x < 0) 
		objectPosition.x = 0;

	if (objectPosition.y < 0) 
		objectPosition.y = 0;

	if (objectPosition.x + bounds.width > window.getSize().x) 
		objectPosition.x = window.getSize().x - bounds.width;

	if (objectPosition.y + bounds.height > window.getSize().y)
	{
		//re spawn player
		objectPosition = { 150.f , 100.f };
		SetVelocity({ 0.f, 0.f });
	} 
		
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

GameObject::~GameObject() = default;
