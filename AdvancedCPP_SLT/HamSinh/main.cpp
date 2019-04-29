#include <iostream>
#include <cmath>
// mo ta ham sinh ra so co NUM chu so thoa man dieu kien tong cua  cac chu so bang SUM
using namespace std;
int Sum{};
int current_sum{};
int NUM{};
int arrayA[10]{};
bool checkPrime(long n)
{
    if (n < 2) return false;
    for (long i{2}; i <= std::sqrt(n); i++)
        if (n%i == 0) return false;
    return true;
}

void xuat(int num)
{
    long sum{};
    for (int i{1}; i <= num; i++) sum = sum*10 + arrayA[i];
    if (checkPrime(sum)) cout << sum << endl;
}
void Try(int i)
{
    int j{};
    if (i == 1) j = 1;
    else if (i == NUM) j = Sum-current_sum;
    for (; j <= Sum-current_sum && j <= 9; j++)
    {
        if (i == NUM) arrayA[i] = Sum-current_sum;
        else arrayA[i] = j;
        current_sum = current_sum + arrayA[i];
        //cout << arrayA[i] << " : ";
        if (i == NUM) xuat(NUM);
        else Try(i+1);
        current_sum = current_sum - arrayA[i];
    }
}

int main(int argc, char *argv[])
{
    for (int i{}; i < argc; i++) std::cout << argv[i] << std::endl;
    Sum = 5;
    current_sum = 0;
    NUM = 3;
    Try(1);
    //for (int i:arrayA) cout << i << " ";
    //QString ab{"101"};
    //cout << ab.toLong();
    return 0;
}
