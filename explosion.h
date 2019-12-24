#pragma once
#include "entity.h"

class Explosion : public Entity {
	protected:
		sf::IntRect rectangle(0, 0, 96, 96);

	public:
		Explosion(sf::Vector2f _position, float _rotation, sf::Vector2f _bbox, sf::RenderTarget* _target, std::vector<Entity*> *_renderQueue) : Entity(_position, _rotation - 90.f, _bbox, "explosion.png", 0.1, _target, _renderQueue) {
			sprite.setOrigin(texture.getSize().x /2, texture.getSize().y /2);
			sprite.setTextureRect(rectangle);
	}

	void animate() {
		animationTime = animationTimer.getElapsedTime();
		if (animationTime > 50.0f) {
			if (rectangle.left >= 5*96)
				rectangle.left = 0;
			else 
				rectangle.left += 96;
		
			if (rectangle.top >= 4*96)
				rectangle.top = 0;
			else 
				rectangle.top += 96;
			
			animationTimer.restart();
		}
	}
};
