#include <SFML/Graphics.hpp>

int main()
{
int obrot_triangle = 0;//obrot trojkata
sf::Clock zegar;//obiekt zegarek
sf::Time czas;//obiekt czas
sf::RenderWindow window(sf::VideoMode(800, 600), "SFML demo");// utworz okno
sf::CircleShape triangle(80, 3);//utworz trojkat
triangle.setPosition(300, 300);//ustaw pozycje trojkata
triangle.setFillColor(sf::Color(0, 255, 255, 200));//ustal kolor wypelnienia
// petla wieczna - dopoki okno jest otwarte
while (window.isOpen())
{
	// w kazdej iteracji petli sprawdzaj zdarzenia
	sf::Event event;
	while (window.pollEvent(event))
	{
		// jezeli odebrano zdarzenie "Closed" zamknij okno
		if (event.type == sf::Event::Closed)
			window.close();
	}

	//rotacja trojkata
	triangle.setRotation(obrot_triangle);
	czas = zegar.getElapsedTime();
	if (czas.asMilliseconds() > 100)
	{
		obrot_triangle += 15;
		zegar.restart();
	}

	if (obrot_triangle >= 360)
		obrot_triangle = 0;

	// wyczysc obszar rysowania
	window.clear();


	// tutaj umiesc procedury rysujace...
	// window.draw(...);
	window.draw(triangle);
	// ostatnia czynnosc - wyswietl okno wraz zawartoscia
	window.display();
}

return 0;
}

