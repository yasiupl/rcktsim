#pragma once
#include <math.h>
#include "entity.h"
#include "explosion.h"
#include "bboxed.h"


class Missle : public Entity, public Bboxed {
    protected:
        bool collidable = false;
        float speed = 1000;

    public:
    Missle(sf::Vector2f _position, float _rotation, sf::FloatRect _bbox, sf::RenderTarget* _target, std::vector<Entity*> *_renderQueue) : Entity("missle", 5, 20, _position, _rotation - 90.f, "missle.png", 0.1, _target, _renderQueue), Bboxed(_bbox) {

        velocity.x = cos(rotation *  3.14159265 / 180) * speed;
        velocity.y = sin(rotation *  3.14159265 / 180) * speed;

    }

     void checkBoundries() {
        if(!bbox.contains(sprite.getPosition())) destroy();
    }

    void collide(Entity *entity) {
        if(entity->getType() != getType())
            entity->attack(damage);
    }

    void destroy() {
        renderQueue->push_back(new Explosion(sprite.getPosition(), sprite.getRotation(), 0.5, target, renderQueue));
        stop();
    }

    void animate() {
        animationTime = animationTimer.getElapsedTime();

        sprite.move(velocity.x * animationTime.asMilliseconds()/1000, velocity.y * animationTime.asMilliseconds()/1000);

        checkBoundries();

        animationTimer.restart();
    }
}; 