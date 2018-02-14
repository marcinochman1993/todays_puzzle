#include <iostream>
#include <cmath>
#include <list>
#include <ctime>
using namespace std;

int hashing(int value, int tabSize)
{
    return fmod(value, tabSize);
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(0));

    int randTabSize = 300, tabSize = 30;
    int randomInputTab[randTabSize];
    list<int> hashTab[tabSize];

    for(int i = 0; i < randTabSize; i++)
    {
        randomInputTab[i] = (rand()%30)+1;
    }

    for(int i = 0; i < randTabSize; i++)
    {
        hashTab[hashing(randomInputTab[i], tabSize)].push_front(randomInputTab[i]);
    }

    for(int i = 0; i < tabSize; i++)
    {
        for(auto x : hashTab[i])
            cout << x << ", ";
        cout << endl;
    }

    return 0;
}
