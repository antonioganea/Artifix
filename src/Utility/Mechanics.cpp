#include "Mechanics.h"

#define _USE_MATH_DEFINES
#include "math.h"

void Mechanics::applyFriction( sf::Vector2f& velocity, const float& friction ){
    sf::Vector2f counterVelocity;
    counterVelocity = velocity * friction;
    velocity -= counterVelocity;
    /*
    float angle = atan2( velocity.y, velocity.x );

    velocity.x -= cos(angle)*friction;
    velocity.y -= sin(angle)*friction;
    */
    /*
    if ( velocity.x < 0 ){
        if ( velocity.x + friction < 0 )
            velocity.x += friction;
        else
            velocity.x = 0;
    }else if ( velocity.x > 0 ){
        if ( velocity.x - friction > 0 )
            velocity.x -= friction;
        else
            velocity.x = 0;
    }

    if ( velocity.y < 0 ){
        if ( velocity.y + friction < 0 )
            velocity.y += friction;
        else
            velocity.y = 0;
    }else if ( velocity.y > 0 ){
        if ( velocity.y - friction > 0 )
            velocity.y -= friction;
        else
            velocity.y = 0;
    }
    */
}

void Mechanics::applyMaxSpeed( sf::Vector2f& velocity, const float& maxSpeed ){
    //Speed limits
    if ( velocity.x > maxSpeed )
        velocity.x = maxSpeed;
    else if ( velocity.x < -maxSpeed )
        velocity.x = -maxSpeed;

    if ( velocity.y > maxSpeed )
        velocity.y = maxSpeed;
    else if ( velocity.y < -maxSpeed )
        velocity.y = -maxSpeed;
}

void Mechanics::applyAcceleration( sf::Vector2f& velocity, const float& xDir, const float& yDir, const float& acceleration ){
    velocity.x += xDir*acceleration;
    velocity.y += yDir*acceleration;
}
