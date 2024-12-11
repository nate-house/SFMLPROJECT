#ifndef STACK_H
#define STACK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Stack
{
private:
    std::vector<int> stack; // Using vector to represent the stack

public:
    // Pushes an element onto the stack
    void push(int value)
    {
        stack.push_back(value);
    }

    // Pops an element from the stack
    void pop()
    {
        if (!stack.empty())
        {
            stack.pop_back();
        }
    }

    // Visualizes the stack in the window
    void visualize(sf::RenderWindow &window)
    {
        for (int i = 0; i < stack.size(); i++)
        {
            sf::RectangleShape rect(sf::Vector2f(50, 50));
            rect.setPosition(100.0f, 100.0f + i * 60);
            rect.setFillColor(sf::Color::Red);
            window.draw(rect);

            // Display the number inside the rectangle
            sf::Font font;
            if (!font.loadFromFile("Arial.ttf"))
            {
                std::cerr << "Error loading font!" << std::endl;
            }
            sf::Text text(std::to_string(stack[i]), font, 20);
            text.setPosition(115.0f, 110.0f + i * 60);
            text.setFillColor(sf::Color::White);
            window.draw(text);
        }
    }

    // Checks if the stack is empty
    bool isEmpty() const
    {
        return stack.empty();
    }

    // Returns the top element of the stack
    int top() const
    {
        return stack.empty() ? -1 : stack.back();
    }
};

#endif // STACK_H
