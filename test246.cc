#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
const int MAXVALUE = 1e9;
const int MAX_LOOP = 100;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void showUsage()
{
    cerr << " 【引数】" << endl;
    cerr << " random: 正解をランダムに生成する" << endl;
    cerr << " min: 正解を最小値(1)にする" << endl;
    cerr << " max: 正解を最大値(1e9)にする" << endl;
    exit(1);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main(int ac, char** av)
{
    string query;

    int answer = 0;

    if (ac < 2) {
        cerr << "*** [Error] 引数を指定してください。 ***" << endl;
        showUsage();
    } else {
        string option(av[1]);
        if (option == "random") {
            // テスト用に正解をランダムに生成する
            srand((unsigned int) time(NULL));
            answer = static_cast<int>((rand() / (double) RAND_MAX) * MAXVALUE);
        } else if (option == "min") {
            answer = 1;
        } else if (option == "max") {
            answer = MAXVALUE;
        } else {
            cerr << "*** [Error] 不正な引数が指定されました。 ***" << endl;
            showUsage();
        }
    }

    for (int i = 0; i < MAX_LOOP; ++ i) {
        int value;
        cin >> query >> value;
        if (query == "?") {
            if (answer >= value) {
                cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
        } else if (query == "!") {
            cout << "### answer = " << answer << endl;
            if (answer == value) {
                cout << "### OK! ###" << endl;
            } else {
                cout << "### NG! ###" << endl;
            }
            break;
        } else {
            cerr << "*** [Error] 不正なクエリです。 ***" << endl;
            return EXIT_FAILURE;
        }
        if (i == MAX_LOOP - 1) {
            cerr << "*** [Error] 規程の回数を越えました。 ***" << endl;
            return EXIT_FAILURE;
        }
    }

    return 0;
}
