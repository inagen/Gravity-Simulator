#include "space.h"
#include <time.h>

space::space(unsigned int number_of_planets){

	srand( time(0) );
	object temp;
	for(int i(0); i <= number_of_planets; i++){
		temp.pos_x = rand() % CONSTS::width  + 1;
		temp.pos_y = rand() % CONSTS::height + 1;
		planets.push_back(temp);
	}
	start();

}

void space::start(){
	window = new sf::RenderWindow(sf::VideoMode(CONSTS::width, CONSTS::height), "Gravity++");
	main_loop();
}

void space::render_planet(object planet){

	sf::CircleShape circle;
	circle.setRadius(planet.radius);
	circle.setFillColor(sf::Color::White);
	circle.setPosition(planet.pos_x, planet.pos_y);
	window->draw(circle);

}

void space::apply_changes(){

	for(int i(0); i != planets.size(); ++i){
		planets[i].speed_x += planets[i].acceleration_x;
		planets[i].speed_y += planets[i].acceleration_y;

		planets[i].pos_x += planets[i].speed_x;
		planets[i].pos_y += planets[i].speed_y;
		render_planet(planets[i]);
	}

}

void space::all_planets_processing(){

	for(int i = planets.size(); i != 0; --i){

		for(int j = 0; j != i; j++){

			if( object::distance(planets[i], planets[j]) <= planets[i].radius ||
				object::distance(planets[i], planets[j]) <= planets[j].radius){

				planets.push_back(planets[j].merge(planets[i]));
				auto it_i = planets.begin() + i;
				auto it_j = planets.begin() + j;
				planets.erase(it_i);
				planets.erase(it_j);

			} else {
				planets[i].acceleration(planets[j]);
				planets[j].acceleration(planets[i]);
			}

		} //for(j)
	} //for (i)

}


void space::main_loop(){

	while (window->isOpen()){

		sf::Event event;
		while (window->pollEvent(event)){

			if (event.type == sf::Event::Closed)
				window->close();

		}

		window->clear();
		all_planets_processing();
		apply_changes();
		window->display();

	}
}

void space::add_object(int x, int y, int r, int m, double ax, double ay){

	object new_object;
	new_object.pos_x = x;
	new_object.pos_y = y;
	new_object.radius = r;
	new_object.mas = m;
	new_object.acceleration_x = ax;
	new_object.acceleration_y = ay;
	planets.push_back(new_object);

}
