#include "space.h"
#include <time.h>
#include <cmath>

space::space(unsigned int number_of_planets){

	srand( time(0) );
	zoom = 1;
	generate(number_of_planets);
	start();

}

space::space(){
	zoom = 1;
	srand( time(0) );
}

void space::generate(unsigned int number_of_planets){
	object temp;
	planets.reserve(number_of_planets);
	for (int i(0); i < number_of_planets; i++) {
		temp.pos_x = rand() % CONSTS::width + 1;
		temp.pos_y = rand() % CONSTS::height + 1;
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
				(planets[i].radius + planets[j].radius) || 
				object::distance(planets[i], planets[j]) == 0){

				if(planets[j].mas > planets[i].mas){
					planets[j].merge(planets[i]);
					auto it_i = planets.begin() + i;
					planets.erase(it_i);
				} else {
					planets[i].merge(planets[j]);
					auto it_j = planets.begin() + j;
					planets.erase(it_j);
				}
				// it is possible that we are shrink our vector and i become out-of-bounds.
				if (i >= planets.size()) {
					break;
				}
			} else {

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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window->close();
			break;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)){
			if(zoom < 10)
				zoom = zoom + 0.1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
			if(zoom > 0)
				zoom = zoom - 0.1;
		}

		window->clear();
		process_all_planets();
		apply_changes();
		sf::View view = window->getDefaultView();
		view.zoom(zoom);
		window->setView(view);
		window->display();

	}
}
