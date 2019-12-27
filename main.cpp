#include <SFML/Graphics.hpp>
#include <iostream>

#include "missle.h"
#include "player.h"
#include "enemy.h"


#define MAX_FPS 6000

class Window {
	private:
	sf::RenderWindow *window;

    public:
    Window(float x, float y, std::string name, int fps) {
        window = new sf::RenderWindow(sf::VideoMode(x, y), "rcktsim 0.0.0b2");
        window->setFramerateLimit(fps);
	}

	sf::RenderWindow* getTarget() {
		return window;
	}

	bool isOpen() {
		return window->isOpen();
	}
};


class Game {
    private:
    bool running = 1;
	Player *falcon;
	sf::RenderWindow *window;
	sf::FloatRect bbox;
	std::vector<Entity*> renderQueue;

    sf::Vector2i mouse;

    public:
    Game(sf::RenderWindow* _window) {
        window = _window;

    	bbox.left = 0;
    	bbox.top = 0;
        bbox.width = (float)window->getSize().x;
        bbox.height = (float)window->getSize().y;

		sf::Vector2f startPosition;
        startPosition.x = window->getSize().x/2;
    	startPosition.y = window->getSize().y/2;
		falcon = new Player("player1", startPosition, bbox, &renderQueue);

        renderQueue.push_back(falcon);
    }

	void consumeInput() {
		sf::Event event;
		
        // fire once
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                stop();
                window->close();
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                falcon->throttleToggle();
            }   
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::E)) {
                falcon->spawnMissle();
            } 

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1)) {
                Rocket *target = new Rocket("target", 100, 10, sf::Vector2f(sf::Mouse::getPosition(*window)), &renderQueue);
                renderQueue.push_back(target);
            } 

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num2)) {
                Rocket *target = new Rocket("target", 100, 10, sf::Vector2f(sf::Mouse::getPosition(*window)), &renderQueue);
                renderQueue.push_back(target);
            } 

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num3)) {
                Missle *practice = new Missle("practice", 0, 30, sf::Vector2f(sf::Mouse::getPosition(*window)), 0, bbox, &renderQueue);

                renderQueue.push_back(practice);
            }  

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num4)) {
                renderQueue.push_back(new Animation(sf::Vector2f(sf::Mouse::getPosition(*window)), (float)rand(), 0.5f, "explosion.png", sf::Vector2i(96, 96), sf::Vector2i(4,4), 50.f, &renderQueue));
            }     
        }

        // fire while pressed
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
        sf::Vector2i point = sf::Mouse::getPosition(*window);
        if(point != mouse) {
            falcon->lookAt(sf::Vector2f(point));
            mouse = point;
        }
	};

	void loop() {
		consumeInput();

        window->clear();

		for(int i = 0; i < renderQueue.size(); ++i) {
			renderQueue[i]->draw(window);

            if(renderQueue[i]->isDead()) {
                delete renderQueue[i];
                renderQueue[i] = NULL;
                renderQueue.erase(renderQueue.begin() + i);
            } 

            for(int j = 0; j < renderQueue.size(); ++j) {
                if(i != j && renderQueue[i]->getHitbox().contains(renderQueue[j]->getPosition())) {
                    if(renderQueue[i]->isDead() == false) {
                        renderQueue[i]->collide(renderQueue[j]);
                        renderQueue[j]->collide(renderQueue[i]);
                    }
                }
            }
            
		}

        //std::cout << renderQueue.size() << std::endl;
        
        window->display();
        if(running) loop();
	}

    void stop() {
        running = 0;
    }

	bool isRunning() {
		return running;
	}
};   


int main()
{
	Window window(500, 1000, "new game", MAX_FPS);

	Game game(window.getTarget());

	game.loop();

    return 0;
};