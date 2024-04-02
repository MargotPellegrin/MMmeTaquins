#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Level.h"

class ContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override;
};