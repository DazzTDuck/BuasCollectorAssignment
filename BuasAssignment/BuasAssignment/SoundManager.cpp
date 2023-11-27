#include "SoundManager.h"

#include <iostream>

SoundManager* SoundManager::_instance = nullptr;

SoundManager::SoundManager()
{
	_instance = this; //initialize singleton
};

SoundManager& SoundManager::Get()
{
	return *_instance;
}

void SoundManager::LoadSounds()
{
	_instance->_soundDefinitions["Collect"] = _instance->BufferLoadFile("Assets/Sounds/collect.wav");
	_instance->_soundDefinitions["Jump"] = _instance->BufferLoadFile("Assets/Sounds/jump.wav");
}

sf::SoundBuffer* SoundManager::BufferLoadFile(const std::string& path)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer;
	if(!buffer->loadFromFile(path))
	{
		std::cout << "ERROR LOADING SOUND" << "\n";
		return nullptr;
	}

	return buffer;
}

sf::SoundBuffer* SoundManager::GetSoundFile(const std::string& soundType)
{
	return _instance->_soundDefinitions.at(soundType);
}


SoundManager::~SoundManager()
{
	for (auto sounds : _instance->_soundDefinitions)
	{
		delete sounds.second;
	}
}
