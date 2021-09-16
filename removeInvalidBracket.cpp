#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stack>
#include<string>
using namespace std;
stack<int>st;///栈放的是左括号的位置
string s;
int n;
int check(int l, int r)
{
    int cnt = 0;
    for (int i = l; i <= r; i++)
    {
        if (s[i] == '(')
            ++cnt;
        else if (s[i] == ')')
            --cnt;
        else if (s[i] == '+' && cnt == 0)//若（x+y)(xy)则前面的括号不能去
            return 0;
    }
    return 1;
}
int main()
{
    int j;
    while (cin >> s)
    {
        while (1)
        {
            int flag = 0;
            int n = s.length();
            while (!st.empty())
                st.pop();
            for (j = 0; j < n; j++)
            {
                if (s[j] == '(')
                    st.push(j);
                else if (s[j] == ')')   //遇到右括号时
                {
                    int x = st.top();   
                    st.pop();   //取栈顶元素
                    if ((x == 0 || s[x - 1] == '+' || s[x - 1] == '(') && (j == n - 1 || s[j + 1] == '+' || s[j + 1] == ')'))
                    {
                        s.erase(x, 1);
                        s.erase(j - 1, 1);
                        flag = 1;
                        break;
                    }
                    else if (check(x + 1, j - 1))//判断（xy)(xy)的这种情况

                    {
                        s.erase(x, 1);
                        s.erase(j - 1, 1);
                        flag = 1;
                        break;
                    }
                }

            }
            if (flag == 0) break;
        }
        cout << s << endl;
    }
    return 0;
}

