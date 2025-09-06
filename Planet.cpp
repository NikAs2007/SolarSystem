#include "header.h"

Planet::Planet(float m, float r, Vector2f p) {
	radius = r;
	mass = m;
	pos = p;
	vel = Vector2f(0, 0);
	acc = Vector2f(0, 0);
	body.setFillColor(Color(rand()%256, rand()%256, rand()%256));
	body.setPointCount(50);
	body.setRadius(radius);
	body.setPosition(pos.x - r, pos.y - r);
}

void Planet::acc_calc(Planet& other) {
	if (dis(other.get_pos(), pos) == 0) return;
	acc += normalize(Vector2f(other.get_pos().x - pos.x, other.get_pos().y - pos.y)) * k * other.get_mass() / float(pow(dis(other.get_pos(), pos), 2));
	//if (dis(other.get_pos(), pos) <= 100) acc -= d * normalize(Vector2f(other.get_pos().x - pos.x, other.get_pos().y - pos.y)) / float(pow(dis(other.get_pos(), pos), 3));
}

void Planet::phy() {
	vel += acc;
	if (mod(vel) > 0.7) vel = 1.f * normalize(vel);
	pos.x += vel.x;
	pos.y += vel.y;
	if (pos.x + radius >= sosx) vel.x *= -1;
	if (pos.y + radius >= sosy) vel.y *= -1;
	if (pos.x - radius <= 0) vel.x *= -1;
	if (pos.y - radius <= 0) vel.y *= -1;
	body.setPosition(pos.x - radius, pos.y - radius);
}

CircleShape Planet::get_body() {
	return body;
}

Vector2f Planet::get_pos() {
	return pos;
}

float Planet::get_mass() {
	return mass;
}

void Planet::set_pos(Vector2f p) {
	pos = p;
	body.setPosition(pos.x, pos.y);
}

void Planet::set_acc(Vector2f a) {
	acc = a;
}

void Planet::set_vel(Vector2f v) {
	vel = v;
}