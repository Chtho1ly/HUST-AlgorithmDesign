#include <iostream>
#include <algorithm>
#include <stdio.h>

#include <fstream>
#define MAX 2010

using namespace std;

typedef struct truck
{
    //int nth;          //序号
    char code[7];
    int parent; //父亲节点
    int size;   //子集规模
    truck(){};
    truck(int nthInit) //构造函数
    {
        //nth = nthInit;
        parent = nthInit;
        size = 1;
    };
} Truck;

typedef struct gap
{
    int beg;  //起始城市
    int end;  //结束城市
    int cost; //花费
    gap(){};
    gap(int a, int b, int c) //构造函数
    {
        beg = a;
        end = b;
        cost = c;
    };
} Gap;

//储存城市信息的并查集vector，创建为全局变量，方便在函数中访问
int truckNum;
Truck *truckV = new Truck[MAX]();
Gap *gapV = new Gap[MAX * (MAX - 1) / 2]();
int *toUpdate = new int[MAX * (MAX - 1) / 2];

//IN:城市序号;OUT:所属并查集根城市序号
//获取某城市root
int getParent(int leaf)
{
    int root = leaf;
    int count = 0;
    while (truckV[root].parent != root)
    {
        toUpdate[count] = root;
        count++;
        root = truckV[root].parent;
    }
    for (int i = 0; i < count; i++)
        truckV[toUpdate[i]].parent = root;
    return root;
}

bool gapCmp(Gap a, Gap b)
{
    return a.cost < b.cost;
}

//IN:公路连接的两城市序号
//合并并查集
int merge(int setA, int setB)
{
    //将较小的树合并到较大的树中
    if (truckV[setA].size < truckV[setB].size)
    {
        truckV[setA].parent = setB;
        truckV[setB].size += truckV[setA].size;
    }
    else
    {
        truckV[setB].parent = setA;
        truckV[setA].size += truckV[setB].size;
    }
    return 0;
}

int getGap(int a, int b)
{
    //string aStr = truckV[a].code;
    //string bStr = truckV[b].code;
    int gap = 0;
    for (int i = 0; i < 7; i++)
        if (truckV[a].code[i] != truckV[b].code[i])
            gap++;
    return gap;
}

bool ifFinish()
{
    int ref = getParent(0);
    for (int i = 1; i < truckNum; i++)
    {
        if (ref != getParent(i))
            return false;
    }
    return true;
}

int main(void)
{
    //freopen("E:\\algorithm_EXP\\test-1-5.txt", "r", stdin);
    while (true)
    {
        int gapNum;
        scanf("%d", &truckNum);
        getchar();
        if (truckNum == 0)
            break;
        //初始化城市vector
        //truckV = new truck[truckNum]();
        for (int i = 0; i < truckNum; i++)
        {
            truckV[i] = truck(i);
            scanf("%s", truckV[i].code);
            getchar();
        }
        //初始化道路数组
        //gapV = new gap[truckNum * (truckNum - 1) / 2]();
        int count = 0;
        for (int i = 0; i < truckNum; i++)
        {
            for (int j = i + 1; j < truckNum; j++, count++)
            {
                int gapCost = getGap(i, j);
                gapV[count].beg = i;
                gapV[count].end = j;
                gapV[count].cost = gapCost;
            }
        }
        //将道路按Cost从小到大排序
        sort(gapV, gapV + truckNum * (truckNum - 1) / 2, gapCmp);
        //从小到大以此尝试添加道路
        int sum = 0;
        for (int i = 0; i < truckNum * (truckNum - 1) / 2; i++)
        {
            int rootA = gapV[i].beg;
            if (rootA != truckV[rootA].parent)
                rootA = getParent(gapV[i].beg);
            int rootB = gapV[i].end;
            if (rootB != truckV[rootB].parent)
                rootB = getParent(gapV[i].end);
            if (rootA != rootB)
            {
                merge(rootA, rootB);
                sum += gapV[i].cost;
            }
            if (ifFinish())
                break;
        }
        printf("The highest possible quality is 1/%d.\n", sum);
        //delete[] gapV;
        //delete[] truckV;
    }
    return 0;
}