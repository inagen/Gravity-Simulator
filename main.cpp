#include "space.h"
#include "object.h"

int main(){

	//space(100);

	space world;
	world.planets.push_back({/*radius*/5, /*mas*/10000, /*pos*/400, 300, /*accel*/0, 0});
	world.planets.push_back({/*radius*/1, /*mas*/10, /*pos*/250, 400,  /*accel*/0, 0});
	world.start();
}