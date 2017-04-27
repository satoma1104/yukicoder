#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class Weight
{
public:
    Weight() : value_(0)
    {
        id_ = count_;
        ++count_;
    }
    virtual ~Weight(){};
    int id() const { return id_; }
    int value() const { return value_; }
    void setID(int id) { id_ = id; }
    void setValue(int value) { value_ = value; }
private:
    int id_;
    int value_;
    static int count_;
};
int Weight::count_ = 1;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
double prob()
{
    return rand() / static_cast<double>(RAND_MAX);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
vector<Weight> initialize(const int n)
{
    srand(static_cast<unsigned int>(time(NULL)));
    vector<Weight> weights(n);
    vector<int> numbers(n);
    for (int i = 0; i < n; ++ i) {
        numbers[i] = i + 1;
    }
    for (int i = 0; i < n; ++ i) {
        int index = static_cast<int>(numbers.size() * prob());
        weights[i].setID(i + 1);
        weights[i].setValue(numbers[index]);
        numbers.erase(numbers.begin() + index);
    }
#ifdef TEST    
    for (int i = 0; i < n; ++ i) {
        cerr << "(i, weight) = (" << weights[i].id() << ", "
             << weights[i].value() << ")" << endl;
    }
#endif
    return weights;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
vector<int> ask(vector<Weight>& weights, bool odd = false)
{
    cout << "?";
    vector<int> numbers(weights.size() * 2, 0);
    int offset = odd ? 1 : 0;
    for (size_t i = 0; i < (weights.size() - offset) - (weights.size() - offset) % 2; ++ i) {
        numbers[i] = weights[i + offset].id();
    }
    for (size_t i = 0; i < numbers.size(); ++ i) {
        cout << " " << numbers[i];
    }        
    cout << endl;
#ifdef TEST
    cerr << "ask: " << ((odd) ? "odd" : "even") << endl;
#endif
    
    return numbers;
}

int findValue(const vector<Weight>& weights, const int id)
{
    int value = 0;
    for (size_t i = 0; i < weights.size(); ++ i) {
        if (weights[i].id() == id) {
            value = weights[i].value();
            break;
        }
    }
    return value;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
vector<string> getReply(vector<int>& numbers, const vector<Weight>& weights)
{
    // for test
    vector<string> reply(numbers.size() / 2, "");
    for (size_t i = 0; i < numbers.size() / 2; ++ i) {
        const size_t leftID = numbers[i * 2];
        const size_t rightID = numbers[i * 2 + 1];
        const int left = (leftID == 0) ? 0 : findValue(weights, leftID);
        const int right = (rightID == 0) ? 0 : findValue(weights, rightID);
        if (left < right) {
            reply[i] = "<";
        } else if (left > right) {
            reply[i] = ">";
        } else {
            reply[i] = "=";
        }
    }        
#ifdef TEST
    for (size_t i = 0; i < reply.size(); ++ i) {
        cerr << " " << reply[i];
    }
    cerr << endl;
#endif
    return reply;
}    

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void sort(vector<Weight>& weights, const vector<string>& reply, const bool odd)
{
    int offset = odd ? 1 : 0;
    for (size_t i = 0 ; i < (weights.size() - offset) - (weights.size() - offset) % 2; ++ i) {
        if (reply[i] == ">") {
            const size_t left = 2 * i + offset;
            const size_t right = 2 * i + 1 + offset;
            Weight tmp = weights[right];
            weights[right] = weights[left];
            weights[left] = tmp;
        }
    }
}

vector<string> execute(vector<Weight>& weights, bool odd)
{
    vector<int> numbers = ask(weights, odd);
    vector<string> reply = getReply(numbers, weights);
    sort(weights, reply, odd);
    return reply;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool check(const vector<string>& reply)
{
    bool finished = true;
    for (size_t i = 0; i < reply.size(); ++ i) {
        if (reply[i] == "=") break;
        if (reply[i] == ">") {
            finished = false;
            break;
        }
    }
    return finished;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main()
{
    // 
    int N;
    cin >> N;
    vector<Weight> weights = initialize(N);
    for (int i = 0; i < 1000; ++ i) {
        const bool even_result = check(execute(weights, false));
        const bool odd_result = check(execute(weights, true));
        if (even_result && odd_result) break;
    }
    cout << "!";
    for (size_t i = 0; i < weights.size(); ++ i) {
        cout << " " << weights[i].id();
    }
    cout << endl;
#ifdef TEST
    for (size_t i = 0; i < weights.size(); ++ i) {
        cerr << " " << weights[i].value();
    }
    cerr << endl;
#endif
    return 0;
}
