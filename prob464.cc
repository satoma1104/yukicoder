#include <iostream>
#include <string>
using namespace std;

bool isAnagram(const string str)
{
    bool flag = true;
    for (size_t i = 0; i < str.size() / 2; ++ i) {
        if (str[i] != str[str.size() - i - 1]) {
            flag = false;
            break;
        }
    }
    return flag;
}

int main()
{
    string str;
    cin >> str;
    const size_t size = str.size();

    int counter = 0;
    for (size_t i = 1; i <= size - 3; ++ i) {
        for (size_t j = 1; j <= size - 3; ++ j) {
            for (size_t k = 1; k <= size - 3; ++ k) {
                if (i + j + k > size - 1) continue;
                const string p1 = str.substr(0, i);
                if (!isAnagram(p1)) continue;
                const string p2 = str.substr(i, j);
                if (!isAnagram(p2)) continue;
                const string p3 = str.substr(size - k);
                if (!isAnagram(p3)) continue;
                const string a = str.substr(i + j, size - (i + j + k));
#ifdef TEST
                cerr << "(" << p1 << ", " << p2 << ", " << a << ", " << p3
                     << ")" << endl;
#endif
                ++counter;
            }
        }
    }
    cout << counter << endl;
    return 0;
}
