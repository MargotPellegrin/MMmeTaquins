#include "ContactListener.h"
#include "HealthManager.h"
#include "GameManager.h"
#include <thread>


void ContactListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    int current_level_nb = GameManager::getGameManager().getCurrentLevelNb();

    if (bodyA->GetUserData().pointer >= 2 && bodyB->GetUserData().pointer == 1) {
        b2Vec2 velocity = bodyB->GetLinearVelocity();
        velocity.x = 0;
        velocity.y = 0;
        bodyB->SetLinearVelocity(velocity);
        if (current_level_nb == 6) {
            // TODO : (DONE) 3. Sur l'un des niveaux, Mme Chipie en manque dangereux d'affection...regagne des vies
            HealthManager::getHealthManager().gainHealth();
        }
        else {
            HealthManager::getHealthManager().loseHealth();
        }
        std::cout << "Chipie se fait chatouiller" << std::endl;
    }
    else if (bodyB->GetUserData().pointer >= 2 && bodyA->GetUserData().pointer == 1) {
        b2Vec2 velocity = bodyA->GetLinearVelocity();
        velocity.x = 0;
        velocity.y = 0;
        bodyA->SetLinearVelocity(velocity);
        if (current_level_nb == 6) {
            HealthManager::getHealthManager().gainHealth();
        }
        else {
            HealthManager::getHealthManager().loseHealth();
        }
        std::cout << "Chipie se fait chatouiller" << std::endl;
    }
}
