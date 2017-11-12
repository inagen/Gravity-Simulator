#include "space.h"
#include <time.h>
#include <cmath>

space::space(unsigned int number_of_planets){

	srand( time(0) );
	generate(number_of_planets);
	start();

}

space::space(){
	srand( time(0) );
	//window = new sf::RenderWindow(sf::VideoMode(CONSTS::width, CONSTS::height), "Gravity++");
	//start();
}

void space::generate(unsigned int number_of_planets){
	object temp;
	planets.reserve(number_of_planets);
	for (int i(0); i < number_of_planets; i++) {
		temp.pos_x = rand() % CONSTS::width + 1;
		temp.pos_y = rand() % CONSTS::height + 1;
		temp.acceleration_x = rand() % 2 - 1;
		temp.acceleration_y = rand() % 2 - 1;

		planets.push_back(temp);
	}
}

void space::start(){
	window = new sf::RenderWindow(sf::VideoMode(CONSTS::width, CONSTS::height), "Gravity++");
	main_loop();
}

void space::clear(){
	planets.clear();
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
		planets[i].pos_x += planets[i].acceleration_x;
		planets[i].pos_y += planets[i].acceleration_y;
		render_planet(planets[i]);
	}

}

void space::process_all_planets(){

	for(int i = 0; i < planets.size(); ++i){

		for(int j = 0; j < planets.size(); ++j){

			if(i == j) continue;

			if( object::distance(planets[i], planets[j]) <= 
				(planets[i].radius + planets[j].radius)/1.5 || 
				object::distance(planets[i], planets[j]) == 0){

				planets[j].merge(planets[i]);

				auto it_i = planets.begin() + i;
				planets.erase(it_i);

				// it is possible that we are shrink our vector and i become out-of-bounds.
				if (i >= planets.size()) {
					break;
				}
			} else {

				/*double dist = object::distance(planets[i], planets[j]);

				double fG = (planets.at(i).mas * planets.at(j).mas / pow(dist, 2)) / 5000;

				double massJtoI = (planets[j].mas / planets[i].mas);
				double massItoJ = (planets[i].mas / planets[j].mas);

				double fGmassJtoI = fG * massJtoI;
				double fGmassItoJ = fG * massItoJ;

				int direction_x = planets[i].pos_x > planets[j].pos_x ? -1 : 1;
				int direction_y = planets[i].pos_y > planets[j].pos_y ? -1 : 1;

				planets[i].acceleration_x += fGmassJtoI * direction_x;
				planets[i].acceleration_y += fGmassJtoI * direction_y;

				planets[j].acceleration_x += fGmassItoJ * -direction_x;
				planets[j].acceleration_y += fGmassItoJ * -direction_y;
				*/
				planets[j].acceleration(planets[i]);
				planets[i].acceleration(planets[j]);
				
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)){
			this->clear();
			this->generate(200);
		}
		window->clear();
		process_all_planets();
		apply_changes();
		window->display();

	}
}
