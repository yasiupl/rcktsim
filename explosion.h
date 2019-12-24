#pragma once
#include "entity.h"

class Explosion : public Entity {
	protected:
		sf::IntRect rectangle;

	public:
		Explosion(sf::Vector2f _position, float _rotation, sf::Vector2f _bbox, sf::RenderTarget* _target, std::vector<Entity*> *_renderQueue) : Entity(_position, _rotation - 90.f, _bbox, "explosion.png", 1.0, _target, _renderQueue), rectangle(0, 0, 96, 96) {
			
			sprite.setTextureRect(rectangle);
			sprite.setOrigin(48, 48);
	}

	void animate() {
		if(dead == false) {
			animationTime = animationTimer.getElapsedTime();
		if (animationTime.asMilliseconds() >= 50.0f) {
			if (rectangle.left >= 4*96) {
				rectangle.left = 0;
				rectangle.top += 96;
			}
			else 
				rectangle.left += 96;
		
			if (rectangle.top >= 4*96) {
				stop();
			}
			
			
			sprite.setTextureRect(rectangle);
			animationTimer.restart();
		}
		}
	}
};
