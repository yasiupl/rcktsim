#pragma once
#include "missle.h"

class Rocket: public Entity {

    protected:
		float rotationSpeed = 250;
        bool engineOn = false;
        float throttle = 0.3;
        float throttleStep = 1;
        float engineISP = 10;
		sf::Vector2i lookAtPoint;
        float springiness = 0.5;
		
        sf::Texture texture1;

    public:
    Rocket(std::string type, float life, float damage, sf::Vector2f position, std::vector<Entity*> *renderQueue) : Entity(type, life, damage, position, 0, "rocket-off.png", 0.1, renderQueue)  {
        texture1.loadFromFile("rocket-on.png");
        sprite.setOrigin(texture.getSize().x /2, texture.getSize().y /1.5);
    };

	void throttleUp() {
        if(throttle < 1) {
            throttle += throttleStep * animationTime.asMilliseconds()/1000;
        }
    }

    void throttleDown() {
        if(throttle > 0.3) {
            throttle -= throttleStep * animationTime.asMilliseconds()/1000;
        }
    }
    void throttleToggle() {
        if(engineOn == true) {
            engineOn = false;
        } else {
            engineOn = true;
        }
    }

    void rotateClockwise() {
        rotation -= rotationSpeed * animationTime.asMilliseconds()/1000;
    }
    void rotateCounterClockwise() {
        rotation += rotationSpeed * animationTime.asMilliseconds()/1000;
    }

    void lookAt(sf::Vector2i point) {
        if(point != lookAtPoint) {
            position = sprite.getPosition();
            rotation = (atan2(point.y - position.y, point.x - position.x) - 80.f) * 180 / 3.14159265;
            lookAtPoint = point;
        }
    }

    void spawnMissle() {
        cooldownTime = cooldownTimer.getElapsedTime();
        if(cooldownTime.asMilliseconds() > 50.0f) {
            renderQueue->push_back(new Missle(getPosition(), getRotation(), 10000, renderQueue));
            cooldownTimer.restart();
        }
	}
	
    void animate() {
        animationTime = animationTimer.getElapsedTime();

        //sprite.setRotation(atan(velocity.y/velocity.x) * 180 / 3.14159265);
        //sprite.rotate(((velocity.x > 0)? 1 : -1) * 90.f);
        sprite.setRotation(rotation);

        if(engineOn) {
            sprite.setTexture(texture1);
            velocity.x += cos((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
            velocity.y += sin((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
        } else sprite.setTexture(texture);
        
        sprite.move(velocity.x, velocity.y);

        animationTimer.restart();
    }

    void collide(Entity *entity) {
        if(entity->getType() != "animation") {
            entity->attack(damage);
            sf::Vector2f colliderPosition = entity->getPosition();
            velocity.x += (colliderPosition.x - position.x)/2;
            velocity.y += (colliderPosition.y - position.y)/2;
            velocity.y *= -0.1 * springiness;
            velocity.x *= -0.1 * springiness;
        }
    }

    void destroy() {
        renderQueue->push_back(new Animation(sprite.getPosition(), sprite.getRotation(), 2, "explosion.png", sf::Vector2i(96, 96), sf::Vector2i(4,4), 50.f, renderQueue));
        stop();
    }
};