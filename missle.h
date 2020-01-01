#pragma once
#include <math.h>
#include "entity.h"
#include "animation.h"
#include "bboxed.h"


class Missle : public Entity, public Bboxed {
    protected:
        bool bounded = false;
        float time = 0;
        float speed = 1000;

    public:
    Missle(std::string type, float life, float damage, sf::Vector2f position, float rotation, float _time, std::vector<Entity*> *renderQueue) : Entity(type, life, damage, position, rotation - 90.f, "assets/sprites/missle.png", 0.1, renderQueue), Bboxed(sf::FloatRect(0, 0, 0, 0)) {
        time = _time;
    }
    Missle(std::string type, float life, float damage, sf::Vector2f position, float rotation, sf::FloatRect bbox, std::vector<Entity*> *renderQueue) : Entity(type, life, damage, position, rotation - 90.f, "assets/sprites/missle.png", 0.1, renderQueue), Bboxed(bbox) {
        bounded = true;
    }

    void checkBoundries() {
        if(bounded) {
            if(!bbox.contains(sprite.getPosition())) destroy();
        } else if(getTime() > time) destroy();
    }

    void collide(Entity *entity) {
        if(entity->getType() != getType() && entity->getTime() > 100.f && Missle::getTime() > 100.f)
            entity->attack(damage);
    }

    void destroy() {
        renderQueue->push_back(new Animation(sprite.getPosition(), sprite.getRotation(), 0.5f, "assets/sprites/explosion.png", sf::Vector2i(96, 96), sf::Vector2i(4,4), 50.f, renderQueue));
        stop();
    }

    void animate() {

        animationTime = animationTimer.getElapsedTime();

        velocity.x = cos(rotation *  3.14159265 / 180) * speed;
        velocity.y = sin(rotation *  3.14159265 / 180) * speed;

        sprite.setRotation(rotation);
        sprite.move(velocity.x * animationTime.asMilliseconds()/1000, velocity.y * animationTime.asMilliseconds()/1000);
    
        checkBoundries();

        animationTimer.restart();
    }
}; 