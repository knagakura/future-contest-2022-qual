#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,N) for(int i=0;i<int(N);++i)
#define rep1(i,N) for(int i=1;i<int(N);++i)
#define all(a) (a).begin(),(a).end()
#define bit(k) (1LL<<(k))
#define SUM(v) accumulate(all(v), 0LL)

typedef pair<int, int> P;
typedef pair<ll, ll> l_l;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;
struct fast_ios{ fast_ios(){ cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; }fast_ios_;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define TOSTRING(x) string(#x)
template <typename T> istream &operator>>(istream &is, vector<T> &vec) { for (T &x : vec) is >> x; return is; }
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) { os  << "["; for(auto _: v) os << _ << ", "; os << "]"; return os; };
template <typename T> ostream &operator<<(ostream &os, set<T> &st) { os << "("; for(auto _: st) { os << _ << ", "; } os << ")";return os;}
template <typename T> ostream &operator<<(ostream &os, multiset<T> &st) { os << "("; for(auto _: st) { os << _ << ", "; } os << ")";return os;}
template <typename T, typename U> ostream &operator<<(ostream &os, const pair< T, U >& p){os << "{" <<p.first << ", " << p.second << "}";return os; }
template <typename T, typename U> ostream &operator<<(ostream &os, const map<T, U> &mp){ os << "["; for(auto _: mp){ os << _ << ", "; } os << "]"; return os; }

#define DUMPOUT cerr
void dump_func(){ DUMPOUT << endl; }
template <class Head, class... Tail> void dump_func(Head &&head, Tail &&... tail) { DUMPOUT << head; if (sizeof...(Tail) > 0) { DUMPOUT << ", "; } dump_func(std::move(tail)...); }

#ifdef DEBUG
#define dbg(...) { dump_func(__VA_ARGS__) }
#define dump(...) DUMPOUT << string(#__VA_ARGS__) << ": "; dump_func(__VA_ARGS__)
#else
#define dbg(...)
#define dump(...)
#endif

const int INF = (ll)1e9;
const ll INFLL = (ll)1e18+1;

/*
const int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
const int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
const string dir = "DRUL";
*/

int taskNum, memberNum, skillNum, dependNum;
int taskSkills[1000][20];
class Solver {
  public:
    Solver(){}

    vector<P> solve(int day) {
        vector<P> res;
        if(day == 1) {
            return vector<P>(1, {1, 1});
        }
        return res;
    }
};

void initialInput() {
    cin >> taskNum >> memberNum >> skillNum >> dependNum;
    for (int i = 0; i < taskNum; i++) {
        for (int j = 0; j < skillNum; j++) {
            cin >> taskSkills[i][j];
        }
    }
    for (int i = 0; i < dependNum; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
    }
}

vector<int> dayInput() {
    int num;
    cin >> num;
    if(num == -1) {
        return vector<int>(1, -1);
    }
    vector<int> in(num);
    for (int i = 0; i < num; i++){
        cin >> in[i];
    }
    return in;
}

void output(const vector<P> &out) {
    dump(out);
    cout << out.size();
    if(out.empty()){
        cout << endl;
        return;
    }
    cout << ' ';
    for (int i = 0; i < (int)out.size(); i++) {
        cout << out[i].first << ' ' << out[i].second;
        if (i == (int)out.size() - 1) {
            cout << endl;
        } else {
            cout << ' ';
        }
    }
}
int main() {
    Solver aSolver;

    initialInput();
    int day = 1;
    while(true) {
        vector<P> out = aSolver.solve(day);
        output(out);
        vector<int> in = dayInput();
        dump(day, out, in);
        if((int)in.size() == 1 && in[0] == -1) {
            return 0;
        }
        day++;
    }
}
