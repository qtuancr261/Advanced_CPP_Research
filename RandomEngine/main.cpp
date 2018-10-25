#include <iostream>
using std::move;
using std::cout;
int x = 10;
int&& getRInt() {return move(x);}
void printAddress(const int& v)
{

}
int main(int argc, char *argv[])
{
}
