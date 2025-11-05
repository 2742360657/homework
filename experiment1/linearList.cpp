#include "linearList.h"
#include <iostream>
#include <iomanip>
using namespace std;

// 确保把类定义写在linearList.h中，类实现写在linearList.cpp中
// 给出的linearList.h中的函数声明不要改动，linearList.h中的内容可以增但不可以删，测试文件将根据已有的函数声明调用，linearList.cpp中的打印函数不要改动。

// 初始化顺序表sequenceList (const int&, const int&, float[]);//顺序表容量，初始化数组长度，初始化数组
sequenceList::sequenceList(const int& cap, const int& len, float a[])
{
    maxCapcity = cap;
    curNumberOfItem = len;
    myList = new float[maxCapcity];
    for (int i = 0; i < len; i++)
        myList[i] = a[i];
}
// 销毁顺序表, ~ sequenceList ()
sequenceList::~sequenceList()
{
    delete[] myList;
}
// 添加元素, bool addItem(const float&);//添加元素顺序表尾，成功返回true，失败返回false
bool sequenceList::addItem(const float& val)
{
    if (curNumberOfItem >= maxCapcity)
        return false;
    myList[curNumberOfItem++] = val;
    return true;
}
// 插入元素, bool insertItem(const int& index, const float&);//插入元素到index位置，成功返回true，失败返回false
bool sequenceList::insertItem(const int& index, const float& val)
{
    if (curNumberOfItem >= maxCapcity || index < 0 || index > curNumberOfItem)
        return false;
    for (int i = curNumberOfItem; i > index; i--)
        myList[i] = myList[i - 1];
    myList[index] = val;
    curNumberOfItem++;
    return true;
}
// 删除元素,int deleteItem(const float&)//返回删除位置，找不到返回-1
int sequenceList::deleteItem(const float& val)
{
    int pos = -1;
    for (int i = 0; i < curNumberOfItem; i++)
    {
        if (myList[i] == val)
        {
            pos = i;
            for (int j = i; j < curNumberOfItem - 1; j++)
                myList[j] = myList[j + 1];
            curNumberOfItem--;
            break;
        }
    }
    return pos;
}
// 查找元素（按序号找）, bool locate(const int&, float& val)// 成功返回true，值放在val中，失败返回false
bool sequenceList::locate(const int& index, float& val)
{
    if (index < 0 || index >= curNumberOfItem)
        return false;
    val = myList[index];
    return true;
}
// 查找元素（按值找）, int locate(const float&)//返回找到位置，找不到返回-1
int sequenceList::locate(const float& val)
{
    for (int i = 0; i < curNumberOfItem; i++)
    {
        if (myList[i] == val)
            return i;
    }
    return -1;
}
// 倒序排列元素（使用原空间），void reverse();
void sequenceList::reverse()
{
    for (int i = 0; i < curNumberOfItem / 2; i++)
    {
        float t = myList[i];
        myList[i] = myList[curNumberOfItem - 1 - i];
        myList[curNumberOfItem - 1 - i] = t;
    }
}
// 按序输出元素, void print()//元素个数:元素1, 元素2…
void sequenceList::print()
{
    cout << curNumberOfItem << ":";
    for (int i = 0; i < curNumberOfItem; i++)
    {
        cout << myList[i];
        if (i != curNumberOfItem - 1)
            cout << ",";
    }
    cout << endl;
}



listNode::listNode(float nodeData, listNode* succ)
{
    data = nodeData;
    next = succ;
}
listNode::~listNode() {}



linkList::linkList()
{
    firstNode = new listNode;
    lastNode = firstNode;
    listSize = 0;
}
// 初始化链表, linkList(const int&, float[]);//初始化数组长度，初始化数组
linkList::linkList(const int& len, float a[])
{
    firstNode = new listNode;
    lastNode = firstNode;
    listSize = 0;
    for (int i = 0; i < len; i++)
        tailInsertItem(a[i]);
}
// 销毁链表，~ linkList ()
linkList::~linkList()
{
    curNode = firstNode;
    while (curNode != nullptr)
    {
        listNode* temp = curNode;
        curNode = curNode->next;
        delete temp;
    }
}
// 插入元素(头插法)，bool headInsertItem(const float&);成功返回true，失败返回false
bool linkList::headInsertItem(const float& val)
{
    listNode* node = new listNode(val, firstNode->next);
    firstNode->next = node;
    if (lastNode == firstNode)
        lastNode = node;
    listSize++;
    return true;
}
// 插入元素(尾插法），bool tailInsertItem(const float&);成功返回true，失败返回false
bool linkList::tailInsertItem(const float& val)
{
    listNode* node = new listNode(val);
    lastNode->next = node;
    lastNode = node;
    listSize++;
    return true;
}
// 插入元素，int insertItem(const int& index, const float&); //插入元素到index位置，成功返回插入位置，错误返回-1
int linkList::insertItem(const int& index, const float& val)
{
    if (index < 0 || index > listSize)
        return -1;
    listNode* p = firstNode;
    for (int i = 0; i < index; i++)
        p = p->next;
    listNode* node = new listNode(val, p->next);
    p->next = node;
    if (node->next == nullptr)
        lastNode = node;
    listSize++;
    return index;
}
// 删除元素,int deleteItem(const float&)//返回删除位置，找不到返回-1
int linkList::deleteItem(const float& val)
{
    listNode* pre = firstNode;
    listNode* p = pre->next;
    int pos = 0;
    while (p != nullptr)
    {
        if (p->data == val)
        {
            pre->next = p->next;
            if (p == lastNode)
                lastNode = pre;
            delete p;
            listSize--;
            return pos;
        }
        pre = p;
        p = p->next;
        pos++;
    }
    return -1;
}
// 查找元素（按序号找）, bool locate(const int&, float& val)//成功返回true，值放在val中，失败返回false
bool linkList::locate(const int& index, float& val)
{
    if (index < 0 || index >= listSize)
        return false;
    listNode* p = firstNode->next;
    for (int i = 0; i < index; i++)
        p = p->next;
    val = p->data;
    return true;
}
// 查找元素（按值找）, int locate(const float&)//返回找到位置，找不到返回-1
int linkList::locate(const float& val)
{
    listNode* p = firstNode->next;
    int pos = 0;
    while (p != nullptr)
    {
        if (p->data == val)
            return pos;
        p = p->next;
        pos++;
    }
    return -1;
}
// 递增排序，void ascendingOrder()//
void linkList::ascendingOrder()
{
    if (listSize <= 1) return;
    listNode* p = firstNode->next;
    for (; p != nullptr; p = p->next)
    {
        listNode* q = p->next;
        for (; q != nullptr; q = q->next)
        {
            if (p->data > q->data)
            {
                float tmp = p->data;
                p->data = q->data;
                q->data = tmp;
            }
        }
    }
}
// 倒序排列元素，void reverse();
void linkList::reverse()
{
    if (listSize <= 1) return;
    listNode* prev = nullptr;
    listNode* cur = firstNode->next;
    listNode* next;
    lastNode = cur;
    while (cur != nullptr)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    firstNode->next = prev;
}
// 按序输出元素, void print()//元素个数:元素1, 元素2…
void linkList::print()
{
    curNode = firstNode;
    cout << listSize << ":";
    while (curNode != lastNode)
    {
        if (curNode->next == lastNode)
            cout << curNode->next->data << endl;
        else
            cout << curNode->next->data << ",";
        curNode = curNode->next;
    }
}





//void merge(linkList& A, linkList& B)，读入A和B两个线性表，输入不需有序，输入后按元素值递增次序排列。
//编写程序将这两个单链表归并为一个按元素值递减次序排列的单链表，利用原来两个单链表的结点存放归并后的单链表,结果存在A线性表中。
void merge(linkList& A, linkList& B)
{
    listNode* p = A.firstNode->next;
    listNode* q = B.firstNode->next;
    
    A.firstNode->next = nullptr;
    A.listSize = 0;

    while (p != nullptr && q != nullptr)
    {
        listNode* temp;
        if (p->data < q->data)
        {
            temp = p;
            p = p->next;
        }
        else
        {
            temp = q;
            q = q->next;
        }
        temp->next = A.firstNode->next;
        A.firstNode->next = temp;
        A.listSize++;
    }

    while (p != nullptr)
    {
        listNode* temp = p;
        p = p->next;
        temp->next = A.firstNode->next;
        A.firstNode->next = temp;
        A.listSize++;
    }
    while (q != nullptr)
    {
        listNode* temp = q;
        q = q->next;
        temp->next = A.firstNode->next;
        A.firstNode->next = temp;
        A.listSize++;
    }

    A.lastNode = A.firstNode;
    while (A.lastNode->next != nullptr)
        {A.lastNode = A.lastNode->next;}

    B.firstNode->next = nullptr;
    B.lastNode = B.firstNode;
    B.listSize = 0;
}