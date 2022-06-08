#include "ResourceManager.h"

#include <SFML/Graphics.hpp>
#include <cstdio>

namespace nadpher
{
template <typename T>
std::unordered_map<std::string, std::shared_ptr<T>> ResourceManager<T>::resources_;

template <>
std::shared_ptr<sf::Font> ResourceManager<sf::Font>::get(const std::string& key)
{
	if (!resources_.count(key))
	{
		sf::Font font;
		if (!font.loadFromFile(key))
		{
			printf("Couldn't load %s\n", key.c_str());
			return nullptr;
		}

		resources_[key] = std::make_shared<sf::Font>(font);
	}

	return resources_[key];
}

}