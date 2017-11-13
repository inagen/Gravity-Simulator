#include "space.h"
#include <time.h>
#include <cmath>
#include <thread>

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
    std::lock_guard<std::mutex> lock(planets_access_mutex);
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
    std::thread physics_thread(&space::logic_loop, this);
	render_event_loop();
    if (physics_thread.joinable()) physics_thread.join();
}

void space::clear(){
    std::lock_guard<std::mutex> lock(planets_access_mutex);
	planets.clear();
}

void space::render_planet(object planet){

	sf::CircleShape circle;
	circle.setRadius(planet.radius);
	circle.setFillColor(sf::Color::White);
	circle.setPosition(planet.pos_x, planet.pos_y);
	window->draw(circle);

}

void space::draw_all_planets(){
    std::lock_guard<std::mutex> lock(planets_access_mutex);
	for(int i(0); i != planets.size(); ++i){
		render_planet(planets[i]);
	}

}

void space::process_all_planets(){
    std::vector<object> new_planets_state;
    {
        std::lock_guard<std::mutex> lock(planets_access_mutex);
        new_planets_state = planets;
    }

	for(int i = 0; i < new_planets_state.size(); ++i){

		for(int j = 0; j < new_planets_state.size(); ++j){

			if(i == j) continue;

            // TODO: Is distance computation expensive?
			if( object::distance(new_planets_state[i], new_planets_state[j]) <=
				(new_planets_state[i].radius + new_planets_state[j].radius) ||
				object::distance(new_planets_state[i], new_planets_state[j]) == 0){

				if(new_planets_state[j].mas > new_planets_state[i].mas){
					new_planets_state[j].merge(new_planets_state[i]);
					auto it_i = new_planets_state.begin() + i;
					new_planets_state.erase(it_i);
				} else {
					new_planets_state[i].merge(new_planets_state[j]);
					auto it_j = new_planets_state.begin() + j;
                    // TODO: Does it worth optimizing out this costly erase?
					new_planets_state.erase(it_j);
				}
				// it is possible that we are shrink our vector and i become out-of-bounds.
				if (i >= new_planets_state.size()) {
					break;
				}
			} else {

				new_planets_state[j].acceleration(new_planets_state[i]);
				new_planets_state[i].acceleration(new_planets_state[j]);
			}

		} //for(j)

        new_planets_state[i].pos_x += new_planets_state[i].acceleration_x;
        new_planets_state[i].pos_y += new_planets_state[i].acceleration_y;
	} //for (i)
    std::lock_guard<std::mutex> lock(planets_access_mutex);
    planets = new_planets_state;
}

void space::logic_loop(){
    static const unsigned tps_limit_base = 1000;

    sf::Clock tps_counter_reset;
    unsigned tps = 0;
    while (window->isOpen()){
        if (tps_counter_reset.getElapsedTime() >= sf::seconds(1)){
            tps = 0;
            tps_counter_reset.restart();
        }

        sf::sleep(sf::seconds(1.0/(tps_limit_base * tps_limit_multipler)));
        process_all_planets();
        ++tps;
    }
}

void space::render_event_loop(){

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
		draw_all_planets();
		sf::View view = window->getDefaultView();
		view.zoom(zoom);
		window->setView(view);
		window->display();

	}
}
