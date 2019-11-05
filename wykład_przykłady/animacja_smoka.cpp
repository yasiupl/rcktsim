#include "SFML/Graphics.hpp"

int main() {
sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Dragon game");

sf::Event event;
sf::Texture tekstura;
tekstura.loadFromFile("smok.png");//laduj teksture

sf::IntRect ksztaltSmoka(0, 0, 200, 200);//okresl obszar spritea
sf::Sprite smok(tekstura, ksztaltSmoka);//utworz spritea powiazanego z tekstura
sf::Clock zegar;//zegarek do odmierzania czasu klatki
ksztaltSmoka.top = 200;//ustaw sie na kolejny wiersz tekstury
while (renderWindow.isOpen()) {
	while (renderWindow.pollEvent(event)) {
		if (event.type == sf::Event::EventType::Closed)
			renderWindow.close();
	}
	//glowna procedura animacji, klatka trwa 300ms
	if (zegar.getElapsedTime().asMilliseconds() > 300.0f) {
		if (ksztaltSmoka.left == 400)//w wierszu tekstury sa 3 klatki (200 x 200px)
			ksztaltSmoka.left = 0;
		else
			ksztaltSmoka.left += 200;//przemieszczaj sie w poziomie tekstury
		smok.move(sf::Vector2f(10.0f, 10.0f));//przemieszczaj smoka
		if (smok.getPosition().y > 480)
			smok.setPosition(sf::Vector2f(10.0f, 10.0f));

		smok.setTextureRect(ksztaltSmoka);
		zegar.restart();
	}


	renderWindow.clear();
	renderWindow.draw(smok);
	renderWindow.display();
}
}