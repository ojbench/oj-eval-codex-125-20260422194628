// Optimized solution: on-the-fly DSU with hashing to avoid sorting
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU() { p.reserve(1); r.reserve(1); }
    int add() {
        int id = (int)p.size();
        p.push_back(id);
        r.push_back(0);
        return id;
    }
    int find(int x) {
        int root = x;
        while (p[root] != root) root = p[root];
        while (p[x] != x) { int nx = p[x]; p[x] = root; x = nx; }
        return root;
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
    }
    bool same(int a, int b) { return find(a) == find(b); }
};

static inline bool fastReadInt(int &out) {
    int c = getchar_unlocked();
    while (c != EOF && (c < '0' || c > '9') && c != '-') c = getchar_unlocked();
    if (c == EOF) return false;
    int sign = 1; if (c == '-') { sign = -1; c = getchar_unlocked(); }
    long long val = 0;
    while (c >= '0' && c <= '9') { val = val * 10 + (c - '0'); c = getchar_unlocked(); }
    out = (int)(val * sign);
    return true;
}

int main() {
    int t; if (!fastReadInt(t)) return 0;
    vector<char> answers; answers.reserve(t);
    while (t--) {
        int n; fastReadInt(n);
        DSU dsu;
        dsu.p.reserve((size_t)min(4*n, 10000000));
        dsu.r.reserve((size_t)min(4*n, 10000000));
        unordered_map<int,int> id;
        id.reserve((size_t)min(4*n, 10000000));
        id.max_load_factor(0.7f);

        auto getId = [&](int x) -> int {
            auto it = id.find(x);
            if (it != id.end()) return it->second;
            int nid = dsu.add();
            id.emplace(x, nid);
            return nid;
        };

        vector<pair<int,int>> neqs; neqs.reserve(n/2 + 8);
        for (int i = 0; i < n; ++i) {
            int a, b, e; fastReadInt(a); fastReadInt(b); fastReadInt(e);
            int ia = getId(a), ib = getId(b);
            if (e == 1) {
                dsu.unite(ia, ib);
            } else {
                neqs.emplace_back(ia, ib);
            }
        }

        bool ok = true;
        for (const auto &pr : neqs) {
            if (dsu.same(pr.first, pr.second)) { ok = false; break; }
        }
        answers.push_back(ok ? 'Y' : 'N');
    }

    for (char c : answers) {
        if (c == 'Y') {
            putchar_unlocked('Y'); putchar_unlocked('E'); putchar_unlocked('S');
        } else {
            putchar_unlocked('N'); putchar_unlocked('O');
        }
        putchar_unlocked('\n');
    }
    return 0;
}
