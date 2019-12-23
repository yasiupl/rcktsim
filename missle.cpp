#include <SFML/Graphics.hpp>
#include <math.h>

class Missle {
    private:
        sf::RenderTarget* target;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position, bbox, vel;
        sf::Clock animationTimer;
        sf::Time animationTime = animationTimer.getElapsedTime();
        
        float rotation, speed = 1000;
        int life, damage;

    public:
    Missle(sf::Vector2f _position, sf::Vector2f _bbox, float _rotation, sf::RenderTarget* _target) {
        position = _position;
        bbox = _bbox;
        rotation = _rotation - 90.f;
        target = _target;
		texture.loadFromFile("missle.png");
        sprite.setScale(0.1, 0.1);
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setRotation(rotation);
        vel.x = cos(rotation *  3.14159265 / 180) * speed;
        vel.y = sin(rotation *  3.14159265 / 180) * speed;
    }

     void checkCollision() {
        position = sprite.getPosition();
        if(position.x <= 0) {
            position.x = 0;
            vel.x = 0;
        }
        if(position.y <= 0) {
            position.y = 0;
            vel.y = 0;
        }
        if(position.x >= bbox.x) {
            position.x = bbox.x;
            vel.x = 0;
        }
        if(position.y >= bbox.y) {
            position.y = bbox.y;
            vel.y = 0;
        }
        sprite.setPosition(position);
        //std::cout<<position.x << ", " << position.y << ": " << x_vel << ", " << y_vel << std::endl;
    }

    bool checkCollisionWithEntity(float x, float y, float radius) {
        position = sprite.getPosition();
        if(abs(x - position.x) < radius || abs(y - position.y) < radius) {
            return true;
        } else return false;
    }

    void animate() {
        animationTime = animationTimer.getElapsedTime();
        
        sprite.move(vel.x * animationTime.asMilliseconds()/1000, vel.y * animationTime.asMilliseconds()/1000);

        checkCollision();

        animationTimer.restart();
    }

    void draw() {
        animate();
        target->draw(sprite);
    }

}; 