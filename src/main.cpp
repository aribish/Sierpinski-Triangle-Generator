#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <vector>
#include <iostream>

#define SFML_STATIC

sf::RenderWindow window;
sf::Event event;

sf::Font gillSans;
sf::Text guideText;

int genCount = -1;
int genSideLength = -1;
std::vector<sf::Vector2f> generations;
bool onStartScreen = true;

sf::Color topColor = sf::Color::Black;
sf::Color leftColor = sf::Color::Black;
sf::Color rightColor = sf::Color::Black;

void drawTriangle(const float x, const float y, const float sideLength, const sf::Color fill)
{
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(sideLength / 2, 0)); // top
    triangle.setPoint(1, sf::Vector2f(0, sideLength)); // left
    triangle.setPoint(2, sf::Vector2f(sideLength, sideLength)); // right
    triangle.setFillColor(fill);

    triangle.setPosition(x, y);

    generations.push_back(triangle.getPosition());
    window.draw(triangle);
}

float pow();

void newGeneration()
{
    int temp = 0;
    window.clear(sf::Color::White);

if (genCount == -1 && genSideLength == -1)
{
    onStartScreen = false;
    genCount = 1;
    genSideLength = 960;

    drawTriangle(0, 0, genSideLength, topColor);
}
    else
    {
        genSideLength /= 2;

        for(int i = 0; i < genCount; i++)
        {
            drawTriangle(generations[i].x + (genSideLength / 2), generations[i].y, genSideLength, topColor); // top
            drawTriangle(generations[i].x, generations[i].y + genSideLength, genSideLength, leftColor); // left
            drawTriangle(generations[i].x + genSideLength, generations[i].y + genSideLength, genSideLength, rightColor); // right

            temp += 3;
        }

        for (int i = 0; i < genCount; i++)
        {
            generations.erase(generations.begin());
        }

        genCount = temp;
    }

    window.display();
}

void setupGuideText()
{
    std::cout << "font file load status: " << gillSans.loadFromFile("gillsans.ttf") << '\n';
    guideText = sf::Text("          Press [SPACE] to watch the fractal grow!\nPress a number key right now to change fractal color!\n                           Press [R] to reset!", gillSans);
    guideText.setFillColor(sf::Color::Black);
    guideText.setPosition(sf::Vector2f(144, 320));

    window.draw(guideText);
}

void resetProgram()
{
    onStartScreen = true;
    genCount = -1;
    genSideLength = -1;
    generations.clear();

    window.clear(sf::Color::White);
    setupGuideText();
    window.display();
}

void init()
{
    window.create(sf::VideoMode(960, 960), "The Bad Sierpinksi Triangle Generator | by Air Boigus", sf::Style::Default);

    window.clear(sf::Color::White);
    setupGuideText();
    window.display();
}

int main()
{
    init();

    while(window.isOpen())
    {
        while(window.pollEvent(event))
            {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                resetProgram();
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    newGeneration();
                }
                else if (event.key.code == sf::Keyboard::R)
                {
                    resetProgram();
                }
                else if (onStartScreen)
                {
                    if (event.key.code == sf::Keyboard::Num1)
                    {
                        topColor = sf::Color::Black;
                        leftColor = sf::Color::Black;
                        rightColor = sf::Color::Black;
                    }
                    else if (event.key.code == sf::Keyboard::Num2)
                    {
                        topColor = sf::Color::Red;
                        leftColor = sf::Color::Green;
                        rightColor = sf::Color::Blue;
                    }
                    else if (event.key.code == sf::Keyboard::Num3)
                    {
                        topColor = sf::Color::Cyan;
                        leftColor = sf::Color::Yellow;
                        rightColor = sf::Color::Magenta;
                    }
                    else if (event.key.code == sf::Keyboard::Num4)
                    {
                        topColor = sf::Color::Black;
                        leftColor = sf::Color::Red;
                        rightColor = sf::Color::Green;
                    }
                    else if (event.key.code == sf::Keyboard::Num5)
                    {
                        topColor = sf::Color::Red;
                        leftColor = sf::Color(255, 175, 0);
                        rightColor = sf::Color::Yellow;
                    }
                    else if (event.key.code == sf::Keyboard::Num6)
                    {
                        topColor = sf::Color::Red;
                        leftColor = sf::Color::Blue;
                        rightColor = sf::Color::Yellow;
                    }
                    else if (event.key.code == sf::Keyboard::Num7)
                    {
                        topColor = sf::Color::Blue;
                        leftColor = sf::Color(100, 100, 255);
                        rightColor = sf::Color::Cyan;
                    }
                    else if (event.key.code == sf::Keyboard::Num8)
                    {
                        topColor = sf::Color::Magenta;
                        leftColor = sf::Color(150, 50, 175);
                        rightColor = sf::Color(150, 0, 255);
                    }
                    else if (event.key.code == sf::Keyboard::Num9)
                    {
                        topColor = sf::Color::Black;
                        leftColor = sf::Color(50, 50, 50);
                        rightColor = sf::Color(100, 100, 100);
                    }
                    else if (event.key.code == sf::Keyboard::Num0)
                    {
                        topColor = sf::Color(65, 165, 65);
                        leftColor = sf::Color(220, 155, 25);
                        rightColor = sf::Color(100, 100, 255);
                    }
                }
            }
        }
    }
}
