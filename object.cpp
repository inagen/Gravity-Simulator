#include "object.h"

object object::merge(const object obj){
	object new_object;
	new_object.radius = this->radius + obj.radius;
	new_object.mas = this->mas + obj.mas;
	new_object.pos_x = this->pos_x;
	new_object.pos_y = this->pos_y;
	new_object.speed_x = this->speed_x + obj.speed_x;
	new_object.speed_y = this->speed_y + obj.speed_y;
	new_object.acceleration_x = this->acceleration_x + obj.acceleration_x;
	new_object.acceleration_x = this->acceleration_x + obj.acceleration_x;
	return new_object;
}

double object::distance(const object obj1, const object obj2){
	auto x1 = obj1.pos_x;
	auto y1 = obj1.pos_y;
	auto x2 = obj2.pos_x;
	auto y2 = obj2.pos_y;

	double distance;
	distance = sqrt( (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
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
	this->acceleration_x += nacceleration_x;
	this->acceleration_y += nacceleration_y; 
}
