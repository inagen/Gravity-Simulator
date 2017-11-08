#pragma once
#include "object.h"
#include <vector>
#include <SFML/Graphics.hpp>

class space{
private:
	std::vector<object> planets;
	sf::RenderWindow* window;
public:
	space(unsigned int number_of_planets);
	void start();
	void all_planets_processing();
	void apply_changes();
	void main_loop();
	void render_planet(object planet);
	void add_object(int, int, int, int, double, double);
};