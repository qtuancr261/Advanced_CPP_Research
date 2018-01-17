#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;
int main(int argc, char *argv[])
{
    system("ls");
    ifstream fileI{"testFile.odt", ios::in | ios::ate};
    char* binaryDataFromFile{};
    int binaryDataSize{};
    if (fileI.is_open())
    {

        cout << "ok" << endl;
        binaryDataSize = fileI.tellg();
        binaryDataFromFile = new char[binaryDataSize]{};
        fileI.seekg(0, ios::beg);
        fileI.read(binaryDataFromFile, binaryDataSize);
        /*string fileData;
        while(getline(file, fileData))
        {
            cout << fileData << endl;
        }*/
        cout << binaryDataFromFile << endl;
        fileI.close();
    }
    else
        cout << "error";
    //cout << binaryDataFromFile << endl;
    printf("data %s", binaryDataFromFile);
    ofstream fileO{"testFile2.odt", ios::out | ios::ate};
    if (fileO.is_open())
    {
        cout << "Ok - O" << endl;
        fileO.seekp(0, ios::beg);
        fileO.write(binaryDataFromFile, binaryDataSize);
        fileO.close();
    }
    else
        cout << "error - O" ;
    return 0;
}
