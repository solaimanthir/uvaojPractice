#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool isSmallInBigSquare(int N, char Big[N][N], int r, int c, int n, char Small[n][n])
{
	int i, j;
	for(i = 0; i < n; ++i){
		for(j = 0; j < n; ++j){
			if(Big[r+i][c+j] != Small[i][j])
				return 0;
		}
	}
	return 1;
}

void check(int N, char Big[N][N], int n, char Small[4][n][n], int res[4])
{
	int i, j, k;
	for(i = 0; i <= (N-n); ++i){
		for(j = 0; j <= (N-n); ++j) {
			for(k = 0; k < 4; ++k) {
				if(isSmallInBigSquare(N, Big, i, j, n, Small[k]))
					res[k]++;
			}
		}
	}
}

int main()
{
	while(1) {
		int N, n, i, j, res[4];
		memset(res, 0, sizeof res);
		scanf("%d %d", &N, &n);
		if((N == 0)&&(n == 0)) break;

		char Big[N][N], Small[4][n][n];
	   	for(i = 0; i < N; ++i){
			scanf("%s", Big[i]);
		}
        for(i = 0; i < n; ++i){
            scanf("%s", Small[0][i]);
        }
		for(i = 0; i < n; ++i){
			for(j = 0; j < n; ++j){
				Small[1][i][j] = Small[0][n-1-j][i];
				Small[2][i][j] = Small[0][n-1-i][n-1-j];
				Small[3][i][j] = Small[0][j][n-1-i];
			}
		}
		check(N, Big, n, Small, res);
		printf("%d %d %d %d\n", *res, *(res+1), *(res+2), *(res+3));
	}
    return 0;
}
