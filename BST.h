#include <SFML/Graphics.hpp>
#include <iostream>

class BST
{
public:
    struct Node
    {
        int value;
        Node *left;
        Node *right;
        sf::CircleShape shape; // Visual representation of the node

        Node(int val) : value(val), left(nullptr), right(nullptr), shape(20)
        {
            shape.setFillColor(sf::Color::Green); // Color the node green
        }
    };

private:
    Node *root;    // Root of the tree
    sf::Font font; // Font for node labels

    // Private helper methods for visualization and insertion
    void visualizeRecursive(Node *node, sf::RenderWindow &window, float x, float y, float xOffset);
    void insertRecursive(Node *&node, int value);
    void deleteTree(Node *node);

public:
    BST();  // Default constructor
    ~BST(); // Destructor

    void insert(int value);                   // Insert a new node with a value
    void visualize(sf::RenderWindow &window); // Visualize the tree
    void setupFont();                         // Setup font for node labels
    Node *getRoot() const;                    // Get the root node of the tree
};

// ------------------------------------------------------
// Implementation of BST methods

BST::BST() : root(nullptr)
{
    setupFont(); // Initialize font
}

BST::~BST()
{
    deleteTree(root); // Clean up tree memory
}

void BST::setupFont()
{
    if (!font.loadFromFile("Arial.ttf"))
    { // Ensure the correct path to the font
        std::cerr << "Error loading font!" << std::endl;
        exit(EXIT_FAILURE); // Exit if font can't be loaded
    }
}

void BST::insert(int value)
{
    insertRecursive(root, value); // Insert the value into the tree
}

void BST::insertRecursive(Node *&node, int value)
{
    if (!node)
    {
        node = new Node(value); // Create a new node if the current node is null
    }
    else if (value < node->value)
    {
        insertRecursive(node->left, value); // Insert to the left
    }
    else
    {
        insertRecursive(node->right, value); // Insert to the right
    }
}

void BST::visualize(sf::RenderWindow &window)
{
    if (root)
    {
        visualizeRecursive(root, window, 400.f, 50.f, 150.f); // Start visualizing from root
    }
}

void BST::visualizeRecursive(Node *node, sf::RenderWindow &window, float x, float y, float xOffset)
{
    if (!node)
        return;

    node->shape.setPosition(x, y); // Set the position of the node
    window.draw(node->shape);      // Draw the node

    // Create and display the value of the node at the center
    sf::Text valueText(std::to_string(node->value), font, 20);
    valueText.setFillColor(sf::Color::White);
    valueText.setPosition(x - 10, y - 10); // Position the text in the center of the node
    window.draw(valueText);

    // Visualize left child if it exists
    if (node->left)
    {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = node->shape.getPosition();
        line[1].position = sf::Vector2f(x - xOffset, y + 100.f);
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;
        window.draw(line);
        visualizeRecursive(node->left, window, x - xOffset, y + 100.f, xOffset / 2.f); // Recursively draw left child
    }

    // Visualize right child if it exists
    if (node->right)
    {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = node->shape.getPosition();
        line[1].position = sf::Vector2f(x + xOffset, y + 100.f);
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;
        window.draw(line);
        visualizeRecursive(node->right, window, x + xOffset, y + 100.f, xOffset / 2.f); // Recursively draw right child
    }
}

void BST::deleteTree(Node *node)
{
    if (node)
    {
        deleteTree(node->left);  // Recursively delete left subtree
        deleteTree(node->right); // Recursively delete right subtree
        delete node;             // Delete the current node
    }
}

BST::Node *BST::getRoot() const
{
    return root; // Return the root node
}
