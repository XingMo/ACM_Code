#include <cstring>
#include <iostream>
using namespace std;
 
//    实现代码
template <int N>    //表示可用区间为[0,N)，其中N必须是2的幂数
class PointTree
{
public:
    PointTree()
    {
        clear();
        size = 0;
    }
    ~PointTree() {};
    void clear()
    {
        memset(this, 0, sizeof(*this));
    }
    void add(int n)
    {
        int i = N + n;
        ++size;
        for (++a[i]; i > 1; i /= 2)
            if (~i & 1)
                a[i / 2]++;
    }
    int cntLs(int n)
    {
        //统计小于
        int c = 0;
        //若统计小于等于则c=a;
        for (int i = N + n; i>1; i /= 2)
            if (i & 1)
                c += a[i / 2];
        return c;
    }
    int cntGt(int n)
    {
        return size - a[N + n] - cntLs(n);
    }
    void del(int n)
    {
        if (!a[n += N])
            return;
        --size;
        for (--a[n]; n > 1; n /= 2)
            if (~n & 1)
                --a[n / 2];
    }
    /*    解决：求点集中第i小的数（由0数起）
    *    注意：如果i>=size返回N-1
    */
    int operator[](int n)    //下标从0开始
    {
        int i = 1;
        while (i < N)
        {
            if (n < a[i])
                i *= 2;
            else n -= a[i], i = i * 2 + 1;
        }
        return i - N;
    }
private:
    int a[2 * N];
    int size;
};
 
PointTree<8192> t;
 
//    测试程序
int main(int argc, char const *argv[])
{
    char c;
    int n;
    while(cin >> c)
    {
        if(c == 'c')
            t.clear();
        else
        {
            cin >> n;
            if(c == 'a')
                t.add(n);
            if(c == 'd')
                t.del(n);
            if(c == 'q')
                cout << t[n] << endl;
        }
    }
    return 0;
}
