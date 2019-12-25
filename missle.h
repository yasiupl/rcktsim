#pragma once
#include <math.h>
#include "entity.h"
#include "explosion.h"


class Missle : public Entity {
    protected:
        bool collidable = false;
        float speed = 1000;

    public:
    Missle(sf::Vector2f _position, float _rotation, sf::Vector2f _bbox, sf::RenderTarget* _target, std::vector<Entity*> *_renderQueue) : Entity("missle", 5, 20, _position, _rotation - 90.f, _bbox, "missle.png", 0.1, _target, _renderQueue) {

        velocity.x = cos(rotation *  3.14159265 / 180) * speed;
        velocity.y = sin(rotation *  3.14159265 / 180) * speed;

    }

     void checkCollision() {
        position = sprite.getPosition();
        
        if(position.x <= 0) {
            position.x = 0;
            destroy();
        }
        if(position.y <= 0) {
            position.y = 0;
            destroy();
        }
        if(position.x >= bbox.x) {
            position.x = bbox.x;
            destroy();
        }
        if(position.y >= bbox.y) {
            position.y = bbox.y;
            destroy();
        }
        sprite.setPosition(position);
    }

    void collide(Entity *entity) {
        if(entity->getType() != getType())
            entity->attack(damage);
    }

    void destroy() {
        renderQueue->push_back(new Explosion(sprite.getPosition(), sprite.getRotation(), 0.5, bbox, target, renderQueue));
        stop();
    }

    void animate() {
        animationTime = animationTimer.getElapsedTime();

        sprite.move(velocity.x * animationTime.asMilliseconds()/1000, velocity.y * animationTime.asMilliseconds()/1000);

        checkCollision();

        animationTimer.restart();
    }
}; 