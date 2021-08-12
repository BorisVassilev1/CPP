#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
//using namespace GL;

const int POINTS_COUNT = 100;

sf::RenderWindow window(sf::VideoMode(800,600), "korab4e");

sf::Vector2u size = window.getSize();

struct Point {
    sf::Vector2f pos;
    sf::Color col;
    sf::Vector2f vel;
    Point() {
        pos = sf::Vector2f(rand() / (float) (1 << 15) * 800, rand() / (float) (1 << 15) * 600);
        vel = sf::Vector2f(rand() / (float) (1 << 15) * 5 - 2.5, rand() / (float) (1 << 15) * 5 - 2.5);
        col = sf::Color(rand() / (float) (1 << 15) * 255, rand() / (float) (1 << 15) * 255, rand() / (float) (1 << 15) * 255,255);
    }
    update() {
        pos += vel;

        if(pos.y < -1) pos.y = size.y - 1;
        if(pos.y > size.y + 1) pos.y = 0;
        if(pos.x < -1) pos.x = size.x - 1;
        if(pos.x > size.x + 1) pos.x = 0;
    }
};


Point points[POINTS_COUNT];


int main() {
    sf::RectangleShape pixel(sf::Vector2f(4.0f,4.0f));

    /*std::cout << "{";
    for(int i = 0; i < POINTS_COUNT; ++ i) {
        std::cout << "vec2(" << points[i].pos.x / 800 << "," << points[i].pos.y / 600 << "), ";
        if(i % 5 == 4) std::cout << std::endl;
    }
    std::cout << "}";*/

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                {window.close(); return 0;}
        }
        //window.clear();

        for(int i = 0; i < POINTS_COUNT; ++ i) {
            points[i].update();
        }

        for(int x = 0; x < 800; x += 4) {
            for(int y = 0; y < 600; y += 4) {
                pixel.setPosition(sf::Vector2f(x,y));
                float best_dist = 99999999;
                int best_point;
                for(int i = 0; i < POINTS_COUNT; ++ i) {
                    //float dist = (int) ((points[i].pos.x - x) * (points[i].pos.x - x)) + (int) ((points[i].pos.y - y) * (points[i].pos.y - y));

                    float dist = abs((int)points[i].pos.x - x) | abs((int)points[i].pos.y - y);
                    //float dist = abs((int)points[i].pos.x ^ x) | abs((int)points[i].pos.y ^ y);
                    //float dist = abs((int)points[i].pos.x + x) | abs((int)points[i].pos.y + y);
                    //float dist = abs((int)points[i].pos.x + x) ^ abs((int)points[i].pos.y + y);
                    //float dist = abs((int)points[i].pos.x | x) | abs((int)points[i].pos.y | y);

                    //float dist = sin((points[i].pos.x - x) / 800 * 3.14159) + cos((points[i].pos.y - y) / 600 * 3.14159);
                    if(dist < best_dist) {
                        best_dist = dist;
                        best_point = i;
                    }
                }
                pixel.setFillColor(points[best_point].col);
                window.draw(pixel);
            }
        }
        window.display();
    }

}
