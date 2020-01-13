#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"


class Animation : public Entity {
	protected:
	float time;

	sf::IntRect rectangle;
	sf::Vector2i size;
	sf::Vector2i frames;
	
	public:
	Animation(sf::Vector2f position, float rotation, float scale, std::string texture, sf::Vector2i _size, sf::Vector2i _frames, float _time, std::vector<Entity*> *renderQueue): Entity("animation", 1000, 0, position, rotation - 90.f, texture, scale, renderQueue), rectangle(0, 0, _size.x, _size.y) {

		time = _time;
		size = _size;
		frames = _frames;
		
		sprite.setTextureRect(rectangle);
		sprite.setOrigin(size.x/2, size.y/2);
	};

	void animate() {
		if (animationTime.asMilliseconds() >= time) {
			if (rectangle.left >= size.x*frames.x) {
				rectangle.left = 0;
				rectangle.top += size.y;
			}
			else 
				rectangle.left += size.x;
		
			if (rectangle.top >= size.y*frames.y) {
				stop();
			}
			
			
			sprite.setTextureRect(rectangle);
			animationTimer.restart();
		}
	}

	void collide(Entity *entity) {};

	void destroy() {stop();};
};
