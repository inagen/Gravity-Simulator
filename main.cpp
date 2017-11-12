#include "space.h"
#include "object.h"

int main(){

	//space(100);

	space world;

	world.planets.push_back({/*radius*/3, /*mas*/10, /*pos*/110, 100, /*accel*/0, -0.1});
	world.planets.push_back({/*radius*/3, /*mas*/8, /*pos*/110, 200, /*accel*/0, 0.1});
	world.planets.push_back({/*radius*/2, /*mas*/6, /*pos*/170, 330, /*accel*/0, -0.15});
	world.planets.push_back({/*radius*/1, /*mas*/3, /*pos*/370, 310, /*accel*/0, 0.15});
	world.planets.push_back({/*radius*/2, /*mas*/5, /*pos*/360, 300, /*accel*/0, 0.2});
	world.planets.push_back({/*radius*/8, /*mas*/5973, /*pos*/300, 300,  /*accel*/0, 0});
	world.start();
}