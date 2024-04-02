#include "Chipie.h"

Chipie::Chipie(const std::string_view& newcolor, double r, double xd, double yd, double speed, b2World* world) :
    r(r),
    speed(speed)
{
    color = newcolor;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(float(xd), float(yd));
    b2BodyUserData userData;
    userData.pointer = 1;
    bodyDef.userData = userData;
    body = world->CreateBody(&bodyDef);

    b2CircleShape chipieShape;
    chipieShape.m_p.Set(0, 0);
    chipieShape.m_radius = float(r);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &chipieShape;
    fixtureDef.density = 5.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.0f;
    body->CreateFixture(&fixtureDef);

}

void Chipie::Stop() {
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0;
    body->SetLinearVelocity(velocity);
}
void Chipie::MoveRight()
{
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = float(speed*1.3);
    body->SetLinearVelocity(velocity);
}

void Chipie::MoveLeft()
{
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = -float(speed*1.3);
    body->SetLinearVelocity(velocity);
}

void Chipie::Jump(int level)
{
    double bonus = 1;
    if (level == 4) {
        bonus = 1.5;
    }
    b2Vec2 velocity = body->GetLinearVelocity();
    if (abs(velocity.y) < 0.1) {
        velocity.y = float(speed*1.6*bonus);
        body->SetLinearVelocity(velocity);
    }
}

void Chipie::draw(sf::RenderWindow& window, float xchipie, float ychipie) const
{
    auto radius = float(r)*30;
    /*
    float xf = float(window.getSize().x)/static_cast<float>(4) -radius;
    float yf = 2*float(window.getSize().y)/static_cast<float>(3) -radius;
    */
    float xf = xchipie-radius;
    float yf = ychipie-radius;
    sf::CircleShape shape(radius);
    shape.setFillColor(which_color(&color));
    shape.setPosition(xf, yf);
    window.draw(shape);
}

void Chipie::Chatouille()
{
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0;
    velocity.y = 0;
    body->SetLinearVelocity(velocity);
}
