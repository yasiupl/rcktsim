#include <SFML/Graphics.hpp>
#include <iostream>

#include "missle.h"
#include "rocket.h"


#define MAX_FPS 60

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
	Rocket *falcon;
	sf::RenderWindow *window;
	sf::Vector2f bbox;
	std::vector<Entity*> renderQueue;

    public:
    Game(sf::RenderWindow* _window) {
        window = _window;

    	bbox.x = (float)window->getSize().x;
    	bbox.y = (float)window->getSize().y;

		sf::Vector2f startPosition;
        startPosition.x = window->getSize().x/2;
    	startPosition.y = window->getSize().y/2;
		falcon = new Rocket(startPosition, bbox, window, &renderQueue);

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
                
                renderQueue.push_back(new Rocket(sf::Vector2f(sf::Mouse::getPosition(*window)), bbox, window, &renderQueue));
            } 

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num2)) {
                
                renderQueue.push_back(new Missle(sf::Vector2f(sf::Mouse::getPosition(*window)), 0, bbox, window, &renderQueue));
            }  

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num3)) {
                
                renderQueue.push_back(new Explosion(sf::Vector2f(sf::Mouse::getPosition(*window)), 0, 0.5, bbox, window, &renderQueue));
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

        falcon->lookAt(sf::Mouse::getPosition(*window));
	};

	void loop() {
		consumeInput();

        window->clear();

		for(int i = 0; i < renderQueue.size(); ++i) {
			renderQueue[i]->draw();

            for(int j = 0; j < renderQueue.size(); ++j) {
                if(i != j && renderQueue[i]->getHitbox().contains(renderQueue[j]->getPosition())) {
                    if(renderQueue[i]->isDead() == false  && renderQueue[i]->getTime() > 100.f && renderQueue[j]->getTime() > 100.f) {
                        renderQueue[i]->collide(renderQueue[j]);
                        renderQueue[j]->collide(renderQueue[i]);
                    }
                }
            }

            if(renderQueue[i]->isDead()) {
                delete renderQueue[i];
                renderQueue.erase(renderQueue.begin() + i);
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