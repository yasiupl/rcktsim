#pragma once
#include <SFML/Graphics.hpp>

class Bboxed {
	protected:
	sf::FloatRect bbox;

	public:
	Bboxed(sf::FloatRect _bbox) {
		bbox = _bbox;
	};

	virtual void checkBoundries() = 0;
};
