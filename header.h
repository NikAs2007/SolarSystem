#ifndef HEADER_H
#define HEADER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include <vector>
#include <Windows.h>
using namespace sf;
using namespace std;

extern int sosx, sosy;
extern float k, d;

float dis(Vector2f a, Vector2f b);
Vector2f normalize(Vector2f orig);
float mod(Vector2f a);

class Planet {

	CircleShape body;

	float mass, radius;
	Vector2f pos, vel, acc;
public:
	Planet(float m, float r, Vector2f p);
	CircleShape get_body();
	float get_mass();
	Vector2f get_pos();
	void acc_calc(Planet& other);
	void phy();
	void set_pos(Vector2f p);
	void set_acc(Vector2f a);
	void set_vel(Vector2f v);
};


class Universe {
	vector<Planet> universe;
public:
	Universe(int count);
	void draw_planets(RenderWindow& window);
	void physics();
};

#endif