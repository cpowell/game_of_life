//
//  main.cpp
//  game_of_life
//
//  Created by Chris Powell on 8/24/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//  http://github.com/cpowell/game_of_life
//  You can redistribute and/or modify this software only in accordance with
//  the terms found in the "LICENSE" file included with the source code.
//
#include "board.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <SFML/Graphics.hpp>
#include <tbb/tbb.h>

using namespace sf;

int main() {
    const unsigned int worldsz = 1500;
    const unsigned int wndWidth{ worldsz }, wndHeight{ worldsz };
    sf::ContextSettings settings;
    sf::ConvexShape live_cell, dead_cell;
    std::unique_ptr<sf::RenderWindow> pwind;

    // Set up the rendering window
    settings.antialiasingLevel = 4;
    pwind = std::make_unique<sf::RenderWindow>(
        sf::VideoMode{ wndWidth, wndHeight }, "Game AI Example", sf::Style::Default, settings);
    pwind->setFramerateLimit(10); // This FPS will set the simulation rate

    // Set up some useful shapes
    live_cell.setPointCount(4);
    live_cell.setFillColor(sf::Color::Blue);
    live_cell.setOutlineThickness(1);
    live_cell.setOutlineColor(sf::Color::Blue);
    live_cell.setOrigin(0, 0);
    live_cell.setPoint(0, sf::Vector2f{ 0, 0 });
    live_cell.setPoint(1, sf::Vector2f{ 15, 0 });
    live_cell.setPoint(2, sf::Vector2f{ 15, 15 });
    live_cell.setPoint(3, sf::Vector2f{ 0, 15 });

    dead_cell.setPointCount(4);
    dead_cell.setFillColor(sf::Color::Black);
    dead_cell.setOutlineThickness(1);
    dead_cell.setOutlineColor(sf::Color::Blue);
    dead_cell.setOrigin(0, 0);
    dead_cell.setPoint(0, sf::Vector2f{ 0, 0 });
    dead_cell.setPoint(1, sf::Vector2f{ 15, 0 });
    dead_cell.setPoint(2, sf::Vector2f{ 15, 15 });
    dead_cell.setPoint(3, sf::Vector2f{ 0, 15 });

    // There are two boards defined; the one "in back" is updated based
    // on the current status of the one "in front", then brought to the
    // front. Efficient, and kind to memory.
    Board flip, flop;

    // Seed the RNG and set up a random smattering of live cells.
    srand((unsigned int)time(NULL));
    flip.randomize(20);

    // This routine evolves and prints the board forever; you must
    // terminate the program.
    sf::Event event{};
    while (true) {
        while (pwind->pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                pwind->close();
                return 0;
            }

            if (event.type == sf::Event::EventType::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    std::cout << "Quitting\n";
                    pwind->close();
                    return 0;
                }
            }
        }

        pwind->clear(sf::Color(100, 100, 100));

        flop.evolve(flip);

        // Render
        for (int row = 0; row < BOARD_HEIGHT; ++row) {
            int y = row * 15;
            for (int col = 0; col < BOARD_WIDTH; ++col) {
                int x = col * 15;
                int cell = flop.getCell(col, row);
                if (cell == ALIVE) {
                    live_cell.setPosition((float)x, (float)y);
                    pwind->draw(live_cell);
                } else {
                    dead_cell.setPosition((float)x, (float)y);
                    pwind->draw(dead_cell);
                }
            }
        }

        pwind->display();

        std::swap(flip, flop);
    }

    return 0;
}
