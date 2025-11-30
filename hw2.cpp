#include <bits/stdc++.h>
#include "poker.h"
using namespace std;
int main()
{
    poker poker;
    int n;
    cout << "How many rounds do you want to play? (Less three)" << endl;
    cin >> n;
    cout << "How many players?" << endl;
    cin >> poker.p;
    srand(time(NULL));
    poker.b = rand() % poker.p + 1;
    for (int i = 1; i <= poker.p; i++)
    {
        poker.money[i] = 10000;
    }
    for (int i = 0; i < n; i++)
    {
        cout << "Banker is p" << poker.b << endl;
        poker.initial();
        cout << "Now, print the first poker" << endl;
        poker.send(1);
        cout << "p" << poker.b << ":" << endl;
        poker.print(poker.b, 1);
        cout << "Now, print the second poker" << endl;
        poker.send(2);
        poker.insure();
        poker.doublebet();
        poker.surrender();
        poker.addpoker();
        poker.final();
    }
    poker.rank();
    system("pause");
    return 0;
}