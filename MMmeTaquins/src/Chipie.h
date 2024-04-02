#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Utils.h"
#include "PhyObject.h"

class Chipie: public PhyObject {
private:
	double r;
	double speed;
public:
	explicit Chipie(const std::string_view& newcolor, double r, double x, double y, double speed, b2World* world);
	void Stop();
	void MoveRight();
	void MoveLeft();
	void Jump(int level);
	void draw(sf::RenderWindow& window, float xchipie = 0, float ychipie = 0) const override;
	void Chatouille();
};