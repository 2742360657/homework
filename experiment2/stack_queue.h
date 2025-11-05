#include<iostream>

class MyStack;

class listNode{
    friend class MyStack;
private:
    listNode* next;
    int data;
public:
    listNode();
    listNode(int nodeData, listNode* succ = NULL);
};

class MyStack
{
private:
    listNode* topNode;
    int stackSize;

public:
    MyStack();
    ~MyStack();

    bool push(const int&);
    bool pop(int&);
    bool getTop(int&);
    void printStack();
};

class MyQueue
{
private:
    int* queue;
    int capacity;
    int front;
    int rear;

public:
    MyQueue(const int&);
    ~MyQueue();

    bool enQueue(const int&);
    bool deQueue(int&);
    bool getFront(int&);
    void printQueue();

    bool isFull();
};

bool postfixExpression(const std::string&, std::string&);
bool expressionVal(const std::string&, int&);
void yanghui(const int&);



