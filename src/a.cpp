#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, N) for(int i = 0; i < int(N); ++i)
#define rep1(i, N) for(int i = 1; i < int(N); ++i)
#define all(a) (a).begin(), (a).end()
#define bit(k) (1LL << (k))
#define SUM(v) accumulate(all(v), 0LL)

typedef pair<int, int> P;
typedef pair<ll, ll> l_l;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;
struct fast_ios {
    fast_ios() {
        cin.tie(0);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(20);
    };
} fast_ios_;

template <class T> inline bool chmax(T &a, T b) {
    if(a < b) {
        a = b;
        return true;
    }
    return false;
}
template <class T> inline bool chmin(T &a, T b) {
    if(a > b) {
        a = b;
        return true;
    }
    return false;
}

#define TOSTRING(x) string(#x)
template <typename T> istream &operator>>(istream &is, vector<T> &vec) {
    for(T &x : vec)
        is >> x;
    return is;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for(auto _ : v)
        os << _ << ", ";
    os << "]";
    return os;
};
template <typename T> ostream &operator<<(ostream &os, set<T> &st) {
    os << "(";
    for(auto _ : st) {
        os << _ << ", ";
    }
    os << ")";
    return os;
}
template <typename T> ostream &operator<<(ostream &os, multiset<T> &st) {
    os << "(";
    for(auto _ : st) {
        os << _ << ", ";
    }
    os << ")";
    return os;
}
template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
    os << "{" << p.first << ", " << p.second << "}";
    return os;
}
template <typename T, typename U>
ostream &operator<<(ostream &os, const map<T, U> &mp) {
    os << "[";
    for(auto _ : mp) {
        os << _ << ", ";
    }
    os << "]";
    return os;
}

#define DUMPOUT cerr
void dump_func() { DUMPOUT << endl; }
template <class Head, class... Tail>
void dump_func(Head &&head, Tail &&...tail) {
    DUMPOUT << head;
    if(sizeof...(Tail) > 0) {
        DUMPOUT << ", ";
    }
    dump_func(std::move(tail)...);
}

#ifdef DEBUG
#define dbg(...)                                                               \
    { dump_func(__VA_ARGS__) }
#define dump(...)                                                              \
    DUMPOUT << string(#__VA_ARGS__) << ": ";                                   \
    dump_func(__VA_ARGS__)
#else
#define dbg(...)
#define dump(...)
#endif

const int INF = (ll)1e9;
const ll INFLL = (ll)1e18 + 1;

constexpr int MAX_TASK_NUM = 1000;
constexpr int MAX_SKILL_NUM = 20;
int requiredSkills[MAX_TASK_NUM][MAX_SKILL_NUM];

class Task {
  public:
    int id;
    bool stillWorked;
    bool isCompleted;
    vector<int> dependency;
    Task(int _id, const vector<int> &_dependency)
        : id(_id), stillWorked(false), isCompleted(false),
          dependency(_dependency) {}

    void setCompleted() {
        stillWorked = false;
        isCompleted = true;
    }
};

class Member {
  public:
    int id;
    vector<int> estimatedSkillLevels;
    vector<int> assignedTasks;
    vector<int> assignedDay;
    vector<int> freeedDay;
    bool assigned;
    Member(int _id) : id(_id), assigned(false) {}

    bool isAssigned() { return assigned; }

    bool isFree() { return !assigned; }

    void assignTask(const Task &task, int day) {
        dump("Assign task", day, task.id, this->id);
        assignedTasks.emplace_back(task.id);
        assignedDay.emplace_back(day);
        assigned = true;
    }

    void freeFromTask(int day) {
        assigned = false;
        freeedDay.emplace_back(day);
    }
};

class Solver {
  public:
    int taskNum;
    int memberNum;
    int skillNum;
    int dependencyNum;
    vector<Member> members;
    vector<Task> tasks;
    Solver(int _taskNum, int _memberNum, int _skillNum, int _dependencyNum)
        : taskNum(_taskNum), memberNum(_memberNum), skillNum(_skillNum),
          dependencyNum(_dependencyNum) {}
    vector<P> solve(int day) {
        vector<P> res;
        for(Task &task : tasks) {
            if(isAssignable(task)) {
                for(Member &member : members) {
                    if(!member.isAssigned()) {
                        member.assignTask(task, day);
                        task.stillWorked = true;
                        res.emplace_back(member.id, task.id);
                        break;
                    }
                }
            }
        }
        return res;
    }

    // memberIdに割り当てられていたtaskをcompletedにする
    void setCompleted(int memberId, int day) {
        members[memberId].freeFromTask(day);
        int completedTaskId = members[memberId].assignedTasks.back();
        tasks[completedTaskId].setCompleted();
    }

    // for initialization
    void setMember(int memberId) { members.emplace_back(Member(memberId)); }

    // for initialization
    void setTask(int taskId, const vector<int> &dependency) {
        tasks.emplace_back(Task(taskId, dependency));
    }

    bool isAssignable(Task &task) {
        if(task.stillWorked || task.isCompleted) {
            return false;
        }
        for(int taskId : task.dependency) {
            if(!tasks[taskId].isCompleted) {
                return false;
            }
        }
        return true;
    }
};

// Input per day from judge server.
vector<int> getCompletedMemberIds() {
    int num;
    cin >> num;
    if(num == -1) {
        return vector<int>(1, -1);
    }
    vector<int> completedMemberIds(num);
    for(int i = 0; i < num; i++) {
        cin >> completedMemberIds[i];
        completedMemberIds[i]--;
    }
    return completedMemberIds;
}

void output(const vector<P> &out) {
    dump(out);
    cout << out.size();
    if(out.empty()) {
        cout << endl;
        return;
    }
    cout << ' ';
    for(int i = 0; i < (int)out.size(); i++) {
        cout << out[i].first + 1 << ' ' << out[i].second + 1;
        if(i == (int)out.size() - 1) {
            cout << endl;
        } else {
            cout << ' ';
        }
    }
}

// valiable for input.
vector<int> _taskDependency[MAX_TASK_NUM]; // taskDependency[i]:
                                           // iの前に完了するべきタスクのリスト
int main() {
    // input
    int taskNum;   // = 1000
    int memberNum; // = 20;
    int skillNum;  // 10 - 20
    int dependNum; // 1000 - 3000
    cin >> taskNum >> memberNum >> skillNum >> dependNum;
    for(int i = 0; i < taskNum; i++) {
        for(int j = 0; j < skillNum; j++) {
            cin >> requiredSkills[i][j];
        }
    }
    for(int i = 0; i < dependNum; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        _taskDependency[v].emplace_back(u);
    }
    // initialize Solver.
    Solver aSolver(taskNum, memberNum, skillNum, dependNum);
    {
        // initialize members
        for(int memberId = 0; memberId < memberNum; memberId++) {
            aSolver.setMember(memberId);
        }
        // initialize tasks
        for(int taskId = 0; taskId < taskNum; taskId++) {
            aSolver.setTask(taskId, _taskDependency[taskId]);
        }
    }

    // iterate
    int day = 1;
    while(true) {
        vector<P> assignList = aSolver.solve(day);
        output(assignList);
        vector<int> completedMemberIds = getCompletedMemberIds();
        dump(day);
        dump(assignList);
        dump(completedMemberIds);
        if(completedMemberIds.size() == 1 && completedMemberIds[0] == -1) {
            break;
        }
        //
        for(int memberId : completedMemberIds) {
            aSolver.setCompleted(memberId, day);
        }
        day++;
    }
    return 0;
}
