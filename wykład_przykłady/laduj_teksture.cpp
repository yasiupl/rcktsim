//#include "SFML/Graphics.hpp"
//
//int main(int argc, char ** argv) {
//	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Dragon game");
//
//	sf::Event event;
//	sf::Texture tekstura;//obiekt `tekstura`
//	tekstura.loadFromFile("smok.png");//laduj teksture z pliku
//	//obiekt smok typu `sprite`
//	sf::Sprite smok(tekstura, sf::IntRect(0, 0, 200, 200));
//
//
//	while (renderWindow.isOpen()) {
//		while (renderWindow.pollEvent(event)) {
//			if (event.type == sf::Event::EventType::Closed)
//				renderWindow.close();
//		}
//		renderWindow.clear();
//		renderWindow.draw(smok);
//		renderWindow.display();
//	}
//}