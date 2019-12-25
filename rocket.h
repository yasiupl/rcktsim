#pragma once
#include "controllable.h"
#include "missle.h"
#include "bboxed.h"

class Rocket : public ControllableEntity, public Bboxed {

    protected:
        float springiness = 0.5;

        sf::Texture texture1;

    public:
    Rocket(sf::Vector2f _position, sf::FloatRect _bbox, std::vector<Entity*> *_renderQueue) : ControllableEntity("rocket", 100, 10, _position, 0, "rocket-off.png", 0.1, _renderQueue), Bboxed(_bbox)  {
        texture1.loadFromFile("rocket-on.png");
        sprite.setOrigin(texture.getSize().x /2, texture.getSize().y /1.5);
    };

    void spawnMissle() {
        cooldownTime = cooldownTimer.getElapsedTime();
        if(cooldownTime.asMilliseconds() > 50.0f) {
            renderQueue->push_back(new Missle(getPosition(), getRotation(), bbox, renderQueue));
            cooldownTimer.restart();
        }
	}
 
    void checkBoundries() {
        position = sprite.getPosition();
        if(!bbox.contains(position)) {
            if(position.x <= bbox.left) {
                position.x = bbox.left;
                velocity.x *= -1 * springiness;
            }
            if(position.y <= bbox.top) {
                position.y = bbox.top;
                velocity.y *= -1 * springiness;
            }
            if(position.x >= (bbox.width - bbox.left)) {
                position.x = (bbox.width - bbox.left);
                velocity.x *= -1 * springiness;
            }
            if(position.y >= (bbox.height - bbox.top)) {
                position.y = (bbox.height - bbox.top);
                velocity.y *= -1 * springiness;
            }
            sprite.setPosition(position);
        }
        //std::cout<<position.x << ", " << position.y << ": " << velocity.x << ", " << velocity.y << std::endl;
    }
 
    void animate() {
        animationTime = animationTimer.getElapsedTime();

        //sprite.setRotation(atan(velocity.y/velocity.x) * 180 / 3.14159265);
        //sprite.rotate(((velocity.x > 0)? 1 : -1) * 90.f);
        sprite.setRotation(rotation);

        if(engineOn) {
            sprite.setTexture(texture1);
            velocity.x += cos((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
            velocity.y += sin((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
        } else sprite.setTexture(texture);
        
        sprite.move(velocity.x, velocity.y);

        checkBoundries();

        animationTimer.restart();
    }

    void collide(Entity *entity) {
        if(entity->getType() != "animation") {
            entity->attack(damage);
            sf::Vector2f colliderPosition = entity->getPosition();
            velocity.x += (colliderPosition.x - position.x)/2;
            velocity.y += (colliderPosition.y - position.y)/2;
            velocity.y *= -0.1 * springiness;
            velocity.x *= -0.1 * springiness;
        }
    }

    void destroy() {
        renderQueue->push_back(new Animation(sprite.getPosition(), sprite.getRotation(), 2, "explosion.png", sf::Vector2i(96, 96), sf::Vector2i(4,4), 50.f, renderQueue));
        stop();
    }
};