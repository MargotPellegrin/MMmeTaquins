//
// Created by Jonathan Weng on 18/6/23.
//

#ifndef MMMETAQUINS_GAMEMANAGER_H
#define MMMETAQUINS_GAMEMANAGER_H

#include "Level.h"
#include "ContactListener.h"
#include <SFML/Graphics.hpp>

class GameManager {
public:
    static GameManager& getGameManager();
    int getCurrentLevelNb() const;
    Level* getCurrentLevel();
    void loadLevel(int level_nb);
    void checkLevelCleared(sf::RenderWindow& window, const sf::Font& font, ContactListener contactListener);
    void checkDeath(const sf::RenderWindow& window, const sf::Font& font, ContactListener contactListener);

private:
    GameManager() = default;
    ~GameManager() = default;
    int current_level_nb = 1;
    Level current_level = Level(current_level_nb);
};

#endif //MMMETAQUINS_GAMEMANAGER_H
