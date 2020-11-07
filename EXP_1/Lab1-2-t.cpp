#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#define villageMAX 30
//#define roadMAX 100

using namespace std;

typedef struct village
{
    //int nth;    //序号
    int parent; //父亲节点
    int size;   //子集规模
    village(){};
    village(int nthInit) //构造函数
    {
        //nth = nthInit;
        parent = nthInit;
        size = 1;
    };
} Village;

typedef struct road
{
    int beg;  //起始城市
    int end;  //结束城市
    int cost; //花费
    road(){};
    road(int a, int b, int c) //构造函数
    {
        beg = a;
        end = b;
        cost = c;
    };
} Road;

//vector，创建为全局变量，方便在函数中访问
vector<Village> villageV(villageMAX, village());
int villageNum;
//vector<Road> roadV(roadMAX, road());
vector<Road> roadV;
int roadNum;
vector<int> toUpdate(villageMAX);

//IN:城市序号;OUT:所属并查集根城市序号
//获取某城市root
int getParent(int leaf)
{
    int root = leaf;
    //int count=0;
    while (villageV[root].parent != root)
    {
        //toUpdate[count] = root;
        //count++;
        root = villageV[root].parent;
    }
    //for (int i = 0; i < count; i++)
    //    villageV[toUpdate[i]].parent = root;
    return root;
}

bool roadCmp(road a, road b)
{
    //return a.cost < b.cost;
    return a.cost > b.cost;
}

//IN:公路连接的两城市序号
//合并并查集
int merge(int setA, int setB)
{
    //将较小的树合并到较大的树中
    villageV[setA].parent = setB;
    return 0;
}

bool ifFinish()
{
    int ref = getParent(0);
    for (int j = 1; j < villageNum; j++)
    {
        if (ref != getParent(j))
            return false;
    }
    return true;
}

int main(void)
{
    while (true)
    {
        villageNum = 0;
        roadNum = 0;
        scanf("%d", &villageNum);
        getchar();
        //结束条件，城市数为0
        if (villageNum == 0)
            break;
        //初始化城市vector
        for (int i = 0; i < villageNum; i++)
        {
            villageV[i].parent = i;
            villageV[i].size = 1;
        }
        //初始化道路vector
        for (int i = 0; i < villageNum - 1; i++)
        {
            int num;
            char villageBeg;
            cin >> villageBeg >> num;
            //scanf("%c %d", &villageBeg, &num);
            getchar();
            //villageBeg -= 'A';
            for (int j = 0; j < num; j++)
            {
                char villageEnd;
                int roadCost;
                //scanf("%c %d", &villageEnd, &roadCost);
                cin >> villageEnd >> roadCost;
                getchar();
                //roadV[roadNum].beg = i;
                //roadV[roadNum].end = int(villageEnd - 'A');
                //roadV[roadNum].cost = roadCost;
                roadV.push_back(road(i, int(villageEnd - 'A'), roadCost));
                roadNum++;
            }
        }
        //将道路按Cost从小到大排序
        sort(roadV.begin(), roadV.end(), roadCmp);
        int sum = 0;
        //从小到大以此尝试添加道路
        //for (int i = 0; i < roadNum; i++)
        while (!roadV.empty())
        {
            Road roadAdd = roadV.back();
            roadV.pop_back();
            //int rootA = getParent(roadAdd.beg);
            //int rootB = getParent(roadAdd.end);
            int rootA = roadAdd.beg;
            int rootB = roadAdd.end;
            while (villageV[rootA].parent != rootA)
                rootA = villageV[rootA].parent;
            while (villageV[rootB].parent != rootB)
                rootB = villageV[rootB].parent;
            if (rootA != rootB)
            {
                villageV[rootA].parent = rootB;
                //merge(rootA, rootB);
                sum += roadAdd.cost;
            }
            //if (ifFinish())
            //    break;
        }
        //printf("%d\n", sum);
        cout << sum << endl;
    }
    return 0;
}