
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T>* next;

    Node(T value) {
        data = value;
        next = NULL;
    }
};

template <class T>
class Stack {
    Node<T>* topNode;

public:
    Stack() {
        topNode = NULL;
    }

    bool isEmpty() {
        return topNode == NULL;
    }

    void push(T value) {
        Node<T>* n = new Node<T>(value);
        n->next = topNode;
        topNode = n;
    }

    bool pop(T& value) {
        if (isEmpty())
            return false;

        Node<T>* temp = topNode;
        value = temp->data;
        topNode = topNode->next;
        delete temp;
        return true;
    }

    bool top(T& value) {
        if (isEmpty())
            return false;

        value = topNode->data;
        return true;
    }

    void clear() {
        T value;
        while (pop(value)) {}
    }

    ~Stack() {
        clear();
    }
};

int precedence(char op) {
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '%';
}

bool convert(string infix, string& postfix) {
    Stack<char> ops;
    postfix = "";
    bool expectOperand = true;
    bool hasToken = false;

    for (int i = 0; i < (int)infix.size();) {
        char c = infix[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        if (isdigit(c)) {
            if (!expectOperand) {
                cout << "Invalid expression.\n";
                return false;
            }

            while (i < (int)infix.size() &&
                   isdigit(infix[i])) {
                postfix += infix[i++];
            }

            postfix += ' ';
            expectOperand = false;
            hasToken = true;
        }
        else if (c == '(') {
            if (!expectOperand) {
                cout << "Invalid expression.\n";
                return false;
            }

            ops.push(c);
            i++;
        }
        else if (c == ')') {
            if (expectOperand) {
                cout << "Invalid expression.\n";
                return false;
            }

            char op;
            bool found = false;

            while (ops.pop(op)) {
                if (op == '(') {
                    found = true;
                    break;
                }

                postfix += op;
                postfix += ' ';
            }

            if (!found) {
                cout << "Mismatched parentheses.\n";
                return false;
            }

            i++;
            expectOperand = false;
        }
        else if (isOperator(c)) {
            if (expectOperand) {
                cout << "Invalid expression.\n";
                return false;
            }

            char op;
            while (ops.top(op) && op != '(' &&
                   precedence(op) >= precedence(c)) {
                ops.pop(op);
                postfix += op;
                postfix += ' ';
            }

            ops.push(c);
            i++;
            expectOperand = true;
        }
        else {
            cout << "Invalid character.\n";
            return false;
        }
    }

    if (!hasToken || expectOperand) {
        cout << "Empty or invalid expression.\n";
        return false;
    }

    char op;
    while (ops.pop(op)) {
        if (op == '(') {
            cout << "Mismatched parentheses.\n";
            return false;
        }

        postfix += op;
        postfix += ' ';
    }

    return true;
}

bool evaluate(string postfix, long long& result) {
    Stack<long long> values;
    stringstream ss(postfix);
    string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            try {
                size_t pos;
                long long value = stoll(token, &pos);

                if (pos != token.size())
                    return false;

                values.push(value);
            }
            catch (...) {
                cout << "Number out of range.\n";
                return false;
            }
        }
        else if (token.size() == 1 &&
                 isOperator(token[0])) {
            long long b, a;

            if (!values.pop(b) || !values.pop(a)) {
                cout << "Invalid expression.\n";
                return false;
            }

            long long answer;

            switch (token[0]) {
                case '+': answer = a + b; break;
                case '-': answer = a - b; break;
                case '*': answer = a * b; break;

                case '/':
                    if (b == 0) {
                        cout << "Division by zero.\n";
                        return false;
                    }
                    answer = a / b;
                    break;

                case '%':
                    if (b == 0) {
                        cout << "Modulus by zero.\n";
                        return false;
                    }
                    answer = a % b;
                    break;

                default:
                    return false;
            }

            values.push(answer);
        }
        else {
            cout << "Invalid postfix token.\n";
            return false;
        }
    }

    if (!values.pop(result) || !values.isEmpty()) {
        cout << "Invalid expression.\n";
        return false;
    }

    return true;
}

int main() {
    string infix, postfix;
    long long result;

    cout << "Enter an infix expression: ";
    getline(cin, infix);

    if (convert(infix, postfix)) {
        cout << "Postfix: " << postfix << endl;

        if (evaluate(postfix, result))
            cout << "Result: " << result << endl;
    }

    return 0;
}
