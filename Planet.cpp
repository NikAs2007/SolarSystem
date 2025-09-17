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
	bool for_phy = true;
}

void Planet::collision(Planet& other) {
	if (dis(other.get_pos(), pos) <= other.get_body().getRadius() + get_body().getRadius()) {
		//новый расёт V
		float V1x = this->get_vel().x, V2x = other.get_vel().x;
		float m1 = this->get_mass(), m2 = other.get_mass();
		float kx = V1x * m1 + V2x * m2;
		float Ekox = m1 * V1x * V1x / 2 + m2 * V2x * V2x / 2;
		float Dx = pow(2 * m1 * kx, 2) + 4 * (m2 * m1 + m1 * m1) * (2 * Ekox * m2 - kx * kx);
		float V1xs1 = (2 * kx * m1 + pow(Dx, 0.5)) / (2 * (m2 * m1 + m1 * m1));
		float V1xs2 = (2 * kx * m1 - pow(Dx, 0.5)) / (2 * (m2 * m1 + m1 * m1));
		float V2xs1 = kx - V1xs1 * m1;
		float V2xs2 = kx - V1xs2 * m1;

		float V1y = this->get_vel().y, V2y = other.get_vel().y;
		float ky = V1y * m1 + V2y * m2;
		float Ekoy = m1 * V1y * V1y / 2 + m2 * V2y * V2y / 2;
		float Dy = pow(2 * m1 * ky, 2) + 4 * (m2 * m1 + m1 * m1) * (2 * Ekoy * m2 - ky * ky);
		float V1ys1 = (2 * k * m1 + pow(Dy, 0.5)) / (2 * (m2 * m1 + m1 * m1));
		float V1ys2 = (2 * k * m1 - pow(Dy, 0.5)) / (2 * (m2 * m1 + m1 * m1));
		float V2ys1 = ky - V1ys1 * m1;
		float V2ys2 = ky - V1ys2 * m1;


		//vx1 & vx2
		float V1xEnd;
		float V2xEnd;
		if (m1 >= m2 && !co_dir(V1x, V2x)) {
			if (!co_dir(V2x, V2xs1)) {
				V1xEnd = V1xs1;
				V2xEnd = V2xs1;
			}
			else {
				V1xEnd = V1xs2;
				V2xEnd = V2xs2;
			}
		}
		else if (m1 < m2 && co_dir(V1x, V2x)) {
			if (co_dir(V2x, V2xs1)) {
				V1xEnd = V1xs1;
				V2xEnd = V2xs1;
			}
			else {
				V1xEnd = V1xs2;
				V2xEnd = V2xs2;
			}
		}
		else if (m1 < m2 && !co_dir(V1x, V2x)) {
			if (!co_dir(V1x, V1xs1)) {
				V1xEnd = V1xs1;
				V2xEnd = V2xs1;
			}
			else {
				V1xEnd = V1xs2;
				V2xEnd = V2xs2;
			}
		}
		else {
			if (co_dir(V1x, V1xs1) && co_dir(V2x, V2xs1)) {
				V1xEnd = V1xs1;
				V2xEnd = V2xs1;
			}
			else {
				V1xEnd = V1xs2;
				V2xEnd = V2xs2;
			}
		}
		//vx1

		//vy1 & vy2
		float V1yEnd;
		float V2yEnd;
		if (m1 >= m2 && !co_dir(V1y, V2y)) {
			if (!co_dir(V2y, V2ys1)) {
				V1yEnd = V1ys1;
				V2yEnd = V2ys1;
			}
			else {
				V1yEnd = V1ys2;
				V2yEnd = V2ys2;
			}
		}
		else if (m1 < m2 && co_dir(V1y, V2y)) {
			if (co_dir(V2y, V2ys1)) {
				V1yEnd = V1ys1;
				V2yEnd = V2ys1;
			}
			else {
				V1yEnd = V1ys2;
				V1yEnd = V1ys2;
			}
		}
		else if (m1 < m2 && !co_dir(V1y, V2y)) {
			if (!co_dir(V1y, V1ys1)) {
				V1yEnd = V1ys1;
				V2yEnd = V2ys1;
			}
			else {
				V1yEnd = V1ys2;
				V1yEnd = V1ys2;
			}
		}
		else {
			if (co_dir(V1y, V1ys1) && co_dir(V2y, V2ys1)) {
				V1yEnd = V1ys1;
				V2yEnd = V2ys1;
			}
			else {
				V1yEnd = V1ys2;
				V1yEnd = V1ys2;
			}
		}
		//vy1


		this->set_vel(Vector2f(V1xEnd, V1yEnd));
		this->for_phy = false;
		other.set_vel(Vector2f(V2xEnd, V2yEnd));
		other.for_phy = false;

		if (pos.x + radius >= sosx) vel.x *= -1;
		if (pos.y + radius >= sosy) vel.y *= -1;
		if (pos.x - radius <= 0) vel.x *= -1;
		if (pos.y - radius <= 0) vel.y *= -1;
	}
}

void Planet::acc_calc(Planet& other) {
	if (dis(other.get_pos(), pos) == 0) return;
	acc += normalize(Vector2f(other.get_pos().x - pos.x, other.get_pos().y - pos.y)) * k * other.get_mass() / float(pow(dis(other.get_pos(), pos), 2));

	//acc -= d * normalize(Vector2f(other.get_pos().x - pos.x, other.get_pos().y - pos.y)) / float(pow(dis(other.get_pos(), pos), 3))
}

void Planet::phy(Planet& other) {

	vel += acc;
	if (mod(vel) > 0.4f) vel = 0.3f * normalize(vel);

	pos.x += vel.x;
	pos.y += vel.y;
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

Vector2f Planet::get_vel() {
	return vel;
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