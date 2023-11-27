#pragma once
#include <map>
#include <string>
#include <SFML/Audio/SoundBuffer.hpp>

class SoundManager
{

public:
	SoundManager();

	static SoundManager& Get();
	static void LoadSounds();
	static sf::SoundBuffer* GetSoundFile(const std::string& soundType);

	~SoundManager();

private:
	static SoundManager* _instance;
	sf::SoundBuffer* BufferLoadFile(const std::string& path);
	std::map<std::string, sf::SoundBuffer*> _soundDefinitions = {};
};

