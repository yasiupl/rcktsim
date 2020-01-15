#pragma once
#include <SFML/Graphics.hpp>
#include "app.h"

class Menu: public App {
	protected:
	App *parent;

	sf::Font font;
	sf::Sprite logo;
	sf::Texture logoTexture;

	std::vector<sf::Text> options;
	std::vector<void (*)(App*, App*)> callbacks;

	int selected = 0;


	public:
	Menu(App *_parent) : App(_parent->getWindow()) {
		parent = _parent;
		this->setSize(parent->getSize());
		setup();
	}
	Menu(sf::RenderWindow *window) : App(window) {
		parent = this;
		this->setSize(sf::Vector2f(window->getSize()));
		setup();
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
			if((event.type == sf::Event::KeyPressed)) {
				if ((event.key.code == sf::Keyboard::W) || (event.key.code == sf::Keyboard::Up)) {
					selectUp();
				}   
				if ((event.key.code == sf::Keyboard::S) || (event.key.code == sf::Keyboard::Down)) {
					selectDown();
				}     
				if ((event.key.code == sf::Keyboard::Enter) || (event.key.code == sf::Keyboard::Space)) {
					select();
				}   
				if ((event.key.code == sf::Keyboard::Escape)) {
					this->stop();
					parent->activate();
				} 
			}
        }
	};


	void addOption(std::string name, void (*callback)(App*, App*)) {
		sf::Text option;
		option.setFont(font);	
		option.setFillColor(sf::Color::White);
		option.setString(name);
		
		sf::FloatRect textRect = option.getLocalBounds();
		option.setOrigin(textRect.width/2,textRect.height/2);

		options.push_back(option);
		callbacks.push_back(callback);

		for(int i = 0; i < (int)options.size(); ++i) {
			options[i].setPosition(sf::Vector2f(size.x / 2, (size.y / 2) - (options.size() * textRect.height * 2)/2 + textRect.height * 2 * i));
		}	
	}

	void addOption(std::string name) {
		sf::Text option;
		option.setFont(font);	
		option.setFillColor(sf::Color::White);
		option.setString(name);
		
		sf::FloatRect textRect = option.getLocalBounds();
		option.setOrigin(textRect.width/2,textRect.height/2);

		options.push_back(option);
		callbacks.push_back([](App *menu, App *parent) {menu->activate();});

		for(int i = 0; i < (int)options.size(); ++i) {
			logo.setPosition(size.x/2, (size.y/2) - options.size() * textRect.height * 2);
			options[i].setPosition(sf::Vector2f(size.x / 2, (size.y / 2) - (options.size() * textRect.height * 2)/2 + textRect.height * 2 * i));
		}	 
	}
	
	private:

	void setup() {
		font.loadFromFile("assets/fonts/moonshot.ttf");
		logoTexture.loadFromFile("assets/logo.png");
		logoTexture.setSmooth(true);
		logo.setTexture(logoTexture);
		sf::FloatRect logoRect = logo.getLocalBounds();
		logo.setOrigin(logoRect.width/2,logoRect.height);
		logo.setPosition(size.x/2, size.y/3);
	}

	void selectUp() {
		if(selected - 1 >= 0) {
			selected -= 1;
		}
	}

	void selectDown() {
		if(selected + 1 < (int)options.size()) {
			selected += 1;
		}
	}

	void select() {
		callbacks[selected](this, parent);
		stop();
	}

	void drawFrame() {
		window->draw(logo);
		for(int i = 0; i < (int)options.size(); ++i) {
			if(i == selected) {
				options[i].setFillColor(sf::Color::Blue);
				options[i].setStyle(sf::Text::Bold);
			} else {
				options[i].setFillColor(sf::Color::White);
				options[i].setStyle(sf::Text::Regular);
			}
			window->draw(options[i]);
		}
	}
};