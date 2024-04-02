#include "Bras.h"

const float rayon_main = 2.0f;
const float longueur_bras = 10.0f;
const float largeur_bras = 1.0f;


Bras::Bras(double x, double y, bool up, b2World* world, int userdata, std::string_view const& newcolor) :
    bras_up(up)
{
    color = newcolor;
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(float(x), float(y));
    b2BodyUserData userData;
    userData.pointer = userdata;
    bodyDef.userData = userData;
    body = world->CreateBody(&bodyDef);
    b2CircleShape mainShape;
    if (up) { // si le bras va vers le haut
        mainShape.m_p.Set(0, longueur_bras / 2 + rayon_main);
        mainShape.m_radius = rayon_main;
    }
    else { // si le bras va vers le bas
        mainShape.m_p.Set(0, -longueur_bras / 2 - rayon_main);
        mainShape.m_radius = rayon_main;
    }

    b2FixtureDef mainFixtureDef;
    mainFixtureDef.shape = &mainShape;
    mainFixtureDef.density = 0.0f;
    mainFixtureDef.friction = 0.3f;
    mainFixtureDef.restitution = 0.0f;
    body->CreateFixture(&mainFixtureDef);

    b2PolygonShape brasShape;
    brasShape.SetAsBox(largeur_bras/2, longueur_bras/2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &brasShape;
    fixtureDef.density = 0.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.0f;
    body->CreateFixture(&fixtureDef);

}

void Bras::draw(sf::RenderWindow& window, float xchipie, float ychipie) const
{
    float x = body->GetPosition().x;
    float y = body->GetPosition().y;
    float xrectangle = (x - largeur_bras / 2 -xchipie/30)*30;
    float yrectangle = -(y + longueur_bras / 2 -ychipie/30)*30;
    float xmain = (x - rayon_main -xchipie/30)*30;
    float ymain;
    if (bras_up) {
        ymain = -(y + 2 * rayon_main + longueur_bras / 2 -ychipie/30) * 30;
    }
    else {
        ymain = -(y - longueur_bras / 2 -ychipie/30) * 30;
    }
    sf::RectangleShape shape(sf::Vector2f(largeur_bras * 30, longueur_bras * 30));
    shape.setFillColor(which_color(&color));
    shape.setPosition(xrectangle, yrectangle);
    window.draw(shape);
    sf::CircleShape circle(rayon_main*30);
    circle.setFillColor(which_color(&color));
    circle.setPosition(xmain, ymain);
    window.draw(circle);
}
