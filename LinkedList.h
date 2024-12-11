#include <SFML/Graphics.hpp>
#include <iostream>

class LinkedList
{
public:
    struct Node
    {
        int value;
        Node *next;
        sf::CircleShape shape; // Visual representation of the node

        Node(int val) : value(val), next(nullptr), shape(20)
        {
            shape.setFillColor(sf::Color::Blue);
        }
    };

private:
    Node *head;
    sf::Font font;

public:
    LinkedList();
    ~LinkedList();

    void insert(int value);                   // Insert a new node with a value
    void visualize(sf::RenderWindow &window); // Visualize the list

    void setupFont();
    Node *getHead() const;
};

LinkedList::LinkedList() : head(nullptr)
{
    setupFont();
}

LinkedList::~LinkedList()
{
    Node *current = head;
    while (current)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::setupFont()
{
    if (!font.loadFromFile("Arial.ttf"))
    { // Make sure the path to your font is correct
        std::cerr << "Error loading font!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void LinkedList::insert(int value)
{
    Node *newNode = new Node(value);

    // Position the node horizontally, with a 100px gap between nodes
    if (!head)
    {
        newNode->shape.setPosition(100, 300); // First node at (100, 300) - fixed Y for horizontal alignment
        head = newNode;
    }
    else
    {
        Node *temp = head;
        int xOffset = 100; // Horizontal offset between nodes
        // Traverse to the last node
        while (temp->next)
        {
            temp = temp->next;
            xOffset += 100; // Increase offset for each node
        }
        newNode->shape.setPosition(xOffset, 300); // Set new node's position horizontally
        temp->next = newNode;                     // Attach the new node to the list
    }
}

void LinkedList::visualize(sf::RenderWindow &window)
{
    if (!head)
        return;

    Node *current = head;
    sf::Text valueText("", font, 20);
    valueText.setFillColor(sf::Color::White);

    while (current)
    {
        window.draw(current->shape); // Draw the node

        // Display the value inside the circle
        valueText.setString(std::to_string(current->value));
        valueText.setPosition(current->shape.getPosition().x + 5, current->shape.getPosition().y + 5);
        window.draw(valueText);

        // Draw the link to the next node (if it exists)
        if (current->next)
        {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = current->shape.getPosition() + sf::Vector2f(20, 0);        // Start at the edge of the current node
            line[1].position = current->next->shape.getPosition() + sf::Vector2f(-20, 0); // End at the edge of the next node
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;

            // Optionally, you can add more visual styling like line thickness or transparency
            window.draw(line);
        }

        current = current->next;
    }
}

LinkedList::Node *LinkedList::getHead() const
{
    return head;
}
