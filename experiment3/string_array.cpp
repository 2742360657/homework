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
    :length(0),next(nullptr),nextVal(nullptr),data(new char[1])
{
    data[0]='\0';
}

myStr::myStr(const int& len)
    :length(len),next(nullptr),nextVal(nullptr)
{
    if(len<=0)
    {
        std::cout<<"非法长度,设置为空串\n";
        length=0;
        data=new char[1];
        data[0]='\0';
        return;
    }
    data=new char[len+1];
    for(int i=0;i<len;i++)
    {
        data[i]='0';
    }
    data[len]='\0';
}

myStr::myStr(const char* s)
    :next(nullptr),nextVal(nullptr)
{
    if(!s)
    {
        std::cout<<"违规字符串,设置为空串\n";
        length=0;
        data=new char[1];
        data[0]='\0';
        return;
    }
    length=std::strlen(s);
    data=new char[length+1];
    for(int i=0;i<=length;i++)
    {
        data[i]=s[i];
    }
    return;
}

myStr::myStr(const myStr& other)
    :length(other.length),next(nullptr),nextVal(nullptr)
{
    if (other.data == nullptr)
    {
        std::cout<<"无data,设置为空串\n";
        data=new char[1];
        data[0]='\0';
        return;
    }
    data=new char[length+1];
    for(int i=0;i<=length;i++)
    {
        data[i]=other.data[i];
    }
    return;
}

myStr::~myStr()
{
    delete[] data;
}

void myStr::print()
{
    for(int i = 0; i < this->length; i++)
        std::cout << this->data[i];

    std::cout << std::endl;
}

void myStr::kmp_next()
{
    
}

void myStr::kmp_nextVal()
{

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
    std::cout << rowNum << "," << colNum << "," << nodeNum << std::endl;

    for(int i = 0; i < nodeNum; i++)
        std::cout << nodeList[i].row << "," << nodeList[i].col << "," << nodeList[i].value << std::endl;
}

void myMatrix::FastTransposeSMatrix(myMatrix& T)
{

}
