#pragma once
#include "rocket.h"
#include "bboxed.h"

class Player : public Rocket,  public Bboxed {

    protected:
        std::string name;
        float rotationSpeed = 250;
        float throttleStep = 1;

    public:
    Player(std::string _name, float life, float damage, sf::Vector2f position, sf::FloatRect bbox, std::vector<Entity*> *renderQueue) : Rocket(_name, life, damage, position, renderQueue), Bboxed(bbox)  {
        name = _name;
        mass = 1000;
    };

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
    void throttleUp() {
        setThrottle(throttle + throttleStep * animationTime.asMilliseconds()/1000);
        
    }

    void throttleDown() {
        setThrottle(throttle - throttleStep * animationTime.asMilliseconds()/1000);
        
    }

    void rotateClockwise() {
        rotation -= rotationSpeed * animationTime.asMilliseconds()/1000;
    }
    void rotateCounterClockwise() {
        rotation += rotationSpeed * animationTime.asMilliseconds()/1000;
    }

	void animate() {
        Rocket::animate();
        checkBoundries();
        animationTimer.restart();
    }
};