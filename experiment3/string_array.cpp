#include "string_array.h"
//测试
using namespace std;

void myStr::print(){
    for(int i = 0; i < this->length; i++)
        cout << this->data[i];

    cout << endl;
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

void myMatrix::printMatrix(){
    cout << rowNum << "," << colNum << "," << nodeNum << endl;

    for(int i = 0; i < nodeNum; i++)
        cout << nodeList[i].row << "," << nodeList[i].col << "," << nodeList[i].value << endl;
}
