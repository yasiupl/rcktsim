#include <SFML/Graphics.hpp>
#include <iostream>

#include "menu.h"
#include "game.h"

#define MAX_FPS 60

class Window {
	private:
	sf::RenderWindow *window;

    public:
    Window(float x, float y, std::string name, int fps) {
        window = new sf::RenderWindow(sf::VideoMode(x, y), name, sf::Style::Fullscreen);
        window->setFramerateLimit(fps);
	}

	sf::RenderWindow* getTarget() {
		return window;
	}

	bool isOpen() {
		return window->isOpen();
	}

    void close() {
        window->close();
    }
};  


int main()
{
	Window window(720, 480, "new game", MAX_FPS);
    
    Menu menu(window.getTarget());
    menu.addOption("Play", [](sf::RenderWindow* window, Menu *parent) 
    { 
        Game game(window);
        game.loop();
    });

    menu.addOption("Nested", [](sf::RenderWindow* window, Menu *parent) 
    { 
        Menu menu1(parent, window);
        menu1.addOption("Exit Game", [](sf::RenderWindow* window, Menu *parent) 
        { 
            window->close();
        });
        menu1.addOption("Go Back", [](sf::RenderWindow* window, Menu *parent) 
        { 
            parent->activate();
        });
        menu1.loop();
    });

    menu.addOption("Exit", [](sf::RenderWindow* window, Menu *menu) 
    { 
        window->close();
    });
    

    menu.loop();
    

    return 0;
};