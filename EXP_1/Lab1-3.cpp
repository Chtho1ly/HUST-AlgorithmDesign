#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

typedef struct city
{
    //int nth;          //序号
    int parent;       //父亲节点
    int size;         //子集规模
    city(int nthInit) //构造函数
    {
        //nth = nthInit;
        parent = nthInit;
        size = 1;
    };
} City;

typedef struct road
{
    int beg;                  //起始城市
    int end;                  //结束城市
    int cost;                 //花费
    road(int a, int b, int c) //构造函数
    {
        beg = a;
        end = b;
        cost = c;
    };
} Road;

//储存城市信息的并查集vector，创建为全局变量，方便在函数中访问
vector<City> cityV;
vector<Road> roadV;

//IN:城市序号;OUT:所属并查集根城市序号
//获取某城市root
int getParent(int leaf)
{
    vector<int> toUpdate;
    int root = leaf;
    while (cityV[root].parent != root)
    {
        toUpdate.push_back(root);
        root = cityV[root].parent;
    }
    for (vector<int>::iterator i = toUpdate.begin(); i < toUpdate.end(); i++)
        cityV[*i].parent = root;
    toUpdate.clear();
    return root;
}

bool roadCmp(Road a, Road b)
{
    return a.cost < b.cost;
}

//IN:公路连接的两城市序号
//合并并查集
int merge(int setA, int setB)
{
    //将较小的树合并到较大的树中
    if (cityV[setA].size < cityV[setB].size)
    {
        cityV[setA].parent = setB;
        cityV[setB].size += cityV[setA].size;
    }
    else
    {
        cityV[setB].parent = setA;
        cityV[setA].size += cityV[setB].size;
    }
    return 0;
}

bool ifFinish()
{
    int ref = getParent(0);
    for (int i = 1; i < cityV.size(); i++)
    {
        if (ref != getParent(i))
            return false;
    }
    return true;
}

int main(void)
{
    while (true)
    {
        int cityNum;
        int roadNum;
        cityV.clear();
        roadV.clear();
        scanf("%d", &cityNum);
        getchar();
        //结束条件，城市数为0
        if (cityNum == 0)
            break;
        //初始化城市vector
        for (int i = 0; i < cityNum; i++)
        {
            City tempcity = city(i);
            cityV.push_back(tempcity);
        }
        //初始化道路vector
        for (int i = 0; i < cityNum * (cityNum - 1) / 2; i++)
        {
            int cityBeg;
            int cityEnd;
            int roadCost;
            scanf("%d %d %d", &cityBeg, &cityEnd, &roadCost);
            getchar();
            roadV.push_back(road(cityBeg - 1, cityEnd - 1, roadCost));
        }
        //将道路按Cost从小到大排序
        sort(roadV.begin(), roadV.end(), roadCmp);
        int sum = 0;
        //从小到大以此尝试添加道路
        while (!roadV.empty())
        {
            Road roadAdd = roadV.front();
            roadV.erase(roadV.begin());
            int rootA = getParent(roadAdd.beg);
            int rootB = getParent(roadAdd.end);
            if (rootA != rootB)
            {
                merge(rootA, rootB);
                sum += roadAdd.cost;
            }
            if (ifFinish())
                break;
        }
        cout << sum << endl;
    }
    return 0;
}