#pragma once
#include "entity.h"
#include <math.h>

class ControllableEntity : public Entity {
	protected:
		

	public:
	ControllableEntity(std::string _type, float _life, float _damage, sf::Vector2f _position, float _rotation, std::string _texture, float _scale, std::vector<Entity*> *_renderQueue) : Entity(_type, _life, _damage, _position, _rotation, _texture, _scale, _renderQueue) {
		

	};

	
};
