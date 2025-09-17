#ifndef HEADER_H
#define HEADER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <math.h>
#include <iostream>
using namespace sf;
using namespace std;

extern int sosx, sosy;
extern float k, d;

float dis(Vector2f a, Vector2f b);
Vector2f normalize(Vector2f orig);
float mod(Vector2f a);
//float angle_between_vetors(Vector2f one, Vector2f two);
//Vector2f rotate_vec(Vector2f vec, float angle);
//Vector2f to_normal(Vector2f one, Vector2f nor);
//Vector2f to_global(Vector2f one, Vector2f nor);
bool co_dir(float a, float b);

class Planet {

	CircleShape body;

	float mass, radius;
	Vector2f pos, vel, acc;
	friend class Universe; //теперь Uiniverse имеет доступ к private Planet
	bool for_phy;

	void acc_calc(Planet& other);
	void set_acc(Vector2f a);
	void phy(Planet& other);
	void collision(Planet& other);
public:

	Planet(float m, float r, Vector2f p);
	CircleShape get_body();
	float get_mass();
	Vector2f get_vel();
	Vector2f get_pos();
	void set_pos(Vector2f p);
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