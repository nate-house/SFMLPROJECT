#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "LinkedList.h"
#include "BST.h"
#include "Heap.h"          // Combined Heap class
#include "RedBlackTree.h"  // Include Red-Black Tree header
#include "Stack.h"         // Include Stack header
#include "Queue.h"         // Include Queue header
#include "PriorityQueue.h" // Include PriorityQueue header

using namespace std;

enum class AppState
{
    MainMenu,
    LinkedList,
    BinarySearchTree,
    Heap,
    RedBlackTree,
    Stack,         // Added Stack to the enum
    Queue,         // Added Queue to the enum
    PriorityQueue, // Added PriorityQueue to the enum
    Exit
};

class Menu
{
private:
    vector<sf::Text> menuItems;
    sf::Font font;
    int selectedItemIndex;
    AppState currentState;

    LinkedList linkedList; // Instance of the LinkedList class
    BST bst;               // Instance of the BinarySearchTree class
    Heap heap;             // Instance of the Heap class
    RedBlackTree rbTree;   // Instance of the Red-Black Tree class
    Stack stack;           // Instance of the Stack class
    Queue queue;           // Instance of the Queue class
    PriorityQueue pq;      // Instance of the PriorityQueue class

public:
    Menu();
    void handleInput(sf::Event::KeyEvent key);
    void updateMenu();
    void draw(sf::RenderWindow &window);
    void displayLinkedList(sf::RenderWindow &window);
    void displayBST(sf::RenderWindow &window);
    void displayHeap(sf::RenderWindow &window);
    void displayRedBlackTree(sf::RenderWindow &window);
    void displayStack(sf::RenderWindow &window);         // Added Stack display function
    void displayQueue(sf::RenderWindow &window);         // Added Queue display function
    void displayPriorityQueue(sf::RenderWindow &window); // Added PriorityQueue display function
    void addNode(int value);
    AppState getCurrentState() const;
    void initializeDataStructures();
};

Menu::Menu() : selectedItemIndex(0), currentState(AppState::MainMenu)
{
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        exit(EXIT_FAILURE);
    }

    vector<string> menuTexts = {
        "Linked List", "Binary Search Tree", "Heap", "Red-Black Tree", "Stack", "Queue", "Priority Queue", "Exit"};

    for (int i = 0; i < menuTexts.size(); ++i)
    {
        sf::Text item(menuTexts[i], font, 30);
        item.setPosition(100, 100 + i * 50);
        menuItems.push_back(item);
    }

    // Initialize all data structures with predefined nodes
    initializeDataStructures();
}

void Menu::handleInput(sf::Event::KeyEvent key)
{
    if (key.code == sf::Keyboard::Up)
    {
        if (selectedItemIndex > 0)
            selectedItemIndex--;
    }
    else if (key.code == sf::Keyboard::Down)
    {
        if (selectedItemIndex < menuItems.size() - 1)
            selectedItemIndex++;
    }
    else if (key.code == sf::Keyboard::Return)
    {
        switch (selectedItemIndex)
        {
        case 0:
            currentState = AppState::LinkedList;
            break;
        case 1:
            currentState = AppState::BinarySearchTree;
            break;
        case 2:
            currentState = AppState::Heap;
            break;
        case 3:
            currentState = AppState::RedBlackTree;
            break;
        case 4:
            currentState = AppState::Stack; // Switch to Stack state
            break;
        case 5:
            currentState = AppState::Queue; // Switch to Queue state
            break;
        case 6:
            currentState = AppState::PriorityQueue; // Switch to PriorityQueue state
            break;
        case 7:
            currentState = AppState::Exit;
            break;
        }
    }
}

void Menu::updateMenu()
{
    for (int i = 0; i < menuItems.size(); ++i)
    {
        if (i == selectedItemIndex)
        {
            menuItems[i].setFillColor(sf::Color::Red);
        }
        else
        {
            menuItems[i].setFillColor(sf::Color::White);
        }
    }
}

void Menu::draw(sf::RenderWindow &window)
{
    for (auto &item : menuItems)
    {
        window.draw(item);
    }
}

void Menu::displayLinkedList(sf::RenderWindow &window)
{
    linkedList.visualize(window);
}

void Menu::displayBST(sf::RenderWindow &window)
{
    bst.visualize(window);
}

void Menu::displayHeap(sf::RenderWindow &window)
{
    heap.visualize(window);
}

void Menu::displayRedBlackTree(sf::RenderWindow &window)
{
    rbTree.display(window);
}

void Menu::displayStack(sf::RenderWindow &window)
{
    stack.visualize(window); // Display the stack visualization
}

void Menu::displayQueue(sf::RenderWindow &window)
{
    queue.visualize(window); // Display the queue visualization
}

void Menu::displayPriorityQueue(sf::RenderWindow &window)
{
    pq.visualize(window); // Display the priority queue visualization
}

void Menu::addNode(int value)
{
    linkedList.insert(value);
    bst.insert(value);    // Add to the BST as well
    heap.insert(value);   // Add to the Heap as well
    rbTree.insert(value); // Add to the Red-Black Tree as well
    stack.push(value);    // Add to the stack as well
    queue.enqueue(value); // Add to the queue as well
    pq.enqueue(value);    // Add to the priority queue as well
}

AppState Menu::getCurrentState() const
{
    return currentState;
}

void Menu::initializeDataStructures()
{
    linkedList.insert(10);
    linkedList.insert(20);
    linkedList.insert(30);
    linkedList.insert(40);
    linkedList.insert(50);

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);

    heap.insert(50);
    heap.insert(30);
    heap.insert(70);
    heap.insert(20);
    heap.insert(40);

    rbTree.insert(50);
    rbTree.insert(30);
    rbTree.insert(70);
    rbTree.insert(20);
    rbTree.insert(40);

    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);

    pq.enqueue(10);
    pq.enqueue(20);
    pq.enqueue(30);
    pq.enqueue(40);
    pq.enqueue(50);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Data Structures Menu");
    Menu menu;

    sf::Event event;
    bool inputReceived = false;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                menu.handleInput(event.key);
        }

        window.clear(sf::Color::Black);

        switch (menu.getCurrentState())
        {
        case AppState::MainMenu:
            menu.updateMenu();
            menu.draw(window);
            break;
        case AppState::LinkedList:
            menu.displayLinkedList(window);
            break;
        case AppState::BinarySearchTree:
            menu.displayBST(window);
            break;
        case AppState::Heap:
            menu.displayHeap(window);
            break;
        case AppState::RedBlackTree:
            menu.displayRedBlackTree(window);
            break;
        case AppState::Stack:
            menu.displayStack(window); // Display Stack
            break;
        case AppState::Queue:
            menu.displayQueue(window); // Display Queue
            break;
        case AppState::PriorityQueue:
            menu.displayPriorityQueue(window); // Display PriorityQueue
            break;
        case AppState::Exit:
            window.close();
            break;
        }

        window.display();
    }

    return 0;
}
