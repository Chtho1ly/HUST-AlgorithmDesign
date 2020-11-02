#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct city
{
    int nth;
    int parent;
    int size;
    city(int nthInit)
    {
        nth = nthInit;
        parent = nthInit;
        size = 1;
    };
} City;

//储存城市信息的并查集vector，创建为全局变量，方便在函数中访问
vector<City> cityV;

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

int merge(int setA, int setB)
{
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
        cityV.clear();
        int cityNum;
        int roadNum;
        cin >> cityNum;
        if (cityNum == 0)
            break;
        cin >> roadNum;

        for (int i = 0; i <= roadNum; i++)
        {
            auto tempcity = city(i);
            cityV.push_back(tempcity);
        }

        for (int i = 0; i < roadNum; i++)
        {
            int cityBeg;
            int cityEnd;
            cin >> cityBeg >> cityEnd;
            if (getParent(cityBeg) != getParent(cityEnd))
            {
                merge(cityBeg, cityEnd);
            }
        }
        int count = -1;
        for (City i : cityV)
        {
            if (getParent(i.nth) == i.nth)
                count++;
        }
        cout << count << endl;
    }
    return 0;
}