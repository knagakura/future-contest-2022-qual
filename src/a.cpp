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

uint32_t rnd(void) {
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    static uint32_t w = 88675123;
    uint32_t t;

    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

class Task {
  public:
    int id;
    int assignedDay;
    int completedDay;
    bool stillWorked;
    bool isCompleted;
    vector<double> requiredSkills;
    double skillSum;
    vector<int> dependency;
    vector<int> dependencyCompleted;
    double uncompletedDependedSkillSum;
    Task(int _id, const vector<double> &_requiredSkills,
         const vector<int> &_dependency)
        : id(_id), assignedDay(-1), completedDay(-1), stillWorked(false),
          isCompleted(false), requiredSkills(_requiredSkills),
          dependency(_dependency), dependencyCompleted(0),
          uncompletedDependedSkillSum(0.0) {
        this->skillSum =
            accumulate(requiredSkills.begin(), requiredSkills.end(), 0.0);
    }

    void setCompleted(int day) {
        this->stillWorked = false;
        this->isCompleted = true;
        this->completedDay = day;
    }

    void setAssigned(int day) {
        this->stillWorked = true;
        this->assignedDay = day;
    }

    int dependencyRemained() const {
        return (int)dependency.size() - (int)dependencyCompleted.size();
    }

    bool isAssigned() const { return this->stillWorked || this->isCompleted; }

    bool isAssignable() {
        if(isAssigned()) {
            return false;
        }
        return dependencyRemained() == 0;
    }

    void addDependencyCompleted(const Task &dependedTask) {
        this->dependencyCompleted.emplace_back(dependedTask.id);
        this->uncompletedDependedSkillSum -= dependedTask.skillSum;
    }

    void addUncompletedDependedSkillSum(const Task &task) {
        this->uncompletedDependedSkillSum += task.skillSum;
    }
};

class Member {
  public:
    int id;
    vector<double> estimatedSkills;
    vector<double> minEstimatedSkills;
    vector<int> assignedTaskIds;
    bool assigned;
    Member() {}
    Member(int _id, int skillNum) : id(_id), assigned(false) {
        estimatedSkills.assign(skillNum, 0.0);
        minEstimatedSkills.assign(skillNum, 0.0);
    }

    bool isAssigned() { return assigned; }

    bool isFree() { return !assigned; }

    void assignTask(const Task &task) {
        assignedTaskIds.emplace_back(task.id);
        assigned = true;
    }

    void freeFromTask() { assigned = false; }
};

class Solver {
  public:
    int taskNum;
    int memberNum;
    int skillNum;
    int dependencyNum;
    vector<Member> members;
    vector<Task> tasks;
    int taskId2Index[MAX_TASK_NUM];
    int taskDistance[MAX_TASK_NUM][MAX_TASK_NUM];
    vector<vector<int>> dependencyGraph;
    Solver(int _taskNum, int _memberNum, int _skillNum, int _dependencyNum,
           const vector<vector<int>> &_dependencyGraph)
        : taskNum(_taskNum), memberNum(_memberNum), skillNum(_skillNum),
          dependencyNum(_dependencyNum), dependencyGraph(_dependencyGraph) {
        for(int i = 0; i < taskNum; i++) {
            taskId2Index[i] = i;
        }
    }
    vector<P> solve(const int day) {
        for(int i = 0; i < taskNum; i++) {
            taskId2Index[tasks[i].id] = i;
        }
        int neetMemberCnt = 0;
        for(const Member &member : members) {
            neetMemberCnt += !member.assigned;
        }
        int remainedTaskCnt = 0;
        for(const Task &task : tasks) {
            remainedTaskCnt += !task.isAssigned();
        }
        dump(day, neetMemberCnt, remainedTaskCnt);
        int rootTaskCnt = 0;
        int leafTaskCnt = 0;
        int independedTaskCnt = 0;
        int independedUnassignedTaskCnt = 0;
        for(Task &task : tasks) {
            if(isLeafTask(task)) {
                leafTaskCnt++;
            }
            if(isRootTask(task)) {
                rootTaskCnt++;
            }
            if(isIndependedTask(task)) {
                independedTaskCnt++;
                if(!task.isAssigned()) {
                    independedUnassignedTaskCnt++;
                }
            }
        }
        dump(rootTaskCnt, leafTaskCnt, independedTaskCnt,
             independedUnassignedTaskCnt);
        vector<P> res;
        for(Member &member : members) {
            if(!member.isAssigned()) {
                double minCost = INF;
                int minTaskId = -1;
                bool allAssigned = true;
                for(Task &task : tasks) {
                    if(!task.isAssigned()) {
                        allAssigned = false;
                    }
                    if(task.isAssignable()) {
                        double estimatedCost = calcCost(member, task);
                        if(!isLeafTask(task)) {
                            if(remainedTaskCnt < 200) {
                                estimatedCost -= 1000;
                            } else {
                                estimatedCost = 0;
                            }
                        }
                        if(chmin(minCost, estimatedCost)) {
                            minTaskId = task.id;
                        }
                    }
                }
                if(minTaskId != -1) {
                    int minIndex = taskId2Index[minTaskId];
                    member.assignTask(tasks[minIndex]);
                    tasks[minIndex].setAssigned(day);
                    res.emplace_back(member.id, tasks[minIndex].id);
                } else if(not allAssigned) {
                    dump("????????????????????????");
                }
            }
        }
        return res;
    }

    // memberId??????????????????????????????task???completed?????????
    void setCompleted(int memberId, int day) {
        members[memberId].freeFromTask();
        int completedTaskId = members[memberId].assignedTaskIds.back();
        Task &completedTask = tasks[taskId2Index[completedTaskId]];
        completedTask.setCompleted(day);
        for(int nxtTaskId : dependencyGraph[completedTaskId]) {
            tasks[taskId2Index[nxtTaskId]].addDependencyCompleted(
                completedTask);
        }
    }

    // for initialization
    void setMember(int memberId) {
        members.emplace_back(Member(memberId, skillNum));
    }

    // for initialization
    void setTask(int taskId, const vector<double> &requiredSkills,
                 const vector<int> &dependency) {
        tasks.emplace_back(Task(taskId, requiredSkills, dependency));
    }

    void setTaskDependencies() {
        for(Task &task : tasks) {
            for(int dependedTaskIds : task.dependency) {
                task.addUncompletedDependedSkillSum(
                    tasks[taskId2Index[dependedTaskIds]]);
            }
        }
    }

    double calcCost(const Member &member, const Task &task) {
        double res = 0;
        for(int skillIndex = 0; skillIndex < skillNum; skillIndex++) {
            res += max(0.0, task.requiredSkills[skillIndex] -
                                member.estimatedSkills[skillIndex]);
        }
        return res;
    }

    void estimate(int memberId) {
        int completedTaskId = members[memberId].assignedTaskIds.back();
        _estimate(members[memberId], tasks[taskId2Index[completedTaskId]]);
        _estimate2(members[memberId], tasks[taskId2Index[completedTaskId]]);
        return;
    }

    void outEstimate(int memberId) {
        cout << "#s"
             << " " << memberId + 1 << " ";
        for(double x : members[memberId].estimatedSkills) {
            cout << (int)x << " ";
        }
        cout << endl;
    }

  private:
    void _estimate(Member &member, const Task &task) {
        int taskTime = task.completedDay - task.assignedDay + 1;

        if(task.skillSum <= 40 && taskTime <= max(4.0, task.skillSum / 10)) {
            for(int i = 0; i < skillNum; i++) {
                chmax(member.minEstimatedSkills[i], task.requiredSkills[i]);
            }
        } else if(task.skillSum > 40 &&
                  taskTime <= max(4.0, task.skillSum / 15)) {
            for(int i = 0; i < skillNum; i++) {
                chmax(member.minEstimatedSkills[i], task.requiredSkills[i]);
            }
        }
        for(int i = 0; i < skillNum; i++) {
            double add =
                max(0.0, task.requiredSkills[i] - double(taskTime) / skillNum);
            member.estimatedSkills[i] = max(member.minEstimatedSkills[i],
                                            (member.estimatedSkills[i] + add) /
                                                member.assignedTaskIds.size());
        }
    }

    void _estimate2(Member &member, const Task &task) {
        {
            vector<int> taskTimes;
            for(const int taskId : member.assignedTaskIds) {
                Task &task = tasks[taskId2Index[taskId]];
                int taskTime = task.completedDay - task.assignedDay + 1;
                taskTimes.emplace_back(taskTime);
            }
            dump(member.assignedTaskIds);
            dump(taskTimes);
        }
        // ???????????????????????????+1??????????????????????????????
        for(int skillId = 0; skillId < skillNum; skillId++) {
            member.estimatedSkills[skillId] += 1.0;
            bool ok = true;
            for(const int taskId : member.assignedTaskIds) {
                Task &task = tasks[taskId2Index[taskId]];
                int taskTime = task.completedDay - task.assignedDay + 1;
                int estimatedTime = max(1.0, calcCost(member, task));
                dump(taskTime, estimatedTime);
                if(taskTime - 3 > estimatedTime) {
                    ok = false;
                }
            }
            if(not ok) {
                member.estimatedSkills[skillId] -= 1.0;
            } else {
                dump("age");
            }
        }
    }

    int distance(const Task &a, const Task &b) {
        int res = 0;
        for(int i = 0; i < skillNum; i++) {
            res += abs(a.requiredSkills[i] - b.requiredSkills[i]);
        }
    }

    bool isLeafTask(const Task &task) {
        return dependencyGraph[task.id].empty();
    }

    bool isRootTask(const Task &task) { return task.dependency.empty(); }

    bool isIndependedTask(const Task &task) {
        return isRootTask(task) && isLeafTask(task);
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
    dump(out);
}

// valiable for input.
vector<double> _requiredSkills[MAX_TASK_NUM];
vector<int> _taskDependency[MAX_TASK_NUM]; // taskDependency[i]:
                                           // i????????????????????????????????????????????????
int main() {
    // input
    int taskNum;   // = 1000
    int memberNum; // = 20;
    int skillNum;  // 10 - 20
    int dependNum; // 1000 - 3000
    cin >> taskNum >> memberNum >> skillNum >> dependNum;
    for(int i = 0; i < taskNum; i++) {
        for(int j = 0; j < skillNum; j++) {
            int r;
            cin >> r;
            _requiredSkills[i].emplace_back(r);
        }
    }
    vector<vector<int>> _dependencyGraph(taskNum);
    for(int i = 0; i < dependNum; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        _taskDependency[v].emplace_back(u);
        _dependencyGraph[u].emplace_back(v);
    }
    // initialize Solver.
    Solver aSolver(taskNum, memberNum, skillNum, dependNum, _dependencyGraph);
    {
        // initialize members
        for(int memberId = 0; memberId < memberNum; memberId++) {
            aSolver.setMember(memberId);
        }
        // initialize tasks
        for(int taskId = 0; taskId < taskNum; taskId++) {
            aSolver.setTask(taskId, _requiredSkills[taskId],
                            _taskDependency[taskId]);
        }
        aSolver.setTaskDependencies();
    }

    // iterate
    int day = 0;
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
            // estimate the skills of member.
            aSolver.estimate(memberId);
            aSolver.outEstimate(memberId);
        }
        day++;
    }
    dump(skillNum, dependNum);
    return 0;
}
