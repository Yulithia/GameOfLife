#include "GameOfLife.h"
#include <random>
#include <fstream>
#include <iterator>

#include <iostream>

GameOfLife::GameOfLife(const int width, const int height, const int cellSize)
    :width(width), height(height), cellSize(cellSize)
{
    for (int y = 0; y < height; y++)
    {
        isAlive.push_back({});
        pixels.push_back({});
        for (int x = 0; x < width; x++)
        {
            isAlive[y].push_back(false);
            pixels[y].emplace_back(sf::Vector2f(cellSize, cellSize));
            pixels[y][x].setPosition(y * cellSize, x * cellSize);
            pixels[y][x].setFillColor(sf::Color::Black);
        }
    }
}

void GameOfLife::updateData()
{
    std::vector<std::vector<bool>> copyIsAlive = isAlive;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int counter = 0;
            for (int i = std::max(y - 1, 0); i <= std::min(y + 1, height - 1); i++)
            {
                for (int j = std::max(x - 1, 0); j <= std::min(x + 1, width - 1); j++)
                {
                    if (copyIsAlive[i][j] && !(i == y && j == x))
                    {
                        counter++;
                    }
                }
            }

            if (isAlive[y][x])
            {
                if (counter == 2 || counter == 3)
                {
                    isAlive[y][x] = true;
                }
                else
                {
                    isAlive[y][x] = false;
                }
            }
            else
            {
                if (counter == 3)
                {
                    isAlive[y][x] = true;
                }
            }
            
        }

    }
}

void GameOfLife::updatePixels()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (isAlive[y][x])
            {
                pixels[y][x].setFillColor(sf::Color::White);
            }
            else
            {
                pixels[y][x].setFillColor(sf::Color::Black);
            }
        }
    }

}

void GameOfLife::updateGrid()
{
    updateData();
    updatePixels();
}

void GameOfLife::saveData(std::string path, int iterations)
{
    std::vector<double> result;
    int size = width * height;
    int countAlive = 0;

    for (int i = 0; i < iterations; i++)
    {
        for (int y = 0; y < pixels.size(); y++)
        {
            for (int x = 0; x < pixels[0].size(); x++)
            {
                if (isAlive[y][x])
                {
                    countAlive++;
                }
            }
        }
        result.push_back(double(countAlive) / double(size));
        updateData();
        countAlive = 0;
    }

    std::ofstream file(path);
    std::ostream_iterator<double> it(file, "\n");
    std::copy(result.begin(), result.end(), it);
}

void GameOfLife::saveSimulation(std::string path, int iterations, int simulations, double prob)
{
    std::vector<double> result;
    int size = width * height;
    int countAlive = 0;

    for (int s = 0; s < simulations; s++)
    {
        for (int i = 0; i < iterations; i++)
        {           
            updateData();       
        }
        for (int y = 0; y < isAlive.size(); y++)
        {
            for (int x = 0; x < isAlive[0].size(); x++)
            {
                if (isAlive[y][x])
                {
                    countAlive++;
                }
            }
        }
        result.push_back(double(countAlive) / double(size));
        countAlive = 0;
        generateGrid(prob);
    }

    std::ofstream file(path);
    std::ostream_iterator<double> it(file, "\n");
    std::copy(result.begin(), result.end(), it);
}

void GameOfLife::generateGrid(double prob)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(prob);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            isAlive[y][x] = dist(gen);
            if (isAlive[y][x]) {
                pixels[y][x].setFillColor(sf::Color::White);
            }
            else {
                pixels[y][x].setFillColor(sf::Color::Black);
            }
        }
    }
}

void GameOfLife::flipPixel(sf::Vector2i mousePos)
{
    std::cout << mousePos.x << " " << mousePos.y << "\n";

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int xStart = y * cellSize;       
            int yStart = x * cellSize;       
            int xEnd = xStart + cellSize;    
            int yEnd = yStart + cellSize;     

            if ((mousePos.x >= xStart && mousePos.x < xEnd) &&
                (mousePos.y >= yStart && mousePos.y < yEnd)) {

                isAlive[y][x] = !isAlive[y][x];
                if (isAlive[y][x]) {
                    pixels[y][x].setFillColor(sf::Color::White);
                }
                else {
                    pixels[y][x].setFillColor(sf::Color::Black);
                }
            }
        }
    }

}

void GameOfLife::flipRunning()
{
    running = !running;
}

bool GameOfLife::getRunning()
{
    return running;
}
