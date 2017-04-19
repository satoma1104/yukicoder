#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class Node
{
public:
    Node() : count_(0){};
    virtual ~Node(){};
    void connect(int id) { connection_.push_back(id); }
    const vector<int>& getConnection() const { return connection_; }
    void count() { ++count_; }
    int getCount() { return count_; }
private:
    int count_;
    vector<int> connection_;
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class NodeManager
{
public:
    NodeManager(const string filename)
    {
        ifstream fin(filename.c_str());
        int number;
        fin >> number;
        vector<Node> villages(number);
        // make connection information
        for (int n = 0; n < number - 1; ++ n) {
            int src, dst;
            fin >> src >> dst;
            nodes_[src]->connect(dst);
            nodes_[dst]->connect(src);
        }
    }
    virtual ~NodeManager(){};
private:
    vector<Node*> nodes_;
};



bool search(vector<Node>& villages, vector<int>& path, int pos, int goal)
{
    path.push_back(pos);
    // 目的地が見つかったらtrueを返す
    if (pos == goal) {
        return true;
    }
    const vector<int>& connection = villages[pos].getConnection();
    // 各ルートを探索
    for (size_t n = 0; n < connection.size(); ++ n) {
        int next = connection[n];
        bool flag = false;
        // 自分自身には戻ってはいけない
        for (size_t j = 0; j < path.size(); ++ j) {
            if (next == path[j]) {
                flag = true;
            }
        }
        if (flag) continue;
        else {
            // 次の接続先を探索
            bool b = search(villages, path, next, goal);
            // 目的地が見つかったらtrue
            if (b) return true;
            // 見つかっていなければ次のルートを探索
        }
    }
    // 目的地が見つからないまま探索先がなくなったらfalseを返す
    path.pop_back();
    return false;
}

int main()
{
    vector<int> path;
    fin >> number;
    for (int i = 0; i < number; ++ i) {
        path.clear();
        int src, dst;
        fin >> src >> dst;
        search(villages, path, src, dst);
        for (int n = 0; n < path.size(); ++ n) {
            villages[path[n]].count();
        }
    }
    int total = 0;
    for (int n = 0; n < villages.size(); ++ n) {
        int count = villages[n].getCount();
        total += count * (count + 1) / 2;
    }

    cout << total << endl;

    return 0;
}
