#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

// Entity is the base element of the gameplay. It is a Sprite on steroids with defined behaviour for collisons, and the flow of time.

class Entity {
	protected:
		bool dead = false;

		std::string type;

		float life, damage, mass = 1;

		std::vector<Entity*> *renderQueue;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position, velocity;

        sf::Clock animationTimer;
        sf::Time animationTime;

		sf::Clock cooldownTimer;
		sf::Time cooldownTime;

		sf::Clock lifeTimer;

		float rotation, scale;

	public:
		Entity(std::string _type, float _life, float _damage, sf::Vector2f _position, float _rotation, std::string _texture, float _scale, std::vector<Entity*> *_renderQueue) {
			type = _type;
			life = _life;
			damage = _damage;
			position = _position;

			renderQueue = _renderQueue;
			scale = _scale;
			rotation = _rotation;

			lifeTimer.restart();

        	texture.loadFromFile(_texture);
        	sprite.setTexture(texture);
        	sprite.setOrigin(texture.getSize().x /2, texture.getSize().y /2);
        	sprite.setScale(_scale, _scale);
        	sprite.setPosition(_position);
			sprite.setRotation(_rotation);
		}

	virtual void animate() = 0;

	virtual void destroy() = 0;

	virtual void collide(Entity *entity) = 0;

	void draw(sf::RenderTarget* target) {
		if(!dead) {
        	animate();
        	target->draw(sprite);
		}
    }

	void stop() {
		dead = true;
	}
	
	void lookAt(sf::Vector2f point) {
		position = sprite.getPosition();
		rotation = (atan2(point.y - position.y, point.x - position.x)) * 180 / 3.14159265;
    }

	float distanceTo(sf::Vector2f distant) {
		position = sprite.getPosition();
		return sqrt(pow(distant.x - position.x, 2) + pow(position.y - distant.x, 2));
	}

	bool attack(float _damage) {
        life -= _damage;
		//std::cout << life << " - " << _damage << " = " << life - _damage << std::endl;
        if (life <= 0) {
			destroy();
            stop();
            return 1;
        }
        return 0;
    }

	float getDamage() {
		return damage;
	}

	float getLife() {
		return life;
	}

	float getTime() {
		return lifeTimer.getElapsedTime().asMilliseconds();
	}

	bool isDead() {
		return dead;
	}

	sf::Vector2f getPosition() {
        return sprite.getPosition();
    } 
	sf::Vector2f getVelocity() {
        return velocity;
    } 

	void addVelocity(sf::Vector2f _velocity) {
		velocity += _velocity;
	}

	float getRotation() {
		return sprite.getRotation();
	}

	float getMass() {
		return mass;
	}

	sf::Rect<float> getHitbox() {
		return sprite.getGlobalBounds();
	}

	std::string getType() {
		return type;
	}
};