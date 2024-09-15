// vector����� 
using i64 = long long;
constexpr int mod = 998244353;
int norm(int x) {
    if (x < 0) {
        x += mod;
    }
    if (x >= mod) {
        x -= mod;
    }
    return x;
}
template<class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(mod - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, mod - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % mod;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend istream &operator>>(istream &is, Z &a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend ostream &operator<<(ostream &os, const Z &a) {
        return os << a.val();
    }
};
vector<int> rev;
vector<Z> roots{0, 1};
void dft(vector<Z> &a) {
    int n = a.size();
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i ++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }
    for (int i = 0; i < n; i ++) {
        if (rev[i] < i) {
            swap(a[i], a[rev[i]]);
        }
    }
    if (int(roots.size()) < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            Z e = power(Z(3), (mod - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i ++) {
                roots[i << 1] = roots[i];
                roots[i << 1 | 1] = roots[i] * e;
            }
            k ++;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j ++) {
                Z u = a[i + j], v = a[i + j + k] * roots[k + j];
                a[i + j] = u + v, a[i + j + k] = u - v;
            }
        }
    }
}
void idft(vector<Z> &a) {
    int n = a.size();
    reverse(a.begin() + 1, a.end());
    dft(a);
    Z inv = (1 - mod) / n;
    for (int i = 0; i < n; i ++) {
        a[i] *= inv;
    }
}
struct Poly {
    vector<Z> a;
    Poly() {}
    Poly(const vector<Z> &a) : a(a) {}
    Poly(const initializer_list<Z> &a) : a(a) {}
    int size() const {
        return a.size();
    }
    void resize(int n) {
        a.resize(n);
    }
    Z operator[](int idx) const {
        if (idx < size()) {
            return a[idx];
        } else {
            return 0;
        }
    }
    Z &operator[](int idx) {
        return a[idx];
    }
    Poly mulxk(int k) const {
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }
    Poly modxk(int k) const {
        k = min(k, size());
        return Poly(vector<Z>(a.begin(), a.begin() + k));
    }
    Poly divxk(int k) const {
        if (size() <= k) {
            return Poly();
        }
        return Poly(vector<Z>(a.begin() + k, a.end()));
    }
    friend Poly operator+(const Poly &a, const Poly &b) {
        vector<Z> res(max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i ++) {
            res[i] = a[i] + b[i];
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly &a, const Poly &b) {
        vector<Z> res(max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i ++) {
            res[i] = a[i] - b[i];
        }
        return Poly(res);
    }
    friend Poly operator*(Poly a, Poly b) {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot) {
            sz *= 2;
        }
        a.a.resize(sz);
        b.a.resize(sz);
        dft(a.a);
        dft(b.a);
        for (int i = 0; i < sz; i ++) {
            a.a[i] = a[i] * b[i];
        }
        idft(a.a);
        a.resize(tot);
        return a;
    }
    friend Poly operator*(Z a, Poly b) {
        for (int i = 0; i < int(b.size()); i ++) {
            b[i] *= a;
        }
        return b;
    }
    friend Poly operator*(Poly a, Z b) {
        for (int i = 0; i < int(a.size()); i ++) {
            a[i] *= b;
        }
        return a;
    }
    Poly &operator+=(Poly b) {
        return (*this) = (*this) + b;
    }
    Poly &operator-=(Poly b) {
        return (*this) = (*this) - b;
    }
    Poly &operator*=(Poly b) {
        return (*this) = (*this) * b;
    }
    Poly deriv() const {
        if (a.empty()) {
            return Poly();
        }
        vector<Z> res(size() - 1);
        for (int i = 0; i < size() - 1; i ++) {
            res[i] = (i + 1) * a[i + 1];
        }
        return Poly(res);
    }
    Poly integr() const {
        vector<Z> res(size() + 1);
        for (int i = 0; i < size(); i ++) {
            res[i + 1] = a[i] / (i + 1);
        }
        return Poly(res);
    }
    Poly inv(int m) const {
        Poly x{a[0].inv()};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }
    Poly log(int m) const {
        return (deriv() * inv(m)).integr().modxk(m);
    }
    Poly exp(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{1} - x.log(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }
    Poly pow(int k, int m) const {
        int i = 0;
        while (i < size() && a[i].val() == 0) {
            i ++;
        }
        if (i == size() || 1LL * i * k >= m) {
            return Poly(vector<Z>(m));
        }
        Z v = a[i];
        auto f = divxk(i) * v.inv();
        return (f.log(m - i * k) * k).exp(m - i * k).mulxk(i * k) * power(v, k);
    }
    Poly sqrt(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((mod + 1) / 2);
        }
        return x.modxk(m);
    }
    Poly mulT(Poly b) const {
        if (b.size() == 0) {
            return Poly();
        }
        int n = b.size();
        reverse(b.a.begin(), b.a.end());
        return ((*this) * b).divxk(n - 1);
    }
};

// vector会变大，最多不能超过15次ntt
#define int long long
const int md = 998244353;

inline void add(int &x, int y) {
    x += y;
    if (x >= md) {
        x -= md;
    }
}

inline void sub(int &x, int y) {
    x -= y;
    if (x < 0) {
        x += md;
    }
}

inline int mul(int x, int y) {
    return (long long) x * y % md;
}

inline int power(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = mul(x, x)) {
        if (y & 1) {
        res = mul(res, x);
        }
    }
    return res;
}

inline int inv(int a) {
    a %= md;
    if (a < 0) {
        a += md;
    }
    int b = md, u = 0, v = 1;
    while (a) {
        int t = b / a;
        b -= t * a;
        swap(a, b);
        u -= t * v;
        swap(u, v);
    }
    if (u < 0) {
        u += md;
    }
    return u;
}

namespace ntt {
    int base = 1, root = -1, max_base = -1;
    vector<int> rev = {0, 1}, roots = {0, 1};

    void init() {
        int temp = md - 1;
        max_base = 0;
        while (temp % 2 == 0) {
            temp >>= 1;
            ++max_base;
        }
        root = 2;
        while (true) {
            if (power(root, 1 << max_base) == 1 && power(root, 1 << (max_base - 1)) != 1) {
                break;
            }
            ++root;
        }
    }

    void ensure_base(int nbase) {
        if (max_base == -1) {
            init();
        }
        if (nbase <= base) {
            return;
        }
        assert(nbase <= max_base);
        rev.resize(1 << nbase);
        for (int i = 0; i < 1 << nbase; ++i) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (nbase - 1));
        }
        roots.resize(1 << nbase);
        while (base < nbase) {
            int z = power(root, 1 << (max_base - 1 - base));
            for (int i = 1 << (base - 1); i < 1 << base; ++i) {
            roots[i << 1] = roots[i];
            roots[i << 1 | 1] = mul(roots[i], z);
            }
            ++base;
        }
    }

    void dft(vector<int> &a) {
        int n = a.size(), zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; ++i) {
            if (i < rev[i] >> shift) {
            swap(a[i], a[rev[i] >> shift]);
            }
        }
        for (int i = 1; i < n; i <<= 1) {
            for (int j = 0; j < n; j += i << 1) {
                for (int k = 0; k < i; ++k) {
                    int x = a[j + k], y = mul(a[j + k + i], roots[i + k]);
                    a[j + k] = (x + y) % md;
                    a[j + k + i] = (x + md - y) % md;
                }
            }
        }
    }

    vector<int> multiply(vector<int> a, vector<int> b) {
        int need = a.size() + b.size() - 1, nbase = 0;
        while (1 << nbase < need) {
            ++nbase;
        }
        ensure_base(nbase);
        int sz = 1 << nbase;
        a.resize(sz);
        b.resize(sz);
        bool equal = a == b;
        dft(a);
        if (equal) {
            b = a;
        } else {
            dft(b);
        }
        int inv_sz = inv(sz);
        for (int i = 0; i < sz; ++i) {
            a[i] = mul(mul(a[i], b[i]), inv_sz);
        }
        reverse(a.begin() + 1, a.end());
        dft(a);
        a.resize(need);
        return a;
    }

    vector<int> inverse(vector<int> a) {
        int n = a.size(), m = (n + 1) >> 1;
        if (n == 1) {
            return vector<int>(1, inv(a[0]));
        } 
        else 
        {
            vector<int> b = inverse(vector<int>(a.begin(), a.begin() + m));
            int need = n << 1, nbase = 0;
            while (1 << nbase < need) {
                ++nbase;
            }
            ensure_base(nbase);
            int sz = 1 << nbase;
            a.resize(sz);
            b.resize(sz);
            dft(a);
            dft(b);
            int inv_sz = inv(sz);
            for (int i = 0; i < sz; ++i) {
                a[i] = mul(mul(md + 2 - mul(a[i], b[i]), b[i]), inv_sz);
            }
            reverse(a.begin() + 1, a.end());
            dft(a);
            a.resize(n);
            return a;
        }
    }
}

using ntt::multiply;
using ntt::inverse;

vector<int>& operator += (vector<int> &a, const vector<int> &b) {
    if (a.size() < b.size()) {
        a.resize(b.size());
    }
    for (int i = 0; i < b.size(); ++i) {
        add(a[i], b[i]);
    }
    return a;
}

vector<int> operator + (const vector<int> &a, const vector<int> &b) {
    vector<int> c = a;
    return c += b;
}

vector<int>& operator -= (vector<int> &a, const vector<int> &b) {
    if (a.size() < b.size()) {
        a.resize(b.size());
    }
    for (int i = 0; i < b.size(); ++i) {
        sub(a[i], b[i]);
    }
    return a;
}

vector<int> operator - (const vector<int> &a, const vector<int> &b) {
    vector<int> c = a;
    return c -= b;
}

vector<int>& operator *= (vector<int> &a, const vector<int> &b) {
    if (min(a.size(), b.size()) < 128) {
        vector<int> c = a;
        a.assign(a.size() + b.size() - 1, 0);
        for (int i = 0; i < c.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            add(a[i + j], mul(c[i], b[j]));
        }
        }
    } else {
        a = multiply(a, b);
    }
    return a;
}

vector<int> operator * (const vector<int> &a, const vector<int> &b) {
    vector<int> c = a;
    return c *= b;
}

vector<int>& operator /= (vector<int> &a, const vector<int> &b) {
    int n = a.size(), m = b.size();
    if (n < m) {
        a.clear();
    } else {
        vector<int> c = b;
        reverse(a.begin(), a.end());
        reverse(c.begin(), c.end());
        c.resize(n - m + 1);
        a *= inverse(c);
        a.erase(a.begin() + n - m + 1, a.end());
        reverse(a.begin(), a.end());
    }
    return a;
}

vector<int> operator / (const vector<int> &a, const vector<int> &b) {
    vector<int> c = a;
    return c /= b;
}

vector<int>& operator %= (vector<int> &a, const vector<int> &b) {
    int n = a.size(), m = b.size();
    if (n >= m) {
        vector<int> c = (a / b) * b;
        a.resize(m - 1);
        for (int i = 0; i < m - 1; ++i) {
        sub(a[i], c[i]);
        }
    }
    return a;
}

vector<int> operator % (const vector<int> &a, const vector<int> &b) {
    vector<int> c = a;
    return c %= b;
}

vector<int> derivative(const vector<int> &a) {
    int n = a.size();
    vector<int> b(n - 1);
    for (int i = 1; i < n; ++i) {
        b[i - 1] = mul(a[i], i);
    }
    return b;
}

vector<int> primitive(const vector<int> &a) {
    int n = a.size();
    vector<int> b(n + 1), invs(n + 1);
    for (int i = 1; i <= n; ++i) {
        invs[i] = i == 1 ? 1 : mul(md - md / i, invs[md % i]);
        b[i] = mul(a[i - 1], invs[i]);
    }
    return b;
}

vector<int> logarithm(const vector<int> &a) {
    vector<int> b = primitive(derivative(a) * inverse(a));
    b.resize(a.size());
    return b;
}

vector<int> exponent(const vector<int> &a) {
    vector<int> b(1, 1);
    while (b.size() < a.size()) {
        vector<int> c(a.begin(), a.begin() + min(a.size(), b.size() << 1));
        add(c[0], 1);
        vector<int> old_b = b;
        b.resize(b.size() << 1);
        c -= logarithm(b);
        c *= old_b;
        for (int i = b.size() >> 1; i < b.size(); ++i) {
            b[i] = c[i];
        }
    }
    b.resize(a.size());
    return b;
}

vector<int> power(vector<int> a, int m) {
    int n = a.size(), p = -1;
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        if (a[i]) {
        p = i;
        break;
        }
    }
    if (p == -1) {
        b[0] = !m;
        return b;
    }
    if ((long long) m * p >= n) {
        return b;
    }
    int mu = power(a[p], m), di = inv(a[p]);
    vector<int> c(n - m * p);
    for (int i = 0; i < n - m * p; ++i) {
        c[i] = mul(a[i + p], di);
    }
    c = logarithm(c);
    for (int i = 0; i < n - m * p; ++i) {
        c[i] = mul(c[i], m);
    }
    c = exponent(c);
    for (int i = 0; i < n - m * p; ++i) {
        b[i + m * p] = mul(c[i], mu);
    }
    return b;
}

vector<int> sqrt(const vector<int> &a) {
    vector<int> b(1, 1);
    while (b.size() < a.size()) {
        vector<int> c(a.begin(), a.begin() + min(a.size(), b.size() << 1));
        vector<int> old_b = b;
        b.resize(b.size() << 1);
        c *= inverse(b);
        for (int i = b.size() >> 1; i < b.size(); ++i) {
        b[i] = mul(c[i], (md + 1) >> 1);
        }
    }
    b.resize(a.size());
    return b;
}

vector<int> multiply_all(int l, int r, vector<vector<int>> &all) {
    if (l > r) {
        return vector<int>();
    } else if (l == r) {
        return all[l];
    } else {
        int y = (l + r) >> 1;
        return multiply_all(l, y, all) * multiply_all(y + 1, r, all);
    }
}

vector<int> evaluate(const vector<int> &f, const vector<int> &x) {
    int n = x.size();
    if (!n) {
        return vector<int>();
    }
    vector<vector<int>> up(n * 2);
    for (int i = 0; i < n; ++i) {
        up[i + n] = vector<int>{(md - x[i]) % md, 1};
    }
    for (int i = n - 1; i; --i) {
        up[i] = up[i << 1] * up[i << 1 | 1];
    }
    vector<vector<int>> down(n * 2);
    down[1] = f % up[1];
    for (int i = 2; i < n * 2; ++i) {
        down[i] = down[i >> 1] % up[i];
    }
    vector<int> y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = down[i + n][0];
    }
    return y;
}

vector<int> interpolate(const vector<int> &x, const vector<int> &y) {
    int n = x.size();
    vector<vector<int>> up(n * 2);
    for (int i = 0; i < n; ++i) {
        up[i + n] = vector<int>{(md - x[i]) % md, 1};
    }
    for (int i = n - 1; i; --i) {
        up[i] = up[i << 1] * up[i << 1 | 1];
    }
    vector<int> a = evaluate(derivative(up[1]), x);
    for (int i = 0; i < n; ++i) {
        a[i] = mul(y[i], inv(a[i]));
    }
    vector<vector<int>> down(n * 2);
    for (int i = 0; i < n; ++i) {
        down[i + n] = vector<int>(1, a[i]);
    }
    for (int i = n - 1; i; --i) {
        down[i] = down[i << 1] * up[i << 1 | 1] + down[i << 1 | 1] * up[i << 1];
    }
    return down[1];
}
