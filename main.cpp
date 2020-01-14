#include <SFML/Graphics.hpp>
#include <iostream>

#include "scoreboard.h"
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
        });
        noobSelector.addOption("Hey, not too rough", [](App *_this, App *parent) 
        {
            Game game(parent, 2);
            game.loop();
        });
        noobSelector.addOption("Hurt Me Plenty", [](App *_this, App *parent) 
        {
            Game game(parent, 3);
            game.loop();
        });
        noobSelector.addOption("Ultra-Violence", [](App *_this, App *parent) 
        {
            Game game(parent, 4);
            game.loop();
        });
        noobSelector.loop();
        
    });

    menu.addOption("Scoreboard", [](App *_this, App *parent) 
    { 
        Menu scoreboard_menu(parent);
        
        scoreboard_menu.addOption("Go Back", [](App *_this, App *parent) 
        { 
            parent->activate();
        });

        Scoreboard scoreboard;
        scoreboard.forEachGame(&scoreboard_menu, [](Menu *menu, Scoreboard_game game){
            //std::cout << game.name + ": " + std::to_string(game.score) + " (" + std::to_string((int)game.time) + ")" << std::endl;
            menu->addOption(std::to_string(game.score) + " points in " + std::to_string((int)game.time) + " seconds at difficulty lvl " + std::to_string(game.difficulty));
        });
        scoreboard_menu.loop();
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