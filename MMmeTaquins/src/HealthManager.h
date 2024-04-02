//
// Created by Jonathan Weng on 18/6/23.
//

#ifndef MMMETAQUINS_HEALTHMANAGER_H
#define MMMETAQUINS_HEALTHMANAGER_H
#include <mutex>
#include <SFML/Graphics.hpp>

class HealthManager {
public:
    static HealthManager& getHealthManager();
    int getHealth() const;
    void setHealth(int value);
    void checkImmunityTimer(float elapsedTime);
    void checkDamageTimer(float elapsedTime);
    void gainHealth();
    void loseHealth();
    void showHealth(sf::RenderWindow& window, const sf::Font& font, sf::View view) const ;
private:
    HealthManager() =  default;
    ~HealthManager() = default;
    int health = 3;
    std::mutex healthLock;
    int immunityDuration = 2;
    bool isImmune;
    float elapsedImmunity = 0;
    int damageInterval = 3;
    float damageTimer = 0;
};

#endif //MMMETAQUINS_HEALTHMANAGER_H
