#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class ExpressionTree {
 private:
  struct Node {
    string ValueAndOpe;
    Node* left;
    Node* right;
    Node(const string& val) : ValueAndOpe(val), left(nullptr), right(nullptr) {}
  };

  Node* root;

  int precedence(const string& op) {
    if (op == "+" || op == "-")
      return 1;
    if (op == "*" || op == "/" || op == "%")
      return 2;
    return 0;
  }

  bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
  }

  void applyOperator(stack<Node*>& numbers, stack<string>& operators) {
    Node* right = numbers.top();
    numbers.pop();
    Node* left = numbers.top();
    numbers.pop();

    Node* opNode = new Node(operators.top());
    operators.pop();

    opNode->left = left;
    opNode->right = right;

    numbers.push(opNode);
  }

  Node* buildExpressionTree(const vector<string>& tokens) {
    stack<Node*> numbers;  // 放還沒處理的數字和已經處理的運算符
    stack<string> operators;  // 放還沒處理的運算符

    for (const string& token : tokens) {
      if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {  // 處理負數
        numbers.push(new Node(token));
      } else if (token == "(") {
        operators.push(token);
      } else if (token == ")") {
        while (!operators.empty() && operators.top() != "(") {  // 處理直到遇到左括號
          applyOperator(numbers, operators);
        }
        operators.pop();
      } else if (isOperator(token)) {  // 處理運算符
        while (!operators.empty() &&
               precedence(operators.top()) >= precedence(token)) {
          applyOperator(numbers, operators);
        }
        operators.push(token);
      }
    }

    while (!operators.empty()) {
      applyOperator(numbers, operators);
    }

    return numbers.top();
  }

  // 中序
  void printInFixOrder(Node* node) {
    if (!node)
      return;
    if (isOperator(node->ValueAndOpe))
      cout << "(";
    printInFixOrder(node->left);
    cout << node->ValueAndOpe << " ";
    printInFixOrder(node->right);
    if (isOperator(node->ValueAndOpe))
      cout << ")";
  }

  // 前序
  void printPreFixOrder(Node* node) {
    if (!node)
      return;
    cout << node->ValueAndOpe << " ";
    printPreFixOrder(node->left);
    printPreFixOrder(node->right);
  }

  // 後序
  void printPostFixOrder(Node* node) {
    if (!node)
      return;
    printPostFixOrder(node->left);
    printPostFixOrder(node->right);
    cout << node->ValueAndOpe << " ";
  }

  int evaluate(Node* node) {
    if (!node)
      return 0;
    if (!isOperator(node->ValueAndOpe))
      return stoi(node->ValueAndOpe);

    int leftVal = evaluate(node->left);
    int rightVal = evaluate(node->right);

    if (node->ValueAndOpe == "+")
      return leftVal + rightVal;
    if (node->ValueAndOpe == "-")
      return leftVal - rightVal;
    if (node->ValueAndOpe == "*")
      return leftVal * rightVal;
    if (node->ValueAndOpe == "/")
      return leftVal / rightVal;
    if (node->ValueAndOpe == "%")
      return leftVal % rightVal;

    throw runtime_error("Invalid operator");
  }

  // 分割字串
  vector<string> divide(const string& expression) {
    istringstream iss(expression);
    vector<string> tokens;
    string token;
    while (iss >> token) {
      tokens.push_back(token);
    }
    return tokens;
  }

 public:
  ExpressionTree(const string& expression) {
    vector<string> tokens = divide(expression);
    root = buildExpressionTree(tokens);
  }

  ~ExpressionTree() { deleteTree(root); }

  void deleteTree(Node* node) {
    if (!node)
      return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }

  // 中序
  void printInFixOrder() {
    printInFixOrder(root);
    cout << endl;
  }

  // 前序
  void printPreFixOrder() {
    printPreFixOrder(root);
    cout << endl;
  }

  // 後序
  void printPostFixOrder() {
    printPostFixOrder(root);
    cout << endl;
  }

  int eval() { return evaluate(root); }
};

int main() {
  string infix;
  getline(cin, infix);
  ExpressionTree exprTree(infix);

  cout << "Inorder: ";
  exprTree.printInFixOrder();
  cout << "Preorder: ";
  exprTree.printPreFixOrder();
  cout << "Postorder: ";
  exprTree.printPostFixOrder();
  cout << "Evaluated result: " << exprTree.eval() << endl;

  return 0;
}