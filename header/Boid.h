#ifndef BOID_H
#define BOID_H
#include <SFML/Graphics/RenderWindow.hpp>


class Boid {
public:
    Boid(float startX, float startY, int group = 0, float initialBiasVal = 0.001f);

    void update(std::vector<Boid>& boids, float dt);

    void draw(sf::RenderWindow &window);

private:
    float x, y;
    float vx, vy;
    float biasVal;
    int group; // 0 = nessun gruppo, 1 = scout group 1, 2 = scout group 2

    void applyBehavior(std::vector<Boid>& boids);
    void enforceBoundaries();
    void updateVelocityWithBias();
    void limitSpeed();
};


#endif //BOID_H
