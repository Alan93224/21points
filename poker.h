#include <bits/stdc++.h>
using namespace std;
class Player
{
public:
    int poker[6];
    bool insure = 0;
    int sum = 0;
    bool doublebet = 0;
    bool surrender = 0;
    bool battle = 1;
    bool special = 0;
    bool loss = 0;
    Player(){};
};
class poker
{
public:
    poker(){};
    ~poker(){};
    Player player[10];
    string plum[14];
    string rhombus[14];
    string compassion[14];
    string spade[14];
    int p, b, r[53];
    int money[10], stake[10], m[10];
    void initial();
    void print(int m, int n);
    void send(int n);
    void insure();
    void doublebet();
    void surrender();
    void addpoker();
    void sum(int n);
    void final();
    void rank();
    void Plum(int n);
    void Rhombus(int n);
    void Compassion(int n);
    void Spade(int n);
};