#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

// Entity is the base element of the gameplay. It is a Sprite on steroids with defined behaviour for collisons, and the flow of time.

class Entity {
	protected:
		bool dead = false;
		bool active = true;

		int score = 0;
		
		std::string type;

		float maxLife, health, damage, rotation, scale, mass = 1;

		std::vector<Entity*> *renderQueue;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position, velocity;

        sf::Clock animationTimer;
        sf::Time animationTime;

		sf::Clock cooldownTimer;
		sf::Time cooldownTime;

		sf::Clock lifeTimer;

		sf::Time pauseTime;

	public:
		Entity(std::string _type, float _health, float _damage, sf::Vector2f _position, float _rotation, std::string _texture, float _scale, std::vector<Entity*> *_renderQueue) {
			type = _type;
			maxLife = _health;
			health = _health;
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

		virtual ~Entity() {
		}

	virtual void animate() {};

	virtual void destroy() {};

	virtual void collide(Entity *entity) {};

	void draw(sf::RenderTarget* target) {
		if(active == true) {
			cooldownTime = cooldownTimer.getElapsedTime() - pauseTime;
			animationTime = animationTimer.getElapsedTime() - pauseTime;
			pauseTime = pauseTime.Zero;
        	animate();
		} else {
			animationTimer.restart();
		}
		target->draw(sprite);
    }

	void resume() {
		pauseTime = animationTimer.getElapsedTime();
		active = true;
	}

	void pause() {
		active = false;
	}

	void stop() {
		dead = true;
		active = false;
	}


	float distanceTo(sf::Vector2f distant) {
		position = sprite.getPosition();
		return sqrt(pow(distant.x - position.x, 2) + pow(position.y - distant.x, 2));
	}

	void attack(Entity *enemy) {
        health -= enemy->getDamage();
		//std::cout << health << " - " << _damage << " = " << health - _damage << std::endl;
        if (health <= 0) {
			enemy->addPoint(maxLife);
			destroy();
            stop();
        }
    }

	void heal(float heal) {
		health += heal;
	}

	float getDamage() {
		return damage;
	}

	float getLife() {
		return health;
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

	void addPoint(int points) {
		score += points;
	}

	int getScore() {
		return score;
	}

	void lookAt(sf::Vector2f point) {
		position = sprite.getPosition();
		rotation = (atan2(point.y - position.y, point.x - position.x)) * 180 / 3.14159265;
    }
};