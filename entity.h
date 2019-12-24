#pragma once
#include <SFML/Graphics.hpp>

class Entity {
	protected:
		bool exploded = false;
		std::vector<Entity*> *renderQueue;
		sf::RenderTarget *target;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position, bbox, velocity;
        sf::Clock animationTimer;
        sf::Time animationTime;

		float rotation, scale;

	public:
		Entity(sf::Vector2f _position, float _rotation, sf::Vector2f _bbox, std::string _texture, float _scale, sf::RenderTarget* _target, std::vector<Entity*> *_renderQueue) {
			position = _position;
        	bbox = _bbox;
        	target = _target;
			renderQueue = _renderQueue;
			scale = _scale;
			rotation = _rotation;

			animationTime = animationTimer.getElapsedTime();

        	texture.loadFromFile(_texture);
        	sprite.setTexture(texture);
        	sprite.setOrigin(texture.getSize().x /2, texture.getSize().y /2);
        	sprite.setScale(_scale, _scale);
        	sprite.setPosition(_position);
			sprite.setRotation(_rotation);
		}

	virtual void animate() = 0;

	void draw() {
		if(!exploded) {
        	animate();
        	target->draw(sprite);
		}
    }

	void stop() {
		exploded = true;
	}

	bool isExploded() {
		return exploded;
	}
};