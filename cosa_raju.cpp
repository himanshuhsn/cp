/**
 * Kosa Raju algo is used to find the strongly connected component.
 * Returns a vector of vector contains Strongly connected components in each vector.
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<vector<int>> g;
vector<vector<int>> inv_g;

vector<int> p;
vector<int> out_mark;
void out_dfs(int v) {
    out_mark[v] = 1;
    for(auto u: g[v]) {
        if(out_mark[u] == 0) {
            out_dfs(u);
        }
    }
    p.push_back(v);
}

vector<int> in_mark;
void in_dfs(int v, vector<int>& cc) {
    in_mark[v] = 1;
    for(auto u: inv_g[v]) {
        if(in_mark[u] == 0) {
            in_dfs(u, cc);
        }
    }
    cc.push_back(v);
}

vector<vector<int>> kosa_raju() {
    int N = g.size();
    vector<vector<int>> ans;
    out_mark.resize(N, 0);
    for(int i=0; i<N; i++) {
        if(out_mark[i] == 0) {
            out_dfs(i);
        }
    }
    reverse(p.begin(), p.end());

    in_mark.resize(N, 0);
    for(auto it: p) {
        if(in_mark[it] == 0) {
            vector<int> vt;
            in_dfs(it, vt);
            ans.push_back(vt);
        }
    }

    return ans;
}

void solve(){
    int n, m; cin >> n >> m;
    g.resize(n);
    inv_g.resize(n);
    for(int i=0; i<m; i++) {
        int v, u; cin >> v >> u;
        v--; u--;
        g[v].push_back(u);
        inv_g[u].push_back(v);
    }

    vector<vector<int>> scc = kosa_raju();
    for(auto cc: scc) {
        for(auto v: cc) {
            cout << v << " ";
        }
        cout << "\n";
    }
}

int32_t main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int test_cases = 1;
	//cin >> test_cases;
	while(test_cases--){
		solve();
	}
	return 0;
}
