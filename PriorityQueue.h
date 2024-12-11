#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

class PriorityQueue
{
private:
    std::vector<int> pq; // Using a vector to represent the heap-based priority queue
    sf::Font font;       // Font for drawing numbers

    // Helper function to maintain the max-heap property by bubbling up
    void bubbleUp(int index)
    {
        while (index > 0)
        {
            int parentIndex = (index - 1) / 2;
            if (pq[parentIndex] < pq[index])
            {
                std::swap(pq[parentIndex], pq[index]);
                index = parentIndex;
            }
            else
            {
                break;
            }
        }
    }

    // Helper function to maintain the max-heap property by bubbling down
    void bubbleDown(int index)
    {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int largest = index;

        if (leftChildIndex < pq.size() && pq[leftChildIndex] > pq[largest])
        {
            largest = leftChildIndex;
        }

        if (rightChildIndex < pq.size() && pq[rightChildIndex] > pq[largest])
        {
            largest = rightChildIndex;
        }

        if (largest != index)
        {
            std::swap(pq[index], pq[largest]);
            bubbleDown(largest); // Recursively bubble down the swapped element
        }
    }

public:
    // Constructor: Load font once
    PriorityQueue()
    {
        if (!font.loadFromFile("Arial.ttf"))
        {
            std::cerr << "Error loading font!" << std::endl;
        }
    }

    // Enqueues an element to the priority queue (max-heap)
    void enqueue(int value)
    {
        pq.push_back(value);     // Add the new element at the end
        bubbleUp(pq.size() - 1); // Bubble it up to maintain heap property
    }

    // Dequeues the highest priority element (root of the max-heap)
    void dequeue()
    {
        if (!pq.empty())
        {
            pq[0] = pq.back(); // Replace the root with the last element
            pq.pop_back();     // Remove the last element
            bubbleDown(0);     // Bubble the new root down to restore heap property
        }
    }

    // Visualizes the priority queue (draws circles with numbers)
    void visualize(sf::RenderWindow &window)
    {
        if (pq.empty())
            return;

        // Constants to handle position
        int xStart = window.getSize().x / 2; // Center horizontally
        int yStart = 40;                     // Starting y-position at the top
        int nodeSpacing = 100;               // Horizontal spacing between nodes
        int verticalSpacing = 150;           // Vertical spacing between levels

        int level = 0;
        int nodesOnLevel = 1; // Start with 1 node at the root level

        // Loop through all elements in the priority queue (heap)
        for (int i = 0; i < pq.size(); ++i)
        {
            // Calculate the position of the current node
            int xPos = xStart - (nodeSpacing * (nodesOnLevel - 1)) / 2 + (i % nodesOnLevel) * nodeSpacing;
            int yPos = yStart + level * verticalSpacing;

            // Draw circle for the current node
            sf::CircleShape circle(30);               // Radius of 30 for each circle
            circle.setPosition(xPos - 30, yPos - 30); // Adjust so the circle is centered
            circle.setFillColor(sf::Color::Magenta);
            window.draw(circle);

            // Draw the text inside the circle
            sf::Text text(std::to_string(pq[i]), font, 24);
            text.setPosition(xPos - 12, yPos - 12); // Center text inside the circle
            text.setFillColor(sf::Color::White);
            window.draw(text);

            // Draw lines connecting the parent to the current node
            if (i > 0) // Skip if it's the root node
            {
                int parentIndex = (i - 1) / 2;
                int parentX = xStart - (nodeSpacing * (nodesOnLevel - 1)) / 2 + (parentIndex % nodesOnLevel) * nodeSpacing;
                int parentY = yStart + (parentIndex / nodesOnLevel) * verticalSpacing;

                sf::Vertex line[] =
                    {
                        sf::Vertex(sf::Vector2f(xPos, yPos)),
                        sf::Vertex(sf::Vector2f(parentX, parentY))};
                line[0].color = sf::Color::White;
                line[1].color = sf::Color::White;
                window.draw(line, 2, sf::Lines);
            }

            // Update for the next node on the same level
            if ((i + 1) % nodesOnLevel == 0)
            {
                level++;
                nodesOnLevel *= 2; // Double the number of nodes on the next level
            }
        }
    }

    // Checks if the priority queue is empty
    bool isEmpty() const
    {
        return pq.empty();
    }

    // Returns the highest priority element (root of the heap)
    int front() const
    {
        return pq.empty() ? -1 : pq[0];
    }

    // Returns the lowest priority element (last element in the heap)
    int back() const
    {
        return pq.empty() ? -1 : pq.back();
    }
};

#endif // PRIORITY_QUEUE_H
