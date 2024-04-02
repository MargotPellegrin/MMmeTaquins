//
// Created by Jonathan Weng on 18/6/23.
//
#include "HealthManager.h"
#include "GameManager.h"
#include <thread>
#include <iostream>
using namespace std;

HealthManager &HealthManager::getHealthManager() {
    static HealthManager instance;
    return instance;
}

int HealthManager::getHealth() const {
    return health;
}

void HealthManager::setHealth(int value) {
    health = value;
}

void HealthManager::checkImmunityTimer(float elapsedTime) {
    elapsedImmunity += elapsedTime;
    if (elapsedImmunity > float(immunityDuration)) {
        isImmune = false;
        elapsedImmunity = 0;
    }
}

// TODO : (DONE) 3. Sur l'un des niveaux, Mme Chipie est en manque dangereux d'affection... elle en perd des vies...
void HealthManager::checkDamageTimer(float elapsedTime) {
    damageTimer += elapsedTime;
    if (damageTimer > float(damageInterval)) {
        scoped_lock<mutex> lock(healthLock);
        health--;
        damageTimer = 0;
    }
}

// TODO : (DONE) 3. ... et regagne des vies grâce à M. Chatouille
void HealthManager::gainHealth() {
    scoped_lock<mutex> lock(healthLock);
    health++;
    cout << "HP regained" << endl;
}

void HealthManager::loseHealth() {
    if(isImmune) {
        cout << "Still immune" << endl;
    }
    else {
        scoped_lock<mutex> lock(healthLock);
        health--;
        cout << "HP lost" << endl;
        isImmune = true; // l'immunisation sera désactivée ensuite par checkImmunityTimer()
    }
}

void HealthManager::showHealth(sf::RenderWindow& window, const sf::Font& font, sf::View view) const {
    sf::Text lives;
    lives.setPosition(0, -2040);
    lives.setFont(font);
    lives.setFillColor(sf::Color::Green);
    string health_str = "Vies : ";
    string health_value = to_string(getHealthManager().getHealth());
    string health_display_str = health_str + health_value;
    lives.setCharacterSize(40);
    lives.setString(sf::String::fromUtf8(health_display_str.begin(), health_display_str.end()));
    window.setView(view);
    window.draw(lives);
}
