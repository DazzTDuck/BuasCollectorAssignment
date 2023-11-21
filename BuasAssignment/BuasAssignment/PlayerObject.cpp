#include "PlayerObject.h"
#include "Game.h"

PlayerObject::PlayerObject(Game* game):
	GameObject(game),
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
	_collider.setSize(_sprite.getGlobalBounds().getSize() - sf::Vector2f{ 30.f, 0.f });
	_collider.setOutlineColor(sf::Color::White);
	_collider.setOutlineThickness(colliderDrawThickness);
	_collider.setFillColor(sf::Color::Transparent);

	objectPosition = { 150.f, 100.f }; //set start position
}

void PlayerObject::Start()
{
}


void PlayerObject::Update(float deltaTime)
{
	float moveX = 0.f;

	if (Input::GetInput(sf::Keyboard::A))
		moveX -= 1.f; //left
	if (Input::GetInput(sf::Keyboard::D))
		moveX += 1.f; //right

	SetVelocityX(moveX * _playerSpeed * deltaTime);

	//jumping
	if (Input::GetInput(sf::Keyboard::Space) && !_jumped)
	{
		float jumpVelocity = -sqrt(2 * GRAVITY * _jumpHeight);

		sf::Vector2f force(0.f, 0.f);
		force.y = objectMass * jumpVelocity / _jumpTime;

		ApplyForce(force, deltaTime, true);
		_jumped = true;
	}

	_jumped = !_grounded; //reset jump

	//handle animation & texture swapping
	if(!_grounded)
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

	//handle flipping of sprite based on movement speed
	FlipSprite(2.f);

	GameObject::Update(deltaTime); //rest of the _game object update function
}
