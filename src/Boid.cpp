//
// Created by alessandro on 26/10/24.
//

#include "../header/Boid.h"
#include "../header/constants.h"

#include <cmath>
#include <cstdlib>
#include <SFML/Graphics/CircleShape.hpp>

Boid::Boid(const float startX, const float startY, const int group, const float initialBiasVal)
    : x(startX), y(startY), biasVal(initialBiasVal), group(group) {

    // genera numero casuale tra -1.0 e 1.0
    vx = static_cast<float>(rand() % 200 - 100) / 100.0f;
    vy = static_cast<float>(rand() % 200 - 100) / 100.0f;
}

void Boid::update(std::vector<Boid>& boids, float dt) {
    applyBehavior(boids);
    limitSpeed();
    updateVelocityWithBias();
    enforceBoundaries();
    x += vx * dt;
    y += vy * dt;
}

void Boid::applyBehavior(std::vector<Boid>& boids) {
    float xpos_avg = 0, ypos_avg = 0;
    float xvel_avg = 0, yvel_avg = 0;
    float close_dx = 0, close_dy = 0;
    int neighboring_boids = 0;

    for (const Boid& other : boids) {
        if (&other == this) continue; // salta se stesso

        // calcolo differenze di posizione
        float dx = x - other.x;
        float dy = y - other.y;
        float squared_distance = dx * dx + dy * dy; // per non usare sqrt

        if (std::abs(dx) < visualRange && std::abs(dy) < visualRange) {
            // se il boide è troppo vicino allora lo allontana
            if (squared_distance < protectedRange * protectedRange) {
                close_dx += dx;
                close_dy += dy;
            } else if (squared_distance < visualRange * visualRange) {
                xpos_avg += other.x;
                ypos_avg += other.y;
                xvel_avg += other.vx;
                yvel_avg += other.vy;
                neighboring_boids++;
            }
        }
    }

    if (neighboring_boids > 0) {
        xpos_avg /= neighboring_boids;
        ypos_avg /= neighboring_boids;
        xvel_avg /= neighboring_boids;
        yvel_avg /= neighboring_boids;

        // boide si muove verso il centro allineando la velocità
        vx += (xpos_avg - x) * centeringFactor + (xvel_avg - vx) * matchingFactor;
        vy += (ypos_avg - y) * centeringFactor + (yvel_avg - vy) * matchingFactor;
    }

    // modifica velocità per allontanarsi dai boidi vicini
    vx += close_dx * avoidFactor;
    vy += close_dy * avoidFactor;
}

void Boid::updateVelocityWithBias() {
    if (group == 1) {   // scout che si muovono verso destra
        if (vx > 0)

            // se si sta già muovendo verso destra aumenta biasVal
            biasVal = std::min(maxBias, biasVal + biasIncrement);
        else

            // diminuisce biasVal per ridurre influenza bias
            biasVal = std::max(biasIncrement, biasVal - biasIncrement);

        // applica bias a velocità + contributo a destra
        vx = (1 - biasVal) * vx + (biasVal * 1);

    } else if (group == 2) {    // scout che si muovono verso sinistra
        if (vx < 0)

            biasVal = std::min(maxBias, biasVal + biasIncrement);
        else

            biasVal = std::max(biasIncrement, biasVal - biasIncrement);

        vx = (1 - biasVal) * vx + (biasVal * -1);
    }
}

void Boid::limitSpeed() {
    float speed = std::sqrt(vx * vx + vy * vy);
    if (speed < minSpeed) {
        vx = (vx / speed) * minSpeed;
        vy = (vy / speed) * minSpeed;
    }
    if (speed > maxSpeed) {
        vx = (vx / speed) * maxSpeed;
        vy = (vy / speed) * maxSpeed;
    }
}

void Boid::enforceBoundaries() {
    if (x < 0) {
        vx += turnFactor;
    }
    if (x > WINDOW_WIDTH) {
        vx -= turnFactor;
    }
    if (y < 0) {
        vy += turnFactor;
    }
    if (y > WINDOW_HEIGHT) {
        vy -= turnFactor;
    }
}

void Boid::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(5.0f); // Raggio di 5 pixel
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
}
