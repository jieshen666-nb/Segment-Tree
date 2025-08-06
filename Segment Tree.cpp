// Segment Tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#define MAX_SIZE 400007

int segTree[MAX_SIZE];
int* baskets;

int max(int a, int b) {
    return a > b ? a : b;
}

void build(int p, int l, int r) {
    if (l == r) {
        segTree[p] = baskets[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    segTree[p] = max(segTree[p << 1], segTree[p << 1 | 1]);
}

int query(int p, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) {
        return INT_MIN;
    }
    if (ql <= l && r <= qr) {
        return segTree[p];
    }
    int mid = (l + r) >> 1;
    return max(query(p << 1, l, mid, ql, qr),
        query(p << 1 | 1, mid + 1, r, ql, qr));
}

void update(int p, int l, int r, int pos, int val) {
    if (l == r) {
        segTree[p] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        update(p << 1, l, mid, pos, val);
    }
    else {
        update(p << 1 | 1, mid + 1, r, pos, val);
    }
    segTree[p] = max(segTree[p << 1], segTree[p << 1 | 1]);
}

int numOfUnplacedFruits(int* fruits, int fruitsSize, int* basketsArr, int basketsSize) {
    baskets = basketsArr;
    int m = basketsSize;
    int count = 0;
    if (m == 0) {
        return fruitsSize;
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        segTree[i] = INT_MIN;
    }
    build(1, 0, m - 1);
    for (int i = 0; i < fruitsSize; i++) {
        int l = 0, r = m - 1, res = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (query(1, 0, m - 1, 0, mid) >= fruits[i]) {
                res = mid;
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        if (res != -1 && baskets[res] >= fruits[i]) {
            update(1, 0, m - 1, res, INT_MIN);
        }
        else {
            count++;
        }
    }
    return count;
}

//int main()
//{
//    std::cout << "Hello World!\n";
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
