#include <SFML/Graphics.hpp>
#include <iostream>

#include "entity.cpp"
//#include "explosion.cpp"
#include "missle.cpp"
#include "rocket.cpp"



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

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::E)) {
                falcon->throttleToggle();
            }   
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                falcon->spawnMissle();
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
	};

	void loop() {
		consumeInput();

        window->clear();

		for(int i = 0; i < renderQueue.size(); ++i) {
			renderQueue[i]->draw();
		}

        falcon->draw();

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