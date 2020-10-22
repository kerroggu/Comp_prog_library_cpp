// https://atcoder.jp/contests/abc138/submissions/me

// template version 1.12
using namespace std;
#include <iostream>
#include <bits/stdc++.h>

// varibable settings
#define infile "../test/sample-1.in"
#define int long long //{{{
const int INF=1e18;
const int MOD=1e9+7; //}}}

// define basic macro {{{
#define _overload3(_1,_2,_3,name,...) name
#define _rep(i,n) repi(i,0,n)
#define repi(i,a,b) for(int i=(int)(a);i<(int)(b);++i)
#define rep(...) _overload3(__VA_ARGS__,repi,_rep,)(__VA_ARGS__)
#define _rrep(i,n) rrepi(i,0,n)
#define rrepi(i,a,b) for(int i=(int)((b)-1);i>=(int)(a);--i)
#define rrep(...) _overload3(__VA_ARGS__,rrepi,_rrep,)(__VA_ARGS__)
#define each(i,a) for (auto&& i : a)
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define uni(x) sort(all(x));x.erase(unique(all(x)),x.end())
#define ub upper_bound
#define lb lower_bound
#define posl(A, x) (lower_bound(all(A), x)-A.begin())
#define posu(A, x) (upper_bound(all(A),x)-A.begin())
template <class T, class U> inline void chmax(T &a, const U &b) { if ((a) < (b)) (a) = (b); }
template <class T, class U> inline void chmin(T &a, const U &b) { if ((a) > (b)) (a) = (b); }
template <typename X, typename T> auto make_table(X x, T a) { return vector<T>(x, a); }
template <typename X, typename Y, typename Z, typename... Zs> auto make_table(X x, Y y, Z z, Zs... zs) { auto cont = make_table(y, z, zs...); return vector<decltype(cont)>(x, cont); }
 
template <class T> T cdiv(T a, T b){ assert(a >= 0 && b > 0); return (a+b-1)/b; }
 
#define is_in(x, a, b) ((a) <= (x) && (x) < (b))
#define slice(l, r) substr(l, r - l)
 
typedef long long ll;
typedef long double ld;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll, ll>;
 
template <typename T>
using PQ = priority_queue<T, vector<T>, greater<T>>;
void check_input() { assert(cin.eof() == 0); int tmp; cin >> tmp; assert(cin.eof() == 1); }


//}}}

#define DUMPOUT cerr  // where to dump. cout or cerr

#define cerrendl cerr << endl

namespace dm {
    stack<vector<string>> varnames;
    stack<int> varidx;
    int i;
    int j;
}  // namespace dm

#define dump(...)                                                            \
    {                                                                        \
        dm::varnames.push([](string s) -> vector<string> {           \
            int n = s.size();                                                \
            vector<string> res;                                              \
            string tmp = "";                                                 \
            int parlevel = 0;                                                \
            int angle_level = 0;                                             \
            for (int i = 0; i < n; i++) {                                    \
                if (s[i] == '(') parlevel++;                                 \
                if (s[i] == ')') parlevel--;                                 \
                if (s[i] == '<') angle_level++;                              \
                if (s[i] == '>') angle_level--;                              \
                if (s[i] == ' ') continue;                                   \
                if (s[i] == ',' && parlevel == 0 && angle_level == 0) {      \
                    res.push_back(tmp);                                      \
                    tmp = "";                                                \
                } else {                                                     \
                    tmp += s[i];                                             \
                }                                                            \
            }                                                                \
            res.push_back(tmp);                                              \
            return res;                                                      \
        }(#__VA_ARGS__));                                                    \
        dm::varidx.push(0);                                                  \
        dump_func(__VA_ARGS__);                                              \
        DUMPOUT << "in [" << __LINE__ << ":" << __FUNCTION__ << "]" << endl; \
        dm::varnames.pop();                                                  \
        dm::varidx.pop();                                                    \
    }

#define dump_1d(x, n)                                                        \
    {                                                                        \
        DUMPOUT << "  " << #x << "[" << #n << "]"                            \
                << ":=> {";                                                  \
        for(dm::i=0; dm::i<n; ++dm::i)                                       \
            DUMPOUT << x[dm::i] << (((dm::i) == (n - 1)) ? "}" : ", ");     \
        DUMPOUT << " in [" << __LINE__ << "]" << endl;                       \
    }

#define dump_2d(x, n, m)                                                     \
    {                                                                        \
        DUMPOUT << "  " << #x << "[" << #n << "]"                            \
                << "[" << #m << "]"                                          \
                << ":=> \n";                                                 \
        for(dm::i=0; dm::i<n; ++dm::i)                                       \
        for(dm::j=0; dm::j<m; ++dm::j) {                                     \
            DUMPOUT << ((dm::j == 0) ? "     |" : " ") << x[dm::i][dm::j]    \
                    << (((dm::j) == (m - 1)) ? "|\n" : " ");                 \
        }                                                                    \
        DUMPOUT << "  in [" << __LINE__ << "]" << endl;                      \
    }

void dump_func() {}
template <class Head, class... Tail>
void dump_func(Head&& head, Tail&&... tail) {
    DUMPOUT << dm::varnames.top()[dm::varidx.top()] << ":"
            << head;
    if (sizeof...(Tail) == 0) {
        DUMPOUT << " ";
    } else {
        DUMPOUT << ", ";
    }
    ++dm::varidx.top();
    dump_func(std::move(tail)...);
}

// 隣接リストで使う辺を表す型
struct Edge {
  int to, cost;  // 辺の接続先頂点, 辺の重み
  Edge(int to, int cost) : to(to), cost(cost) {}  // コンストラクタ
};

typedef vector<vector<Edge> > AdjList;  // 隣接リストの型
AdjList graph;  // グラフの辺を格納した構造体
                // graph[v][i]は頂点vから出るi番目の辺Edge

vector<int> dist; // 最短距離



int solve(){
    
    ll n,Q,a,b;
    
    cin>>n>>Q;
    
    auto g=make_table(n,0,0);
    rep(i,n-1){
        cin>>a>>b;
        a--;b--;
        g[a].pb(b);
        g[b].pb(a);
    }
    
    auto p=make_table(n,0);
    rep(i,Q){
        int x,l;
        cin>>l>>x;
        p[l-1]+=x;
    }
    
    auto q=make_table(1,0);
    auto v=make_table(n,0);
    v[0]=1;
    while (!q.empty()){
        ll c=q.back();
        q.pop_back();
        for (auto nb:g[c]){
            if(v[nb]==0){
                v[nb]=1;
                q.push_back(nb);
                p[nb]+=p[c];
            }
        }
    }
    
    //rep(i,n)dump_1d(g[i],g[i].size());
    //dump_1d(p,n);
    
    rep(i,n)cout<<p[i]<<' ';
    return 0;
}

signed main() {
#ifdef INPUT_FROM_FILE
  std::ifstream in(infile);
  std::cin.rdbuf(in.rdbuf());
#endif
  solve();
  return 0;
}

