#include "stack_queue.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "===== 测试 MyStack =====" << std::endl;
    MyStack ms;
    int val;

    ms.push(1);
    ms.printStack();   // 1
    ms.push(2);
    ms.printStack();   // 2,1
    ms.pop(val);
    std::cout << "pop得到: " << val << std::endl; // 2
    ms.printStack();   // 1
    ms.getTop(val);
    std::cout << "当前栈顶: " << val << std::endl; // 1
    ms.printStack();   // 1

    std::cout << "\n===== 测试 MyQueue =====" << std::endl;
    MyQueue mq(5);
    mq.enQueue(1);
    mq.printQueue();   // 1
    mq.enQueue(2);
    mq.printQueue();   // 1,2
    mq.deQueue(val);
    std::cout << "出队得到: " << val << std::endl; // 1
    mq.printQueue();   // 2
    mq.getFront(val);
    std::cout << "当前队首: " << val << std::endl; // 2
    mq.printQueue();   // 2

    std::cout << "\n===== 测试 中缀转后缀 =====" << std::endl;
    std::string result;
    postfixExpression("5*(7-2)", result);
    std::cout << "中缀: 5*(7-2)\n后缀: " << result << std::endl; // 572-*

    postfixExpression("5*(7-2", result);
    std::cout << "错误示例: " << result << std::endl; // Expression is wrong!

    std::cout << "\n===== 测试 表达式求值 =====" << std::endl;
    int eval;
    std::string postfix;
    postfixExpression("5*(7-2)", postfix);
    if (expressionVal(postfix, eval))
        std::cout << "表达式结果: " << eval << std::endl; // 25
    else
        std::cout << "表达式错误" << std::endl;

    postfixExpression("3+5*2", postfix);
    std::cout << "3+5*2 => 后缀: " << postfix << std::endl;
    if (expressionVal(postfix, eval))
        std::cout << "结果: " << eval << std::endl; // 13

    std::cout << "\n===== 测试 杨辉三角 =====" << std::endl;
    yanghui(1);
    yanghui(3);
    yanghui(5);

    std::cout << "\n===== 所有测试结束 =====" << std::endl;
    return 0;
}
