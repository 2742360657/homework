#include "string_array.h"
#include <cstring>

// myStr实现-------------------------------------

myStr::myStr()
    : length(0), next(nullptr), nextVal(nullptr), data(new char[1])
{
    data[0] = '\0';
}

myStr::myStr(const int &len)
    : length(len), next(nullptr), nextVal(nullptr)
{
    if (len <= 0)
    {
        std::cout << "非法长度,设置为空串\n";
        length = 0;
        data = new char[1];
        data[0] = '\0';
        return;
    }
    data = new char[len + 1];
    for (int i = 0; i < len; i++)
    {
        data[i] = '0';
    }
    data[len] = '\0';
}

myStr::myStr(const char *s)
    : next(nullptr), nextVal(nullptr)
{
    if (!s)
    {
        std::cout << "违规字符串,设置为空串\n";
        length = 0;
        data = new char[1];
        data[0] = '\0';
        return;
    }
    length = std::strlen(s);
    data = new char[length + 1];
    for (int i = 0; i <= length; i++)
    {
        data[i] = s[i];
    }
    return;
}

myStr::myStr(const myStr &other)
    : length(other.length), next(nullptr), nextVal(nullptr)
{
    if (other.data == nullptr)
    {
        std::cout << "无data,设置为空串\n";
        data = new char[1];
        data[0] = '\0';
        return;
    }
    data = new char[length + 1];
    for (int i = 0; i <= length; i++)
    {
        data[i] = other.data[i];
    }

    if (other.next != nullptr)
    {
        next = new int[length];
        for (int i = 0; i < length; ++i)
            next[i] = other.next[i];
    }
    else
    {
        next = nullptr;
    }

    if (other.nextVal != nullptr)
    {
        nextVal = new int[length];
        for (int i = 0; i < length; ++i)
            nextVal[i] = other.nextVal[i];
    }
    else
    {
        nextVal = nullptr;
    }

    return;
}

myStr::~myStr()
{
    delete[] data;
    delete[] next;
    delete[] nextVal;
}

void myStr::print()
{
    for (int i = 0; i < this->length; i++)
        std::cout << this->data[i];

    std::cout << std::endl;
}

void myStr::kmp_next()
{
    if (length <= 0)
    {
        return;
    }
    delete[] next;
    int *temnext = new int[length + 1]; // 忽略0，从下标1开始
    next[1] = 0;
    int a = 2; // 从第 2 个字符开始
    int b = 0; // 当前最长前后缀长度
    while (a <= length)
    {
        if (b == 0 || data[a - 1] == data[b - 1])
        {
            ++a;
            ++b;
            next[a - 1] = b; // 对应前 a-1 个字符的 next
        }
        else
        {
            b = next[b]; // 回退
        }
    }
}

// // 构造 KMP 的改进 nextVal 数组（1-based）
// static void buildNextVal(const char* pat, int m, int* nextVal1)
// {
//     if (m <= 0) return;

//     int i = 1;
//     int j = 0;
//     nextVal1[1] = 0;

//     while (i < m)
//     {
//         if (j == 0 || pat[i - 1] == pat[j - 1])
//         {
//             ++i;
//             ++j;
//             if (i <= m)
//             {
//                 if (pat[i - 1] != pat[j - 1])
//                     nextVal1[i] = j;
//                 else
//                     nextVal1[i] = nextVal1[j];
//             }
//         }
//         else
//         {
//             j = nextVal1[j];
//         }
//     }
// }

void myStr::kmp_nextVal()
{
}

void myStr::printNext()
{
    for (int i = 0; i < length; i++)
        std::cout << next[i];
    std::cout << std::endl;
}

void myStr::printNextVal()
{
    for (int i = 0; i < length; i++)
        std::cout << nextVal[i];
    std::cout << std::endl;
}

// 友元函数-----------------------------------------

int simpleMatch(const myStr &S, const myStr &T)
{
}

// KMP匹配，使用nextVal
int kmpMatch(const myStr &S, const myStr &T)
{
}

// 串替换：在 S 中从 start 位置开始寻找 T，找到后用 V 替换
bool replaceStr(myStr &S, const int &start, const myStr &T, const myStr &V)
{
}

// myMatrix实现--------------------------------------------------

myMatrix::myMatrix()
{
}

myMatrix::myMatrix(const int &rNum, const int &cNum, const int &nNum, const int *arr)
{
}

myMatrix::myMatrix(const myMatrix &other)
{
}

myMatrix::~myMatrix()
{
}

void myMatrix::printMatrix()
{
    std::cout << rowNum << "," << colNum << "," << nodeNum << std::endl;

    for (int i = 0; i < nodeNum; i++)
        std::cout << nodeList[i].row << "," << nodeList[i].col << "," << nodeList[i].value << std::endl;
}

void myMatrix::FastTransposeSMatrix(myMatrix &T)
{
}
