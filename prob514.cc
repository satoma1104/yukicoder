#include <iostream>
#include <cstdlib>
#include <cmath>
#ifdef TEST
#include <sstream>
#endif
using namespace std;
const int MAXPOS = 1000000000;
const int MAX_ITER = 100;
int X_ANS;
int Y_ANS;

int getDistance(const int x, const int y)
{
    cout << x << " " << y << endl;
    int distance;
#ifdef TEST
    distance = fabs(x - X_ANS)+ fabs(y - Y_ANS);
#else
    cin >> distance;
#endif
    if (distance == 0) {
#ifdef TEST
        cout << "OK!" << endl;
#endif
        exit(0);
    }
    return distance;
}

int main(int ac, char** av)
{
#ifdef TEST
    if (ac != 3) {
        cerr << "コマンドラインオプションで正解座標を与えて下さい。" << endl;
        exit(1);
    }
    istringstream xsin(av[1]);
    istringstream ysin(av[2]);
    xsin >> X_ANS;
    ysin >> Y_ANS;
#endif
    int x = MAXPOS / 2;
    int y = MAXPOS / 2;
    int base_distance = getDistance(x, y);
    int distance1 = getDistance(x + base_distance, y);
    int distance2 = getDistance(x - base_distance, y);
    if (distance1 == distance2) {
        getDistance(x, y + distance1);
        getDistance(x, y - distance1);
    } else {
        if (distance1 < distance2) {
            const int diff = distance1 / 2;
            getDistance(x + base_distance - diff, y + diff);
            getDistance(x + base_distance - diff, y - diff);
        } else {
            const int diff = distance2 / 2;
            getDistance(x - base_distance + diff, y + diff);
            getDistance(x - base_distance + diff, y - diff);
        }
    }

    return 0;
}
