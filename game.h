#pragma once
#include <SFML/Graphics.hpp>
#include "app.h"
#include "menu.h"
#include "missle.h"
#include "player.h"
#include "enemy.h"

class Game: public App {
    private:

    int difficulty = 1;

    App *mainMenu;
	Player *falcon;
	sf::FloatRect bbox;
	std::vector<Entity*> renderQueue;

    sf::Font font;
    sf::Text score;
    sf::Text life;

    sf::Vector2i mouse;

    sf::Clock gameTimer;
    float gameTime = 0, pauseTime = 0, pauseLength = 0, lastWave = 0;

    public:
    Game(App *menu, int _difficulty) : App(menu->getWindow()) {
        difficulty = _difficulty;
        font.loadFromFile("assets/fonts/pixelated.ttf");
        mainMenu = menu;
    	bbox.left = -32;
    	bbox.top = -32;
        bbox.width = (float)window->getSize().x+64;
        bbox.height = (float)window->getSize().y+64;

		sf::Vector2f startPosition;
        startPosition.x = window->getSize().x/2;
    	startPosition.y = window->getSize().y/2;
		falcon = new Player("player1", 100 * difficulty * difficulty, 10 * difficulty, startPosition, bbox, &renderQueue);

        renderQueue.push_back(falcon);

        this->setSize(sf::Vector2f(window->getSize()));

       
		score.setFont(font);	
		score.setFillColor(sf::Color::White);
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
            Menu *pause_menu = new Menu(this);
            pause_menu->addOption("Resume", [](App *_this, App *parent) 
            { 
                //parent->removeOverlay(_this);
                parent->activate();
                delete _this;
            });

            pause_menu->addOption("Exit", [](App *_this, App *parent) 
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
            //this->addOverlay(pause_menu);
            pause_menu->loop();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
        {
            this->stop();
            Menu *f1_menu = new Menu(this);
            f1_menu->addOption("Resume", [](App *_this, App *parent) 
            { 
                //parent->removeOverlay(_this);
                parent->activate();
                //delete _this;
            });

            f1_menu->addOption("The premise of the game consists of shooting down as many enemy spacecraft attacking your position as possible.");
            f1_menu->addOption("Use arrow keys or WSAD to set the orientation and thrust of your engines.");
            f1_menu->addOption("Spacebar toggles the engine thrust.");
            f1_menu->addOption("E shoots a missle.");
            
            f1_menu->loop();
            //this->addOverlay(f1_menu);
        }

        sf::Vector2i point = sf::Mouse::getPosition(*window);
        if(point != mouse) {
            falcon->lookAt(sf::Vector2f(point));
            mouse = point;
        }
	};

    void gameOver() {
        this->stop();
        Menu gameover_menu(mainMenu);

        gameover_menu.addOption("You have scored " + std::to_string(falcon->getScore()) + " points. \n");
        gameover_menu.addOption("Better luck next time!\n");
        gameover_menu.addOption("Main Menu", [](App *_this, App *parent) 
        { 
            parent->activate();
        });     
        gameover_menu.addOption("Exit Game", [](App *_this, App *parent) 
        {
            _this->getWindow()->close();
        });        
        gameover_menu.loop();
    }

    void pause() {
        paused = true;
        pauseTime = gameTimer.getElapsedTime().asMilliseconds();
        for(int i = 0; i < renderQueue.size(); ++i) {
			renderQueue[i]->pause();
        }
    }
    void resume() {
        paused = false;
        pauseLength += gameTimer.getElapsedTime().asMilliseconds() - pauseTime;
        for(int i = 0; i < renderQueue.size(); ++i) {
			renderQueue[i]->resume();
        }
        pauseTime = 0;
    }

    void spawnEnemy(sf::Vector2f position) {
        Enemy *enemy = new Enemy("enemy", 25 * (gameTime / 10000) + 1, 10, position, bbox, &renderQueue);
        enemy->lookAt(sf::Vector2f(window->getSize().x/2,window->getSize().y/2));
        if(difficulty >= 2) enemy->targetEntity(falcon);
        if(difficulty == 3) enemy->setAgressive();
        enemy->throttleToggle();
        renderQueue.push_back(enemy);
    }

	void drawFrame() {
        gameTime = gameTimer.getElapsedTime().asMilliseconds() - pauseLength;
        if(falcon->isDead() == true) {
            this->gameOver();
        }
    
        if(!paused && gameTime - lastWave > 2000) {
            
            spawnEnemy(sf::Vector2f(rand() % int(bbox.width - bbox.left), 0));
            spawnEnemy(sf::Vector2f(rand() % int(bbox.width - bbox.left), (bbox.height - bbox.top)));
            spawnEnemy(sf::Vector2f(0, rand() % int(bbox.height - bbox.top)));
            spawnEnemy(sf::Vector2f((bbox.width - bbox.left), rand() % int(bbox.height - bbox.top)));

            lastWave = gameTime;
        }

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
        score.setString("Score: " + std::to_string(falcon->getScore()) + " Life: " + std::to_string(falcon->getLife()));
        sf::FloatRect textRect = score.getLocalBounds();
		score.setOrigin(textRect.width/2,textRect.height/2);
        score.setPosition(bbox.width/2, textRect.height/2);
        window->draw(score);
        //std::cout << renderQueue.size() << std::endl;
        
	}
}; 