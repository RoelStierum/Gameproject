#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class drawable{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
};

class rectangle: public drawable{
private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;

    sf::RectangleShape rectangleShape;

    void update_position(){
        rectangleShape.setPosition(position);
    }

public:

    rectangle(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color& color = sf::Color::White):
            position(position),
            size(size),
            color(color)
    {
        rectangleShape.setPosition(position);
        rectangleShape.setSize(size);
        rectangleShape.setFillColor(color);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(rectangleShape);
    }

    void move_x(const float& move_){
        position.x += move_;
        update_position();
    }

    void move_y(const float& move_){
        position.y += move_;
        update_position();
    }

    void setColor(const sf::Color &color) {
        rectangle::color = color;
    }
};

class Platformer{
private:
    sf::RenderWindow& renderWindow;
    rectangle character = {sf::Vector2f {100,100},sf::Vector2f {100,100},sf::Color::Magenta};

    float speed = 20;

    // bool function for checking for collision

public:
    Platformer(sf::RenderWindow &renderWindow) :
        renderWindow(renderWindow)
    {}

    void draw(){
        character.draw(renderWindow);
    }

    void update(const float& time_delta){
        character.move_y(speed * time_delta);
    }
};

int main() {
    sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window Daan"  };
    sf::Clock clock1;

    auto platformer = Platformer{window};

    //auto r1 = rectangle{sf::Vector2f{10,10},sf::Vector2f{10,10}};
    //drawable* d1 = new rectangle{sf::Vector2f{40,10},sf::Vector2f{10,40}};

    while (window.isOpen()) {


        //update
        platformer.update(clock1.getElapsedTime().asSeconds());
        clock1.restart();


        //draw
        window.clear();

        platformer.draw();

        window.display();

        sf::sleep( sf::milliseconds( 20 ));

        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                window.close();
            }
        }
    }
}