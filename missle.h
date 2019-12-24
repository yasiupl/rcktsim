#pragma once
#include <math.h>
#include "entity.h"
#include "explosion.h"


class Missle : public Entity {
    protected:
        float speed = 10;
        int life, damage;

    public:
    Missle(sf::Vector2f _position, float _rotation, sf::Vector2f _bbox, sf::RenderTarget* _target, std::vector<Entity*> *_renderQueue) : Entity(_position, _rotation - 90.f, _bbox, "missle.png", 0.1, _target, _renderQueue) {
    }

     void checkCollision() {
        position = sprite.getPosition();
        if(position.x <= 0) {
            position.x = 0;
            explode();
        }
        if(position.y <= 0) {
            position.y = 0;
            explode();
        }
        if(position.x >= bbox.x) {
            position.x = bbox.x;
            explode();
        }
        if(position.y >= bbox.y) {
            position.y = bbox.y;
            explode();
        }
        sprite.setPosition(position);
        //std::cout<<position.x << ", " << position.y << ": " << x_vel << ", " << y_vel << std::endl;
    }

    void explode() {
        if(!exploded) {
            renderQueue->push_back(new Explosion(sprite.getPosition(), sprite.getRotation(), bbox, target, renderQueue));
            stop();
        }
    }

    bool checkCollisionWithEntity(float x, float y, float radius) {
        position = sprite.getPosition();
        if(abs(x - position.x) < radius || abs(y - position.y) < radius) {
            return true;
        } else return false;
    }

    void animate() {
        animationTime = animationTimer.getElapsedTime();

        velocity.x += cos(rotation *  3.14159265 / 180) * speed;
        velocity.y += sin(rotation *  3.14159265 / 180) * speed;
        
        sprite.move(velocity.x * animationTime.asMilliseconds()/1000, velocity.y * animationTime.asMilliseconds()/1000);

        checkCollision();

        animationTimer.restart();
    }

}; 