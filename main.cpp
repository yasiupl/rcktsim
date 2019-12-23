#include <SFML/Graphics.hpp>
#include <iostream>

#include "rocket.cpp"
#include "missle.cpp"

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
	Rocket *falcon;
	sf::RenderWindow *window;
	sf::Vector2f bbox;
	std::vector<Missle*> projectiles;

    public:
    Game(sf::RenderWindow* _window) {
        window = _window;

    	bbox.x = (float)window->getSize().x;
    	bbox.y = (float)window->getSize().y;

		sf::Vector2f startPosition;
        startPosition.x = window->getSize().x/2;
    	startPosition.y = window->getSize().y/2;
		falcon = new Rocket(startPosition, 0.1, bbox, 0.5, window);
    }

	void spawnMissle() {
		Missle *newMissle;
		newMissle = new Missle(falcon->getPosition(), bbox, falcon->getRotation(), window);
		projectiles.push_back(newMissle);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            spawnMissle();
        }
	};

	void mainLoop() {
		consumeInput();

        window->clear();

		for(int i = 0; i < projectiles.size(); ++i) {
			projectiles[i]->draw();
		}

        falcon->draw();

        window->display();
	}

	bool isRunning() {
		return window->isOpen();
	}
};   


int main()
{
	Window window(500, 1000, "new game", MAX_FPS);

	Game game(window.getTarget());
    while (game.isRunning())
    {
		game.mainLoop();
    }

    return 0;
};