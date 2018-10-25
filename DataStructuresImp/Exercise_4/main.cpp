#include "menu.h"
#include <stack>
int main(int argc, char *argv[])
{
    std::stack<Node<char>*> charStack;
    string postFixExpression = " ";
    for (int index = 0; index < postFixExpression.length(); index++)
    {
        if (postFixExpression.at(index) == 'H') // toan hang
            charStack.push(new Node<char>{postFixExpression[index], nullptr, nullptr});
        else // toan tu
        {
            Node<char>* newNode = new Node<char>{postFixExpression[index], nullptr, nullptr};
            Node<char>* right = charStack.top();
            charStack.pop();
            Node<char>* left = charStack.top();
            charStack.pop();
            newNode->ptrNext = right; // Ptr Right
            newNode->ptrPre = left; // Ptr Left
            charStack.push(newNode);
        }
    }
    //Menu menu;
    //menu.initMenu();
    return 0;
}
