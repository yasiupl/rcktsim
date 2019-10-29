#include <SFML/Graphics.hpp>

class Sprite {
    private:
        sf::CircleShape shape;
        float x_vel, y_vel = 0;
        
    public:
    Sprite(float x, float y, float size) {
        shape.setRadius(size);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(x, y);
    };

    sf::Vector2f getPostion() {
        return shape.getPosition();
    } 

    void setVelocityX(float x) {
        x_vel = x;
    } 

    void setVelocityY(float y) {
        y_vel = y;
    } 

    void setVelocity(float x, float y) {
        x_vel = x;
        y_vel = y;
    } 

    void animate() {
        sf::Vector2f postion = getPostion();
        shape.setPosition(postion.x + x_vel, postion.y + y_vel);
    }

    sf::CircleShape getDrawable() {
        return shape;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "rcktsim 0.0.0b1");
    window.setFramerateLimit(60);
    
    Sprite Circle(100, 100, 50.f);
    
    float speed = 10;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Circle.setVelocity(0,0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            Circle.setVelocityY(-1 * speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            Circle.setVelocityY(1 * speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            Circle.setVelocityX(-1 * speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            Circle.setVelocityX(1 * speed);
        }

        Circle.animate();
        window.clear();
        window.draw(Circle.getDrawable());
        window.display();
    }

    return 0;
};