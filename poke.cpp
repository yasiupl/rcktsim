#include <SFML/Graphics.hpp>
#include <iostream>

class Sprite {
    private:
        sf::Sprite sprite;
        float x_vel = 1;
        float y_vel = 1;
        sf::Vector2f position;
        sf::Texture texture;
        sf::Vector2f bbox;
        
    public:
    Sprite(float x, float y, float max_x, float max_y) {
        position.x = x;
        position.y = y;

        bbox.x = max_x;
        bbox.y = max_y;

        texture.loadFromFile("pokeball.png");
        sprite.setTexture(texture);
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
        if(position.x <= 0) x_vel *= -1;
        if(position.y <= 0) y_vel *= -1;
        if(position.x >= bbox.x) x_vel *= -1;
        if(position.y >= bbox.y) y_vel *= -1;
        std::cout<<position.x << ", " << position.y << std::endl;
    }
 
    void animate() {
        checkCollision();
        sprite.move(x_vel, y_vel);
        position = sprite.getPosition();
    }

    sf::Sprite getDrawable() {
        return sprite;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "rcktsim 0.0.0b1");
    window.setFramerateLimit(60);
    
    Sprite pokeball(100, 100, 520, 500);
    

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