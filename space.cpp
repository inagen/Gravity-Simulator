#include "space.h"

space::space(unsigned int num){
	srand( time(0) );
	object temp;
	for(int i(0); i <= num; i++){
		temp.pos_x = rand() % CONSTS::width  + 1;
		temp.pos_y = rand() % CONSTS::height + 1;
		planets.push_back(temp);
	}
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

void space::one_planet_processing(unsigned int num){

	for(int i(0); i != planets.size(); ++i){
		if(num == i) continue;
		if(planets[num].pos_x == planets[i].pos_y && planets[num].pos_y == planets[i].pos_y){	
			planets[num].merge(planets[i]);
			auto it = planets.begin() + num;
			planets.erase(it);
		} else {
			planets[num].acceleration(planets[i]);
		}
	}
}

void space::all_planets_processing(){

	for(int i(0); i != planets.size(); ++i){
		one_planet_processing(i);
	}
}


void space::main_loop(){

	while (window->isOpen()){

        sf::Event event;
        while (window->pollEvent(event)){
        	window->clear();
            if (event.type == sf::Event::Closed)
                window->close();
			all_planets_processing();
			apply_changes();
			window->display();
        }

    }
}