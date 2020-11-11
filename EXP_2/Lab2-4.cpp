#include <algorithm>
#include <iostream>
#include <vector>
#define ll long long
#define INF 0x7fffffffffffff

using namespace std;

struct site
{
    ll x, y, z;
};

vector<site> siteV; //各城市坐标

ll distance(ll a, ll b) //返回由a到达b的cost
{
    return abs(siteV[a].x - siteV[b].x) + abs(siteV[a].y - siteV[b].y) + max(siteV[b].z - siteV[a].z, (long long)0);
}

int main()
{
    int N;
    cin >> N;
    siteV.insert(siteV.begin(), N, site());
    for (int i = 0; i < N; i++)
        cin >> siteV[i].x >> siteV[i].y >> siteV[i].z;
    //dp[i][j]表示由起点出发，到达状态i，目前处于城市j所需花费
    //状态：长度为N的二进制序列，第k位为1表示城市k已访问，为0表示未访问
    vector<vector<ll>> dp(1 << N, vector<ll>(N, INF));
    //由未访问任何城市的状态访问起点花费为0
    dp[0][0] = 0;
    for (ll i = 1; i < (1 << N); i++)
    {
        for (ll j = 0; j < N; j++)
        {
            if (((i >> j) & 1) == 1)
            {
                for (ll k = 0; k < N; k++) //确定上一次访问的城市k，即从哪种状态转换到当前状态可以使总cost最小
                {
                    dp[i][j] = min(dp[i][j], dp[i - (1 << j)][k] + distance(k, j));
                }
            }
        }
    }
    cout << dp[(1 << N) - 1][0] << endl;
    return 0;
}