#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include <unordered_map>
#include "cTree.h"
using namespace std;
struct Pos { float x, y; };

// x = orden inorder, y = profundidad
void layout(Node* n, int depth, int& cnt, unordered_map<Node*, Pos>& pos) {
    if (!n) return;
    layout(n->left, depth + 1, cnt, pos);
    pos[n] = { 60.f + cnt * 50.f, 60.f + depth * 80.f };
    cnt++;
    layout(n->right, depth + 1, cnt, pos);
}

void drawEdges(sf::RenderWindow& w, Node* n, const unordered_map<Node*, Pos>& pos) {
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

void drawNodes(sf::RenderWindow& w, const unordered_map<Node*, Pos>& pos, const sf::Font& font) {
    const float r = 20.f;
    for (const auto& [n, p] : pos) {
        sf::CircleShape circle(r);
        circle.setOrigin({ r, r });
        circle.setPosition({ p.x, p.y });
        circle.setFillColor(sf::Color(40, 90, 160));
        circle.setOutlineThickness(2.f);
        circle.setOutlineColor(sf::Color::White);
        w.draw(circle);

        sf::Text text(font, to_string(n->val), 18);
        sf::FloatRect b = text.getLocalBounds();            // centrar el texto
        text.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
        text.setPosition({ p.x, p.y });
        w.draw(text);
    }
}
inline int dibujarTotal(Node* root){
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) return 1;

    unordered_map<Node*, Pos> pos;
    int cnt = 0;
    layout(root, 0, cnt, pos);

    sf::RenderWindow window(sf::VideoMode({ 800, 500 }), "Mi arbol");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }
        window.clear(sf::Color(25, 25, 30));
        drawEdges(window, root, pos);
        drawNodes(window, pos, font);
        window.display();
    }
}
