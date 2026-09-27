#include <stdio.h>
#include <stdlib.h>

/*  
    题目描述
给定一个带权无向图，求权值总和最小的生成树（生成树需连通所有顶点，且无环，边数为顶点数 - 1）。

贪心策略
将图中所有边按权值升序排序，依次选择边，若加入该边后不会形成环，则保留该边；重复此过程，直至选择的边数为顶点数 - 1，此时得到的就是最小生成树。
*/

// 定义边结构体：包含两个顶点和边的权值
typedef struct {
    int u;  // 顶点1
    int v;  // 顶点2
    int w;  // 边的权值
} Edge;

int parent[100];  // 并查集：存储每个顶点的父节点，用于判断环

/*
 * 函数功能：并查集查找根节点（带路径压缩，提高效率）
 * 参数说明：
 * x: 需要查找根节点的顶点
 * 返回值：顶点x的根节点
 */
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // 路径压缩
    }
    return parent[x];
}

// 排序比较函数：按边的权值升序排序
int cmp(const void* a, const void* b) {
    Edge* x = (Edge*)a;
    Edge* y = (Edge*)b;
    return x->w - y->w;
}

/*
 * 函数功能：Kruskal算法求最小生成树总权值
 * 参数说明：
 * edges: 图的边数组
 * n: 图的顶点数量
 * e: 图的边数量
 * 返回值：最小生成树的总权值
 */
int kruskal(Edge edges[], int n, int e) {
    // 初始化并查集：每个顶点的父节点是自身
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    // 按边的权值升序排序
    qsort(edges, e, sizeof(Edge), cmp);

    int sum = 0;    // 最小生成树的总权值
    int count = 0;  // 已选择的边数

    // 遍历所有边，筛选符合条件的边
    for (int i = 0; i < e; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        // 若两个顶点不在同一集合，加入边不会形成环
        if (find(u) != find(v)) {
            parent[find(u)] = find(v);  // 合并两个集合
            sum += w;                   // 累加边的权值
            count++;                    // 已选择边数+1

            // 最小生成树边数为n-1，满足条件则退出
            if (count == n - 1) {
                break;
            }
        }
    }

    return sum;
}

// 主函数：测试代码
int main() {
    // 定义图的边数组（3个顶点，3条边）
    Edge edges[] = { {1, 2, 1}, {1, 3, 3}, {2, 3, 1} };
    int n = 3;  // 顶点数量
    int e = 3;  // 边数量
    // 调用函数，输出结果
    printf("最小生成树的总权值：%d\n", kruskal(edges, n, e));
    return 0;
}
