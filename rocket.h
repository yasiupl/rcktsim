#pragma once
#include <math.h>
#include "entity.h"
#include "missle.h"

class Rocket : public Entity {

    protected:
        float life = 100;

        float springiness = 0.5;
        float rotationSpeed = 250;
        bool engineOn = false;
        float throttle = 0.3;
        float throttleStep = 1;
        float engineISP = 10;

        sf::Texture texture1;

        sf::Vector2i lookAtPoint;

    public:
    Rocket(sf::Vector2f _position, sf::Vector2f _bbox, sf::RenderTarget* _target, std::vector<Entity*> *_renderQueue) : Entity("rocket", 100, 10, _position, 0, _bbox, "rocket-off.png", 0.1, _target, _renderQueue)  {
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
            sprite.setTexture(texture);
            engineOn = false;
        } else {
            engineOn = true;
            sprite.setTexture(texture1);
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
            renderQueue->push_back(new Missle(getPosition(), getRotation(), bbox, target, renderQueue));
            cooldownTimer.restart();
        }
	}
 
    void checkCollision() {
        position = sprite.getPosition();
        if(position.x <= 0) {
            position.x = 0;
            velocity.x *= -1 * springiness;
        }
        if(position.y <= 0) {
            position.y = 0;
            velocity.y *= -1 * springiness;
        }
        if(position.x >= bbox.x) {
            position.x = bbox.x;
            velocity.x *= -1 * springiness;
        }
        if(position.y >= bbox.y) {
            position.y = bbox.y;
            velocity.y *= -1 * springiness;
        }
        sprite.setPosition(position);
        //std::cout<<position.x << ", " << position.y << ": " << velocity.x << ", " << velocity.y << std::endl;
    }
 
    void animate() {
        animationTime = animationTimer.getElapsedTime();

        //sprite.setRotation(atan(velocity.y/velocity.x) * 180 / 3.14159265);
        //sprite.rotate(((velocity.x > 0)? 1 : -1) * 90.f);
        sprite.setRotation(rotation);

        if(engineOn) {
            velocity.x += cos((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
            velocity.y += sin((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
        }
        
        sprite.move(velocity.x, velocity.y);

        checkCollision();

        animationTimer.restart();
    }

    void collide(Entity *entity) {
        if(entity->getType() != "explosion") {
            entity->attack(damage);
            sf::Vector2f colliderPosition = entity->getPosition();
            velocity.x += (colliderPosition.x - position.x)/2;
            velocity.y += (colliderPosition.y - position.y)/2;
            velocity.y *= -0.1 * springiness;
            velocity.x *= -0.1 * springiness;
        }
    }

    void destroy() {
        renderQueue->push_back(new Explosion(sprite.getPosition(), sprite.getRotation(), 2, bbox, target, renderQueue));
        stop();
    }
};