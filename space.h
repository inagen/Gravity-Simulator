#pragma once
#include "object.h"
#include <vector>
#include <SFML/Graphics.hpp>

class space{
private:
	sf::RenderWindow* window;
	double zoom;

public:
	std::vector<object> planets;

private:
	void process_all_planets();
	void apply_changes();
	void main_loop();
	void render_planet(object planet);
public:
	space(unsigned int number_of_planets);
	space();
	void start();
	void clear();
	void generate(unsigned int number_of_planets);
	void add_object(int, int, int, int, double, double);
};