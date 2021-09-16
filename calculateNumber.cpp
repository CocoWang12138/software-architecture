#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

const int MID = 200;          
int facts[11];                //  阶乘表
unordered_map<int, int> sqts; //  平方根表
int n, sqtn, factn, temp;
string n_str;
string f[2 * MID + 5][4]; // f[i][j]表示j个数组合得到i的情况

inline int fact(int x) { return facts[x]; } //  返回x的阶乘
inline int sqt(int x) { return sqts[x]; }   //  返回x的平方根

void init() { // 预处理平方根表和阶乘表
    facts[1] = sqts[1] = 1;
    for (int i = 2; i <= 10; i++) {
        facts[i] = i * facts[i - 1];
        sqts[facts[i] + i] = i;
    }
}

void initiate(int x) { //  初始化判断
    //  正负
    f[MID + x][0] = "(" + n_str + ")";
    f[MID - x][0] = "(-" + n_str + ")";
    //  是否为平方数
    if (sqtn) {
        f[MID + sqtn][0] = "(sqrt(" + n_str + "))";
        f[MID - sqtn][0] = "(-sqrt(" + n_str + "))";
        if (sqtn < 5) f[MID + fact(sqtn)][0] = "sqrt(" + n_str + ")!", f[MID - fact(sqtn)][0] = "-sqrt(" + n_str + "!)";
    }
    //  阶乘
    if (factn < MID) {
        f[MID + factn][0] = "(" + n_str + "!)";
        f[MID - factn][0] = "(-" + n_str + "!)";
    }
}

inline bool isDone(int i) { return i <= MID && i >= -MID; } //  合法性判断

void work(int j, int i) {   //  阶乘和开方
    temp = j - MID;
    if (temp > 0 && temp < 5) {
        if (f[MID + fact(temp)][i] == "") f[MID + fact(temp)][i] = f[j][i] + "!"; //  正负阶乘
        if (f[MID - fact(temp)][i] == "") f[MID - fact(temp)][i] = "-" + f[j][i] + "!";
    }
    int stmp = sqt(temp);
    if (stmp) {
        if (f[MID + stmp][0] == "") f[MID + stmp][0] = "sqrt(" + f[j][i] + ")"; //  正负开方
        if (f[MID - stmp][0] == "") f[MID - stmp][0] = "-sqrt(" + f[j][i] + ")";
        if (stmp < 5) {
            if (f[MID + fact(stmp)][0] == "") f[MID + fact(stmp)][0] = "sqrt(" + f[j][i] + ")!"; //  正负开方加阶乘
            if (f[MID - fact(stmp)][0] == "") f[MID - fact(stmp)][0] = "-sqrt(" + f[j][i] + ")!";
        }
    }
}

void addn(int i, int j) {
    temp = j - MID + n;
    if (isDone(temp) && f[MID + temp][i + 1] == "") { //  判断结果在范围内以及算出的结果之前没有出现过
        f[MID + temp][i + 1] = "(" + f[j][i] + "+" + n_str + ")";
        work(MID + temp, i + 1);
    }
    if (isDone(-temp) && f[MID - temp][i + 1] == "") {
        f[MID - temp][i + 1] = "(-(" + f[j][i] + "+" + n_str + "))";
        work(MID - temp, i + 1);
    }
}

void multn(int i, int j) {
    temp = (j - MID) * n;
    if (isDone(temp) && f[MID + temp][i + 1] == "") {
        f[MID + temp][i + 1] = "(" + f[j][i] + "*" + n_str + ")";
        work(MID + temp, i + 1);
    }
    if (isDone(-temp) && f[MID - temp][i + 1] == "") {
        f[MID - temp][i + 1] = "(-(" + f[j][i] + "*" + n_str + "))";
        work(MID - temp, i + 1);
    }
}

void subn(int i, int j) {
    temp = (j - MID) - n;
    if (isDone(temp) && f[MID + temp][i + 1] == "") { //  f[][]-n
        f[MID + temp][i + 1] = "(" + f[j][i] + "-" + n_str + ")";
        work(MID + temp, i + 1);
    }
    if (isDone(-temp) && f[MID - temp][i + 1] == "") { //  n-f[][]
        f[MID - temp][i + 1] = "(" + n_str + "-" + f[j][i] + ")";
        work(MID - temp, i + 1);
    }
}
void divn(int i, int j) {
    temp = (j - MID) / n; //  除法不会溢出
    if (temp * n == (j - MID) && f[MID + temp][i + 1] == "") {
        f[MID + temp][i + 1] = "(" + f[j][i] + "/" + n_str + ")";
        work(MID + temp, i + 1);
    }
    if (temp * n == (j - MID) && f[MID - temp][i + 1] == "") {
        f[MID - temp][i + 1] = "(-" + f[j][i] + "/" + n_str + ")";
        work(MID - temp, i + 1);
    }
}
void redivn(int i, int j) {
    if (j - MID != 0) {
        temp = n / (j - MID); //  除法不会溢出
        if (temp * (j - MID) == n && f[MID + temp][i + 1] == "") {
            f[MID + temp][i + 1] = "(" + n_str + "/" + f[j][i] + ")";
            work(MID + temp, i + 1);
        }
        if (temp * (j - MID) == n && f[MID - temp][i + 1] == "") {
            f[MID - temp][i + 1] = "(-" + n_str + "/" + f[j][i] + ")";
            work(MID - temp, i + 1);
        }
    }
}
void dp(int i, int j) { //  枚举所有合法情况 转移状态

    addn(i, j);         //  f[][]+n

    multn(i, j);        //  f[][]*n

    subn(i, j);         //  f[][]-n

    divn(i, j);         //  f[][]/n

    redivn(i, j);       //  n/f[][]

    work(j, i);         //  单独阶乘开方
}

int main() {
    cin >> n;
    n_str = to_string(n);
    init();
    sqtn = sqt(n);
    factn = fact(n);
    initiate(n);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j <= 2 * MID; j++)
            if (f[j][i] != "") //新加入一个n做运算
                dp(i, j);

    for (int i = 1; i <= 10; i++)
        if (f[i + MID][3] != "")
            cout << f[i + MID][3] << "=" << i << endl;
        else
            cout << "该式子无法给成" << i << endl;
    return 0;
}
