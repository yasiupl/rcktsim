#pragma once
#include "rocket.h"
#include "missle.h"
#include "bboxed.h"

class Enemy : public Rocket,  public Bboxed {

    protected:
		Entity *target;
        int difficulty = 0;

    public:
    Enemy(std::string _name, float life, float damage, sf::Vector2f position, sf::FloatRect bbox, std::vector<Entity*> *renderQueue) : Rocket(_name, life, damage, position, renderQueue), Bboxed(bbox)  {
		target = this;
        sprite.setColor(sf::Color::Red);
    };

    void checkBoundries() {
        position = sprite.getPosition();
        if(!bbox.contains(sprite.getPosition())) stop();
    }

    void targetEntity(Entity *_target) {
        target = _target;
    }

    void setDifficulty(int _difficulty) {
        difficulty = _difficulty;
    }

	void animate() {
        if(difficulty >= 3) {
            cooldownTime = cooldownTimer.getElapsedTime();
            if(cooldownTime.asMilliseconds() > rand() % 2000 + 1000.f) {
                Missle *missle = new Missle(this, 0, 30, 500, 2000, renderQueue);
                if(difficulty == 4) missle->targetEntity(target);
                renderQueue->push_back(missle);
                cooldownTimer.restart();
            }
        }
        Rocket::animate();
		if(target != this) Rocket::lookAt(target->getPosition());
        checkBoundries();
    }
};