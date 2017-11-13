#pragma once
#include "object.h"
#include <vector>
#include <mutex>
#include <SFML/Graphics.hpp>

class space{
private:
	sf::RenderWindow* window;
	double zoom;
    std::mutex planets_access_mutex;

public:
	std::vector<object> planets;

private:
	void process_all_planets();
	void draw_all_planets();
	void render_event_loop();
    void logic_loop();
	void render_planet(object planet);
public:
	space(unsigned int number_of_planets);
	space();
	void start();
	void clear();
	void generate(unsigned int number_of_planets);
	void add_object(int, int, int, int, double, double);

    float tps_limit_multipler = 1.0;
};
