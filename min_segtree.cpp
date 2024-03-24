/* https://cses.fi/problemset/task/1649 */

#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;

struct min_segtree {
    
    int sz;
    vector<int> val;

    void init(int n) {
        sz = 1;
        while(sz < n) sz *= 2;
        val.resize(2 * sz);
    }

    void build(vector<int>& a) {
        build(a, 0, 0, sz);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < (int) a.size()) val[x] = a[lx];
            return;
        }

        int m = (lx + rx)/2;
        build(a, 2*x + 1, lx, m);
        build(a, 2*x + 2, m, rx);
        val[x] = min(val[2*x + 1], val[2*x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, sz);

    }

    void set(int i, int v, int x, int lx, int rx) {
        if(rx - lx == 1) {
            val[x] = v;
            return;
        }

        int m = (lx + rx)/2;
        if(i < m) set(i, v, 2*x + 1, lx, m);
        else set(i, v, 2*x + 2, m, rx);
        val[x] = min(val[2*x + 1], val[2*x + 2]);
    }

    int calc(int l, int r) {
        return calc(l, r, 0, 0, sz);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if(r <= lx || l >= rx) return INF;
        if(l <= lx && r >= rx) return val[x];
        int m = (lx + rx)/2; 
        int lv = calc(l, r, 2*x + 1, lx, m);
        int rv = calc(l, r, 2*x + 2, m, rx);
        return min(lv, rv);
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for(int i=0; i<n; i++) {
        cin >> v[i];
    }

    min_segtree st;
    st.init(n);
    st.build(v);

    while(q--) {
        int t, a, b;
        cin >> t >> a >> b;

        if(t == 1) {
            st.set(--a, b);
        } else if(t == 2) {
            cout << st.calc(--a, b) << "\n";
        }
    }

    return 0;
}

