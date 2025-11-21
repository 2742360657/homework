#include "string_array.h"
#include <cstring>

// ===================== 文件内辅助函数 =====================

// 构造 KMP 的 next 数组（1-based）
static void buildNext(const char* pat, int m, int* next1)
{
    if (m <= 0) return;

    int i = 1;
    int j = 0;
    next1[1] = 0;

    while (i < m)
    {
        if (j == 0 || pat[i - 1] == pat[j - 1])
        {
            ++i;
            ++j;
            if (i <= m)
                next1[i] = j;
        }
        else
        {
            j = next1[j];
        }
    }
}

// 构造 KMP 的改进 nextVal 数组（1-based）
static void buildNextVal(const char* pat, int m, int* nextVal1)
{
    if (m <= 0) return;

    int i = 1;
    int j = 0;
    nextVal1[1] = 0;

    while (i < m)
    {
        if (j == 0 || pat[i - 1] == pat[j - 1])
        {
            ++i;
            ++j;
            if (i <= m)
            {
                if (pat[i - 1] != pat[j - 1])
                    nextVal1[i] = j;
                else
                    nextVal1[i] = nextVal1[j];
            }
        }
        else
        {
            j = nextVal1[j];
        }
    }
}

// ===================== myStr 实现 =====================

// 新增：无参构造函数
myStr::myStr()
{
    length = 0;
    data = new char[1];
    data[0] = '\0';

    next = nullptr;
    nextVal = nullptr;
}

// 已有：从 const char* 构造
myStr::myStr(const char* s)
{
    if (!s)
    {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }
    else
    {
        length = static_cast<int>(std::strlen(s));
        data = new char[length + 1];
        std::memcpy(data, s, length + 1); // 包括 '\0'
    }

    next = nullptr;
    nextVal = nullptr;
}

// 新增：拷贝构造函数
myStr::myStr(const myStr& other)
{
    length = other.length;

    data = new char[length + 1];
    std::memcpy(data, other.data, length + 1);

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
}

myStr::~myStr()
{
    delete[] data;
    delete[] next;
    delete[] nextVal;
}

// ======== 题目给定的打印函数，保持不变 =========

void myStr::print(){
    for(int i = 0; i < this->length; i++)
        std::cout << this->data[i];

    std::cout << std::endl;
}

void myStr::printNext(){
    for(int i = 0; i < length; i++)
        std::cout << next[i];
    std::cout << std::endl;
}

void myStr::printNextVal(){
    for(int i = 0; i < length; i++)
        std::cout << nextVal[i];
    std::cout << std::endl;
}

// ====================================================
// KMP 辅助数组 next
void myStr::kmp_next()
{
    if (length <= 0)
        return;

    delete[] next;
    next = new int[length];

    // 用 1-based 临时数组计算，再拷贝到成员 next（0-based）
    int* tmpNext = new int[length + 1];
    buildNext(data, length, tmpNext);

    for (int i = 0; i < length; ++i)
        next[i] = tmpNext[i + 1];

    delete[] tmpNext;
}

// KMP 改进辅助数组 nextVal
void myStr::kmp_nextVal()
{
    if (length <= 0)
        return;

    delete[] nextVal;
    nextVal = new int[length];

    int* tmpNextVal = new int[length + 1];
    buildNextVal(data, length, tmpNextVal);

    for (int i = 0; i < length; ++i)
        nextVal[i] = tmpNextVal[i + 1];

    delete[] tmpNextVal;
}

// ===================== 友元函数实现 =====================

// 朴素匹配算法
int simpleMatch(const myStr& S, const myStr& T)
{
    if (T.length == 0 || T.length > S.length)
        return -1;

    for (int i = 0; i <= S.length - T.length; ++i)
    {
        int j = 0;
        while (j < T.length && S.data[i + j] == T.data[j])
            ++j;
        if (j == T.length)
            return i + 1; // 位置从 1 开始
    }
    return -1;
}

// KMP 匹配，使用 nextVal
int kmpMatch(const myStr& S, const myStr& T)
{
    if (T.length == 0 || T.length > S.length)
        return -1;

    int n = S.length;
    int m = T.length;

    // 构造 nextVal（1-based）
    int* nextVal1 = new int[m + 1];
    buildNextVal(T.data, m, nextVal1);
    nextVal1[0] = 0;

    int i = 1; // S 的下标（1-based）
    int j = 1; // T 的下标（1-based）

    while (i <= n && j <= m)
    {
        if (j == 0 || S.data[i - 1] == T.data[j - 1])
        {
            ++i;
            ++j;
        }
        else
        {
            j = nextVal1[j];
        }
    }

    int pos = (j > m) ? (i - m) : 0;
    delete[] nextVal1;

    if (pos == 0)
        return -1;
    else
        return pos; // 1-based
}

// 串替换：在 S 中从 start 位置开始寻找 T，找到后用 V 替换
bool replaceStr(myStr& S, const int& start, const myStr& T, const myStr& V)
{
    if (start < 1 || start > S.length || T.length == 0 || T.length > S.length)
        return false;

    int begin = -1; // 匹配起始下标（0-based）

    for (int i = start - 1; i <= S.length - T.length; ++i)
    {
        int j = 0;
        while (j < T.length && S.data[i + j] == T.data[j])
            ++j;
        if (j == T.length)
        {
            begin = i;
            break;
        }
    }

    if (begin == -1)
        return false;

    int prefixLen   = begin;
    int suffixStart = begin + T.length;
    int suffixLen   = S.length - suffixStart;
    int newLen      = prefixLen + V.length + suffixLen;

    char* newData = new char[newLen + 1];

    // 前缀
    for (int i = 0; i < prefixLen; ++i)
        newData[i] = S.data[i];

    // 替换串
    for (int i = 0; i < V.length; ++i)
        newData[prefixLen + i] = V.data[i];

    // 后缀
    for (int i = 0; i < suffixLen; ++i)
        newData[prefixLen + V.length + i] = S.data[suffixStart + i];

    newData[newLen] = '\0';

    delete[] S.data;
    S.data   = newData;
    S.length = newLen;

    // 原有 next / nextVal 已失效，释放
    delete[] S.next;
    delete[] S.nextVal;
    S.next    = nullptr;
    S.nextVal = nullptr;

    return true;
}

// ===================== myMatrix 实现 =====================

// 新增：无参构造函数
myMatrix::myMatrix()
{
    rowNum = 0;
    colNum = 0;
    nodeNum = 0;
    nodeList = nullptr;
}

// 已有：带参数构造函数（行数，列数，非零元个数，三元组数组）
myMatrix::myMatrix(const int& rNum, const int& cNum, const int& nNum, const int* arr)
{
    rowNum = rNum;
    colNum = cNum;
    nodeNum = nNum;

    if (nodeNum > 0 && arr != nullptr)
    {
        nodeList = new matrixNode[nodeNum];
        for (int i = 0; i < nodeNum; ++i)
        {
            nodeList[i].row   = arr[3 * i];       // 行
            nodeList[i].col   = arr[3 * i + 1];   // 列
            nodeList[i].value = arr[3 * i + 2];   // 值
        }
    }
    else
    {
        nodeList = nullptr;
    }
}

// 新增：拷贝构造函数
myMatrix::myMatrix(const myMatrix& other)
{
    rowNum  = other.rowNum;
    colNum  = other.colNum;
    nodeNum = other.nodeNum;

    if (nodeNum > 0 && other.nodeList != nullptr)
    {
        nodeList = new matrixNode[nodeNum];
        for (int i = 0; i < nodeNum; ++i)
            nodeList[i] = other.nodeList[i];
    }
    else
    {
        nodeList = nullptr;
    }
}

myMatrix::~myMatrix()
{
    delete[] nodeList;
}

// ======== 打印函数（题目给定，不要改） ========

void myMatrix::printMatrix(){
    std::cout << rowNum << "," << colNum << "," << nodeNum << std::endl;

    for(int i = 0; i < nodeNum; i++)
        std::cout << nodeList[i].row << "," << nodeList[i].col << "," << nodeList[i].value << std::endl;
}

// 快速转置
void myMatrix::FastTransposeSMatrix(myMatrix& T)
{
    // 先释放 T 原有空间，避免内存泄漏
    delete[] T.nodeList;

    T.rowNum  = colNum;
    T.colNum  = rowNum;
    T.nodeNum = nodeNum;

    if (nodeNum == 0)
    {
        T.nodeList = nullptr;
        return;
    }

    T.nodeList = new matrixNode[nodeNum];

    int* num  = new int[colNum]; // 每列非零个数
    int* cpot = new int[colNum]; // 每列在 T 中的起始位置

    for (int i = 0; i < colNum; ++i)
        num[i] = 0;

    // 统计每列中的非零个数
    for (int i = 0; i < nodeNum; ++i)
    {
        int col = nodeList[i].col; // 1-based 列号
        if (col >= 1 && col <= colNum)
            ++num[col - 1];
    }

    // 计算每列的起始位置
    cpot[0] = 0;
    for (int i = 1; i < colNum; ++i)
        cpot[i] = cpot[i - 1] + num[i - 1];

    // 填充转置矩阵
    for (int i = 0; i < nodeNum; ++i)
    {
        int col = nodeList[i].col;      // 原矩阵列
        int pos = cpot[col - 1];        // 在 T.nodeList 中的位置

        T.nodeList[pos].row   = nodeList[i].col; // 行列互换
        T.nodeList[pos].col   = nodeList[i].row;
        T.nodeList[pos].value = nodeList[i].value;

        ++cpot[col - 1];
    }

    delete[] num;
    delete[] cpot;
}
