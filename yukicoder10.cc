#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int main()
{
    vector<int> numbers;
    numbers.push_back(1);
    numbers.push_back(1);
    numbers.push_back(2);
    int answer = 2;
    size_t hoge = 99999;
    for (size_t j = 0; j < pow(2, numbers.size() - 1); ++ j) {
        int result = numbers[0];
        for (size_t i = 0; i < numbers.size() - 1; ++ i) {
            if (j >> i & 0x01 == 1) result *= numbers[i + 1];
            else result += numbers[i + 1];
        }
        if (result == answer) {
            hoge = j;
            break;
        }
    }
    if (hoge == 99999) {
        cout << "no answer" << endl;
    } else {
        for (size_t i = 0; i < numbers.size() - 1; ++ i) {
            if (hoge >> i & 0x01 == 1) cout << "*";
            else cout << "+";
        }
        cout << endl;
    }

    return 0;
}
