#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int number;
    cin >> number;
    double result = 1;
    double threshold = 1e9 + 7;
    for (int i = 0; i < number; ++ i) {
        result *= (i + 1);
        if (result > threshold) {
            result = result - floor(result / threshold) * threshold;
        }
    }
    cout << static_cast<int>(result) << endl;
    return 0;
}
