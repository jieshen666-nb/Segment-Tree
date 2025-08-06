
#include <iostream>
#include <stdio.h>
using namespace std;
int tr[10000001];
int a[100000001];
int ans[100000001];
void bui(int id, int l, int r)
{
    if (l == r)
    {
        tr[id] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    bui(id * 2, l, mid);
    bui(id * 2 + 1, mid + 1, r);
    tr[id] = min(tr[id * 2], tr[id * 2 + 1]);
}


int find(int id, int l, int r, int x, int y)
{
    if (x <= l && y >= r) return tr[id];
    int mid = (l + r) / 2;
    int ans = INT_MAX;
    if (x <= mid) ans = min(ans, find(id * 2, l, mid, x, y));
    if (y >= mid + 1) ans = min(ans, find(id * 2 + 1, mid + 1, r, x, y));
    return ans;
}

int main() {
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
    {
        cin >> a[i];
    }
    bui(1, 1, m);
    int i = 0;
    while (n--)
    {
        int x, y;
        cin >> x >> y;
        ans[i]=find(1, 1, m, x, y) ;
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        cout << ans[j] << " ";
    }
    return 0;
}
