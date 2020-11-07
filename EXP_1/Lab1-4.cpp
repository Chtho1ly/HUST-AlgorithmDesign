#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <math.h>

using namespace std;

typedef struct land
{
    //int nth;          //序号
    int posX;
    int posY;
    int parent;                                   //父亲节点
    int size;                                     //子集规模
    land(int nthInit, int posXInit, int posYInit) //构造函数
    {
        //nth = nthInit;
        posX = posXInit;
        posY = posYInit;
        parent = nthInit;
        size = 1;
    };
} Land;

typedef struct bridge
{
    int beg;                    //起始城市
    int end;                    //结束城市
    double cost;                //花费
    bridge(int a, int b, double c) //构造函数
    {
        beg = a;
        end = b;
        cost = c;
    };
} Bridge;

//储存城市信息的并查集vector，创建为全局变量，方便在函数中访问
vector<Land> landV;
vector<Bridge> bridgeV;

//IN:城市序号;OUT:所属并查集根城市序号
//获取某城市root
int getParent(int leaf)
{
    vector<int> toUpdate;
    int root = leaf;
    while (landV[root].parent != root)
    {
        toUpdate.push_back(root);
        root = landV[root].parent;
    }
    for (vector<int>::iterator i = toUpdate.begin(); i < toUpdate.end(); i++)
        landV[*i].parent = root;
    toUpdate.clear();
    return root;
}

bool bridgeCmp(Bridge a, Bridge b)
{
    return a.cost < b.cost;
}

//IN:公路连接的两城市序号
//合并并查集
int merge(int setA, int setB)
{
    //将较小的树合并到较大的树中
    if (landV[setA].size < landV[setB].size)
    {
        landV[setA].parent = setB;
        landV[setB].size += landV[setA].size;
    }
    else
    {
        landV[setB].parent = setA;
        landV[setA].size += landV[setB].size;
    }
    return 0;
}

double getDistance(int i, int j)
{
    return (sqrt(pow(landV[i].posX - landV[j].posX, 2) + pow(landV[i].posY - landV[j].posY, 2)));
}

bool ifFinish()
{
    int ref = getParent(0);
    for (int i = 1; i < landV.size(); i++)
    {
        if (ref != getParent(i))
            return false;
    }
    return true;
}

int main(void)
{
    int s;
    scanf("%d", &s);
    getchar();
    while (s-- != 0)
    {
        int landNum;
        int bridgeNum;
        landV.clear();
        bridgeV.clear();
        scanf("%d", &landNum);
        getchar();
        //初始化城市vector
        for (int i = 0; i < landNum; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            getchar();
            Land templand = land(i, x, y);
            landV.push_back(templand);
        }
        //初始化道路vector
        for (int i = 0; i < landNum; i++)
        {
            for (int j = i + 1; j < landNum; j++)
            {
                double bridgeCost = getDistance(i, j);
                if (bridgeCost < 10 || bridgeCost > 1000)
                    continue;
                bridgeV.push_back(bridge(i, j, bridgeCost * 100));
            }
        }
        //将道路按Cost从小到大排序
        sort(bridgeV.begin(), bridgeV.end(), bridgeCmp);
        double sum = 0;
        bool getAnswer = false;
        //从小到大以此尝试添加道路
        while (!bridgeV.empty())
        {
            Bridge bridgeAdd = bridgeV.front();
            bridgeV.erase(bridgeV.begin());
            int rootA = getParent(bridgeAdd.beg);
            int rootB = getParent(bridgeAdd.end);
            if (rootA != rootB)
            {
                merge(rootA, rootB);
                sum += bridgeAdd.cost;
            }
            if (ifFinish())
            {
                getAnswer = true;
                break;
            }
        }
        if (getAnswer)
            printf("%.1f\n", sum);
        else
            printf("oh!\n");
    }
    return 0;
}