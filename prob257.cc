#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int main()
{
    int N, K;
    // ゲームの条件を読み込む
    cin >> N >> K;
    int value = 0;
    while (1) {
        int increment = (N - 1 - value) % (K + 1);
        // 仮に相手が自分の取りたい数字を取った場合、こちらはランダムな
        // 数字を宣言して様子を見る
        // （※プログラムが正しく動作していれば、以下のif文は実行されない
        // はず）
        if (increment == 0 && value != 0) {
            increment = (int) floor(rand() / (double) RAND_MAX * K) + 1;
        }
        cout << value + increment << endl;
        // 相手の数字を待つ
        cin >> value;
        // 相手が降参したらループを抜けてプログラム終了
        if (value >= N) {
            break;
        }
    }
    return 0;
}
