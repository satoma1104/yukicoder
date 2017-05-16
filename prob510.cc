#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
const double DIVISOR = 1.0e9 + 7;

double getDoubleModulus(const double value)
{
    double quotient = floor(value / DIVISOR);
    return value - quotient * DIVISOR;
}

int calAnswer(const vector<double>& x, const vector<double>& y, const int number)
{
    double a = 1;
    double b = 1;
    for (int i = 0; i < number; ++ i) {
        a = getDoubleModulus(x[i] * getDoubleModulus(b * b)) + a;
        b = getDoubleModulus(y[i] * b) + 1;
    }
    return static_cast<int>(getDoubleModulus(a));
}


int main()
{
    int n;
    int q;
    cin >> n >> q;
    vector<double> x(n, 0);
    vector<double> y(n, 0);
    int ai;
    
    for (int i = 0; i < q; ++ i) {
        string query;
        cin >> query;
        if (query == "a") {
            cin >> ai;
            cout << calAnswer(x, y, ai) << endl;
        } else {
            int index, value;
            cin >> index >> value;
            if (query == "x") {
                x[index] = value;
            } else if (query == "y") {
                y[index] = value;
            }
        }
    }
    return 0;
}
