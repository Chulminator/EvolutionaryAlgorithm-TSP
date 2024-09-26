#pragma once

#include <SFML/Graphics.hpp>
#include <type_traits> // For std::is_same_v

template <typename Entity>
class BlinkEntity: public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
	static_assert(std::is_base_of<sf::Drawable, Entity>::value, "Entity must inherit from sf::Drawable");
	static_assert(std::is_base_of<sf::Transformable, Entity>::value, "Entity must inherit from sf::Transformable");

public:
	BlinkEntity();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool update(sf::Time dt);
	bool handleEvent(const sf::Event& event);

	void setEntity(Entity& entity_);
	void startBlink();

	Entity entity;  // Store the entity
private:
	sf::Time blinkTime;
	// Entity entity;  // Store the entity
	bool flagBlink;
};

#include "BlinkEntity.inl"
