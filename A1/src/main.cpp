#include <SFML/Config.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <iterator>
#include <memory>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui/imgui.h"


class Entity {
public:
    std::string name;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;

    virtual ~Entity() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(float windowWidth, float windowHeight) = 0;
};

class CircleEntity : public Entity {
public:
    float radius;
    sf::CircleShape shape;

    CircleEntity(const std::string& name, const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& col, float rad)
        : radius(rad)
    {
        this->name = name;
        this->position = pos;
        this->velocity = vel;
        this->color = col;

        shape.setRadius(radius);
        shape.setPosition(position);
        shape.setFillColor(color);
    }
    void update(float windowWidth, float windowHeight) override
    {
        // Update position based on current velocity
        position += velocity;
        shape.setPosition(position);  // Update the shape position

        // Get the bounding box of the shape
        auto bounds = shape.getGlobalBounds();

        // Check for collision with left or right edges
        if (bounds.left <= 0 || bounds.left + bounds.width >= windowWidth) {
            velocity.x = -velocity.x;  // Reverse x-direction
        }

        // Check for collision with top or bottom edges
        if (bounds.top <= 0 || bounds.top + bounds.height >= windowHeight) {
            velocity.y = -velocity.y;  // Reverse y-direction
        }
    }


    void draw(sf::RenderWindow& window) override
    {
        shape.setPosition(position);
        window.draw(shape);
    }
};

class RectangleEntity : public Entity {
public:
    sf::Vector2f size;
    sf::RectangleShape shape;

    RectangleEntity(const std::string& name, const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& col, const sf::Vector2f& size)
        : size(size) {
        this->name = name;
        this->position = pos;
        this->velocity = vel;
        this->color = col;

        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(color);
    }
    void update(float windowWidth, float windowHeight) override
    {
        // Update position based on current velocity
        position += velocity;
        shape.setPosition(position);  // Update the shape position

        // Get the bounding box of the shape
        auto bounds = shape.getGlobalBounds();

        // Check for collision with left or right edges
        if (bounds.left <= 0 || bounds.left + bounds.width >= windowWidth) {
            velocity.x = -velocity.x;  // Reverse x-direction
        }

        // Check for collision with top or bottom edges
        if (bounds.top <= 0 || bounds.top + bounds.height >= windowHeight) {
            velocity.y = -velocity.y;  // Reverse y-direction
        }
    }


    void draw(sf::RenderWindow& window) override {
        shape.setPosition(position);
        window.draw(shape);
    }
};


struct FontProps
{
    std::string name;
    sf::Font myfont;
    uint16_t size;
    uint16_t r;
    uint16_t g;
    uint16_t b;
};
struct Game
{
    FontProps font;
    int wWidth;
    int wHeight;
};


std::vector<std::shared_ptr<Entity>> loadConfigFile(const std::string &filename, Game &game);

int main(int argc, char* argv[])
{
    Game game;

    auto entities = loadConfigFile("../config.txt", game);
    //const int wWidth = 1280;
    //const int wHeight = 720;

    sf::RenderWindow window(sf::VideoMode(game.wWidth, game.wHeight), "Sfml works");

    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    //sclae imgui ui and text by 2
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    //float c[3] = {0.0f, 1.0f, 1.0f};


    //float circleRadius = 50;
    //int circle_segments = 32;
    //float circle_speed_x = 1.0f;
    //float circle_speed_y = 0.5f;
    //bool drawCircle = true;
    //bool drawText = true;


    //sf::CircleShape circle(circleRadius, circle_segments);
    //circle.setPosition(10.0f, 10.0f);

    //sf::Font myFont;

    if(!game.font.myfont.loadFromFile(game.font.name))
    {
        std::cout << "Could not load file!" << std::endl;
        exit(-1);

    }

    sf::Text text("Sample Text", game.font.myfont, 24);
    text.setPosition(0, game.wHeight - (float)text.getCharacterSize());

    char displayString[255] = "Sample Text";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            ImGui::SFML::ProcessEvent(window, event);

            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                std::cout << "Key pressed with code = " << event.key.code << std::endl;

                if(event.key.code == sf::Keyboard::X)
                {
                    //circle_speed_x *= -1.0f;
                }
            }
        }

        for (auto& entity : entities) {
            entity->update(window.getSize().x, window.getSize().y);
        }

        // Draw each entity
        window.clear();
        for (auto& entity : entities) {
            entity->draw(window);
        }
        window.display();

                
    }
    return 0;
}

std::vector<std::shared_ptr<Entity>> loadConfigFile(const std::string &filename, Game &game)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::shared_ptr<Entity>> entities;

    while (std::getline(file, line)) 
    {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        
        if (type == "Window")
        {
            iss >> game.wWidth >> game.wHeight;
        }
        if(type == "Font")
        {
            iss >> game.font.name >> game.font.size >> game.font.r >> game.font.g >> game.font.b;
        }
        if (type == "Circle") {
            std::string name;
            float x, y, vx, vy;
            int r, g, b, radius;
            iss >> name >> x >> y >> vx >> vy >> r >> g >> b >> radius;

            auto circle = std::make_shared<CircleEntity>(name,
                sf::Vector2f(x, y),
                sf::Vector2f(vx, vy),
                sf::Color(r, g, b),
                radius);

            entities.push_back(circle);
        } else if (type == "Rectangle") {
            std::string name;
            float x, y, vx, vy, width, height;
            int r, g, b;
            iss >> name >> x >> y >> vx >> vy >> r >> g >> b >> width >> height;

            auto rectangle = std::make_shared<RectangleEntity>(name,
                sf::Vector2f(x, y),
                sf::Vector2f(vx, vy),
                sf::Color(r, g, b),
                sf::Vector2f(width, height));

            entities.push_back(rectangle);
        }
    }
    return entities;
}

