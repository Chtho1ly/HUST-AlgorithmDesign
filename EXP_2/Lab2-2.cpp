#include <algorithm>
#include <iostream>
#include <vector>
#define INF 0x3fffffff

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long H, N; //怪物血量，魔法容量
    cin >> H >> N;
    vector<long long> damageV(N);
    vector<long long> costV(N);
    //输入魔法伤害和消耗
    for (long long i = 0; i < N; i++)
        cin >> damageV[i] >> costV[i];
    long long maxDPH = *max_element(damageV.begin(), damageV.end());
    vector<long long> dp(H + maxDPH + 1, INF);
    dp[0] = 0;
    //对于种魔法，更新使怪物死亡消耗的最小魔力值
    for (long long i = 0; i < N; i++)
    {
        for (long long j = damageV[i]; j <= H + maxDPH; j++)
            dp[j] = min(dp[j], dp[j - damageV[i]] + costV[i]);
    }
    cout << *min_element(dp.begin() + H, dp.end()) << endl;
    return 0;
}