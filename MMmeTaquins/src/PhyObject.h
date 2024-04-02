#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

class PhyObject {
protected:
	b2Body* body = nullptr;
	std::string color = "Magenta";
public:
	explicit PhyObject() = default;
	virtual void draw(sf::RenderWindow& window, float xchipie, float ychipie) const= 0;
	b2Body* GetBody() { return body; };
	virtual ~PhyObject() = default;;
};