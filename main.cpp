#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Sprite {
    private:
        sf::Sprite sprite;
        float x_vel = 1;
        float y_vel = 1;
        float springiness = 0.8;
        sf::Vector2f position;
        sf::Texture texture;
        sf::Vector2f bbox;
        
    public:
    Sprite(sf::Vector2f _position, float scale, sf::Vector2f _bbox, float _springiness) {
        position = _position;

        bbox = _bbox;

        springiness = _springiness;

        texture.loadFromFile("rocket.png");
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x /2, texture.getSize().y /1.5);
        sprite.setScale(scale, scale);
        sprite.setPosition(position);
        
    };

    sf::Vector2f getPostion() {
        return sprite.getPosition();
    } 

    void setVelocityX(float x) {
        x_vel += x;
    } 

    void setVelocityY(float y) {
        y_vel += y;
    } 

    void setVelocity(float x, float y) {
        x_vel += x;
        y_vel += y;
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
        std::cout<<position.x << ", " << position.y << ": " << x_vel << ", " << y_vel << std::endl;
    }
 
    void animate() {
        sprite.move(x_vel, y_vel);
        sprite.setRotation(atan(y_vel/x_vel) * 180 / 3.14159265);
        sprite.rotate(((x_vel > 0)? 1 : -1) * 90.f);
        checkCollision();
    }

    sf::Sprite getDrawable() {
        return sprite;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "rcktsim 0.0.0b2");

    //TODO: Implement correct animation frame limit
    window.setFramerateLimit(60);
    sf::Vector2f startPosition;
    startPosition.x = 100;
    startPosition.y = 100;
    sf::Vector2f bbox;
    bbox.x = (float)window.getSize().x;
    bbox.y = (float)window.getSize().y;
    Sprite pokeball(startPosition, 0.5, bbox, 0.5);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        //pokeball.setVelocity(0,0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            pokeball.setVelocityY(-0.1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            pokeball.setVelocityY(0.1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            pokeball.setVelocityX(-0.1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            pokeball.setVelocityX(0.1);
        }

        pokeball.animate();
        window.clear();
        window.draw(pokeball.getDrawable());
        window.display();
    }

    return 0;
};