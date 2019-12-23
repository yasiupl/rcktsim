#include <SFML/Graphics.hpp>
#include <math.h>

class Projectile {
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position, bbox, vel;
        sf::Clock animationTimer;
        sf::Time animationTime = animationTimer.getElapsedTime();
        
        float rotation, speed = 10;
        int life, damage;

    public:
    Projectile(sf::Vector2f _position, sf::Vector2f _bbox, float spawn_ang) {
        position = _position;
        bbox = _bbox;
        rotation = spawn_ang;
        sprite.setTexture(texture);
        vel.x = cos((sprite.getRotation() - 90.f) *  3.14159265 / 180) * speed;
        vel.y = sin((sprite.getRotation() - 90.f) *  3.14159265 / 180) * speed;
    }

     void checkCollision() {
        position = sprite.getPosition();
        if(position.x <= 0) {
            position.x = 0;
        }
        if(position.y <= 0) {
            position.y = 0;
        }
        if(position.x >= bbox.x) {
            position.x = bbox.x;
        }
        if(position.y >= bbox.y) {
            position.y = bbox.y;
        }
        sprite.setPosition(position);
        //std::cout<<position.x << ", " << position.y << ": " << x_vel << ", " << y_vel << std::endl;
    }
 
    void animate() {
        animationTime = animationTimer.getElapsedTime();

        //sprite.setRotation(atan(y_vel/x_vel) * 180 / 3.14159265);
        //sprite.rotate(((x_vel > 0)? 1 : -1) * 90.f);
        sprite.setRotation(rotation);
        
        sprite.move(vel.x * animationTime.asMilliseconds()/1000, vel.y * animationTime.asMilliseconds()/1000);

        checkCollision();

        animationTimer.restart();
    }

    void draw(sf::RenderTarget* target) {
        animate();
        target->draw(sprite);
    }

}; 