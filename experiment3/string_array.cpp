#include "string_array.h"
#include<cstring>

//next辅助--------------------------------------

static void buildNext(const char* pat, int m, int* next1)
{

}

static void buildNextVal(const char* pat, int m, int* nextVal1)
{

}

//myStr实现-------------------------------------

myStr::myStr()
{

}

myStr::myStr(const int& len)
{

}

myStr::myStr(const char* s)
{

}

myStr::myStr(const myStr& other)
{

}

myStr::~myStr()
{

}

void myStr::print()
{
    for(int i = 0; i < this->length; i++)
        cout << this->data[i];

    cout << endl;
}

void myStr::kmp_next()
{
    
}

void myStr::kmp_nextVal()
{

}

void myStr::printNext(){
    for(int i = 0; i < length; i++)
        cout << next[i];
    cout << endl;
}

void myStr::printNextVal(){
    for(int i = 0; i < length; i++)
        cout << nextVal[i];
    cout << endl;
}

//友元函数-----------------------------------------

int simpleMatch(const myStr& S, const myStr& T)
{

}

//KMP匹配，使用nextVal
int kmpMatch(const myStr& S, const myStr& T)
{

}

//串替换：在 S 中从 start 位置开始寻找 T，找到后用 V 替换
bool replaceStr(myStr& S, const int& start, const myStr& T, const myStr& V)
{

}

//myMatrix实现--------------------------------------------------

myMatrix::myMatrix()
{

}

myMatrix::myMatrix(const int& rNum, const int& cNum, const int& nNum, const int* arr)
{

}

myMatrix::myMatrix(const myMatrix& other)
{

}

myMatrix::~myMatrix()
{

}

void myMatrix::printMatrix()
{
    cout << rowNum << "," << colNum << "," << nodeNum << endl;

    for(int i = 0; i < nodeNum; i++)
        cout << nodeList[i].row << "," << nodeList[i].col << "," << nodeList[i].value << endl;
}

void myMatrix::FastTransposeSMatrix(myMatrix& T)
{

}
