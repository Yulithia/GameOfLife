#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class GameOfLife {
private:
	std::vector<std::vector<sf::RectangleShape>> pixels;
	std::vector<std::vector<bool>> isAlive;
	const int width;
	const int height;
	const int cellSize;
	bool running = true;
	void updateData();
	void updatePixels();

public:
	GameOfLife(const int width, const int height, const int cellSize);

	void updateGrid();
	void saveData(std::string path, int iterations);
	void saveSimulation(std::string path, int iterations, int simulations, double prob);
	void generateGrid(double prob);
	void flipPixel(sf::Vector2i mousePos);
	void flipRunning();
	bool getRunning();
	std::vector<std::vector<sf::RectangleShape>> getPixels() const { return pixels; }
	std::vector<std::vector<bool>> getAlive() const { return isAlive; }
};