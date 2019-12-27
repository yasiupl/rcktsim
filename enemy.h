#pragma once
#include "rocket.h"
#include "bboxed.h"

class Enemy : public Rocket,  public Bboxed {

    protected:
        std::string name;
        float rotationSpeed = 250;
        float throttleStep = 1;
		Entity *target;

    public:
    Enemy(std::string _name, sf::Vector2f position, sf::FloatRect bbox, Entity *_target, std::vector<Entity*> *renderQueue) : Rocket(_name, 100, 10, position, renderQueue), Bboxed(bbox)  {
        name = _name;
		target = _target;
    };

    void checkBoundries() {
        position = sprite.getPosition();
        if(!bbox.contains(sprite.getPosition())) destroy();
    }

	void animate() {
        Rocket::animate();
		Rocket::lookAt(target->getPosition());
        checkBoundries();
    }
};