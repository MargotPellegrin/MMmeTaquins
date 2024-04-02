#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Chipie.h"
#include "Bras.h"
#include "pugixml.hpp"
#include <vector>
#include "Utils.h"
class Level {
private:
	int level;
	std::unique_ptr<b2World> world;
	b2Body* groundBody;
	std::string colorfloor;
	std::unique_ptr<Chipie> chipie;
	std::vector<std::unique_ptr<Bras>> vecteurbras;
	int nbBras;
    std::string getStory() const;
public:
	explicit Level(int i);
	b2World* getWorld() const;
	Chipie* getChipie() const;
	Bras* getBras(int i) const;
	int getNbBras() const;
	void drawWorld(sf::RenderWindow& window, sf::View view) const;
	void AddBras(float x, float y, bool up, std::string color);
    void showStory(sf::RenderWindow& window, const sf::Font& font, sf::View view) const;
};