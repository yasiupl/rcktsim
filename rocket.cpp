#include <SFML/Graphics.hpp>
#include <math.h>

class Rocket : public Entity {

    protected:
        float springiness = 0.5;
        float rotationSpeed = 250;
        bool engineOn = false;
        float throttle = 0.3;
        float throttleStep = 1;
        float engineISP = 10;

        sf::Texture texture1;

    public:
    Rocket(sf::Vector2f _position, sf::Vector2f _bbox, sf::RenderTarget* _target, std::vector<Entity*> *_renderQueue) : Entity(_position, 0, _bbox, "rocket-off.png", 0.1, _target, _renderQueue)  {

        texture1.loadFromFile("rocket-on.png");
        sprite.setOrigin(texture.getSize().x /2, texture.getSize().y /1.5);
    };

    sf::Vector2f getPosition() {
        return sprite.getPosition();
    } 

	float getRotation() {
		return sprite.getRotation();
	}

    void throttleUp() {
        if(throttle < 1) {
            throttle += throttleStep * animationTime.asMilliseconds()/1000;
        }
    }

    void throttleDown() {
        if(throttle > 0.3) {
            throttle -= throttleStep * animationTime.asMilliseconds()/1000;
        }
    }
    void throttleToggle() {
        if(engineOn == true) {
            sprite.setTexture(texture);
            engineOn = false;
        } else {
            engineOn = true;
            sprite.setTexture(texture1);
        }
    }

    void rotateClockwise() {
        rotation -= rotationSpeed * animationTime.asMilliseconds()/1000;
    }
    void rotateCounterClockwise() {
        rotation += rotationSpeed * animationTime.asMilliseconds()/1000;
    }

    void spawnMissle() {
        Missle* missle;
        missle = new Missle(getPosition(), getRotation(), bbox, target, renderQueue);
		renderQueue->push_back(missle);
	}
 
    void checkCollision() {
        position = sprite.getPosition();
        if(position.x <= 0) {
            position.x = 0;
            velocity.x *= -1 * springiness;
        }
        if(position.y <= 0) {
            position.y = 0;
            velocity.y *= -1 * springiness;
        }
        if(position.x >= bbox.x) {
            position.x = bbox.x;
            velocity.x *= -1 * springiness;
        }
        if(position.y >= bbox.y) {
            position.y = bbox.y;
            velocity.y *= -1 * springiness;
        }
        sprite.setPosition(position);
        //std::cout<<position.x << ", " << position.y << ": " << velocity.x << ", " << velocity.y << std::endl;
    }
 
    void animate() {
        animationTime = animationTimer.getElapsedTime();

        //sprite.setRotation(atan(velocity.y/velocity.x) * 180 / 3.14159265);
        //sprite.rotate(((velocity.x > 0)? 1 : -1) * 90.f);
        sprite.setRotation(rotation);

        if(engineOn) {
            velocity.x += cos((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
            velocity.y += sin((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
        }
        
        sprite.move(velocity.x, velocity.y);

        checkCollision();

        animationTimer.restart();
    }
};