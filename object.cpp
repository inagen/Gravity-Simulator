#include "object.h"
#include <math.h>

void object::merge(const object obj){

	this->radius += obj.radius;
	this->mas += obj.mas;
	this->acceleration_x += obj.acceleration_x;
	this->acceleration_x += obj.acceleration_x;

}

double object::distance(const object obj1, const object obj2){
	auto x1 = obj1.pos_x;
	auto y1 = obj1.pos_y;
	auto x2 = obj2.pos_x;
	auto y2 = obj2.pos_y;

	double distance = sqrt( (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) );
	return distance;
}

void object::acceleration(const object obj){

	double dist = distance(*this, obj);
	double acceleration = CONSTS::G * ( obj.mas/(obj.radius + dist) );
	double x = abs(this->pos_x - obj.pos_x);
	double y = abs(this->pos_y - obj.pos_y);
	double phi = atan2(y, x);
	double nacceleration_x = abs(acceleration) * cos(phi);
	double nacceleration_y = abs(acceleration) * sin(phi);
	int direction_x = (this->pos_x >= obj.pos_x ? -1 : 1);
	int direction_y = (this->pos_y >= obj.pos_y ? -1 : 1);  
	this->acceleration_x += nacceleration_x * direction_x * 1000000; // very big number
	this->acceleration_y += nacceleration_y * direction_y * 1000000; 

}
