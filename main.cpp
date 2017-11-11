#include "space.h"
#include "object.h"

int main(){

	//space(100);

	space world;
	world.add_object( 400, 300, 5, 100, 0, 0);
	world.add_object( 250, 400, 1, 10, 0, 0);
	world.start();
}