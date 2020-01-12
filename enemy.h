#pragma once
#include "rocket.h"
#include "missle.h"
#include "bboxed.h"

class Enemy : public Rocket,  public Bboxed {

    protected:
		Entity *target;
        bool shoot = false;

    public:
    Enemy(std::string _name, float life, float damage, sf::Vector2f position, sf::FloatRect bbox, std::vector<Entity*> *renderQueue) : Rocket(_name, life, damage, position, renderQueue), Bboxed(bbox)  {
		target = this;
        sprite.setColor(sf::Color::Red);
    };

    void checkBoundries() {
        position = sprite.getPosition();
        if(!bbox.contains(sprite.getPosition())) destroy();
    }

    void targetEntity(Entity *_target) {
        target = _target;
    }

    void setAgressive() {
        shoot = true;
    }

	void animate() {
        if(shoot) {
            cooldownTime = cooldownTimer.getElapsedTime();
            if(cooldownTime.asMilliseconds() > rand() % 1000 + 1000.f) {
                Missle *missle = new Missle(this, 0, 30, bbox, renderQueue);
                missle->targetEntity(target);
                renderQueue->push_back(missle);
                cooldownTimer.restart();
            }
        }
        Rocket::animate();
		if(target != this) Rocket::lookAt(target->getPosition());
        checkBoundries();
    }
};