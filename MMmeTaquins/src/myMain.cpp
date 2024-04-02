#include "myMain.h"
#include "pugixml.hpp"
#include "Chipie.h"
#include "Bras.h"
#include "ContactListener.h"
#include "box2d/box2d.h"
#include "Level.h"
#include "HealthManager.h"
#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int myMain() {
    int level_nb;
    Level const* level = GameManager::getGameManager().getCurrentLevel();
    int width = 2000;
    int height = 1200;
#ifdef __APPLE__
    sf::RenderWindow window(sf::VideoMode(width, height), "MMeTaquins");
#else
    sf::RenderWindow window(sf::VideoMode(width, height), "MMeTaquins", sf::Style::Fullscreen);
#endif
    // TODO : (DONE) 2. Gérer le framerate globalement... avec l'option VSync
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;
    // Créer un objet ContactListener
    ContactListener contactListener;

    // Définir le ContactListener pour le monde Box2D
    level->getWorld()->SetContactListener(&contactListener);

    // Définir la police pour afficher du texte
    sf::Font game_font;

    if (!game_font.loadFromFile("resources/Arial.ttf")) {
        cout << "Error loading font file" << endl;

        exit(1);
    }
    // TODO : (DONE) 5. Utiliser la vue SFML... en changeant les fonctions utilisant le rendu SFML
    sf::View view(sf::Vector2f(float(window.getSize().x)/2,float(window.getSize().y)/2), sf::Vector2f(float(window.getSize().x), float(window.getSize().y)));
    view.setViewport(sf::FloatRect(0.f, 0.2f, 1.f, 1.f));
    window.setView(view);

    sf::View gameStatusView(sf::Vector2f(float(window.getSize().x)/2, -1750.f), sf::Vector2f(float(window.getSize().x), float(window.getSize().y) * 0.5f));
    gameStatusView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.5f));
    window.setView(gameStatusView);
    while (window.isOpen()) {
        level_nb = GameManager::getGameManager().getCurrentLevelNb();
        level = GameManager::getGameManager().getCurrentLevel();
        level->getWorld()->SetContactListener(&contactListener);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.key.code == sf::Keyboard::Right) {
                level->getChipie()->MoveRight();
            }
            if (event.key.code == sf::Keyboard::Left) {
                level->getChipie()->MoveLeft();
            }
            if (event.key.code == sf::Keyboard::Up) {
                level->getChipie()->Jump(level_nb);
            }
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if (event.key.code == sf::Keyboard::Space) {
                level->getChipie()->Stop();
            }
        }

        window.clear(sf::Color::White);
        float elapsedTime = clock.getElapsedTime().asSeconds();
        // TODO : (DONE) 3. Sur l'un des niveaux, Mme Chipie est en manque dangereux d'affection... et elle en perd des vies
        if (level_nb == 6) {
            HealthManager::getHealthManager().checkDamageTimer(elapsedTime);
        }
        // TODO : (DONE) 1. Supprimer les threads... et les remplacer par une incrémentation dans la Game Loop
        else {
            HealthManager::getHealthManager().checkImmunityTimer(elapsedTime);
        }
        level->getWorld()->Step(elapsedTime, 6, 2);
        level->drawWorld(window, view);
        level->drawWorld(window, gameStatusView);
        clock.restart();
        GameManager::getGameManager().checkLevelCleared(window, game_font, contactListener);
        GameManager::getGameManager().checkDeath(window, game_font, contactListener);
        GameManager::getGameManager().getCurrentLevel()->showStory(window, game_font, gameStatusView);
        HealthManager::getHealthManager().showHealth(window, game_font, gameStatusView);
        window.display();
    }

    return 0;
}