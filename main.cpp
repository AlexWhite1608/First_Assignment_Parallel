#include <SFML/Graphics.hpp>

#include "header/Boid.h"

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    const float deltaTime = 0.1f;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Simulazione Boidi");

    int scout_group_1_count = 20;
    int scout_group_2_count = 20;
    float biasval_group_1 = 0.001f;
    float biasval_group_2 = 0.001f;

    std::vector<Boid> boids;
    for (int i = 0; i < scout_group_1_count; ++i) {
        auto x = static_cast<float>(rand() % windowWidth);
        auto y = static_cast<float>(rand() % windowHeight);
        boids.emplace_back(x, y, 1, biasval_group_1);
    }
    for (int i = 0; i < scout_group_2_count; ++i) {
        auto x = static_cast<float>(rand() % windowWidth);
        auto y = static_cast<float>(rand() % windowHeight);
        boids.emplace_back(x, y, 2, biasval_group_2);
    }
    for (int i = 0; i < 60; ++i) {
        auto x = static_cast<float>(rand() % windowWidth);
        auto y = static_cast<float>(rand() % windowHeight);
        boids.emplace_back(x, y);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (Boid& boid : boids) {
            boid.update(boids, deltaTime);
        }

        window.clear(sf::Color::Black);

        for (Boid& boid : boids) {
            boid.draw(window);
        }

        window.display();
    }

    return 0;
}
