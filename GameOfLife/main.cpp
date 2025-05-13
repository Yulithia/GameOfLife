#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "GameOfLife.h"

template<typename T>
std::ostream& operator<< (std::ostream& ostream, const std::vector<T>& vec)
{
    std::cout << " ";

    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }

    std::cout << "\n";

    return ostream;
}



int main()
{
    const int width = 100;
    const int height = 100;
    const int cellSize = 10;
    double prob = 0.5;
    GameOfLife gof = GameOfLife::GameOfLife(width, height, cellSize);
    std::vector<std::vector<sf::RectangleShape>> grid;

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Ewolucja Siatki");

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::R)
                {
                    gof.flipRunning();
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::G)
                {
                    gof.generateGrid(prob);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    gof.flipPixel(sf::Mouse::getPosition(window));
                    
                }
            }
        }
        
        if(gof.getRunning())
        {
            gof.updateGrid();
        }
        
        grid = gof.getPixels();

        window.clear();

        for (int y = 0; y < grid.size(); y++)
        {
            for (int x = 0; x < grid[y].size(); x++)
            {
                window.draw(grid[y][x]);
            }
        }

        window.display();
    }

    

    return 0;
}

