#include <SFML/Graphics.hpp>

int main() {
    // 1. Crea una finestra
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // 2. Crea un cerchio
    sf::CircleShape shape(50); // Cerchio con raggio 50
    shape.setFillColor(sf::Color::Green); // Colore verde

    // 3. Loop principale
    while (window.isOpen()) {
        // Gestisci gli eventi
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 4. Pulisci la finestra
        window.clear();

        // 5. Disegna il cerchio
        window.draw(shape);

        // 6. Mostra il contenuto della finestra
        window.display();
    }

    return 0;
}
