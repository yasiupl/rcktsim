//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//class pilka {
//private:
//	sf::Vector2f position;//wspolrzedne
//	float xVel = 10;//predkosc w poziomie
//	float yVel = 10;//predkosc w pionie
//	sf::CircleShape ball;//pilka
//
//public:
//	pilka(float x_in, float y_in);//tworz pilke w polozeniu (x,y)
//	void przesun(float x_in, float y_in);//przesun pilke
//	sf::CircleShape getPilka() { return ball; }//zwroc pilke	
//	sf::Vector2f getPos() { return ball.getPosition(); }
//};
//
//pilka::pilka(float x_in, float y_in)
//{
//	position.x = x_in;
//	position.y = y_in;
//	//kolo o promieniu 10px
//	ball.setRadius(20);
//	ball.setFillColor(sf::Color(150, 50, 250));
//	// obramowka kola o grubosci 2px
//	ball.setOutlineThickness(2);
//	ball.setOutlineColor(sf::Color(250, 150, 100));
//	ball.setPosition(position);//pozycja poczatkowa
//}
//
//void pilka::przesun(float x_in, float y_in)
//{
//	sf::Vector2f pos;
//	pos.x = x_in;
//	pos.y = y_in;
//	ball.move(pos);
//}
//
//int main()
//{	
//	// stworz okno
//	sf::RenderWindow window(sf::VideoMode(800, 600), "GRA v.01");
//	pilka p1(400, 300);//stworz pilke
//	int x=0, y=0;//pozycja pilki
//	int dx = 10, dy = 10;//kierunek x, kierunek y
//	sf::Clock zegar;//zegarek
//	// okno widoczne, dopoki nie [x]
//	while (window.isOpen())
//	{
//		// petla sprawdzajace zdarzenia
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			// jezeli zdarzenie zamknij - zamykamy okno
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		//procedura animacji odswiezana co 100ms
//		if (zegar.getElapsedTime().asMilliseconds() > 100.0f) {	
//			//sprawdz brzegi okna w poziomie
//			if (p1.getPos().x > window.getSize().x || p1.getPos().x < 0)
//				dx = -dx;//zmien kierunek na przeciwny
//			//sprawdz brzegi okna w pionie
//			if (p1.getPos().y > window.getSize().y || p1.getPos().y < 0)
//				dy = -dy;
//			p1.przesun(dx, dy);
//			zegar.restart();
//			std::cout << "rozmiar okna: " << window.getSize().x << ", " << window.getSize().y << std::endl;
//			std::cout << "x = " << p1.getPos().x << "y= " << p1.getPos().y << std::endl;
//		}		
//		//rysowanie z buforowaniem
//		// czysci okno, wypelniajac kolorem
//		window.clear(sf::Color::White);
//		// procedura rysujaca poszczegolne obiekty w oknie
//		// umieszcza obiekty w buforze
//		// window.draw(...);
//		window.draw(p1.getPilka());
//		// finalizacja - wyswietlenie elementow okna
//		window.display();
//	}
//	return 0;
//}
