#include <iostream>
#include <cmath>
#ifdef TEST
#include <sstream>
#include <time.h>
#include <cstdlib>
#endif

using namespace std;
const int LENGTH_MAX = 1e9;
const int ASK_MAX = 100;

#ifdef TEST
int answer;
void showUsage()
{
    cerr << " 【引数】" << endl;
    cerr << " random: 正解をランダムに生成する" << endl;
    cerr << " min: 正解を最小値(10)にする" << endl;
    cerr << " max: 正解を最大値(1e9)にする" << endl;
    cerr << " その他の文字列: 整数と解釈して正解に設定する" << endl;
    exit(1);
}
#endif

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int ask(int val)
{
    cout << "? " << val << endl;
    int result;
#ifdef TEST
    if (val > answer) {
        result = -1;
    } else if (val < answer) {
        result = 1;
    } else {
        result = 0;
    }
    if (answer != 0) --answer;
#else
    cin >> result;
#endif
    return result;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main(int ac, char** av)
{
#ifdef TEST
    if (ac != 2) {
        cerr << "*** [Error] 引数を指定してください。 ***" << endl;
        showUsage();
    } else {
        string option(av[1]);
        if (option == "random") {
            // テスト用に正解をランダムに生成する
            srand(static_cast<unsigned int>(time(NULL)));
            const double prob = rand() / static_cast<double>(RAND_MAX);
            answer = static_cast<int>(prob * LENGTH_MAX);
            if (answer < 10) answer = 10;
        } else if (option == "min") {
            answer = 10;
        } else if (option == "max") {
            answer = LENGTH_MAX;
        } else {
            if (option[0] == '-') {
                cerr << "*** [Error] 負の数が指定されました。 ***" << endl;
                showUsage();
            }
            istringstream iss(option);
            iss >> answer;
        }
    }
#endif

    int solution = LENGTH_MAX / 2;
    double correction = solution;
    for (int n = 0; n < ASK_MAX; ++ n) {
        int result = ask(solution);
        if (result == 0) { // 等しい場合
            if (solution != 0) --solution;
            break;
        } else {
            correction /= 2;
            // 通常の２分探索に対して、探索範囲を下にずらす
            solution = solution + ((result > 0) ? 1 : -1) *
                static_cast<int>(ceil(correction)) - 1;
            if (solution < 0) solution = 0;
        }
    }
    cout << "! " << solution << endl;
#ifdef TEST
    cout << "### " << ((answer == solution) ? "OK" : "NG") << "! ###" << endl;
#endif
    return 0;
}
