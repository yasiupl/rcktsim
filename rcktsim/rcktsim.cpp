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

class ClearScreen: public App {
    private:
    ClearScreen(sf::RenderWindow *window) : App(window) {};
    void consumeInput() {}
    void draw() {
        window->clear();
    }
};


int main()
{
	Window window(720, 480, "rcktsim", MAX_FPS);
    
    Menu menu(window.getTarget());
    menu.addOption("Play", [](App *_this, App *parent) 
    { 
        Menu noobSelector(parent);
        noobSelector.addOption("I'm too young to die", [](App *_this, App *parent) 
        {
            Game game(parent, 1);
            game.loop();
            _this->activate();
        });
        noobSelector.addOption("Hey, not too rough", [](App *_this, App *parent) 
        {
            Game game(parent, 2);
            game.loop();
            _this->activate();
        });
        noobSelector.addOption("Hurt Me Plenty", [](App *_this, App *parent) 
        {
            Game game(parent, 3);
            game.loop();
            _this->activate();
        });
        noobSelector.addOption("Ultra-Violence", [](App *_this, App *parent) 
        {
            Game game(parent, 4);
            game.loop();
            _this->activate();
        });
        noobSelector.loop();
        
    });

    menu.addOption("Exit Game", [](App *_this, App *parent) 
    { 
        Menu menu1(parent);
        menu1.addOption("Confirm", [](App *_this, App *parent) 
        {
            _this->getWindow()->close();
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