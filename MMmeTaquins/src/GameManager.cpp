//
// Created by Jonathan Weng on 18/6/23.
//
#include "GameManager.h"
#include "HealthManager.h"
using namespace std;

GameManager &GameManager::getGameManager() {
    static GameManager instance;
    return instance;
}
                                                                                           
int GameManager::getCurrentLevelNb() const {
    return current_level_nb;
}

Level* GameManager::getCurrentLevel() {
    return &current_level;
}

void GameManager::loadLevel(int level_nb) {
    current_level = Level(level_nb);
    if (level_nb == 2) {
        HealthManager::getHealthManager().setHealth(4);
    }
    else {
        HealthManager::getHealthManager().setHealth(3);
    }
}

void GameManager::checkLevelCleared(sf::RenderWindow& window, const sf::Font& font, ContactListener contactListener) {
    if (current_level.getChipie()->GetBody()->GetPosition().x > 195) {
        if (current_level_nb < 7) {
            current_level_nb++;
            loadLevel(current_level_nb);
            current_level.getWorld()->SetContactListener(&contactListener);
        }
    }
}

void GameManager::checkDeath(const sf::RenderWindow &window, const sf::Font &font, ContactListener contactListener) {
    if (!HealthManager::getHealthManager().getHealth()) {
        sf::Text text;
        text.setFont(font);
        string game_over = "Plus de vies !";
        text.setString(sf::String::fromUtf8(game_over.begin(), game_over.end()));
        text.setPosition(0, 50);
        text.setCharacterSize(70);
        text.setFillColor(sf::Color::Black);

        current_level_nb = GameManager::getGameManager().getCurrentLevelNb();
        loadLevel(current_level_nb);
        current_level.getWorld()->SetContactListener(&contactListener);
    }
}
