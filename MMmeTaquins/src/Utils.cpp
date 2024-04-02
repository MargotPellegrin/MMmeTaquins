#include "Utils.h"

sf::Color which_color(std::string const* ptrcolor) {
    std::string color = *ptrcolor;
    if (color == "Black") {
        return sf::Color::Black;
    }
    else if (color == "White") {
        return sf::Color::White;
    }
    else if (color == "Red") {
        return sf::Color::Red;
    }
    else if (color == "Green") {
        return sf::Color::Green;
    }
    else if (color == "Blue") {
        return sf::Color::Blue;
    }
    else if (color == "Yellow") {
        return sf::Color::Yellow;
    }
    else if (color == "Magenta") {
        return sf::Color::Magenta;
    }
    else if (color == "Cyan") {
        return sf::Color::Cyan;
    }
    else if (color == "Transparent") {
        return sf::Color::Transparent;
    }
    else if (color == "Purple") {
        sf::Color thecolor(128, 0, 128);
        return thecolor;
    }
    else if (color == "Orange") {
        sf::Color thecolor(255, 165, 0);
        return thecolor;
    }
    else if (color == "Grey") {
        sf::Color thecolor(150, 150, 150);
        return thecolor;
    }
    else {
        return sf::Color::Yellow; //Color by default
    }
}