#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU() {}
    explicit DSU(size_t n) { init(n); }
    void init(size_t n) {
        p.resize(n);
        r.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        int root = x;
        while (p[root] != root) root = p[root];
        while (p[x] != x) {
            int nx = p[x];
            p[x] = root;
            x = nx;
        }
        return root;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
};

struct Constraint { int a; int b; int e; };

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Use fast C IO because of huge input volume
    // Read t using fastReadInt to avoid sync issues
    int t; 
    if (!fastReadInt(t)) return 0;
    string out; out.reserve((size_t)t * 4);
    while (t--) {
        int n; fastReadInt(n);
        vector<Constraint> eqs; eqs.reserve(n);
        vector<Constraint> neqs; neqs.reserve(64);
        eqs.clear(); neqs.clear();
        eqs.shrink_to_fit(); neqs.shrink_to_fit(); // ensure capacity set above applies
        eqs.reserve(n);
        neqs.reserve(n / 8 + 8);

        vector<pair<int,int>> pairs; pairs.reserve(n);
        pairs.clear();

        eqs.reserve(n);
        for (int i = 0; i < n; ++i) {
            int a, b, e; fastReadInt(a); fastReadInt(b); fastReadInt(e);
            if (e == 1) {
                eqs.push_back({a, b, e});
            } else {
                neqs.push_back({a, b, e});
            }
            pairs.emplace_back(a, b);
        }

        // Coordinate compression
        vector<int> vals; vals.reserve(pairs.size() * 2);
        for (auto &pr : pairs) { vals.push_back(pr.first); vals.push_back(pr.second); }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        auto getId = [&](int x) {
            return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        };

        DSU dsu(vals.size());

        // Merge equalities first
        for (const auto &cns : eqs) {
            int x = getId(cns.a), y = getId(cns.b);
            dsu.unite(x, y);
        }

        // Check inequalities
        bool ok = true;
        for (const auto &cns : neqs) {
            int x = getId(cns.a), y = getId(cns.b);
            if (dsu.same(x, y)) { ok = false; break; }
        }

        if (ok) out += "YES\n"; else out += "NO\n";
    }

    // Use fwrite for faster single output
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}

