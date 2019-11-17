#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define MAX_FPS 60

class Rocket {

    /* 
        Rocket Properties:
        Fuel
        No* Engines
        Thrust per engine

        Landing legs animated sprite.

        Controlls for the rocket:
        Thrust on / off (space)
        Throttle 0.3-1.0 (W/S)
        Engine Gimbal (A/D)
        RCS rotate clockwise/counter clockwise (only above atmosphere, turn on E key) (A/D)
        Deploy legs (Q)
    */

    private:
        sf::Sprite sprite;
        float x_vel = 0;
        float y_vel = 0;
        float springiness = 0;
        float rotation;
        float rotationSpeed = 5;
        bool engineOn = false;
        float throttle = 0.3;
        float throttleStep = 0.1;
        float engineISP = 10;

        sf::Vector2f position;
        sf::Vector2f bbox;

        sf::Clock animationTimer;

        sf::Texture texture;
        sf::Texture texture1;
        
    public:
    Rocket(sf::Vector2f _position, float scale, sf::Vector2f _bbox, float _springiness) {
        position = _position;

        bbox = _bbox;

        springiness = _springiness;

        texture.loadFromFile("rocket-off.png");
        texture1.loadFromFile("rocket-on.png");
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x /2, texture.getSize().y /1.5);
        sprite.setScale(scale, scale);
        sprite.setPosition(position);
        
    };

    sf::Vector2f getPostion() {
        return sprite.getPosition();
    } 

    void throttleUp() {
        if(throttle < 1) {
            throttle += throttleStep;
        }
    }

    void throttleDown() {
        if(throttle > 0.3) {
            throttle -= throttleStep;
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
        rotation -= rotationSpeed;
    }
    void rotateCounterClockwise() {
        rotation += rotationSpeed;
    }
 
    void checkCollision() {
        position = sprite.getPosition();
        if(position.x <= 0) {
            position.x = 0;
            x_vel *= -1 * springiness;
        }
        if(position.y <= 0) {
            position.y = 0;
            y_vel *= -1 * springiness;
        }
        if(position.x >= bbox.x) {
            position.x = bbox.x;
            x_vel *= -1 * springiness;
        }
        if(position.y >= bbox.y) {
            position.y = bbox.y;
            y_vel *= -1 * springiness;
        }
        sprite.setPosition(position);
        //std::cout<<position.x << ", " << position.y << ": " << x_vel << ", " << y_vel << std::endl;
    }
 
    void animate() {
        sf::Time time = animationTimer.getElapsedTime();
        
        //sprite.setRotation(atan(y_vel/x_vel) * 180 / 3.14159265);
        //sprite.rotate(((x_vel > 0)? 1 : -1) * 90.f);
        sprite.setRotation(rotation);

        if(engineOn) {
            x_vel += cos((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * time.asMilliseconds()/1000;
            y_vel += sin((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * time.asMilliseconds()/1000;
        }
        
        sprite.move(x_vel, y_vel);

        checkCollision();

        animationTimer.restart();
    }

    sf::Sprite getDrawable() {
        return sprite;
    }
};

class Game {
    
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "rcktsim 0.0.0b2");

    //TODO: Implement correct animation frame limit
    //window.setFramerateLimit(60);
    sf::Vector2f startPosition;
    startPosition.x = 100;
    startPosition.y = 100;
    sf::Vector2f bbox;
    bbox.x = (float)window.getSize().x;
    bbox.y = (float)window.getSize().y;
    Rocket falcon(startPosition, 0.5, bbox, 0.5);
    
    sf::Clock loopTimer;
	sf::Time loopTime;

    while (window.isOpen())
    {
        loopTimer.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                falcon.throttleToggle();
            }   
        
        }

        
        //pokeball.setVelocity(0,0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            falcon.throttleUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            falcon.throttleDown();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            falcon.rotateClockwise();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            falcon.rotateCounterClockwise();
        }

        falcon.animate();
        window.clear();
        window.draw(falcon.getDrawable());
        window.display();
        
        while(1) {
            loopTime = loopTimer.getElapsedTime();
            if (loopTime.asMilliseconds() > 1000/MAX_FPS) {
                //std::cout<< "Waited " << loopTime.asMilliseconds() << std::endl; 
                break;
            }
			
        }
    }

    return 0;
};