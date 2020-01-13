#pragma once
#include <math.h>
#include "entity.h"
#include "animation.h"
#include "bboxed.h"


class Missle : public Entity, public Bboxed {
    protected:
        Entity *parent;
        Entity *target = this;
        bool bounded = false;
        float time = 0;
        float speed = 1000;

    public:
    Missle(Entity *_parent, float life, float damage, float _speed, float _time, std::vector<Entity*> *renderQueue) : Entity(_parent->getType(), life, damage, _parent->getPosition(), _parent->getRotation() - 90.f, "assets/sprites/missle.png", 0.1, renderQueue), Bboxed(sf::FloatRect(0, 0, 0, 0)) {
        parent = _parent;
        speed = _speed;
        time = _time;
        mass = 1;
    }
    Missle(Entity *_parent, float life, float damage, float _speed, sf::FloatRect bbox, std::vector<Entity*> *renderQueue) : Entity(_parent->getType(), life, damage, _parent->getPosition(), _parent->getRotation() - 90.f, "assets/sprites/missle.png", 0.1, renderQueue), Bboxed(bbox) {
        parent = _parent;
        bounded = true;
        speed = _speed;
        mass = 1;
    }
    Missle(std::string type, float life, float damage, float _speed, sf::Vector2f position, float rotation, float _time, std::vector<Entity*> *renderQueue) : Entity(type, life, damage, position, rotation - 90.f, "assets/sprites/missle.png", 0.1, renderQueue), Bboxed(sf::FloatRect(0, 0, 0, 0)) {
        parent = this;
        time = _time;
        speed = _speed;
        mass = 1;
    }
    Missle(std::string type, float life, float damage, float _speed, sf::Vector2f position, float rotation, sf::FloatRect bbox, std::vector<Entity*> *renderQueue) : Entity(type, life, damage, position, rotation - 90.f, "assets/sprites/missle.png", 0.1, renderQueue), Bboxed(bbox) {
        parent = this;
        bounded = true;
        speed = _speed;
        mass = 1;
    }

    void checkBoundries() {
        if(bounded) {
            if(!bbox.contains(sprite.getPosition())) destroy();
        } else if(getTime() > time) destroy();
    }

    void targetEntity(Entity *_target) {
        target = _target;
    }

    void collide(Entity *entity) {
        if(entity->getType() != getType() && entity->getTime() > 100.f && Missle::getTime() > 100.f && entity->getType() != "animation") {
            entity->attack(this);
            if(parent != this) parent->addPoint(score);
        }
        
    }

    void destroy() {
        renderQueue->push_back(new Animation(sprite.getPosition(), sprite.getRotation(), 0.5f, "assets/sprites/explosion.png", sf::Vector2i(96, 96), sf::Vector2i(4,4), 50.f, renderQueue));
        stop();
    }

    void animate() {

        if(target != this) Entity::lookAt(target->getPosition());

        velocity.x = cos(rotation *  3.14159265 / 180) * speed;
        velocity.y = sin(rotation *  3.14159265 / 180) * speed;

        sprite.setRotation(rotation);
        sprite.move(velocity.x * animationTime.asMilliseconds()/1000, velocity.y * animationTime.asMilliseconds()/1000);
    
        checkBoundries();
        animationTimer.restart();
    }
}; 