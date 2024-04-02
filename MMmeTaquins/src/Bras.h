#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Utils.h"
#include "PhyObject.h"

class Bras: public PhyObject{
private:
    bool bras_up;
public:
	explicit Bras(double x, double y, bool up, b2World* world, int userdata, std::string_view const& color);
	void draw(sf::RenderWindow& window, float xchipie, float ychipie) const override;
};