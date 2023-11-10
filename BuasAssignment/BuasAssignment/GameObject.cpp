#include "GameObject.h"
#include "Game.h"
#include "MathFunctions.h"
#include <iostream>

GameObject::GameObject():
	_sprite(),
	_collider(),
	_idleTexture(),
	_runTexture(),
	_jumpTexture(),
	_idleAnimation(4),
	_runAnimation(8),
	_jumpAnimation(2)
	{
		_idleTexture.loadFromFile("Assets/Character/Idle/Idle-Sheet.png");
		_runTexture.loadFromFile("Assets/Character/Run/Run-Sheet.png");
		_jumpTexture.loadFromFile("Assets/Character/Jump-All/Jump-All-Sheet.png");

		_sprite.setTexture(_idleTexture);
		_sprite.setTextureRect({ 22, 16, 35, 48 });
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

	//make collider follow sprite
	_collider.setPosition(objectPosition);

	//handle flipping of sprite based on movement speed
	FlipSprite(2.f);

	//handle animation & texture swapping
	if(!_colliding)
	{
		if (_jumpAnimation.PlayAnimation("PlayerJumpAir", _sprite, deltaTime))
			_sprite.setTexture(_jumpTexture);
	}
	else if (abs(_velocity.x) > 0.f)
	{	
		if(_runAnimation.PlayAnimation("PlayerRun", _sprite, deltaTime))
			_sprite.setTexture(_runTexture);
	}
	else if (abs(_velocity.x) == 0.f)
	{	
		if(_idleAnimation.PlayAnimation("PlayerIdle", _sprite, deltaTime))
			_sprite.setTexture(_idleTexture);
	}


	//collision check
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
	//TODO calculate world offset if player goes too far left or right

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
		SetVelocity({ 0.f, 0.f }); //reset velocity 
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

GameObject::~GameObject() = default;
