#include <algorithm>
#include <iostream>
#include <vector>
#define ll long long
#define INF 0x7fffffffffffffff

using namespace std;

ll sum(vector<ll>::iterator beg, vector<ll>::iterator end)
{
    ll ans = 0;
    while (beg < end)
    {
        ans += *beg;
        beg++;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<ll> slimes(N); //各史莱姆初始大小
    for (ll i = 0; i < N; i++)
        cin >> slimes[i];
    vector<vector<ll>> dp(N, vector<ll>(N, INF)); //动态规划，dp[i][j]表示合并从[i,j]的史莱姆的最小消耗
    //将对角线上的小号初始化为1
    for (ll i = 0; i < N; i++)
        dp[i][i] = 0;
    for (ll k = 0; k < N; k++)
    {
        for (ll i = k - 1; i >= 0; i--)
        {
            ll minCost = INF;
            for (ll j = i; j < k; j++)
            {
                minCost = min(minCost, dp[i][j] + dp[j + 1][k] + sum(slimes.begin() + i, slimes.begin() + k + 1));
            }
            dp[i][k] = minCost;
        }
    }
    cout << dp[0][N - 1] << endl;
    return 0;
}