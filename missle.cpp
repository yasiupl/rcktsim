#include <SFML/Graphics.hpp>
#include <math.h>

class Missle : public Entity {
    protected:
        float speed = 1000;
        int life, damage;

    public:
    Missle(sf::Vector2f _position, float _rotation, sf::Vector2f _bbox, sf::RenderTarget* _target, std::vector<Entity*> *_renderQueue) : Entity(_position, _rotation - 90.f, _bbox, "missle.png", 0.1, _target, _renderQueue) {
        velocity.x = cos(rotation *  3.14159265 / 180) * speed;
        velocity.y = sin(rotation *  3.14159265 / 180) * speed;
    }

     void checkCollision() {
        position = sprite.getPosition();
        if(position.x <= 0) {
            position.x = 0;
            velocity.x = 0;
            velocity.y = 0;
        }
        if(position.y <= 0) {
            position.y = 0;
            velocity.x = 0;
            velocity.y = 0;
        }
        if(position.x >= bbox.x) {
            position.x = bbox.x;
            velocity.x = 0;
            velocity.y = 0;
        }
        if(position.y >= bbox.y) {
            position.y = bbox.y;
            velocity.x = 0;
            velocity.y = 0;
        }
        sprite.setPosition(position);
        //std::cout<<position.x << ", " << position.y << ": " << x_vel << ", " << y_vel << std::endl;
    }

    void explode() {
        
    }

    bool checkCollisionWithEntity(float x, float y, float radius) {
        position = sprite.getPosition();
        if(abs(x - position.x) < radius || abs(y - position.y) < radius) {
            return true;
        } else return false;
    }

    void animate() {
        animationTime = animationTimer.getElapsedTime();
        
        sprite.move(velocity.x * animationTime.asMilliseconds()/1000, velocity.y * animationTime.asMilliseconds()/1000);

        checkCollision();

        animationTimer.restart();
    }

}; 