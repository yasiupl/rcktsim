#pragma once
#include <SFML/Graphics.hpp>

// App takes input from the user and maps it to the screen via the drawFrame function.
// There are 2 "apps" in this project so far: Menu and Game itself.

class App {
	protected:
	sf::Vector2f size;
	sf::RenderWindow *window;
	bool active = true;
	bool paused = false;

	public:
	App(sf::RenderWindow *_window) {
		window = _window;
	}

	virtual void consumeInput() {
		sf::Event event;
		
        // fire once
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                stop();
                window->close();
            }
		}
	}

	bool isActive() {
		return active;
	}

	void activate() {
		paused = false;
		active = true;
		resume();
		loop();
	}

	virtual void pause() {
		paused = true;
	}

	virtual void resume() {
		paused = false;
	}

	void stop() {
		active = false;
		pause();
	}

	void setSize(sf::Vector2f _size) {
		size = _size;
	}

	sf::Vector2f getSize() {
		return size;
	}

	sf::RenderWindow *getWindow() {
		return window;
	}


	virtual void drawFrame() = 0;

	virtual void loop() {
		window->clear();
		if(!paused) consumeInput();
		this->drawFrame();
		window->display();
		if(active) loop();
	}
};