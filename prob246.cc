#include <iostream>
#include <cmath>
#ifdef TEST
#include <cstdlib>
#include <time.h>
#include <string>
#endif
using namespace std;
const int MAXVAL = 1000000000;

#ifdef TEST
void showUsage()
{
    cerr << " 【引数】" << endl;
    cerr << " random: 正解をランダムに生成する" << endl;
    cerr << " min: 正解を最小値(1)にする" << endl;
    cerr << " max: 正解を最大値(1e9)にする" << endl;
    exit(1);
}
#endif

int main(int ac, char** av)
{
#ifdef TEST
    int answer = 0;
    if (ac != 2) {
        cerr << "*** [Error] 引数を指定してください。 ***" << endl;
        showUsage();
    } else {
        string option(av[1]);
        if (option == "random") {
            // テスト用に正解をランダムに生成する
            srand((unsigned int) time(NULL));
            answer = static_cast<int>((rand() / (double) RAND_MAX) * MAXVAL);
        } else if (option == "min") {
            answer = 1;
        } else if (option == "max") {
            answer = MAXVAL;
        } else {
            cerr << "*** [Error] 不正な引数が指定されました。 ***" << endl;
            showUsage();
        }
    }
#endif
    // 推定解（初期値は最大数の半分）
    int solution = MAXVAL / 2;
    // 推定解の修正量（初期値は推定解と等しい）
    double correctionAmount = solution;
    while (1) {
        // 質問クエリの出力
        cout << "? " << solution << endl;
        cout.flush();
        int result;
#ifdef TEST
        result = (answer >= solution) ? 1 : 0; //+++ for test
#else
        cin >> result;
#endif
        // 修正量を半分にする
        correctionAmount /= 2.0;
        // 修正量が１未満になったらもう探索をする必要がない
        if (correctionAmount < 1) {
            // resultが０の時は、今の数より１小さい数が正解となる
            // resultが１の時は、今の数が正解になっている
            if (result == 0) --solution;
            break;
        }
        correctionAmount = ceil(correctionAmount);
        if (result == 1) {
            solution = solution + correctionAmount;
        } else {
            solution = solution - correctionAmount;
        }
    }
    // 回答クエリの出力
    cout << "! " << solution << endl;
#ifdef TEST
    cout << ((answer == solution) ? "OK!" : "NG!") << endl;
#endif
    return 0;
}
