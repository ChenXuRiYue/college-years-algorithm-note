#include <bits/stdc++.h>
using namespace std;

struct Point { double x, y; };        // 点
using Vec = Point;                    // 向量
struct Line { Point P; Vec v; };      // 直线（点向式）
struct Seg { Point A, B; };           // 线段（存两个端点）
struct Circle { Point O; double r; }; // 圆（存圆心和半径）

const Point O = {0, 0};                        // 原点
const Line Ox = {O, {1, 0}}, Oy = {O, {0, 1}}; // 坐标轴
const double PI = acos(-1), EPS = 1e-9;

bool eq(double a, double b) { return abs(a - b) < EPS; } // ==
bool gt(double a, double b) { return a - b > EPS; }      // >
bool lt(double a, double b) { return a - b < -EPS; }     // <
bool ge(double a, double b) { return a - b > -EPS; }     // >=
bool le(double a, double b) { return a - b < EPS; }      // <=

Vec r90a(Vec v) { return {-v.y, v.x}; }                          // 逆时针旋转90度的向量
Vec r90c(Vec v) { return {v.y, -v.x}; }                          // 顺时针旋转90度的向量
Vec operator+(Vec u, Vec v) { return {u.x + v.x, u.y + v.y}; }   // 向量加向量
Vec operator-(Vec u, Vec v) { return {u.x - v.x, u.y - v.y}; }   // 向量减向量
Vec operator*(double k, Vec v) { return {k * v.x, k * v.y}; }    // 数乘
double operator*(Vec u, Vec v) { return u.x * v.x + u.y * v.y; } // 点乘
double operator^(Vec u, Vec v) { return u.x * v.y - u.y * v.x; } // 叉乘
double len(Vec v) { return sqrt(v.x * v.x + v.y * v.y); }        // 向量长度
double slope(Vec v) { return v.y / v.x; }                        // 斜率 // NOTE 不要用isinf判断斜率不存在，用后面的paral_y

// 两向量的夹角余弦
double cos_t(Vec u, Vec v) { return u * v / len(u) / len(v); }// DEPENDS len, V*V

// 归一化向量（与原向量方向相同的单位向量）
Vec norm(Vec v) { return {v.x / len(v), v.y / len(v)}; }// DEPENDS len

// 与原向量平行且横坐标大于等于0的单位向量
Vec pnorm(Vec v) { return (v.x < 0 ? -1 : 1) / len(v) * v; }// DEPENDS d*V, len

// 线段的方向向量
// NOTE 直线的方向向量直接访问属性v
Vec dvec(Seg l) { return l.B - l.A; }// DEPENDS V-V

// 两点式直线
Line line(Point A, Point B) { return {A, B - A}; }

// 斜截式直线
Line line(double k, double b) { return {{0, b}, {1, k}}; }

// 点斜式直线
Line line(Point P, double k) { return {P, {1, k}}; }

// 线段所在直线
Line line(Seg l) { return {l.A, l.B - l.A}; }// DEPENDS V-V

// 给定直线的横坐标求纵坐标
// NOTE 请确保直线不与y轴平行
double at_x(Line l, double x) { return l.P.y + (x - l.P.x) * l.v.y / l.v.x; }

// 给定直线的纵坐标求横坐标
// NOTE 请确保直线不与x轴平行
double at_y(Line l, double y) { return l.P.x - (y + l.P.y) * l.v.x / l.v.y; }

// 点到直线的垂足
// DEPENDS V-V, V*V, d*V
Point pedal(Point P, Line l) { return l.P - (l.P - P) * l.v / (l.v * l.v) * l.v; }

// 过某点作直线的垂线
Line perp(Line l, Point P) { return {P, r90c(l.v)}; }// DEPENDS r90c

// 角平分线
Line bisec(Point P, Vec u, Vec v) { return {P, norm(u) + norm(v)}; }// DEPENDS V+V, len, norm

// 线段的方向向量
// NOTE 直线的方向向量直接访问属性v
Vec dvec(Seg l) { return l.B - l.A; }// DEPENDS V-V

// 线段中点
Point midp(Seg l) { return {(l.A.x + l.B.x) / 2, (l.A.y + l.B.y) / 2}; }

// 线段中垂线
Line perp(Seg l) { return {midp(l), r90c(l.B - l.A)}; }// DEPENDS r90c, V-V, midp


// 向量是否互相垂直
bool verti(Vec u, Vec v) { return eq(u * v, 0); }// DEPENDS eq, V*V

// 向量是否互相平行
bool paral(Vec u, Vec v) { return eq(u ^ v, 0); }// DEPENDS eq, V^V

// 向量是否与x轴平行
bool paral_x(Vec v) { return eq(v.y, 0); }// DEPENDS eq  V-V

// 向量是否与y轴平行
bool paral_y(Vec v) { return eq(v.x, 0); }// DEPENDS eq

// 点是否在直线上
bool on(Point P, Line l) { return eq((P.x - l.P.x) * l.v.y, (P.y - l.P.y) * l.v.x); }// DEPENDS eq

// 点是否在线段上
bool on(Point P, Seg l) { return eq(len(P - l.A) + len(P - l.B), len(l.A - l.B)); }// DEPENDS eq, len, V-V

// 两个点是否重合
bool operator==(Point A, Point B) { return eq(A.x, B.x) && eq(A.y, B.y); }// DEPENDS eq

// 两条直线是否重合
bool operator==(Line a, Line b) { return on(a.P, b) && on(a.P + a.v, b); }// DEPENDS eq, on(L)

// 两条线段是否重合
bool operator==(Seg a, Seg b) { return (a.A == b.A && a.B == b.B) || (a.A == b.B && a.B == b.A); }// DEPENDS eq, P==P

// 以横坐标为第一关键词、纵坐标为第二关键词比较两个点
bool operator<(Point A, Point B) { return lt(A.x, B.x) || (eq(A.x, B.x) && lt(A.y, B.y)); }// DEPENDS eq, lt

// 直线与圆是否相切
bool tangency(Line l, Circle C) { return eq(abs((C.O ^ l.v) - (l.P ^ l.v)), C.r * len(l.v)); }// DEPENDS eq, V^V, len

// 圆与圆是否相切
bool tangency(Circle C1, Circle C2) { return eq(len(C1.O - C2.O), C1.r + C2.r); }// DEPENDS eq, V-V, len

// 两点间的距离
double dis(Point A, Point B) { return len(A - B); }// DEPENDS len, V-V

// 点到直线的距离
double dis(Point P, Line l) { return abs((P ^ l.v) - (l.P ^ l.v)) / len(l.v); }// DEPENDS V^V, len

// 平行直线间的距离
// NOTE 请确保两直线是平行的
double dis(Line a, Line b) { return abs((a.P ^ pnorm(a.v)) - (b.P ^ pnorm(b.v))); }// DEPENDS d*V, V^V, len, pnorm


// 平移
Line operator+(Line l, Vec v) { return {l.P + v, l.v}; }// DEPENDS V+V
Seg operator+(Seg l, Vec v) { return {l.A + v, l.B + v}; }

// 旋转
Point rotate(Point P, double rad) { return {cos(rad) * P.x - sin(rad) * P.y, sin(rad) * P.x + cos(rad) * P.y}; }// DEPENDS V+V, V-V
Point rotate(Point P, double rad, Point C) { return C + rotate(P - C, rad); }                     // DEPENDS ^1
Line rotate(Line l, double rad, Point C = O) { return {rotate(l.P, rad, C), rotate(l.v, rad)}; }  // DEPENDS ^1, ^2
Seg rotate(Seg l, double rad, Point C = O) { return {rotate(l.A, rad, C), rotate(l.B, rad, C)}; } // DEPENDS ^1, ^2

// 对称
// 关于点对称
Point reflect(Point A, Point P) { return {P.x * 2 - A.x, P.y * 2 - A.y}; }
Line reflect(Line l, Point P) { return {reflect(l.P, P), l.v}; }           // DEPENDS ^1
Seg reflect(Seg l, Point P) { return {reflect(l.A, P), reflect(l.B, P)}; } // DEPENDS ^1
// 关于直线对称

// NOTE 向量和点在这里的表现不同，求向量关于某直线的对称向量需要用reflect_v
Point reflect(Point A, Line ax) { return reflect(A, pedal(A, ax)); }             // DEPENDS ^1  DEPENDS V-V, V*V, d*V, pedal
Vec reflect_v(Vec v, Line ax) { return reflect(v, ax) - reflect(O, ax); }        // DEPENDS ^1, ^4
Line reflect(Line l, Line ax) { return {reflect(l.P, ax), reflect_v(l.v, ax)}; } // DEPENDS ^1, ^4, ^5
Seg reflect(Seg l, Line ax) { return {reflect(l.A, ax), reflect(l.B, ax)}; }     // DEPENDS ^1, ^4

// 直线与直线交点
vector<Point> inter(Line a, Line b){// DEPENDS eq, d*V, V*V, V+V, V^V
    double c = a.v ^ b.v;
    if (eq(c, 0)) return {};
    Vec v = 1 / c * Vec{a.P ^ (a.P + a.v), b.P ^ (b.P + b.v)};
    return {{v * Vec{-b.v.x, a.v.x}, v * Vec{-b.v.y, a.v.y}}};
}

// 直线与圆交点
vector<Point> inter(Line l, Circle C){// DEPENDS eq, gt, V+V, V-V, V*V, d*V, len, pedal
    Point P = pedal(C.O, l);
    double h = len(P - C.O);
    if (gt(h, C.r)) return {};
    if (eq(h, C.r)) return {P};
    double d = sqrt(C.r * C.r - h * h);
    Vec vec = d / len(l.v) * l.v;
    return {P + vec, P - vec};
}

// 圆与圆的交点
vector<Point> inter(Circle C1, Circle C2){// DEPENDS eq, gt, V+V, V-V, d*V, len, r90c
    Vec v1 = C2.O - C1.O, v2 = r90c(v1);
    double d = len(v1);
    if (gt(d, C1.r + C2.r) || gt(abs(C1.r - C2.r), d)) return {};
    if (eq(d, C1.r + C2.r) || eq(d, abs(C1.r - C2.r))) return {C1.O + C1.r / d * v1};
    double a = ((C1.r * C1.r - C2.r * C2.r) / d + d) / 2;
    double h = sqrt(C1.r * C1.r - a * a);
    Vec av = a / len(v1) * v1, hv = h / len(v2) * v2;
    return {C1.O + av + hv, C1.O + av - hv};
}

// 三角形的重心
Point barycenter(Point A, Point B, Point C){return {(A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3};}

// 三角形的外心
// NOTE 给定圆上三点求圆，要先判断是否三点共线
Point circumcenter(Point A, Point B, Point C){// DEPENDS r90c, V*V, d*V, V-V, V+V
    double a = A * A, b = B * B, c = C * C;
    double d = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    return 1 / d * r90c(a * (B - C) + b * (C - A) + c * (A - B));
}

// 三角形的内心
Point incenter(Point A, Point B, Point C){// DEPENDS len, d*V, V-V, V+V
    double a = len(B - C), b = len(A - C), c = len(A - B);
    double d = a + b + c;
    return 1 / d * (a * A + b * B + c * C);
}

// 三角形的垂心
Point orthocenter(Point A, Point B, Point C){// DEPENDS V*V, d*V, V-V, V^V, r90c
    double n = B * (A - C), m = A * (B - C);
    double d = (B - C) ^ (A - C);
    return 1 / d * r90c(n * (C - B) - m * (C - A));
}

double cross(Point a,Point b){ return a^b;}
int Quadrant(Point& a) {
    if(a.x > 0 && a.y >= 0) return 1;
    if(a.x <= 0 && a.y > 0) return 2;
    if(a.x < 0 && a.y <= 0) return 3;
    if(a.x >= 0 && a.y < 0) return 4;
}
void psort(vector<Point>&ps, Point c = O)  {// 极角排序
    sort(ps.begin(), ps.end(), [&](auto a, auto b) {
        if(Quadrant(a)!=Quadrant(b)) return Quadrant(a) < Quadrant(b);
	    return cross(a,b) > 0;
    });
}

int sgn(double x){
    if (fabs(x) < EPS) return 0;
    return (x < 0) ? -1 : 1;
}
vector<Point>andrew(int top,vector<Point>&ps){//凸包
    sort(ps.begin(),ps.end(),[&](const Point& a,const Point& b){
        return a.x < b.x || (sgn(a.x - b.x) == 0 && a.y < b.y);
    });
    auto side=[&](Point a,Point b,Point p){
        auto ab=b-a,ap=p-a;
        return cross(ab,ap);
    };
    int n=ps.size();
    if(n<3)return {};
    vector<Point>stk;
    stk.push_back(ps[0]);stk.push_back(ps[1]);
    top=1;
    for(int i=2;i<n;++i){
        while(top&&side(stk[top-1],stk[top],ps[i])<0)--top,stk.pop_back();
        ++top;
        stk.push_back(ps[i]);
    }
    ++top;
    stk.push_back(ps[n-2]);
    for(int i=n-3;i>=0;--i){
        while(top&&side(stk[top-1],stk[top],ps[i])<0)--top,stk.pop_back();
        ++top;
        stk.push_back(ps[i]);
    }
    return stk;
}
void solve(){
    
}
signed main(){
    std::ios::sync_with_stdio(false);cin.tie(0);
    solve();
}