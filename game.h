#pragma once
#include <SFML/Graphics.hpp>
#include "app.h"
#include "menu.h"
#include "missle.h"
#include "player.h"
#include "enemy.h"
#include "scoreboard.h"

class Game: public App {
    private:

    int difficulty = 1;
    unsigned int iterations = 0;
    App *mainMenu;
	Player *falcon;
	sf::FloatRect bbox;
	std::vector<Entity*> renderQueue;

    sf::Font font;
    sf::Text score;

    //sf::View *view;

    sf::Texture background;
    sf::RectangleShape backdrop;

    sf::Vector2i mouse;

    sf::Clock gameTimer;
    float gameTime = 0, waveTime = 0, pauseTime = 0, pauseLength = 0;

    public:
    Game(App *menu, int _difficulty) : App(menu->getWindow()) {
        difficulty = _difficulty;
        mainMenu = menu;
    	bbox.left = 0;
    	bbox.top = 0;
        bbox.width = (float)window->getSize().x;
        bbox.height = (float)window->getSize().y;
        
        //view = new sf::View(bbox);

		sf::Vector2f startPosition;
        startPosition.x = window->getSize().x/2;
    	startPosition.y = window->getSize().y/2;
		falcon = new Player("player1", 100 * difficulty * difficulty, 10 * difficulty, startPosition, bbox, &renderQueue);

        renderQueue.push_back(falcon);

        this->setSize(sf::Vector2f(window->getSize()));

        font.loadFromFile("assets/fonts/moonshot.ttf");
		score.setFont(font);	
		score.setFillColor(sf::Color::White);

        background.loadFromFile("assets/background.png");
        backdrop.setTexture(&background);
        backdrop.setSize(sf::Vector2f(bbox.width, bbox.height));
        backdrop.setPosition(bbox.left, bbox.top);
    }

    virtual ~Game() {
        for(int i = 0; i < (int)renderQueue.size(); ++i) {
            delete renderQueue[i];
            renderQueue.erase(renderQueue.begin() + i);
        } 
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

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space) && (event.key.code == sf::Keyboard::Space)) {
                falcon->throttleToggle();
            }   
            //Developer bindings
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1)) {
                Rocket *target = new Rocket("target", 100, 10, sf::Vector2f(sf::Mouse::getPosition(*window)), &renderQueue);
                renderQueue.push_back(target);
            } 

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num3)) {
                Missle *practice = new Missle("practice", 0, 30, 4000, sf::Vector2f(sf::Mouse::getPosition(*window)), 0, bbox, &renderQueue);

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            falcon->spawnMissle();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            this->stop();
            Menu *pause_menu = new Menu(this);
            pause_menu->addOption("Resume", [](App *_this, App *parent) 
            { 
                parent->activate();
            });

            pause_menu->addOption("Exit", [](App *_this, App *parent) 
            { 
                Menu confirmation(parent);
                confirmation.addOption("Confirm", [](App *_this, App *parent) 
                {
                    _this->getWindow()->close();
                    parent->stop();
                });
                confirmation.addOption("Go Back", [](App *_this, App *parent) 
                { 
                    parent->activate();
                });
                confirmation.loop();
            });
            pause_menu->loop();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
        {
            this->stop();
            Menu *f1_menu = new Menu(this);
            f1_menu->addOption("Resume", [](App *_this, App *parent) 
            { 
                parent->activate();
            });

            f1_menu->addOption("The premise of the game consists of");
            f1_menu->addOption("shooting down as many enemy spacecraft attacking your position as possible.");
            f1_menu->addOption("Use arrow keys or WSAD to set the orientation and thrust of your engines.");
            f1_menu->addOption("Spacebar toggles the engine thrust.");
            f1_menu->addOption("E shoots a missle.");
            
            f1_menu->loop();
        }

        sf::Vector2i point = sf::Mouse::getPosition(*window);
        if(point != mouse) {
            falcon->lookAt(sf::Vector2f(point));
            mouse = point;
        }
	};

    void gameOver() {
        this->stop();
        Scoreboard_game game;
        game.difficulty = difficulty;
        game.time = gameTimer.getElapsedTime().asSeconds();
        game.score = falcon->getScore() * difficulty;
        
        Scoreboard scoreboard;
        scoreboard.addGame(&game);

        Menu gameover_menu(mainMenu);

        gameover_menu.addOption("You have scored " + std::to_string(game.score) + " points. \n");
        gameover_menu.addOption("Time: " + std::to_string((int)game.time) + " seconds");
        gameover_menu.addOption("Better luck next time!");
        gameover_menu.addOption("Main Menu", [](App *_this, App *parent) 
        { 
            parent->activate();
        });     
        gameover_menu.addOption("Exit Game", [](App *_this, App *parent) 
            { 
                Menu confirmation(parent);
                confirmation.addOption("Confirm", [](App *_this, App *parent) 
                {
                    _this->getWindow()->close();
                    parent->stop();
                });
                confirmation.addOption("Go Back", [](App *_this, App *parent) 
                { 
                    parent->activate();
                });
                confirmation.loop();
            });    
        gameover_menu.loop();
       
    }

    void pause() {
        paused = true;
        pauseTime = gameTimer.getElapsedTime().asMilliseconds();
        for(int i = 0; i < (int)renderQueue.size(); ++i) {
			renderQueue[i]->pause();
        }
    }
    void resume() {
        paused = false;
        pauseLength += gameTimer.getElapsedTime().asMilliseconds() - pauseTime;
        for(int i = 0; i < (int)renderQueue.size(); ++i) {
			renderQueue[i]->resume();
        }
    }

    void spawnEnemy(sf::Vector2f position) {
        Enemy *enemy = new Enemy("enemy", 25 * (gameTime / 10000) + 1, 10, position, bbox, &renderQueue);
        enemy->lookAt(sf::Vector2f(window->getSize().x/2,window->getSize().y/2));
        if(difficulty >= 2) enemy->targetEntity(falcon);
        enemy->setDifficulty(difficulty);
        enemy->throttleToggle();
        renderQueue.push_back(enemy);
    }

	void drawFrame() {
        gameTime = gameTimer.getElapsedTime().asMilliseconds() - pauseLength;

        if(falcon->isDead() == true) {
            this->gameOver();
        }  

        //view->setRotation(falcon->getRotation());
        //view->setCenter(falcon->getPosition());
        //window->setView(*view);

        window->draw(backdrop);
        if(!paused && (gameTime - waveTime > 5000 || iterations == 0)) {
            
            spawnEnemy(sf::Vector2f(rand() % int(bbox.width - bbox.left), 0));
            spawnEnemy(sf::Vector2f(rand() % int(bbox.width - bbox.left), (bbox.height - bbox.top)));
            spawnEnemy(sf::Vector2f(0, rand() % int(bbox.height - bbox.top)));
            spawnEnemy(sf::Vector2f((bbox.width - bbox.left), rand() % int(bbox.height - bbox.top)));

            waveTime = gameTime;
        }

		for(int i = 0; i < (int)renderQueue.size(); ++i) {
			renderQueue[i]->draw(window);

            if(renderQueue[i]->isDead()) {
                delete renderQueue[i];
                renderQueue.erase(renderQueue.begin() + i);
            } 

            for(int j = 0; j < (int)renderQueue.size(); ++j) {
                if(i != j && renderQueue[i]->getHitbox().contains(renderQueue[j]->getPosition())) {
                    if(renderQueue[i]->isDead() == false) {
                        renderQueue[i]->collide(renderQueue[j]);
                        renderQueue[j]->collide(renderQueue[i]);
                    }
                }
            }
            
		}

        score.setString("Time: " + std::to_string((int)gameTimer.getElapsedTime().asSeconds()) + "    Multiplier: " + std::to_string(difficulty) + "   Score: " + std::to_string(falcon->getScore()) + "    Life: " + std::to_string((int)falcon->getLife()));
        sf::FloatRect textRect = score.getLocalBounds();
		score.setOrigin(textRect.width/2,textRect.height/2);
        score.setPosition(bbox.width/2, textRect.height/2);
        window->draw(score);
        //std::cout << renderQueue.size() << std::endl;
        ++iterations;
	}
}; 