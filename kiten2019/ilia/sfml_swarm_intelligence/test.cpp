#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
const int BIRDS_COUNT = 400;

sf::RenderWindow window(sf::VideoMode(1200,900), "pti4ki");

sf::Vector2u size = window.getSize();

float lengthSq(sf::Vector2f &vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

struct Bird {
    sf::ConvexShape shape;
    sf::Vector2f vel;
    sf::Vector2f acc;
    float rot = 0;
    float rotSpd = 1;
    float maxSpeed = 1;
    Bird(sf::Vector2f &pos) {
        shape.setPointCount(3);
        shape.setPoint(0, sf::Vector2f(-3, -3));
        shape.setPoint(1, sf::Vector2f(-3, 3));
        shape.setPoint(2, sf::Vector2f(5, 0));
        shape.setScale(sf::Vector2f(1,1));
        shape.setPosition(pos);
        vel = sf::Vector2f();
        acc = sf::Vector2f();
        rot = 0;
        shape.setRotation(rot);
    }
    Bird() {
        shape.setPointCount(3);
        shape.setPoint(0, sf::Vector2f(-4, -4));
        shape.setPoint(1, sf::Vector2f(-4, 4));
        shape.setPoint(2, sf::Vector2f(5, 0));
        shape.setScale(sf::Vector2f(1,1));
        shape.setPosition(sf::Vector2f(rand() / (float)(1 << 15) * size.x, rand() / (float)(1 << 15) * size.y));
        vel = sf::Vector2f();
        acc = sf::Vector2f();
        rot = rand() / (float) (1 << 15) * 360;
        //rot = 70;
        shape.setRotation(rot);
        //acc = sf::Vector2f(cos(rot / 180 * 3.14159) * 0.01, sin(rot / 180 * 3.14159) * 0.01);
    }
    void update(Bird *swarm) {

        acc.x = 0;
        acc.y = 0;

        int adjacent_birds_count = 0;
        float rotation = 0;
        sf::Vector2f position(0,0);
        for(int i = 0; i < BIRDS_COUNT; ++ i) {
            if(swarm + i != this) {
                ///nameri nai blizkite v radius 30, nameri sredna rotaciq i skorost, zavurti se s malko i ako e mujno zabavi.
                sf::Vector2f deltas[7];
                deltas[0] = (shape.getPosition() - swarm[i].shape.getPosition()) + sf::Vector2f( 0     , 0     );
                deltas[1] = (shape.getPosition() - swarm[i].shape.getPosition()) + sf::Vector2f( size.x, 0     );
                deltas[2] = (shape.getPosition() - swarm[i].shape.getPosition()) + sf::Vector2f( 0     , size.y);
                deltas[3] = (shape.getPosition() - swarm[i].shape.getPosition()) + sf::Vector2f( size.x, size.y);
                deltas[4] = (shape.getPosition() - swarm[i].shape.getPosition()) + sf::Vector2f(-size.x, 0     );
                deltas[5] = (shape.getPosition() - swarm[i].shape.getPosition()) + sf::Vector2f( 0     ,-size.y);
                deltas[6] = (shape.getPosition() - swarm[i].shape.getPosition()) + sf::Vector2f(-size.x,-size.y);
                sf::Vector2f delta = deltas[0];
                for(int i = 1; i < 6; ++ i) {
                    if(lengthSq(deltas[i]) < lengthSq(delta))
                        delta = deltas[i];
                }
                float dist = lengthSq(delta);
                if(dist < 50 * 50) {
                    ++ adjacent_birds_count;
                    rotation += swarm[i].rot;
                    position += swarm[i].shape.getPosition();
                }
                if(dist < 20 * 20) {
                    acc.x += 1 / delta.x / 10;
                    acc.y += 1 / delta.y / 10;
                }
            }
        }
        if(adjacent_birds_count > 0) {
            rotation /= adjacent_birds_count;
            position /= (float)adjacent_birds_count;
            if(rot > rotation) {rot -= rotSpd;}
            else rot += rotSpd;
            //acc += (-shape.getPosition() + position) * 0.0001f;
        }
        //else {rot += 5;}
        rot += rand() / (float) (1 << 15) * 5 - 2.5;
        if(rot > 360) rot -= 360;
        if(rot < 0) rot += 360;

        shape.setRotation(rot);
        acc.x += cos(rot / 180.0 * 3.14159) * 0.01;
        acc.y += sin(rot / 180.0 * 3.14159) * 0.01;

        vel += acc;
        if(lengthSq(vel) > maxSpeed * maxSpeed) {
            vel /= (float)sqrt(lengthSq(vel));
            vel *= maxSpeed;
            //vel *= 0.99f;
        }
        shape.move(vel);
        sf::Vector2f pos = shape.getPosition();
        if(pos.y < -1) pos.y = size.y - 1;
        if(pos.y > size.y + 1) pos.y = 0;
        if(pos.x < -1) pos.x = size.x - 1;
        if(pos.x > size.x + 1) pos.x = 0;
        shape.setPosition(pos);
    }

};

Bird birds[BIRDS_COUNT];

int main() {
    srand(21);

    //window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                {window.close(); return 0;}
            if(event.type == sf::Event::KeyPressed) {
                //if(event.key.code == sf::Keyboard::Tab) window.setVerticalSyncEnabled(false);
            }else if(event.type == sf::Event::KeyReleased) {
                //if(event.key.code == sf::Keyboard::Tab) window.setVerticalSyncEnabled(true);
            }else if(event.type == sf::Event::Resized){
                size.x = event.size.width;
                size.y = event.size.height;
            }
        }
        // Clear screen
        window.clear();

        for(int i = 0; i < BIRDS_COUNT; ++ i) {
            birds[i].update(birds);
            birds[i].update(birds);
            window.draw(birds[i].shape);
        }
        // Update the window
        window.display();
    }
}
