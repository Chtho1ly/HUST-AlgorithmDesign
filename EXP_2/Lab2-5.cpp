#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#define ll long long
#define INF 0x7fffffffff

using namespace std;

//用邻接矩阵
struct pipe
{
    ll posC; //正向残存容量
    ll negC; //反向残存容量
};

ll N;
vector<vector<ll>> residualPlot; //残差图
vector<ll> augPath;              //增广路径
vector<bool> visited;

int DFS(ll curNode)
{
    augPath.push_back(curNode);
    visited[curNode] = true;
    if (curNode == N + 1)
        return 1;
    for (ll i = 0; i < N + 2; i++)
    {
        //若i未被访问且存在由当前节点到n的残存边
        if (!visited[i] && residualPlot[curNode][i] > 0)
        {
            if (DFS(i) != 0) //若找到路径，则结束DFS
                return 1;
        }
    }
    //便利所有邻边，无增广路径，恢复现场，返回
    augPath.pop_back();
    visited[curNode] = false;
    return 0;
}

int main()
{
    cin >> N;
    //输入宝石信息
    vector<ll> gems(N + 1);
    for (ll i = 1; i <= N; i++)
        cin >> gems[i];
    //初始化残差图邻接矩阵，所有边容量置为0
    //0为源点，1-N为宝石，N+1为汇点
    residualPlot.insert(residualPlot.begin(), N + 2, vector<ll>(N + 2, 0));
    for (ll i = 1; i <= N; i++)
    {
        //若宝石价值为负，则添加由源点到宝石的边，容量为宝石价值绝对值
        if (gems[i] < 0)
        {
            residualPlot[0][i] = -gems[i];
            //添加由负宝石到相关正宝石的边，容量为INF
            for (ll j = 2 * i; j <= N; j += i)
            {
                if (gems[j] > 0)
                    residualPlot[i][j] = INF;
            }
        }
        //否则，添加宝石到汇点的边，容量为宝石价值绝对值
        else
            residualPlot[i][N + 1] = gems[i];
    }
    //使用FF算法求最大流、最小割
    while (true)
    {
        //求增广路径，保存在augPath中
        visited.insert(visited.begin(), N + 2, false);
        if (DFS(0) == 0)
            break;
        ll bottleCapacity = INF;
        for (ll i = 0; i < augPath.size() - 1; i++)
            bottleCapacity = min(bottleCapacity, residualPlot[augPath[i]][augPath[i + 1]]);
        for (ll i = 0; i < augPath.size() - 1; i++)
        {
            residualPlot[augPath[i]][augPath[i + 1]] -= bottleCapacity;
            residualPlot[augPath[i + 1]][augPath[i]] += bottleCapacity;
        }
        augPath.clear();
        visited.clear();
    }

    ll total = 0; //总奖励
    for (ll i = 1; i <= N; i++)
        total += gems[i];
    //使用BFS求最小割，在退出FF、算法前visited已初始化，直接使用
    queue<ll> bfs;
    bfs.push(0);
    visited[0] = true;
    while (!bfs.empty())
    {
        ll cur = bfs.front();
        bfs.pop();
        for (ll next = 1; next <= N; next++)
        {
            if (!visited[next] && residualPlot[cur][next] > 0)
            {
                bfs.push(next);
                visited[next] = true;
                total -= gems[next];
            }
        }
    }
    cout << total << endl;
    return 0;
}