#include "SFML/Graphics.hpp"

class Explosion : public Entity {
	protected:
	sf::IntRect rect(0, 0, 96, 96);

	public:
	Explosion(sf::Vector2f _position, float _rotation, sf::Vector2f _bbox, sf::RenderTarget* _target) : Entity(_position, _rotation -90.f, _bbox, _target, "explosion.png", 0.1) {
		sprite.setOrigin(texture.getSize().x /2, texture.getSize().y /2);
		sprite.setTextureRect(rect);
	}

	void animate() {
		animationTime = animationTimer.getElapsedTime();
		if (animationTime > 50.0f) {
			if (rect.left >= 5*96)
				rect.left = 0;
			else 
				rect.left += 96;
		
			if (rect.top >= 4*96)
				rect.top = 0;
			else 
				rect.top += 96;
			
			animationTimer.restart();
		}
	}
};
