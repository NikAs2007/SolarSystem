#include "header.h"

int width = GetSystemMetrics(SM_CXSCREEN);
int height = GetSystemMetrics(SM_CYSCREEN);

int sosx = 1500, sosy = sosx * height / width;



int main()
{
    srand(time(0));
    ContextSettings settings;
    settings.antialiasingLevel = 5;
    RenderWindow window(VideoMode(sosx, sosy), "Solar System", Style::Default, settings);

    //Planet planet1(50, 5,Vector2f(900, 100));
    //Planet planet2(500, 10, Vector2f(950, 200));
    Universe universe(3);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        /*Тут пишем*/

        window.clear(sf::Color(255, 255, 255));

        //planet1.acc_calc(planet2);
        //planet2.acc_calc(planet1);


        //planet1.phy();
        //planet2.phy();
        universe.physics();

        universe.draw_planets(window);
        //window.draw(planet1.get_body());
        //window.draw(planet2.get_body());

        window.display();
    }

    return 0;
}

float dis(Vector2f a, Vector2f b) {
    return pow((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y), 0.5);
}

float mod(Vector2f a) {
    return pow(a.x * a.x + a.y * a.y, 0.5);
}

float angle_between_vetors(Vector2f one, Vector2f two) {
    if (mod(one) == 0) return 0;
    if (mod(two / mod(one))) return 0;
    return 1.0f / mod(two / mod(one));
}

Vector2f normalize(Vector2f orig) {
    if (mod(orig) == 0) return Vector2f(0, 0);
    return orig / mod(orig);
}

Vector2f rotate_vec(Vector2f vec, float angle) {
    if (normalize(vec).x == 0) return vec;
    if (cosf(acosf(1.0f / normalize(vec).x) + angle) || sinf(acosf(1.0f / normalize(vec).x) + angle)) return vec;
    return mod(vec) * Vector2f(1.0f / cosf(acosf(1.0f / normalize(vec).x) + angle), 1.0f / sinf(acosf(1.0f / normalize(vec).x) + angle));
}

Vector2f to_normal(Vector2f one, Vector2f nor) {
    return rotate_vec(one, angle_between_vetors(one, nor));
}

Vector2f to_global(Vector2f one, Vector2f nor) {
    return rotate_vec(one, -angle_between_vetors(one, nor));
}