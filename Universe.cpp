#include "header.h"

float k = 0.001;
float d = 15;

Universe::Universe(int count) {
	for (int i = 0; i < count; i++) {
		universe.push_back(Planet(rand() % 491 + 100, rand() % 10 + 5, Vector2f(rand() % (sosx / 2) + sosx / 4, rand() % (sosy / 2) + sosy / 4)));
		universe[i].set_vel(Vector2f((rand() % 1000 - 500) * 1.f / 10000, (rand() % 1000 - 500) * 1.f / 10000));
	}
}

void Universe::draw_planets(RenderWindow& window) {
	for (int i = 0; i < universe.size(); i++) {
		window.draw(universe[i].get_body());
	}
}

void Universe::physics() {
	for (int i = 0; i < universe.size(); i++) {
		universe[i].set_acc(Vector2f(0, 0));
		for (int j = 0; j < universe.size(); j++) {
			if (i != j) {
				universe[i].acc_calc(universe[j]);
			}
		}
		universe[i].phy();
	}
}