#include "stack_queue.h"
#include <iostream>

listNode::listNode()
    : next(nullptr), data(0) {}

listNode::listNode(int nodeData, listNode *succ)
    // 如果没有显式传入 succ 参数，就自动把 succ 的值设为 nullptr，如果传入了就使用提供的值,=NULL在声明中写一遍就够了，这里不必写
    : next(succ), data(nodeData)
{
}

MyStack::MyStack()
    : topNode(nullptr), stackSize(0) {}
MyStack::~MyStack()
{
    while (topNode)
    {
        listNode *n = topNode;
        topNode = topNode->next;
        delete n;
    }
    stackSize = 0;
}
bool MyStack::push(const int &a)
{
    try
    {
        listNode *xin = new listNode(a, topNode); // new 执行失败相当于一个 throw
        topNode = xin;
        stackSize++;
        return true;
    }
    catch (std::bad_alloc &) // 出现 throw 会直接跳转到对应的 catch
    {
        return false;
    }
}
bool MyStack::pop(int &a)
{
    if (topNode == nullptr)
    {
        return false;
    }
    listNode *temp = topNode;
    topNode = topNode->next;
    stackSize--;
    a = temp->data;
    delete temp;
    return true;
}
bool MyStack::getTop(int &a)
{
    if (topNode == nullptr)
    {
        return 0;
    }
    a = topNode->data;
    return 1;
}
void MyStack::printStack()
{
    listNode *p = topNode;

    while (p != NULL)
    {
        if (p->next == NULL)
            std::cout << p->data << std::endl;
        else
            std::cout << p->data << ",";

        p = p->next;
    }
}

MyQueue::MyQueue(const int &a)
{
    capacity = (a > 0) ? a + 1: 2; // 多留一格
    queue = new int[capacity];
    front = 0;
    rear = 0;
}
MyQueue::~MyQueue()
{
    delete[] queue;
    queue = nullptr;
    capacity = front = rear = 0;
}
bool MyQueue::enQueue(const int &val)
{
    if (isFull())
    {
        std::cout << "队列已满\n";
        return false;
    }
    queue[rear] = val;
    rear = (rear + 1) % capacity;
    return true;
}
bool MyQueue::deQueue(int &val)
{
    if (front == rear)
    {
        std::cout << "队列空\n";
        return false;
    }
    val = queue[front];
    front = (front + 1) % capacity;
    return true;
}
bool MyQueue::getFront(int &val)
{
    if (front == rear)
    {
        std::cout << "队列空\n";
        return false;
    }
    val = queue[front];
    return true;
}
bool MyQueue::isFull()
{
    return ((rear + 1) % capacity == front);
}
void MyQueue::printQueue()
{
    if (front == rear)
    {
        std::cout << "[空队列]" << std::endl;
        return;
    }
    int i = front;
    while (i != rear)
    {
        std::cout << queue[i];
        i = (i + 1) % capacity;
        if (i != rear)
            std::cout << ",";
    }
    std::cout << std::endl;
}

bool postfixExpression(const std::string &infix, std::string &postfix)
// 中缀表达式转后缀表达式,转化成功返回true, 后缀表达式放在result中,表达式错误返回false, 错误字符串Expression is wrong!放在result中
{
    MyStack opStack;
    postfix.clear();

    for (size_t i = 0; i < infix.size(); ++i)
    {
        char c = infix[i];
        if (c == ' ')
            continue;

        // 若是数字，直接加入输出
        if (isdigit(c))
        {
            postfix += c;
            // 如果下一个不是数字，说明是一个完整的操作数
            if (i + 1 == infix.size() || !isdigit(infix[i + 1]))
                postfix += ' ';
        }
        else if (c == '(')
        {
            opStack.push(c);
        }
        else if (c == ')')
        {
            int top;
            while (opStack.getTop(top) && top != '(')
            {
                opStack.pop(top);
                postfix += static_cast<char>(top);
                postfix += ' ';
            }
            if (!opStack.pop(top)) // 弹出左括号
            {
                postfix = "Expression is wrong!";
                return false; // 括号不匹配
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            int top;
            while (opStack.getTop(top) && ((c == '+' || c == '-') ? (top == '+' || top == '-' || top == '*' || top == '/') : (top == '*' || top == '/')))
            {
                opStack.pop(top);
                postfix += static_cast<char>(top);
                postfix += ' ';
            }
            opStack.push(c);
        }
        else
        {
            postfix = "Expression is wrong!";
            return false; // 非法字符
        }
    }

    int top;
    while (opStack.pop(top))
    {
        if (top == '(')
        {
            postfix = "Expression is wrong!";
            return false; // 括号不匹配
        }
        postfix += static_cast<char>(top);
        postfix += ' ';
    }
    return true;
}

bool expressionVal(const std::string &postfix, int &result)
// 表达式求值,表达式正确成功计算返回true,结果放在result中,表达式错误计算不能完成返回false, result中放0
{
    MyStack valStack;
    for (size_t i = 0; i < postfix.size(); ++i)
    {
        char c = postfix[i];
        if (c == ' ')
            continue;

        if (isdigit(c))
        {
            int num = 0;
            while (i < postfix.size() && isdigit(postfix[i]))
            {
                num = num * 10 + (postfix[i] - '0');
                ++i;
            }
            valStack.push(num);
            --i;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            int b, a;
            if (!valStack.pop(b) || !valStack.pop(a))
            {
                result = 0;
                return false;
            }
            int res = 0;
            switch (c)
            {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
                break;
            case '/':
                if (b == 0)
                    return false;
                res = a / b;
                break;
            }
            valStack.push(res);
        }
        else
        {
            result = 0;
            return false;
        }
    }

    if (!valStack.pop(result) || valStack.pop(result))
    {
        result = 0;
        return false;
    } // 结果不唯一或表达式错误
    return true;
}

void yanghui(const int &n)
{
    if(n<=0)
    {
        return;
    }
    else
    {
        MyStack y,z;
        int temp[2]={0,0};
        int x=n-1;
        y.push(1);
        y.push(1);
        y.printStack();
        while(x--)
        {
            int t;
            while(y.pop(t))
            {
                temp[0]=temp[1];
                temp[1]=t;
                z.push(temp[0]+temp[1]);
            }
            z.push(temp[1]);
            z.printStack();
            while(z.pop(t))
            {
                y.push(t);
            }
            temp[0]=0;
            temp[1]=0;
        }
    }
}
