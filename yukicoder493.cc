#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;
const int N = 100;

//------------------------------------------------------------------------------
// K=n のときの文字列f(K)の長さを求める関数（n < 10^9）
//------------------------------------------------------------------------------
double calLength(int n)
{
    assert(n >= 0);
    if (n == 0) return 0;
    if (n < 4) {
        return pow(2, n) - 1;
    }        
    const double number = static_cast<double>(n);
    const int beta = static_cast<int>(floor(log(number * number) / log(10) + 1));
    const int alpha = static_cast<int>(ceil(sqrt(pow(10, beta - 1)))) - 1;
    const double tmp = pow(2.0, n - alpha);
    return tmp * calLength(alpha) + beta * (tmp - 1);
}

//------------------------------------------------------------------------------
// K=n のときの文字列f(K)の長さを求める関数（※n-1回の再帰をするので注意）
//------------------------------------------------------------------------------
double calLengthTest(int n)
{
    assert(n > 0);
    if (n == 1) return 1;
    const double length = floor(log(n * n) / log(10) + 1);
    return calLengthTest(n - 1) * 2 + length;
}

//------------------------------------------------------------------------------
// 数列f(K)の和を計算する
//------------------------------------------------------------------------------
// 【引数】
// n: Kの値
//------------------------------------------------------------------------------
int calSum(int n)
{
    assert(n >= 0);
    if (n == 0) return 0;
    if (n == 1) return 1;
    int power2 = n * n;
    int sum = 0;
    // 数列のKの２乗部分については、１の位の数から順番に和をとる
    do {
        const int digit = power2 % 10;        // 一桁の値
        if (digit == 0) sum += 10;
        else sum += digit;
        power2 /= 10;
    } while (power2 > 0);
    // Kの２乗部分の和と、その両側の数列f(K-1)の和を足したものが、求めるべき値
    return calSum(n - 1) * 2 + sum;
}

double calModulus(double val)
{
    const double modulus = val - 1000000007 * floor(val / 1000000007.0);
    return static_cast<int>(modulus);
}

//------------------------------------------------------------------------------
// 数列f(K)の積を計算する
//------------------------------------------------------------------------------
// 【引数】
// n: Kの値
//------------------------------------------------------------------------------
int calMul(int n)
{
    assert(n >= 0);
    if (n == 0) return 1;
    if (n == 1) return 1;
    int power2 = n * n;
    double mul = 1;
    // 数列のKの２乗部分については、１の位の数から順番に積を計算する
    do {
        const int digit = power2 % 10;
        if (digit == 0) mul *= 10;
        else mul *= digit;
        power2 /= 10;
    } while (power2 > 0);
    // Kの２乗部分の積と、その両側の数列f(K-1)の積を掛けた値に対して、
    // 1000000007で割った余りが求めるべき値
    const double calmul = calMul(n - 1);
    return static_cast<int>(calModulus(calmul * calmul * mul));
}

//------------------------------------------------------------------------------
// 数列の先頭からpos番目までの和を計算する
//------------------------------------------------------------------------------
double calTotalSum(double pos)
{
    assert(pos >= 0);
    if (pos == 0) return 0;
    double sum = 0;
    int count = 1;
    // 数列の和を、長さがpos以下の数列の中で最大のf(K)の和と、それ以外の和に
    // 分けて計算する
    while (1) {
        double length = calLength(count);
        // cout << "pos, i, length = " << pos << ", " << count << ", " << length << endl;
        if (length > pos - 1) {
            sum += calSum(count - 1);
            double power2 = count * count;
            int power2length = static_cast<int>(floor(log(power2) / log(10) + 1));
            int subcount = 0;
            // 2乗部分の和を計算する
            while (subcount < min((double) power2length, pos - calLength(count - 1))) {
                int val = static_cast<int>(power2 / pow(10, power2length - 1 - subcount));
                // cout << "val = " << val << endl;
                if (val == 0) sum += 10;
                else sum += val;
                power2 -= val * pow(10, power2length - 1 - subcount);
                ++subcount;
            }
            sum += calTotalSum(pos - calLength(count - 1) - subcount); 
            break;
        }
        ++count;
    }
    return sum;
}

//------------------------------------------------------------------------------
// 数列の先頭からpos番目までの積を計算する
//------------------------------------------------------------------------------
double calTotalMul(double pos)
{
    assert(pos >= 0);
    if (pos == 0) return 1;
    double mul = 1;
    int count = 1;
    // 数列の積を、長さがpos以下の数列の中で最大のf(K)の積と、それ以外の積に
    // 分けて計算する
    while (1) {
        double length = calLength(count);
        if (length > pos - 1) {
            mul *= calMul(count - 1);
            double power2 = count * count;
            int power2length = static_cast<int>(floor(log(power2) / log(10) + 1));
            int subcount = 0;
            // 2乗部分の積を計算する
            while (subcount < min((double) power2length, pos - calLength(count - 1))) {
                int val = static_cast<int>(power2 / pow(10, power2length - 1 - subcount));
                if (val == 0) mul *= 10;
                else mul *= val;
                power2 -= val * pow(10, power2length - 1 - subcount);
                ++subcount;
            }
            mul *= calTotalMul(pos - calLength(count - 1) - subcount); 
            break;
        }
        ++count;
    }
    
    return mul;
}

//------------------------------------------------------------------------------
// メインルーチン
//------------------------------------------------------------------------------
int main()
{
    // 数列のp番目からq番目の和をとるときには、数列の先頭からq番目までの和から、
    // 同じく数列の先頭からp-1番目の和を引く。
    cout << "sum = " << calTotalSum(7) - calTotalSum(1 - 1) << endl;
    cout << "sum = " << calTotalSum(19) - calTotalSum(12 - 1) << endl;
    cout << "sum = " << calTotalSum(515) - calTotalSum(510 - 1) << endl;
    cout << "sum = " << calTotalSum(19e8) - calTotalSum(19e8 - 1) << endl;
    // 数列のp番目からq番目の積をとるときには、数列の先頭からq番目までの積を、
    // 同じく数列の先頭からp-1番目の積で割る。
    cout << "mul = " << calModulus(calTotalMul(7) / calTotalMul(1 - 1)) << endl;
    cout << "mul = " << calModulus(calTotalMul(19) / calTotalMul(12 - 1)) << endl;
    cout << "mul = " << calModulus(calTotalMul(515) / calTotalMul(510 - 1)) << endl;
    cout << "mul = " << calModulus(calTotalMul(19e8) / calTotalMul(19e8 - 1)) << endl;
    
    return 0;
}
