//
//  main.cpp
//  shunting_yard
//
//  Created by Егор on 21.05.2024.
//

//
//  main.cpp
//  shunting_yard
//
//  Created by Егор on 21.05.2024.
//

#include <iostream>
#include <stack>
#include <map>
#include <cmath>
#include <string>

using namespace std;

void change(stack<char> &op, stack<double> &num) {
    if (op.top() == '(') {
        return;
    }
    // берем два числа из стека и проводим операцию с верхним элементом
    double b = num.top();
    num.pop();
    double a = num.top();
    num.pop();
    if (op.top() == '+') {
        num.push(a + b);
    } else if (op.top() == '-') {
        num.push(a - b);
    } else if (op.top() == '*') {
        num.push(a * b);
    } else if (op.top() == '/') {
        num.push(a / b);
    } else if (op.top() == '^') {
        num.push(pow(a, b));
    }
    op.pop();
}

double shunting_yard(const string &s) {
    map<char, int> priority; // словарь с приоритетом операций
    priority['+'] = 3;
    priority['-'] = 3;
    priority['*'] = 2;
    priority['/'] = 2;
    priority['^'] = 1;
    priority['('] = 0;
    priority[')'] = 0;

    stack<char> op;
    stack<double> num;
    string cur_num;

    cout << "Input expression: " << s << endl;
    cout << "Postfix expression: ";

    for (char i: s) {
        if (i >= '0' && i <= '9') {
            cur_num += i;
        } else if (i == ' ') {
            if (!cur_num.empty()) {
                num.push(stod(cur_num));
                cout << cur_num << " ";
                cur_num = "";
            }
        } else {
            if (!cur_num.empty()) {
                num.push(stod(cur_num));
                cout << cur_num << " ";
                cur_num = "";
            }

            if (i == ')') {
                while (op.top() != '(') {
                    cout << op.top() << " ";
                    change(op, num);
                }
                op.pop();
            } else {
                while ((!op.empty() && priority[op.top()] <= priority[i]) && op.top() != '(') {
                    cout << op.top() << " ";
                    change(op, num);
                }
                op.push(i);
            }
        }
    }
    if (!cur_num.empty()) {
        num.push(stod(cur_num));
        cout << cur_num << " ";
    }

    while (!op.empty()) {
        cout << op.top() << " ";
        change(op, num);
    }

    cout << endl << "Result: " << num.top() << endl;
    return num.top();
}

int main() {
    string s;
    getline(cin, s);
    shunting_yard(s);
}
//4*3/2+13+(12-3)+(((3-2)*1)/3)
//коректный ввывод 28.1/3
