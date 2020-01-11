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
    menu.addOption("Play", [](App *_this, App *parent) 
    { 
        Game game(_this);
        game.loop();
    });

    menu.addOption("Exit Game", [](App *_this, App *parent) 
    { 
        Menu menu1(parent);
        menu1.addOption("Confirm", [](App *_this, App *parent) 
        { 
        });
        menu1.addOption("Go Back", [](App *_this, App *parent) 
        { 
            parent->activate();
        });
        menu1.loop();
    });
    
    menu.loop();
    

    return 0;
};