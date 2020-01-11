#pragma once
#include <SFML/Graphics.hpp>
#include "app.h"
#include "menu.h"
#include "missle.h"
#include "player.h"
#include "enemy.h"

class Game: public App {
    private:
    bool running = 1;
	Player *falcon;
	sf::FloatRect bbox;
	std::vector<Entity*> renderQueue;

    sf::Vector2i mouse;

    sf::Clock gameTimer;
    int gameTime;
    int lastWave = 0;

    public:
    Game(App *menu) : App(menu->getWindow()) {
    	bbox.left = 0;
    	bbox.top = 0;
        bbox.width = (float)window->getSize().x;
        bbox.height = (float)window->getSize().y;

		sf::Vector2f startPosition;
        startPosition.x = window->getSize().x/2;
    	startPosition.y = window->getSize().y/2;
		falcon = new Player("player1", startPosition, bbox, &renderQueue);

        renderQueue.push_back(falcon);

        this->setSize(sf::Vector2f(window->getSize()));
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            this->stop();
            Menu pause_menu(this);
            pause_menu.addOption("Resume", [](App *_this, App *parent) 
            { 
                parent->activate();
            });

            pause_menu.addOption("Exit", [](App *_this, App *parent) 
            { 
                Menu confirmation(parent);
                confirmation.addOption("Confirm", [](App *_this, App *parent) 
                {
                    _this->getWindow()->close();
                });
                confirmation.addOption("Go Back", [](App *_this, App *parent) 
                { 
                    parent->activate();
                });
                confirmation.loop();
            });
            pause_menu.loop();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
        {
            this->stop();
            Menu f1_menu(this);
            f1_menu.addOption("Resume", [](App *_this, App *parent) 
            { 
                parent->activate();
            });

            f1_menu.addOption("Lorem ipsum dolor sit amet. \n lol");
            
            f1_menu.loop();
        }

        sf::Vector2i point = sf::Mouse::getPosition(*window);
        if(point != mouse) {
            falcon->lookAt(sf::Vector2f(point));
            mouse = point;
        }
	};

	void draw() {
        gameTime = gameTimer.getElapsedTime().asMilliseconds();

        if(gameTime - lastWave > 2000) {
            Rocket *enemy = new Rocket("enemy", 25 * (gameTime / 10000) + 1, 10, sf::Vector2f(0, 0), &renderQueue);
            enemy->lookAt(sf::Vector2f(window->getSize().x/2,window->getSize().y/2));
            enemy->throttleToggle();
            renderQueue.push_back(enemy);
            lastWave = gameTime;
        }

        window->clear();

		for(int i = 0; i < renderQueue.size(); ++i) {
			renderQueue[i]->draw(window);

            if(renderQueue[i]->isDead()) {
                delete renderQueue[i];
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
	}
}; 