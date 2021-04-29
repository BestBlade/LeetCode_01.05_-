/* ------------------------------------------------------------------|
字符串有三种编辑操作:插入一个字符、删除一个字符或者替换一个字符。 给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。

 

示例 1:

输入:
first = "pale"
second = "ple"
输出: True
 

示例 2:

输入:
first = "pales"
second = "pal"
输出: False

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/one-away-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	压缩dp法
*
*	执行用时：8 ms, 在所有 C++ 提交中击败了33.98%的用户
*	内存消耗：6.2 MB, 在所有 C++ 提交中击败了21.40%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
//动态规划，压缩dp
bool oneEditAway(string first, string second) {
    int m = first.size();
    int n = second.size();
    if (!(m * n)) {
        return (m + n) <= 1;
    }
    if (abs(m - n) > 1) {
        return false;
    }
    vector<int> pre(n + 1, 0);
    vector<int> dp(n + 1, 0);

    for (int i = 0; i <= n; ++i) {
        pre[i] = i;
    }

    for (int i = 1; i <= m; ++i) {
        dp[0] = i;
        for (int j = 1; j <= n; ++j) {
            if (first[i - 1] == second[j - 1]) {
                dp[j] = pre[j - 1];
            }
            else {
                dp[j] = min(dp[j - 1], min(pre[j], pre[j - 1])) + 1;
            }
        }
        pre = dp;
    }
    return dp[n] <= 1;
}

//双指针
bool oneEditAway(string first, string second) {
    int m = first.size();
    int n = second.size();
    if (!(m * n)) {
        return (m + n) <= 1;
    }
    if (abs(m - n) > 1) {
        return false;
    }

    int cnt = 0;
    int f = 0;
    int s = 0;
    while (cnt <= 1 && f < m && s < n) {
        if (first[f++] == second[s++]) {
            continue;
        }
        cnt++;
        if (m != n) {
            if (m > n) {
                s--;
            }
            else {
                f--;
            }
        }
    }
    return cnt <= 1;
}

int main() {
    string f = "ab";
    string s = "bc";
    cout << oneEditAway(f, s);
}