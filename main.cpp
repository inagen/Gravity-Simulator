#include "space.h"
#include "object.h"

int main(){

	//space(100);

	space world;
	world.planets.push_back({/*pos*/400, 300, /*radius*/5, /*mas*/10000, /*accel*/0, 0});
	world.planets.push_back({/*pos*/250, 400, /*radius*/1, /*mas*/10, /*accel*/0, 0});
	world.start();
}