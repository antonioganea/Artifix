#ifndef MECHANICS_H
#define MECHANICS_H

#include <SFML/System/Vector2.hpp>

namespace Mechanics
{
    void applyFriction( sf::Vector2f& velocity, const float& friction );
    void applyMaxSpeed( sf::Vector2f& velocity, const float& maxSpeed );
    void applyAcceleration( sf::Vector2f& velocity, const float& xDir, const float& yDir, const float& acceleration );
}

#endif // MECHANICS_H
