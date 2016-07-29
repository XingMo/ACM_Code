#include<bits/stdc++.h>
using namespace std;
const int N = 105;
const double eps = 1e-8;
int tp[N];
double n[N][N];
double x[N];
int free_x[N];
int Gauss(int row, int col){
    int r, c, tmax;
    memset(x, 0, sizeof(x));
    for(r = c = 0; r < row && c < col; c++){
//    	printf("%d %d %d\n", r, c, (int)n[15][15]);
        tmax = r;
        for(int i = r+1; i < row; ++i) if( abs(n[i][c]) > abs(n[tmax][c]) ) tmax = i;
        if(tmax != r ) for(int i = c; i < col+1; ++i) swap(n[tmax][i], n[r][i]);
        if(abs(n[r][c] < eps)) continue;
        for(int i = r+1; i < row; ++i){
            if(abs(n[i][c]) <= eps) continue;
            double tmp = n[i][c] / n[r][c];
            for(int j = c; j < col+1; ++j){
                n[i][j] -= n[r][j]*tmp;
            }
        }
        r++;
    }
//    for(int i=0; i<100; i++,puts("")) for(int j=0; j<=100; j++) printf("%2d", (int)n[i][j]);
    
    for(int i = r-1; i >= 0; --i){
        double tmp = n[i][col];
        for(int j = i+1; j < col; ++j){
            if( abs(n[i][j]) > eps){
                tmp -= x[j]*n[i][j];
            }
        }
        x[i] = tmp / n[i][i];
    }
    for(int i=0; i<100; i++) printf("%d ", (int)x[i]);
//    for(int i=0; i<100; i++,puts("")) for(int j=0; j<=100; j++) printf("%2d", (int)n[i][j]);
    return 1;
}
int main(){
	freopen("in.txt", "r", stdin);
	freopen("stdout.txt", "w", stdout);
    int T, ca = 1;
    scanf("%d", &T);
    while(T--){
        int a, b, N;
        scanf("%d", &N);
        memset(tp, 0, sizeof(tp));
        for(int i = 0; i < N; ++i) {
            scanf("%d%d", &a, &b);
            tp[a] = b;
        }
        memset(n, 0, sizeof(n));
        n[99][99] = 1;
        n[99][100] = 0;
        for(int i = 1; i < 100; ++i){
            if(tp[i]){
                n[i-1][i-1] = 1;
                n[i-1][tp[i]-1] = -1;
                n[i-1][100] = 0;
            }
            else{
                int k = 0;
                for(int j = 1; j <= 6; ++j){
                    if(j+i <= 100){
                        k += 1;
                        n[i-1][i+j-1] = -1;
                    }
                }
                n[i-1][i-1] = k;
                n[i-1][100] = 6;
            }
        }
        
        Gauss(100, 100);
//        printf("Case %d: %.8f\n", ca++, x[0]);
    }
}
