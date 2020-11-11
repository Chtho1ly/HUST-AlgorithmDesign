#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct item
{
    long long weight;
    long long value;
    bool operator<(item &i)
    {
        return weight < i.weight;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    long long N, W; //物品数量，背包容量
    cin >> N >> W;
    vector<item> itemV(N);
    //输入重量和价值信息
    for (long long i = 0; i < N; i++)
        cin >> itemV[i].weight >> itemV[i].value;
    sort(itemV.begin(), itemV.end());
    vector<long long> dp(W + 1, 0);
    //从物品0开始尝试装入背包
    for (long long i = 0; i < N; i++)
    {
        for (long long j = W; j >= itemV[i].weight; j--)
            dp[j] = max(dp[j], dp[j - itemV[i].weight] + itemV[i].value);
    }
    cout << dp.back() << endl;
    return 0;
}