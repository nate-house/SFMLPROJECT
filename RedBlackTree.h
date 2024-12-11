#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RedBlackTree
{
private:
    enum class Color
    {
        RED,
        BLACK
    };

    struct Node
    {
        int value;
        Color color;
        Node *left, *right, *parent;

        Node(int val)
            : value(val), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node *root;

    // Helper functions for balancing and rotating
    void rotateLeft(Node *&root, Node *&pt);
    void rotateRight(Node *&root, Node *&pt);
    void fixViolation(Node *&root, Node *&pt);
    void inorderHelper(Node *root, std::vector<int> &values);
    void visualizeNode(sf::RenderWindow &window, Node *node, int x, int y, int offset);
    void visualizeEdges(sf::RenderWindow &window, Node *node, int x, int y, int offset);

public:
    RedBlackTree();
    void insert(int value);
    void insertHelper(Node *&root, Node *&pt);
    void display(sf::RenderWindow &window);
    void inorderTraversal();

    // Utility functions
    Node *getRoot() { return root; }
};

// Constructor to initialize the Red-Black Tree
RedBlackTree::RedBlackTree() : root(nullptr) {}

void RedBlackTree::rotateLeft(Node *&root, Node *&pt)
{
    Node *ptRight = pt->right;
    pt->right = ptRight->left;

    if (ptRight->left != nullptr)
    {
        ptRight->left->parent = pt;
    }

    ptRight->parent = pt->parent;

    if (pt->parent == nullptr)
    {
        root = ptRight;
    }
    else if (pt == pt->parent->left)
    {
        pt->parent->left = ptRight;
    }
    else
    {
        pt->parent->right = ptRight;
    }

    ptRight->left = pt;
    pt->parent = ptRight;
}

void RedBlackTree::rotateRight(Node *&root, Node *&pt)
{
    Node *ptLeft = pt->left;
    pt->left = ptLeft->right;

    if (ptLeft->right != nullptr)
    {
        ptLeft->right->parent = pt;
    }

    ptLeft->parent = pt->parent;

    if (pt->parent == nullptr)
    {
        root = ptLeft;
    }
    else if (pt == pt->parent->right)
    {
        pt->parent->right = ptLeft;
    }
    else
    {
        pt->parent->left = ptLeft;
    }

    ptLeft->right = pt;
    pt->parent = ptLeft;
}

// Function to fix violations of Red-Black Tree properties
void RedBlackTree::fixViolation(Node *&root, Node *&pt)
{
    Node *parent_pt = nullptr;
    Node *grandparent_pt = nullptr;

    while (pt != root && pt->color == Color::RED && pt->parent->color == Color::RED)
    {
        parent_pt = pt->parent;
        grandparent_pt = pt->parent->parent;

        if (parent_pt == grandparent_pt->left)
        {
            Node *uncle = grandparent_pt->right;

            if (uncle != nullptr && uncle->color == Color::RED)
            {
                grandparent_pt->color = Color::RED;
                parent_pt->color = Color::BLACK;
                uncle->color = Color::BLACK;
                pt = grandparent_pt;
            }
            else
            {
                if (pt == parent_pt->right)
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateRight(root, grandparent_pt);
                swap(parent_pt->color, grandparent_pt->color);
                pt = parent_pt;
            }
        }
        else
        {
            Node *uncle = grandparent_pt->left;

            if (uncle != nullptr && uncle->color == Color::RED)
            {
                grandparent_pt->color = Color::RED;
                parent_pt->color = Color::BLACK;
                uncle->color = Color::BLACK;
                pt = grandparent_pt;
            }
            else
            {
                if (pt == parent_pt->left)
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateLeft(root, grandparent_pt);
                swap(parent_pt->color, grandparent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = Color::BLACK;
}

// Helper function to insert a new node in the Red-Black Tree
void RedBlackTree::insert(int value)
{
    Node *pt = new Node(value);
    insertHelper(root, pt);
    fixViolation(root, pt);
}

// Recursive function to insert a node into the Red-Black Tree
void RedBlackTree::insertHelper(Node *&root, Node *&pt)
{
    if (root == nullptr)
    {
        root = pt;
        return;
    }

    if (pt->value < root->value)
    {
        if (root->left == nullptr)
        {
            root->left = pt;
            pt->parent = root;
        }
        else
        {
            insertHelper(root->left, pt);
        }
    }
    else
    {
        if (root->right == nullptr)
        {
            root->right = pt;
            pt->parent = root;
        }
        else
        {
            insertHelper(root->right, pt);
        }
    }
}

// In-order traversal to get values for visualization
void RedBlackTree::inorderTraversal()
{
    std::vector<int> values;
    inorderHelper(root, values);
    for (int val : values)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void RedBlackTree::inorderHelper(Node *root, std::vector<int> &values)
{
    if (root == nullptr)
    {
        return;
    }
    inorderHelper(root->left, values);
    values.push_back(root->value);
    inorderHelper(root->right, values);
}

// Function to visualize the tree structure using SFML
void RedBlackTree::visualizeNode(sf::RenderWindow &window, Node *node, int x, int y, int offset)
{
    if (node == nullptr)
        return;

    sf::CircleShape shape(20);
    shape.setFillColor(node->color == Color::RED ? sf::Color::Red : sf::Color::Black);
    shape.setPosition(x, y);
    window.draw(shape);

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        exit(EXIT_FAILURE);
    }

    sf::Text text(std::to_string(node->value), font, 20);
    text.setFillColor(sf::Color::White);
    text.setPosition(x + 5, y + 5);
    window.draw(text);

    if (node->left != nullptr)
    {
        visualizeEdges(window, node, x, y, offset);
        visualizeNode(window, node->left, x - offset, y + 60, offset / 2);
    }
    if (node->right != nullptr)
    {
        visualizeEdges(window, node, x, y, offset);
        visualizeNode(window, node->right, x + offset, y + 60, offset / 2);
    }
}

// Function to draw edges between parent and child nodes
void RedBlackTree::visualizeEdges(sf::RenderWindow &window, Node *node, int x, int y, int offset)
{
    if (node->left != nullptr)
    {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x + 20, y + 20);
        line[1].position = sf::Vector2f(x - offset + 20, y + 60 + 20);
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;
        window.draw(line);
    }
    if (node->right != nullptr)
    {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x + 20, y + 20);
        line[1].position = sf::Vector2f(x + offset + 20, y + 60 + 20);
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;
        window.draw(line);
    }
}

// Function to display the tree in a window
void RedBlackTree::display(sf::RenderWindow &window)
{
    if (root == nullptr)
        return;
    visualizeNode(window, root, window.getSize().x / 2, 50, window.getSize().x / 4);
}

#endif // REDBLACKTREE_H
