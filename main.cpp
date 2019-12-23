#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define MAX_FPS 60

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

class Rocket {

    private:
        sf::RenderTarget* target;
        sf::Sprite sprite;
        float x_vel = 0;
        float y_vel = 0;
        float springiness = 0;
        float rotation = 0;
        float rotationSpeed = 250;
        bool engineOn = false;
        float throttle = 0.3;
        float throttleStep = 1;
        float engineISP = 10;

        sf::Vector2f position;
        sf::Vector2f bbox;

        sf::Clock animationTimer;

        sf::Texture texture;
        sf::Texture texture1;

        sf::Time animationTime = animationTimer.getElapsedTime();
        
    public:
    Rocket(sf::Vector2f _position, float scale, sf::Vector2f _bbox, float _springiness, sf::RenderTarget* _target) {
        position = _position;

        bbox = _bbox;

        springiness = _springiness;

        target = _target;

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

    void spawnMissle() {
        Projectile missle(sprite.getPosition(), bbox, sprite.getRotation());
        //queue->add(missle.draw);
    }
 
    void animate() {
        animationTime = animationTimer.getElapsedTime();

        //sprite.setRotation(atan(y_vel/x_vel) * 180 / 3.14159265);
        //sprite.rotate(((x_vel > 0)? 1 : -1) * 90.f);
        sprite.setRotation(rotation);

        if(engineOn) {
            x_vel += cos((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
            y_vel += sin((sprite.getRotation() - 90.f) *  3.14159265 / 180) * engineISP * throttle * animationTime.asMilliseconds()/1000;
        }
        
        sprite.move(x_vel, y_vel);

        checkCollision();

        animationTimer.restart();
    }

    void draw() {
        animate();
        target->draw(sprite);
    }
};

class Game {
    private:
	Rocket *falcon;
	sf::RenderWindow *window;
	std::vector<Projectile> projectiles;

    public:
    Game(float x, float y, std::string name) {
        window = new sf::RenderWindow(sf::VideoMode(x, y), "rcktsim 0.0.0b2");
        window->setFramerateLimit(MAX_FPS);
        
		sf::Vector2f startPosition;
        startPosition.x = window->getSize().x/2;
    	startPosition.y = window->getSize().y/2;
        sf::Vector2f bbox;
    	bbox.x = (float)window->getSize().x;
    	bbox.y = (float)window->getSize().y;
		falcon = new Rocket(startPosition, 0.1, bbox, 0.5, window);
    }

	void consumeInput() {
		sf::Event event;
		
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                falcon->throttleToggle();
            }   
        
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            falcon->throttleUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            falcon->throttleDown();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            falcon->rotateClockwise();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            falcon->rotateCounterClockwise();
        }
	};

	void mainLoop() {
		consumeInput();

        window->clear();

		falcon->draw();

        window->display();
	}

	bool isRunning() {
		return window->isOpen();
	}
};   

int main()
{
	Game game(500, 1000, "new game");

    while (game.isRunning())
    {
		game.mainLoop();
    }

    return 0;
};