#include <algorithm>
#include <iostream>
#include <vector>
#define INF 0x3fffffff

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long N, W; //物品数量，背包容量
    cin >> N >> W;
    vector<long long> valueV(N);
    vector<long long> weightV(N);
    //输入重量和价值信息
    long long sumValue = 0;
    for (long long i = 0; i < N; i++)
    {
        cin >> weightV[i] >> valueV[i];
        sumValue += valueV[i];
    }
    vector<long long> dp(sumValue + 1, INF);
    dp[0] = 0;
    //对于每个物品，更新能够使总value到达某值所需最小重量
    for (long long i = 0; i < N; i++)
    {
        for (long long j = sumValue; j - valueV[i] >= 0; j--)
            dp[j] = min(dp[j], dp[j - valueV[i]] + weightV[i]);
    }
    long long ans;
    for (ans = sumValue; ans >= 0; ans--)
        if (dp[ans] <= W)
            break;
    cout << ans << endl;
    return 0;
}