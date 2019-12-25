#pragma once
#include "entity.h"
#include <math.h>

class ControllableEntity : public Entity {
	protected:
		float rotationSpeed = 250;
        bool engineOn = false;
        float throttle = 0.3;
        float throttleStep = 1;
        float engineISP = 10;
		sf::Vector2i lookAtPoint;

	public:
	ControllableEntity(std::string _type, float _life, float _damage, sf::Vector2f _position, float _rotation, std::string _texture, float _scale, sf::RenderTarget* _target, std::vector<Entity*> *_renderQueue) : Entity(_type, _life, _damage, _position, _rotation, _texture, _scale, _target, _renderQueue) {
		

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

};
