#pragma once
#include "missle.h"

class Rocket: public Entity {

    protected:
		bool engineOn = false;
		float springiness = 0.5;
		float throttle = 0.3;
		float engineISP = 10;
        sf::Texture texture1;

    public:
    Rocket(std::string type, float life, float damage, sf::Vector2f position, std::vector<Entity*> *renderQueue) : Entity(type, life, damage, position, 0, "assets/sprites/rocket-off.png", 0.1, renderQueue)  {
        texture1.loadFromFile("assets/sprites/rocket-on.png");
        sprite.setOrigin(texture.getSize().x /2, texture.getSize().y /1.5);
        mass = 500;
    };

	void throttleToggle() {
        if(engineOn == true) {
            engineOn = false;
        } else {
            engineOn = true;
        }
    }

	void setThrottle(float _throttle) {
		if(_throttle > 0.3 && _throttle <= 1) throttle = _throttle;
	}

    void spawnMissle() {
        cooldownTime = cooldownTimer.getElapsedTime();
        if(cooldownTime.asMilliseconds() > 100.0f) {
            renderQueue->push_back(new Missle(this, 0, 30, 1000, 5000, renderQueue));
            cooldownTimer.restart();
        }
	}

	void animate() {
        sprite.setRotation(rotation + 90.f);

        if(engineOn) {
            sprite.setTexture(texture1);
            velocity.x += cos((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
            velocity.y += sin((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
        } else sprite.setTexture(texture);
        
        sprite.move(velocity.x, velocity.y);
        animationTimer.restart();
	};
	
    void collide(Entity *entity) {
        if(entity->getType() != Rocket::getType() && entity->getType() != "animation") {
            entity->attack(this);
            
            float colliderMass = entity->getMass();
            sf::Vector2f colliderPosition = entity->getPosition();
            sf::Vector2f colliderVelocity = entity->getVelocity();
            sf::Vector2f DeltaPosition = colliderPosition - position;
            sf::Vector2f DeltaVelocity = colliderVelocity - velocity;

            //calculation of new velocities:
            velocity += (colliderMass / (mass + colliderMass)) * (float)(((DeltaVelocity.x * DeltaPosition.x) + (DeltaVelocity.y * DeltaPosition.y)) / (pow((DeltaPosition.x), 2) + pow((DeltaPosition.y), 2))) * DeltaPosition;
        }
    }

    void destroy() {
        renderQueue->push_back(new Animation(sprite.getPosition(), sprite.getRotation(), 2, "assets/sprites/explosion.png", sf::Vector2i(96, 96), sf::Vector2i(4,4), 50.f, renderQueue));       
        stop();
    }
};