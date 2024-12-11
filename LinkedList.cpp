#include "LinkedList.h"

LinkedList::Node::Node(int val) : value(val), next(nullptr), shape(30) // Shape size: 30px
{
    shape.setFillColor(sf::Color::Green); // Set the circle's fill color to green
}

LinkedList::LinkedList() : head(nullptr)
{
    setupFont();
}

LinkedList::~LinkedList()
{
    Node *current = head;
    while (current)
    {
        Node *next = current->next; // Save the next node
        delete current;             // Delete the current node
        current = next;             // Move to the next node
    }
}

void LinkedList::setupFont()
{
    if (!font.loadFromFile("Arial.ttf"))
    { // Ensure the font file exists and is loaded
        std::cerr << "Error loading font!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void LinkedList::insert(int value)
{
    Node *newNode = new Node(value);
    newNode->shape.setPosition(100, 100 + (head ? 100 * (rand() % 5) : 0)); // Random Y-offset to prevent overlap

    if (!head)
    {
        head = newNode; // First node inserted, set head to point to it
    }
    else
    {
        Node *temp = head;
        while (temp->next) // Traverse to the end of the list
        {
            temp = temp->next;
        }
        temp->next = newNode; // Link the new node at the end
    }
}

void LinkedList::visualize(sf::RenderWindow &window)
{
    if (!head) // If the list is empty, do nothing
        return;

    Node *current = head;                     // Start from the head (first node)
    sf::Text valueText("", font, 20);         // Text for displaying node value
    valueText.setFillColor(sf::Color::White); // Set text color to white

    while (current)
    {
        window.draw(current->shape); // Draw the node (circle)

        // Display the node's value inside the circle
        valueText.setString(std::to_string(current->value)); // Convert value to string
        valueText.setPosition(current->shape.getPosition().x + 5, current->shape.getPosition().y + 5);
        window.draw(valueText);

        // Draw a line connecting the nodes if there is a next node
        if (current->next)
        {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = current->shape.getPosition();       // Current node position
            line[1].position = current->next->shape.getPosition(); // Next node position
            line[0].color = sf::Color::White;                      // Set line color to white
            line[1].color = sf::Color::White;
            window.draw(line); // Draw the line between nodes
        }

        current = current->next; // Move to the next node in the list
    }
}

LinkedList::Node *LinkedList::getHead() const
{
    return head;
}
