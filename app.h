#pragma once
#include <SFML/Graphics.hpp>

// App takes input from the user and maps it to the screen via the draw function.
// There are 2 "apps" in this project so far: Menu and Game itself.

class App {
	protected:
	sf::RenderWindow *window;
	bool active = true;

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
		active = true;
		loop();
	}

	void stop() {
		active = false;
	}

	virtual void draw() = 0;

	virtual void loop() {
		consumeInput();
		draw();
		if(active) loop();
	}

};