
#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <optional>
#include <string>
#include <unordered_map>
#include "cTree.h"

struct Pos { float x, y; };

// Parámetros de dibujo (fijos)
constexpr float MARGEN = 60.f;   // margen izquierdo y superior
constexpr float DX = 50.f;   // separación horizontal entre nodos consecutivos (inorder)
constexpr float DY = 80.f;   // separación vertical entre niveles
constexpr float RADIO = 20.f;   // radio de cada círculo

// ---------------------------------------------------------------------
// layout: x = orden inorder, y = profundidad
// ---------------------------------------------------------------------
inline void layout(Node* n, int depth, int& cnt, std::unordered_map<Node*, Pos>& pos) {
    if (!n) return;
    layout(n->left, depth + 1, cnt, pos);
    pos[n] = { MARGEN + cnt * DX, MARGEN + depth * DY };
    cnt++;
    layout(n->right, depth + 1, cnt, pos);
}

// ---------------------------------------------------------------------
// drawEdges: línea desde cada nodo hacia sus hijos
// ---------------------------------------------------------------------
inline void drawEdges(sf::RenderWindow& w, Node* n, const std::unordered_map<Node*, Pos>& pos) {
    if (!n) return;
    for (Node* c : { n->left, n->right }) {
        if (!c) continue;
        sf::Vertex line[] = {
            sf::Vertex{ sf::Vector2f(pos.at(n).x, pos.at(n).y), sf::Color::White },
            sf::Vertex{ sf::Vector2f(pos.at(c).x, pos.at(c).y), sf::Color::White }
        };
        w.draw(line, 2, sf::PrimitiveType::Lines);
        drawEdges(w, c, pos);
    }
}

// ---------------------------------------------------------------------
// drawNodes: círculo + valor centrado
// ---------------------------------------------------------------------
inline void drawNodes(sf::RenderWindow& w, const std::unordered_map<Node*, Pos>& pos,
    const sf::Font& font) {
    for (const auto& [n, p] : pos) {
        sf::CircleShape circle(RADIO);
        circle.setOrigin({ RADIO, RADIO });
        circle.setPosition({ p.x, p.y });
        circle.setFillColor(sf::Color(40, 90, 160));
        circle.setOutlineThickness(2.f);
        circle.setOutlineColor(sf::Color::White);
        w.draw(circle);

        sf::Text text(font, std::to_string(n->val), 18);
        sf::FloatRect b = text.getLocalBounds();   // centrar el texto
        text.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
        text.setPosition({ p.x, p.y });
        w.draw(text);
    }
}

// ---------------------------------------------------------------------
// dibujarTotal: ventana + bucle principal con cámara
// ---------------------------------------------------------------------
inline int dibujarTotal(Node* root) {
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) return 1;

    // 1) Calcular posiciones (una sola vez)
    std::unordered_map<Node*, Pos> pos;
    int cnt = 0;
    layout(root, 0, cnt, pos);

    // 2) Ventana
    sf::RenderWindow window(sf::VideoMode({ 800, 500 }), "Mi arbol");
    window.setFramerateLimit(60);

    // 3) Cámara
    //    base = tamaño "normal" de la vista (igual al de la ventana)
    //    zoom = factor actual (1 = normal, <1 = acercado, >1 = alejado)
    sf::Vector2f base(800.f, 500.f);
    float zoom = 1.f;
    sf::View view(sf::FloatRect({ 0.f, 0.f }, base));
    window.setView(view);

    sf::Vector2i lastMouse;   // última posición del mouse durante el arrastre

    // 4) Bucle principal
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            // Cerrar ventana
            if (event->is<sf::Event::Closed>()) window.close();

            // Redimensionar: el dibujo no se deforma, solo se ve más área
            if (const auto* rs = event->getIf<sf::Event::Resized>()) {
                base = sf::Vector2f(rs->size);
                view.setSize(base * zoom);
                window.setView(view);
            }

            // Zoom con la rueda (rueda arriba = acercar)
            if (const auto* wheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
                zoom *= (wheel->delta > 0) ? 0.9f : 1.1f;
                zoom = std::clamp(zoom, 0.1f, 10.f);   // límites para no perderse
                view.setSize(base * zoom);
                window.setView(view);
            }

            // Al presionar clic izquierdo, guardar dónde empezó el arrastre
            if (const auto* press = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (press->button == sf::Mouse::Button::Left) lastMouse = press->position;
            }

            // Arrastrar con clic izquierdo mantenido
            if (const auto* mv = event->getIf<sf::Event::MouseMoved>()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    sf::Vector2f antes = window.mapPixelToCoords(lastMouse);
                    sf::Vector2f ahora = window.mapPixelToCoords(mv->position);
                    view.move(antes - ahora);          // la cámara se mueve al revés del mouse
                    window.setView(view);
                    lastMouse = mv->position;
                }
            }

            // Tecla R: reiniciar la vista
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::R) {
                    zoom = 1.f;
                    view.setSize(base);
                    view.setCenter(base / 2.f);
                    window.setView(view);
                }
            }
        }

        // Dibujar
        window.clear(sf::Color(25, 25, 30));
        drawEdges(window, root, pos);
        drawNodes(window, pos, font);
        window.display();
    }
    return 0;
}