#pragma once
#include <SFML/Graphics.hpp>
#include "app.h"

class Menu: public App {
	protected:
	Menu *parent;

	sf::Font font;
	sf::Vector2f size;

	std::vector<sf::Text> options;
	std::vector<void (*)(sf::RenderWindow*, Menu*)> callbacks;

	int selected = 0;


	public:
	Menu(Menu *_parent, sf::RenderWindow *window) : App(window) {
		parent = _parent;
		size = parent->size;
		font.loadFromFile("assets/fonts/pixelated.ttf");
	}
	Menu(sf::Vector2f _size, sf::RenderWindow *window) : App(window) {
		parent = this;
		size = _size;
		font.loadFromFile("assets/fonts/pixelated.ttf");
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

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W)) {
                selectUp();
            }   
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S)) {
                selectDown();
            }     
			 if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter)) {
                select();
            }   
        }
	};


	void addOption(std::string name, void (*callback)(sf::RenderWindow*, Menu*)) {
		sf::Text option;
		option.setFont(font);	
		option.setFillColor(sf::Color::White);
		option.setString(name);
		options.push_back(option);
		callbacks.push_back(callback);

		for(int i = 0; i < options.size(); ++i) {
			options[i].setPosition(sf::Vector2f(size.y / 2, size.x * i / options.size()));
		}	
	}

	void selectUp() {
		if(selected - 1 >= 0) {
			selected -= 1;
		}
	}

	void selectDown() {
		if(selected + 1 < options.size()) {
			selected += 1;
		}
	}

	void select() {
		callbacks[selected](window, parent);
		stop();
	}

	void draw() {
		window->clear();

		for(int i = 0; i < options.size(); ++i) {
			if(i == selected) {
				options[i].setFillColor(sf::Color::Red);
				options[i].setStyle(sf::Text::Bold);
			} else {
				options[i].setFillColor(sf::Color::White);
				options[i].setStyle(sf::Text::Regular);
			}
			window->draw(options[i]);
		}

		window->display();
	}
};