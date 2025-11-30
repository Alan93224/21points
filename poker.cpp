#include <bits/stdc++.h>
#include "poker.h"
using namespace std;
void poker::initial()
{
    for (int i = 1; i <= p; i++)
    {
        if (i == b || player[i].loss == 1)
            continue;
        else
        {
            cout << "Please input your stake. ( >=1000 )" << endl;
            cout << "p" << i << ":" << endl;
            while (1)
            {
                cin >> stake[i];
                if (stake[i] >= 1000 && stake[i] <= money[i])
                {
                    break;
                }
                else if (stake[i] < 1000)
                    cout << "Your stake is less than 1000" << endl;
                else if (stake[i] > money[i])
                    cout << "Your stake is more than the money you have" << endl;
            }
        }
    }
    for (int i = 1; i <= 52; i++)
    {
        r[i] = 0;
    }
    for (int j = 1; j <= p; j++)
    {
        for (int i = 0; i < 6; i++)
        {
            player[j].poker[i] = 0;
        }
    }
}
void poker::print(int m, int n)
{
    int pk;
    srand(time(NULL));
    do
    {
        pk = rand() % 52 + 1;
    } while (r[pk] != 0);
    r[pk] = 1;
    player[m].poker[n] = pk;
    if (pk % 4 == 1)
    {
        Plum((pk / 4) + 1);
        for (int j = 0; j < 13; j++)
        {
            cout << plum[j] << endl;
        }
    }
    else if (pk % 4 == 2)
    {
        Rhombus((pk / 4) + 1);
        for (int j = 0; j < 13; j++)
        {
            cout << rhombus[j] << endl;
        }
    }
    else if (pk % 4 == 3)
    {
        Compassion((pk / 4) + 1);
        for (int j = 0; j < 13; j++)
        {
            cout << compassion[j] << endl;
        }
    }
    else if (pk % 4 == 0)
    {
        Spade(pk / 4);
        for (int j = 0; j < 13; j++)
        {
            cout << spade[j] << endl;
        }
    }
}
void poker::send(int n)
{
    for (int i = 1; i <= p; i++)
    {
        if (i == b || player[i].loss == 1)
            continue;
        else
        {
            cout << "p" << i << ":" << endl;
            print(i, n);
        }
    }
}
void poker::insure()
{
    int ans;
    int pk;
    srand(time(NULL));
    do
    {
        pk = rand() % 52 + 1;
    } while (r[pk] != 0);
    r[pk] = 1;
    player[b].poker[2] = pk;
    if (player[b].poker[1] >= 1 && player[b].poker[1] <= 4)
    {
        for (int i = 1; i <= p; i++)
        {
            if (i == b || player[i].loss == 1)
                continue;
            else
            {
                cout << "p" << i << ", Do you want to take insurance? (1 or 0)" << endl;
                cin >> ans;
                if (ans == 1)
                {
                    player[i].insure = 1;
                }
                else
                {
                    player[i].insure = 0;
                }
            }
        }
        if ((pk - 1 / 4) >= 9)
        {
            for (int i = 1; i <= p; i++)
            {
                if (i == b || player[i].loss == 1)
                    continue;
                else
                {
                    if (player[i].insure == 1)
                    {
                        money[i] += stake[i];
                        money[b] -= stake[i];
                    }
                }
            }
        }
        else
        {

            for (int i = 1; i <= p; i++)
            {
                if (i == b || player[i].loss == 1)
                    continue;
                else
                {
                    if (player[i].insure == 1)
                    {
                        money[i] -= (stake[i] / 2);
                        money[b] += (stake[i] / 2);
                    }
                }
            }
        }
        for (int i = 1; i <= p; i++)
        {
            if (player[i].loss == 1)
                continue;
            cout << "p" << i << " : " << money[i] << endl;
        }
    }
}
void poker::doublebet()
{
    int ans;
    for (int i = 1; i <= p; i++)
    {
        if (i == b || player[i].loss == 1)
            continue;
        else
        {
            player[i].sum = ((player[i].poker[1] - 1) / 4) + ((player[i].poker[2] - 1) / 4) + 2;
            if ((player[i].poker[1] - 1 / 4 + 1) == 1)
                player[i].sum += 10;
            if (player[i].sum == 11)
            {
                cout << "P" << i << ", Do you want to double down? (1 or 0)" << endl;
                cin >> ans;
                if (ans == 1)
                {
                    stake[i] *= 2;
                    print(i, 3);
                    sum(i);
                    cout << "p" << i << ", your pokers' sum is " << player[i].sum << endl;
                    player[i].doublebet = 1;
                }
                else
                {
                    player[i].doublebet = 0;
                }
            }
        }
    }
}
void poker::surrender()
{
    int ans;
    for (int i = 1; i <= p; i++)
    {
        if (i == b || player[i].loss == 1)
            continue;
        else
        {
            cout << "p" << i << ", Do you want to surrender? (1 or 0)" << endl;
            cin >> ans;
            if (ans == 1)
            {
                money[i] -= (stake[i] / 2);
                player[i].surrender = 1;
            }
        }
    }
}
void poker::addpoker()
{
    int ans, cnt;
    for (int i = 1; i <= p; i++)
    {
        if (i == b || player[i].loss == 1 || player[i].surrender == 1 || player[i].doublebet == 1)
            continue;
        else
        {
            cnt = 3;
            for (int j = 0; j < 13; j++)
            {
                if (player[i].poker[1] % 4 == 1)
                {
                    Plum((player[i].poker[1] / 4) + 1);
                    cout << plum[j] << " ";
                }
                else if (player[i].poker[1] % 4 == 2)
                {
                    Rhombus((player[i].poker[1] / 4) + 1);
                    cout << rhombus[j] << " ";
                }
                else if (player[i].poker[1] % 4 == 3)
                {
                    Compassion((player[i].poker[1] / 4) + 1);
                    cout << compassion[j] << " ";
                }
                else if (player[i].poker[1] % 4 == 0)
                {
                    Spade(player[i].poker[1] / 4);
                    cout << spade[j] << " ";
                }
                if (player[i].poker[2] % 4 == 1)
                {
                    Plum((player[i].poker[2] / 4) + 1);
                    cout << plum[j] << " ";
                }
                else if (player[i].poker[2] % 4 == 2)
                {
                    Rhombus((player[i].poker[2] / 4) + 1);
                    cout << rhombus[j] << " ";
                }
                else if (player[i].poker[2] % 4 == 3)
                {
                    Compassion((player[i].poker[2] / 4) + 1);
                    cout << compassion[j] << " ";
                }
                else if (player[i].poker[2] % 4 == 0)
                {
                    Spade(player[i].poker[2] / 4);
                    cout << spade[j] << " ";
                }
                cout << endl;
            }
            for (int k = 0; k < 4; k++)
            {
                if (player[k].surrender == 1)
                    break;
                sum(i);
                if (player[i].sum > 21)
                {
                    player[i].battle = 0;
                    cout << "Your pokers' sum is more than 21" << endl;
                    break;
                }
                if (cnt == 6)
                {
                    cout << "You pass the five levels!" << endl;
                    player[i].special = 1;
                    break;
                }
                else
                {
                    cout << "p" << i << ", your pokers' sum is " << player[i].sum << endl;
                    cout << "Do you want to add poker? (1 or 0)" << endl;
                    cin >> ans;
                    if (ans == 1)
                    {
                        print(i, cnt);
                        cnt++;
                    }
                    else
                    {
                        sum(i);
                        break;
                    }
                }
            }
        }
    }
    for (int j = 0; j < 13; j++)
    {
        if (player[b].poker[1] % 4 == 1)
        {
            Plum((player[b].poker[1] / 4) + 1);
            cout << plum[j] << " ";
        }
        else if (player[b].poker[1] % 4 == 2)
        {
            Rhombus((player[b].poker[1] / 4) + 1);
            cout << rhombus[j] << " ";
        }
        else if (player[b].poker[1] % 4 == 3)
        {
            Compassion((player[b].poker[1] / 4) + 1);
            cout << compassion[j] << " ";
        }
        else if (player[b].poker[1] % 4 == 0)
        {
            Spade(player[b].poker[1] / 4);
            cout << spade[j] << " ";
        }
        if (player[b].poker[2] % 4 == 1)
        {
            Plum((player[b].poker[2] / 4) + 1);
            cout << plum[j] << " ";
        }
        else if (player[b].poker[2] % 4 == 2)
        {
            Rhombus((player[b].poker[2] / 4) + 1);
            cout << rhombus[j] << " ";
        }
        else if (player[b].poker[2] % 4 == 3)
        {
            Compassion((player[b].poker[2] / 4) + 1);
            cout << compassion[j] << " ";
        }
        else if (player[b].poker[2] % 4 == 0)
        {
            Spade(player[b].poker[2] / 4);
            cout << spade[j] << " ";
        }
        cout << endl;
    }
    cnt = 3;
    while (1)
    {
        sum(b);
        if (player[b].sum > 21)
        {
            player[b].battle = 0;
            cout << "p" << b << ", your pokers' sum is more than 21" << endl;
            break;
        }
        else if (player[b].sum < 17)
        {
            print(b, cnt);
            cnt++;
            if (cnt == 6)
                player[b].special = 1;
        }
        else
        {
            cout << "p" << b << ", your pokers' sum is " << player[b].sum << endl;
            cout << "Do you want to add poker? (1 or 0)" << endl;
            cin >> ans;
            if (ans == 1)
            {
                print(b, cnt);
                cnt++;
                if (cnt == 6)
                    player[b].special = 1;
            }
            else
            {
                sum(b);
                break;
            }
        }
    }
}
void poker::final()
{
    m[b] = money[b];
    for (int i = 1; i <= p; i++)
    {
        if (i == b || player[i].loss == 1 || player[i].surrender == 1)
            continue;
        else
        {
            if (player[b].battle == 0)
            {
                if (player[i].battle == 0)
                    ;
                else
                {
                    m[i] = money[i];
                    money[i] += stake[i];
                    money[b] -= stake[i];
                    m[i] -= money[i];
                }
            }
            else if (player[b].battle == 1)
            {
                if (player[i].battle == 0)
                {
                    m[i] = money[i];
                    money[b] += stake[i];
                    money[i] -= stake[i];
                    m[i] -= money[i];
                }
                else if (player[b].special == 1)
                {
                    if (player[i].special == 1)
                    {
                        if (player[b].sum >= player[i].sum)
                        {
                            m[i] = money[i];
                            money[b] += (stake[i] * 3);
                            money[i] -= (stake[i] * 3);
                            m[i] -= money[i];
                        }
                        else
                        {
                            m[i] = money[i];
                            money[b] -= (stake[i] * 3);
                            money[i] += (stake[i] * 3);
                            m[i] -= money[i];
                        }
                    }
                    else
                    {
                        m[i] = money[i];
                        money[b] += stake[i];
                        money[i] -= stake[i];
                        m[i] -= money[i];
                    }
                }
                else if (player[b].special == 0)
                {
                    if (player[i].special == 1)
                    {
                        m[i] = money[i];
                        money[b] -= stake[i];
                        money[i] += stake[i];
                        m[i] -= money[i];
                    }
                    else
                    {
                        if (player[b].sum >= player[i].sum)
                        {
                            m[i] = money[i];
                            money[b] += stake[i];
                            money[i] -= stake[i];
                            m[i] -= money[i];
                        }
                        else
                        {
                            m[i] = money[i];
                            money[b] -= stake[i];
                            money[i] += stake[i];
                            m[i] -= money[i];
                        }
                    }
                }
            }
        }
    }
    m[b] -= money[b];
    for (int i = 1; i <= p; i++)
    {
        if (player[i].loss == 1)
            continue;
        cout << "p" << i << "'s money = " << money[i] << endl;
        player[i].sum = 0;
    }
    int max = 0;
    for (int i = 1; i <= p; i++)
    {
        if (player[i].loss == 1)
            continue;
        if (money[i] <= 0)
            player[i].loss = 1;
        if (-m[i] > max)
        {
            max = -m[i];
            b = i;
        }
        player[i].surrender = 0;
    }
}
void poker::sum(int n)
{
    int cnt = 0;
    player[n].sum = 0;
    for (int i = 1; i < 6; i++)
    {
        if (player[n].poker[i] != 0)
        {
            player[n].sum += (((player[n].poker[i] - 1) / 4) + 1);
            if (((player[n].poker[i] - 1) / 4 + 1) == 1)
            {
                cnt++;
                player[n].sum += 10;
            }
            else if (((player[n].poker[i] - 1) / 4 + 1) >= 11)
            {
                player[n].sum -= (((player[n].poker[i] - 1) / 4 + 1) - 10);
            }
        }
    }
    if (cnt > 0 && player[n].sum > 21)
    {
        while (cnt > 0 && player[n].sum > 21)
        {
            player[n].sum -= 10;
            cnt--;
        }
    }
}
void poker::rank()
{
    int a[p], temp;
    for (int i = 1; i <= p; i++)
        a[i] = i;
    for (int j = 2; j < p; j++)
    {
        for (int i = 1; i < p; i++)
        {
            if (money[i] < money[i + 1])
            {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
    }
    cout << "Rank: ";
    for (int i = 1; i <= p; i++)
    {
        cout << "p" << a[i] << " ";
    }
    cout << endl;
}
void poker::Plum(int n)
{
    if (n == 1)
    {
        plum[0] = "***************";
        plum[1] = "* A           *";
        plum[2] = "*      *      *";
        plum[3] = "*     ***     *";
        plum[4] = "*    *****    *";
        plum[5] = "*   * *** *   *";
        plum[6] = "*  *** * ***  *";
        plum[7] = "* *********** *";
        plum[8] = "*  *** * ***  *";
        plum[9] = "*   * *** *   *";
        plum[10] = "*    *****    *";
        plum[11] = "*           A *";
        plum[12] = "***************";
    }
    else if (n >= 2 && n <= 9)
    {
        plum[0] = "***************";
        plum[1] = "* " + to_string(n) + "           *";
        plum[2] = "*      *      *";
        plum[3] = "*     ***     *";
        plum[4] = "*    *****    *";
        plum[5] = "*   * *** *   *";
        plum[6] = "*  *** * ***  *";
        plum[7] = "* *********** *";
        plum[8] = "*  *** * ***  *";
        plum[9] = "*   * *** *   *";
        plum[10] = "*    *****    *";
        plum[11] = "*           " + to_string(n) + " *";
        plum[12] = "***************";
    }
    else if (n == 10)
    {
        plum[0] = "***************";
        plum[1] = "*10           *";
        plum[2] = "*      *      *";
        plum[3] = "*     ***     *";
        plum[4] = "*    *****    *";
        plum[5] = "*   * *** *   *";
        plum[6] = "*  *** * ***  *";
        plum[7] = "* *********** *";
        plum[8] = "*  *** * ***  *";
        plum[9] = "*   * *** *   *";
        plum[10] = "*    *****    *";
        plum[11] = "*           10*";
        plum[12] = "***************";
    }
    else if (n == 11)
    {
        plum[0] = "***************";
        plum[1] = "* J           *";
        plum[2] = "*      *      *";
        plum[3] = "*     ***     *";
        plum[4] = "*    *****    *";
        plum[5] = "*   * *** *   *";
        plum[6] = "*  *** * ***  *";
        plum[7] = "* *********** *";
        plum[8] = "*  *** * ***  *";
        plum[9] = "*   * *** *   *";
        plum[10] = "*    *****    *";
        plum[11] = "*           J *";
        plum[12] = "***************";
    }
    else if (n == 12)
    {
        plum[0] = "***************";
        plum[1] = "* Q           *";
        plum[2] = "*      *      *";
        plum[3] = "*     ***     *";
        plum[4] = "*    *****    *";
        plum[5] = "*   * *** *   *";
        plum[6] = "*  *** * ***  *";
        plum[7] = "* *********** *";
        plum[8] = "*  *** * ***  *";
        plum[9] = "*   * *** *   *";
        plum[10] = "*    *****    *";
        plum[11] = "*           Q *";
        plum[12] = "***************";
    }
    else if (n == 13)
    {
        plum[0] = "***************";
        plum[1] = "* K           *";
        plum[2] = "*      *      *";
        plum[3] = "*     ***     *";
        plum[4] = "*    *****    *";
        plum[5] = "*   * *** *   *";
        plum[6] = "*  *** * ***  *";
        plum[7] = "* *********** *";
        plum[8] = "*  *** * ***  *";
        plum[9] = "*   * *** *   *";
        plum[10] = "*    *****    *";
        plum[11] = "*           K *";
        plum[12] = "***************";
    }
}
void poker::Rhombus(int n)
{
    if (n == 1)
    {
        rhombus[0] = "***************";
        rhombus[1] = "* A    *      *";
        rhombus[2] = "*     ***     *";
        rhombus[3] = "*    *****    *";
        rhombus[4] = "*   *******   *";
        rhombus[5] = "*  *********  *";
        rhombus[6] = "* *********** *";
        rhombus[7] = "*  *********  *";
        rhombus[8] = "*   *******   *";
        rhombus[9] = "*    *****    *";
        rhombus[10] = "*     ***     *";
        rhombus[11] = "*      *    A *";
        rhombus[12] = "***************";
    }
    else if (n >= 2 && n <= 9)
    {
        rhombus[0] = "***************";
        rhombus[1] = "* " + to_string(n) + "    *      *";
        rhombus[2] = "*     ***     *";
        rhombus[3] = "*    *****    *";
        rhombus[4] = "*   *******   *";
        rhombus[5] = "*  *********  *";
        rhombus[6] = "* *********** *";
        rhombus[7] = "*  *********  *";
        rhombus[8] = "*   *******   *";
        rhombus[9] = "*    *****    *";
        rhombus[10] = "*     ***     *";
        rhombus[11] = "*      *    " + to_string(n) + " *";
        rhombus[12] = "***************";
    }
    else if (n == 10)
    {
        rhombus[0] = "***************";
        rhombus[1] = "*10    *      *";
        rhombus[2] = "*     ***     *";
        rhombus[3] = "*    *****    *";
        rhombus[4] = "*   *******   *";
        rhombus[5] = "*  *********  *";
        rhombus[6] = "* *********** *";
        rhombus[7] = "*  *********  *";
        rhombus[8] = "*   *******   *";
        rhombus[9] = "*    *****    *";
        rhombus[10] = "*     ***     *";
        rhombus[11] = "*      *    10*";
        rhombus[12] = "***************";
    }
    else if (n == 11)
    {
        rhombus[0] = "***************";
        rhombus[1] = "* J    *      *";
        rhombus[2] = "*     ***     *";
        rhombus[3] = "*    *****    *";
        rhombus[4] = "*   *******   *";
        rhombus[5] = "*  *********  *";
        rhombus[6] = "* *********** *";
        rhombus[7] = "*  *********  *";
        rhombus[8] = "*   *******   *";
        rhombus[9] = "*    *****    *";
        rhombus[10] = "*     ***     *";
        rhombus[11] = "*      *    J *";
        rhombus[12] = "***************";
    }
    else if (n == 12)
    {
        rhombus[0] = "***************";
        rhombus[1] = "* Q    *      *";
        rhombus[2] = "*     ***     *";
        rhombus[3] = "*    *****    *";
        rhombus[4] = "*   *******   *";
        rhombus[5] = "*  *********  *";
        rhombus[6] = "* *********** *";
        rhombus[7] = "*  *********  *";
        rhombus[8] = "*   *******   *";
        rhombus[9] = "*    *****    *";
        rhombus[10] = "*     ***     *";
        rhombus[11] = "*      *    Q *";
        rhombus[12] = "***************";
    }
    else if (n == 13)
    {
        rhombus[0] = "***************";
        rhombus[1] = "* K    *      *";
        rhombus[2] = "*     ***     *";
        rhombus[3] = "*    *****    *";
        rhombus[4] = "*   *******   *";
        rhombus[5] = "*  *********  *";
        rhombus[6] = "* *********** *";
        rhombus[7] = "*  *********  *";
        rhombus[8] = "*   *******   *";
        rhombus[9] = "*    *****    *";
        rhombus[10] = "*     ***     *";
        rhombus[11] = "*      *    K *";
        rhombus[12] = "***************";
    }
}
void poker::Compassion(int n)
{
    if (n == 1)
    {
        compassion[0] = "***************";
        compassion[1] = "* A           *";
        compassion[2] = "*  ***   ***  *";
        compassion[3] = "* ***** ***** *";
        compassion[4] = "* *********** *";
        compassion[5] = "* *********** *";
        compassion[6] = "*  *********  *";
        compassion[7] = "*   *******   *";
        compassion[8] = "*    *****    *";
        compassion[9] = "*     ***     *";
        compassion[10] = "*      *      *";
        compassion[11] = "*           A *";
        compassion[12] = "***************";
    }
    else if (n >= 2 && n <= 9)
    {
        compassion[0] = "***************";
        compassion[1] = "* " + to_string(n) + "           *";
        compassion[2] = "*  ***   ***  *";
        compassion[3] = "* ***** ***** *";
        compassion[4] = "* *********** *";
        compassion[5] = "* *********** *";
        compassion[6] = "*  *********  *";
        compassion[7] = "*   *******   *";
        compassion[8] = "*    *****    *";
        compassion[9] = "*     ***     *";
        compassion[10] = "*      *      *";
        compassion[11] = "*           " + to_string(n) + " *";
        compassion[12] = "***************";
    }
    else if (n == 10)
    {
        compassion[0] = "***************";
        compassion[1] = "*10           *";
        compassion[2] = "*  ***   ***  *";
        compassion[3] = "* ***** ***** *";
        compassion[4] = "* *********** *";
        compassion[5] = "* *********** *";
        compassion[6] = "*  *********  *";
        compassion[7] = "*   *******   *";
        compassion[8] = "*    *****    *";
        compassion[9] = "*     ***     *";
        compassion[10] = "*      *      *";
        compassion[11] = "*           10*";
        compassion[12] = "***************";
    }
    else if (n == 11)
    {
        compassion[0] = "***************";
        compassion[1] = "* J           *";
        compassion[2] = "*  ***   ***  *";
        compassion[3] = "* ***** ***** *";
        compassion[4] = "* *********** *";
        compassion[5] = "* *********** *";
        compassion[6] = "*  *********  *";
        compassion[7] = "*   *******   *";
        compassion[8] = "*    *****    *";
        compassion[9] = "*     ***     *";
        compassion[10] = "*      *      *";
        compassion[11] = "*           J *";
        compassion[12] = "***************";
    }
    else if (n == 12)
    {
        compassion[0] = "***************";
        compassion[1] = "* Q           *";
        compassion[2] = "*  ***   ***  *";
        compassion[3] = "* ***** ***** *";
        compassion[4] = "* *********** *";
        compassion[5] = "* *********** *";
        compassion[6] = "*  *********  *";
        compassion[7] = "*   *******   *";
        compassion[8] = "*    *****    *";
        compassion[9] = "*     ***     *";
        compassion[10] = "*      *      *";
        compassion[11] = "*           Q *";
        compassion[12] = "***************";
    }
    else if (n == 13)
    {
        compassion[0] = "***************";
        compassion[1] = "* K           *";
        compassion[2] = "*  ***   ***  *";
        compassion[3] = "* ***** ***** *";
        compassion[4] = "* *********** *";
        compassion[5] = "* *********** *";
        compassion[6] = "*  *********  *";
        compassion[7] = "*   *******   *";
        compassion[8] = "*    *****    *";
        compassion[9] = "*     ***     *";
        compassion[10] = "*      *      *";
        compassion[11] = "*           K *";
        compassion[12] = "***************";
    }
}
void poker::Spade(int n)
{
    if (n == 1)
    {
        spade[0] = "***************";
        spade[1] = "* A    *      *";
        spade[2] = "*     ***     *";
        spade[3] = "*    *****    *";
        spade[4] = "*   *******   *";
        spade[5] = "*  *********  *";
        spade[6] = "* *********** *";
        spade[7] = "* *********** *";
        spade[8] = "* *********** *";
        spade[9] = "*  *** * ***  *";
        spade[10] = "*     ***     *";
        spade[11] = "*    *****  A *";
        spade[12] = "***************";
    }
    else if (n >= 2 && n <= 9)
    {
        spade[0] = "***************";
        spade[1] = "* " + to_string(n) + "    *      *";
        spade[2] = "*     ***     *";
        spade[3] = "*    *****    *";
        spade[4] = "*   *******   *";
        spade[5] = "*  *********  *";
        spade[6] = "* *********** *";
        spade[7] = "* *********** *";
        spade[8] = "* *********** *";
        spade[9] = "*  *** * ***  *";
        spade[10] = "*     ***     *";
        spade[11] = "*    *****  " + to_string(n) + " *";
        spade[12] = "***************";
    }
    else if (n == 10)
    {
        spade[0] = "***************";
        spade[1] = "*10    *      *";
        spade[2] = "*     ***     *";
        spade[3] = "*    *****    *";
        spade[4] = "*   *******   *";
        spade[5] = "*  *********  *";
        spade[6] = "* *********** *";
        spade[7] = "* *********** *";
        spade[8] = "* *********** *";
        spade[9] = "*  *** * ***  *";
        spade[10] = "*     ***     *";
        spade[11] = "*    *****  10*";
        spade[12] = "***************";
    }
    else if (n == 11)
    {
        spade[0] = "***************";
        spade[1] = "* J    *      *";
        spade[2] = "*     ***     *";
        spade[3] = "*    *****    *";
        spade[4] = "*   *******   *";
        spade[5] = "*  *********  *";
        spade[6] = "* *********** *";
        spade[7] = "* *********** *";
        spade[8] = "* *********** *";
        spade[9] = "*  *** * ***  *";
        spade[10] = "*     ***     *";
        spade[11] = "*    *****  J *";
        spade[12] = "***************";
    }
    else if (n == 12)
    {
        spade[0] = "***************";
        spade[1] = "* Q    *      *";
        spade[2] = "*     ***     *";
        spade[3] = "*    *****    *";
        spade[4] = "*   *******   *";
        spade[5] = "*  *********  *";
        spade[6] = "* *********** *";
        spade[7] = "* *********** *";
        spade[8] = "* *********** *";
        spade[9] = "*  *** * ***  *";
        spade[10] = "*     ***     *";
        spade[11] = "*    *****  Q *";
        spade[12] = "***************";
    }
    else if (n == 13)
    {
        spade[0] = "***************";
        spade[1] = "* K    *      *";
        spade[2] = "*     ***     *";
        spade[3] = "*    *****    *";
        spade[4] = "*   *******   *";
        spade[5] = "*  *********  *";
        spade[6] = "* *********** *";
        spade[7] = "* *********** *";
        spade[8] = "* *********** *";
        spade[9] = "*  *** * ***  *";
        spade[10] = "*     ***     *";
        spade[11] = "*    *****  K *";
        spade[12] = "***************";
    }
}