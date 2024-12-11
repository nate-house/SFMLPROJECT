#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath> // For calculating positions
#include <string>

using namespace std;

class Heap
{
private:
    struct Node
    {
        int value;
        sf::CircleShape shape; // Visual representation of the node (circle)
        sf::Text valueText;    // Text to display the value inside the node
        bool isInOperation;    // Flag to highlight nodes during operations (insert/remove)

        Node(int val, sf::Font &font)
            : value(val), shape(30), valueText(to_string(val), font, 20), isInOperation(false)
        {
            shape.setFillColor(sf::Color::Yellow);
            valueText.setFillColor(sf::Color::Black);
            valueText.setPosition(5, 5); // Initial text position
        }
    };

    vector<Node> heap; // Heap storage
    sf::Font font;     // Font for displaying values

    void heapifyUp(int index);         // Ensure heap property is maintained while adding a new node
    void heapifyDown(int index);       // Ensure heap property is maintained while removing the root
    void swap(int index1, int index2); // Swap two nodes in the heap

public:
    Heap();                                   // Constructor to initialize the heap
    void insert(int value);                   // Insert a new value into the heap
    void remove();                            // Remove the root node (maximum value)
    void visualize(sf::RenderWindow &window); // Visualize the heap as circles and lines
    void setupFont();                         // Load font for displaying node values

    int getSize() const; // Get the size of the heap
    Node *getRoot();     // Get the root of the heap (max value)
};

// Constructor to initialize the heap
Heap::Heap()
{
    setupFont();
}

// Load font for displaying node values
void Heap::setupFont()
{
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Insert a new value into the heap
void Heap::insert(int value)
{
    Node newNode(value, font);
    heap.push_back(newNode);
    int index = heap.size() - 1;

    // Ensure heap property is maintained by "bubbling up" the inserted node
    heapifyUp(index);
}

// "Bubble up" to maintain heap property
void Heap::heapifyUp(int index)
{
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;

        // If the current node is greater than its parent, swap them
        if (heap[index].value > heap[parentIndex].value)
        {
            swap(index, parentIndex);
            index = parentIndex;
        }
        else
        {
            break; // If heap property is satisfied, no need to continue
        }
    }
}

// Remove the root node (maximum value)
void Heap::remove()
{
    if (heap.size() == 0)
        return;

    // Swap the root with the last element
    swap(0, heap.size() - 1);
    heap.pop_back(); // Remove the last element (which is now the root)

    // Ensure heap property is maintained by "bubbling down" the new root
    heapifyDown(0);
}

// "Bubble down" to maintain heap property
void Heap::heapifyDown(int index)
{
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    // Check if the left child exists and is larger than the current node
    if (leftChild < heap.size() && heap[leftChild].value > heap[largest].value)
    {
        largest = leftChild;
    }

    // Check if the right child exists and is larger than the current node
    if (rightChild < heap.size() && heap[rightChild].value > heap[largest].value)
    {
        largest = rightChild;
    }

    // If the largest is not the current node, swap and continue bubbling down
    if (largest != index)
    {
        swap(index, largest);
        heapifyDown(largest);
    }
}

// Swap two nodes in the heap
void Heap::swap(int index1, int index2)
{
    std::swap(heap[index1], heap[index2]);
}

// Get the size of the heap
int Heap::getSize() const
{
    return heap.size();
}

// Get the root of the heap (max value)
Heap::Node *Heap::getRoot()
{
    return heap.empty() ? nullptr : &heap[0];
}

// Visualize the heap
void Heap::visualize(sf::RenderWindow &window)
{
    if (heap.empty())
        return;

    // Maximum number of levels in the heap
    int levels = static_cast<int>(log2(heap.size())) + 1;

    // Calculate horizontal offset based on window size and heap size
    int xOffset = window.getSize().x / (pow(2, levels - 1) + 1);
    int verticalSpacing = 120; // Adjust vertical spacing for better readability
    int initialYPos = 50; // Initial Y position for the top level (root)

    // Iterate through each node and calculate its position
    for (int i = 0; i < heap.size(); ++i)
    {
        // Calculate the level of the current node
        int level = static_cast<int>(log2(i + 1));

        // Calculate horizontal position (i % (1 << level)) ensures correct positioning in the current level
        int posX = (i % (1 << level)) * xOffset + xOffset / 2;
        int posY = initialYPos + level * verticalSpacing;

        // Set the position for the node's circle and the text
        heap[i].shape.setPosition(posX, posY);
        heap[i].valueText.setPosition(posX + 10, posY + 10); // Adjust text inside circle

        // Highlight the node during operations (insertion or removal)
        if (heap[i].isInOperation)
        {
            heap[i].shape.setFillColor(sf::Color::Red); // Highlighting in red during operations
        }
        else
        {
            heap[i].shape.setFillColor(sf::Color::Yellow); // Normal color
        }

        // Draw the node's circle and value
        window.draw(heap[i].shape);
        window.draw(heap[i].valueText);

        // Draw lines to the children
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < heap.size())
        {
            // Draw line from parent to left child
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(posX + 30, posY + 30); // Parent's position (center of circle)
            line[1].position = sf::Vector2f(heap[leftChild].shape.getPosition().x + 30,
                                            heap[leftChild].shape.getPosition().y + 30); // Child's position
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
            window.draw(line);
        }

        if (rightChild < heap.size())
        {
            // Draw line from parent to right child
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(posX + 30, posY + 30);
            line[1].position = sf::Vector2f(heap[rightChild].shape.getPosition().x + 30,
                                            heap[rightChild].shape.getPosition().y + 30);
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
            window.draw(line);
        }
    }
}
