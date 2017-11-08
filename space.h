#pragma once
#include "object.h"
#include <vector>
#include <thread>
#include <SFML/Graphics.hpp>

class space{
private:
	std::vector<object> planets;
	sf::RenderWindow* window;
public:
	space(unsigned int num);
	void one_planet_processing(unsigned int num);
	void all_planets_processing();
	void apply_changes();
	void main_loop();
	void render_planet(object planet);
};