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
//	sf::FloatRect getBounds() { return ball.getGlobalBounds(); }//pobierz obramowke pilki
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
//	ball.setPosition(position);
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
//	pilka p1(400, 300);
//	// stworz okno
//	sf::RenderWindow window(sf::VideoMode(800, 600), "GRA v.01");
//	sf::CircleShape oktagon(60, 8);
//	oktagon.setFillColor(sf::Color::Cyan);
//	oktagon.setPosition(100, 100);
//	sf::FloatRect boundingOkta = oktagon.getGlobalBounds();
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
//			//jezeli zdarzenie nacisnieto klawisz - przechwyc kod klawisza
//			if (event.type == sf::Event::KeyPressed)
//			{
//				if (event.key.code == sf::Keyboard::W)
//				{
//					p1.przesun(0, -10);
//				}
//				if (event.key.code == sf::Keyboard::Z)
//				{
//					p1.przesun(0, 10);
//				}
//				if (event.key.code == sf::Keyboard::A)
//				{
//					p1.przesun(-10, 0);
//				}
//				if (event.key.code == sf::Keyboard::S)
//				{
//					p1.przesun(10, 0);
//				}
//				//jezeli jakikolwiek klawisz - testuj kolizje
//				if (boundingOkta.intersects(p1.getBounds()))
//				{
//					std::cout << "kolizja!\n";
//				}
//			}
//		}
//
//		//rysowanie z buforowaniem
//		// czysci okno, wypelniajac kolorem
//		window.clear(sf::Color::White);
//
//		// procedura rysujaca poszczegolne obiekty w oknie
//		// umieszcza obiekty w buforze
//		// window.draw(...);
//		window.draw(p1.getPilka());
//		window.draw(oktagon);
//
//		// finalizacja - wyswietlenie elementow okna
//		window.display();
//	}
//
//	return 0;
//}
