#ifndef QUEUE_H
#define QUEUE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Queue
{
private:
    std::vector<int> queue; // Using vector to represent the queue

public:
    // Enqueues an element to the back of the queue
    void enqueue(int value)
    {
        queue.push_back(value);
    }

    // Dequeues the front element of the queue
    void dequeue()
    {
        if (!queue.empty())
        {
            queue.erase(queue.begin());
        }
    }

    // Visualizes the queue (draws rectangles with numbers)
    void visualize(sf::RenderWindow &window)
    {
        for (int i = 0; i < queue.size(); i++)
        {
            sf::RectangleShape rect(sf::Vector2f(50, 50));
            rect.setPosition(100.0f + i * 60, 100.0f); // Queue is horizontal
            rect.setFillColor(sf::Color::Green);
            window.draw(rect);

            // Display the number inside the rectangle
            sf::Font font;
            if (!font.loadFromFile("Arial.ttf"))
            {
                std::cerr << "Error loading font!" << std::endl;
            }
            sf::Text text(std::to_string(queue[i]), font, 20);
            text.setPosition(115.0f + i * 60, 110.0f);
            text.setFillColor(sf::Color::White);
            window.draw(text);
        }
    }

    // Checks if the queue is empty
    bool isEmpty() const
    {
        return queue.empty();
    }

    // Returns the front element of the queue
    int front() const
    {
        return queue.empty() ? -1 : queue.front();
    }

    // Returns the back element of the queue
    int back() const
    {
        return queue.empty() ? -1 : queue.back();
    }
};

#endif // QUEUE_H
