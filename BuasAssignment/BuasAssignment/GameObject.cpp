#include "GameObject.h"
#include "Game.h"
#include "MathFunctions.h"
#include <iostream>
#include "SoundManager.h"

GameObject::GameObject(Game* game)
{
	this->_game = game;

	_defaultTexture.loadFromFile("Assets/Assets/Tiles.png");

	//setup sprite
	_sprite.setTexture(_defaultTexture);
	_sprite.setTextureRect({240, 336, 16, 16}); //a coin as the default object
	_sprite.setPosition(objectPosition);
	_sprite.setScale(objectScale);
	spriteOrigin = _sprite.getOrigin();
	respawnLocation = objectPosition;
	
	//make collider shape & resize it
	_collider.setSize(_sprite.getGlobalBounds().getSize());
	_collider.setOutlineColor(sf::Color::White);
	_collider.setOutlineThickness(colliderDrawThickness);
	_collider.setFillColor(sf::Color::Transparent);

	//physic properties
	_hasGravity = false;
	objectMass = 0.f;
}


void GameObject::Start()
{
}


void GameObject::Update(float deltaTime)
{
	if (isDisabled)
		return;

	//Add gravity force
	if(_hasGravity)
	{
		ApplyForce(sf::Vector2f(0.f, (GRAVITY * objectMass) * static_cast<float>(!_grounded)), deltaTime);

		if (_grounded && _velocity.y > 0) //stop player if colliding with something
		{
			SetVelocityY(0.f);
		}

		//set ground collision points
		_pointL = (objectPosition + sf::Vector2f(5.f, _collider.getGlobalBounds().height + 2.f));
		_pointR = (objectPosition + sf::Vector2f(_collider.getGlobalBounds().width - 14.f, _collider.getGlobalBounds().height + 2.f));

		//collision check
		_grounded = false;
		_rightPointGrounded = false;
		_leftPointGrounded = false;

		//make collider follow sprite
		_collider.setPosition(objectPosition);

		for (auto tileObject : _game->collisionTiles)
		{
			sf::FloatRect tileBounds = tileObject->GetSprite()->getGlobalBounds();

			if(!_rightPointGrounded)
				_rightPointGrounded = MathFunctions::IsPointInBounds(_pointR, tileBounds);

			if(!_leftPointGrounded)
				_leftPointGrounded = MathFunctions::IsPointInBounds(_pointL, tileBounds);

			if (!_grounded)
				_grounded = _rightPointGrounded || _leftPointGrounded;

			if (MathFunctions::AreBoundsColliding(_collider.getGlobalBounds(), tileBounds, _overlapCollision))
			{
				if (MathFunctions::SqrMagnitude(_overlapCollision) > _minSqrCollisionOverlap)
				{
					//add overlap to player to set it to the correct position
					objectPosition -= _overlapCollision;
					_collider.setPosition(objectPosition);
				}
			}
		}
	}

	//update sprite position and scale
	_sprite.setPosition(objectPosition);
	_sprite.setScale(objectScale);
	_sprite.setOrigin(spriteOrigin);

	
	//apply drag to the velocity
	if (_grounded)
		_velocity *= _objectDrag;
	else
		_velocity.x *= _objectDrag;


	objectPosition += _velocity; //update position with velocity
}

void GameObject::Draw(sf::RenderWindow& window)
{
	if (isDisabled)
		return;

	if(drawCollider)
		window.draw(_collider);

	window.draw(_sprite);
}

void GameObject::ApplyForce(sf::Vector2f force, float deltaTime)
{
	if (isDisabled)
		return;

	//value makes sure the speed will never go faster than a certain amount
	float speedPercentX = 1 - MathFunctions::Clamp01( abs(_velocity.x) / _maxVelocity);
	float speedPercentY = 1 - MathFunctions::Clamp01(abs(_velocity.y) / _maxVelocity);

	_acceleration.x = force.x * deltaTime * speedPercentX;
	_acceleration.y = force.y * deltaTime * speedPercentY;

	_velocity += _acceleration;
}

void GameObject::ApplyImpulse(sf::Vector2f impulse, float deltaTime)
{
	_velocity += (impulse / objectMass) * deltaTime;
}


sf::Vector2f GameObject::GetVelocity() const
{
	return _velocity;
}

sf::Sprite& GameObject::GetSprite()
{
	return _sprite;
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
void GameObject::FlipSprite(float originalScaleX, float widthMultiplier, bool flipped)
{
	float newScaleX = objectScale.x;
	float widthOrigin = _originalOrigin.x;

	if (flipped ? _velocity.x <= 0 : _velocity.x > 0)
	{
		_isFlipped = false;
		newScaleX = originalScaleX;
	}

	if (flipped ? _velocity.x > 0 : _velocity.x <= 0)
	{
		newScaleX = -originalScaleX;
		widthOrigin = _sprite.getLocalBounds().width * widthMultiplier; //center sprite after flipping
		_isFlipped = true;
	}

	if (objectScale.x != newScaleX)
	{
		spriteOrigin.x = widthOrigin;
		objectScale = { newScaleX, objectScale.y };
	}
}

sf::FloatRect GameObject::GetBounds() const
{
	return _sprite.getGlobalBounds();
}

void GameObject::PlaySound(const std::string& soundName, float volume)
{
	sound.setBuffer(*SoundManager::GetSoundFile(soundName));
	sound.setVolume(volume);
	sound.play();
}

void GameObject::CheckOutOfBounds(sf::RenderWindow& window)
{
}

void GameObject::OnRespawn()
{
	objectPosition = respawnLocation;
	SetVelocity({ 0.f, 0.f }); //reset velocity
}

GameObject::~GameObject() = default;
