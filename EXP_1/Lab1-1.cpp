#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct city
{
    int nth;//序号
    int parent;//父亲节点
    int size;//子集规模
    city(int nthInit)//构造函数
    {
        nth = nthInit;
        parent = nthInit;
        size = 1;
    };
} City;

//储存城市信息的并查集vector，创建为全局变量，方便在函数中访问
vector<City> cityV;

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
    for (int i : toUpdate)
        cityV[i].parent = root;
    return root;
}

//IN:公路连接的两城市序号
//合并并查集
int merge(int setA, int setB)
{
    setA = getParent(setA);
    setB = getParent(setB);
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

int main(void)
{
    while (true)
    {
        int cityNum;
        int roadNum;
        cityV.clear();
        cin >> cityNum;
        //结束条件，城市数为0
        if (cityNum == 0)
            break;
        cin >> roadNum;
        //初始化vector，因为城市序号从1开始，所以第一个元素无意义
        for (int i = 0; i <= cityNum; i++)
        {
            auto tempcity = city(i);
            cityV.push_back(tempcity);
        }

        for (int i = 0; i < roadNum; i++)
        {
            int cityBeg;
            int cityEnd;
            scanf("%d %d", &cityBeg, &cityEnd);
            if (getParent(cityBeg) != getParent(cityEnd))
            {
                merge(cityBeg, cityEnd);
            }
        }
        //第一个元素无意义，初值为-1
        int count = -1;
        for (City i : cityV)
        {
            //对根节点计数，结果减1即为需要路径数量
            if (getParent(i.nth) == i.nth)
                count++;
        }
        cout << count - 1 << endl;
    }
    return 0;
}