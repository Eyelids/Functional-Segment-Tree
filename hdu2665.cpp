#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = (int)1e5;
const int M = N * 22 + 10;
struct node {
	int ls, rs, sum;
}	seg_node[M];
int seg_rt[N + 10], seg_cnt, n, m;

void build( int &rt, int l, int r ) {
	rt = ++seg_cnt;
	seg_node[rt].sum = 0;
	if ( l == r ) return;

	int m = ( l + r ) >> 1;
	build( seg_node[rt].ls, l, m );
	build( seg_node[rt].rs, m + 1, r );
}
void update( int pre_rt, int &cur_rt, int l, int r, int val ) {
	cur_rt = ++seg_cnt;
	seg_node[cur_rt].sum = seg_node[pre_rt].sum + 1; 
	seg_node[cur_rt].ls = seg_node[pre_rt].ls;
	seg_node[cur_rt].rs = seg_node[pre_rt].rs;
	if ( l == r ) return;

	int m = ( l + r ) >> 1;
	if ( val <= m ) {
		update( seg_node[pre_rt].ls, seg_node[cur_rt].ls, l, m, val );
	} else {
		update( seg_node[pre_rt].rs, seg_node[cur_rt].rs, m + 1, r, val );
	}	
}
int query( int l_rt, int r_rt, int l, int r, int k ) {
	if ( l == r ) return l;
	int num = seg_node[seg_node[r_rt].ls].sum - seg_node[seg_node[l_rt].ls].sum;

	int m = ( l + r ) >> 1;
	if ( num < k ) {
		return query( seg_node[l_rt].rs, seg_node[r_rt].rs, m + 1, r, k - num );
	} else {
		return query( seg_node[l_rt].ls, seg_node[r_rt].ls, l, m, k );
	}
}

int a[N + 10], b[N + 10];

int main() {
	//freopen( "A.in", "r", stdin );

	int T;
	scanf( "%d", &T );
	while ( T -- ) {
		scanf( "%d%d", &n, &m );
		seg_cnt = 0;

		for ( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			//update( seg_rt[i - 1], seg_rt[i], 1, n, x );
			b[i] = a[i];
		}
		sort( a + 1, a + n + 1 );
		int an = unique( a + 1, a + n + 1 ) - a - 1;
		build( seg_rt[0], 1, an );
		for ( int i = 1; i <= n; i ++ ) {
			b[i] = lower_bound( a + 1, a + 1 + an, b[i] ) - a;
			update( seg_rt[i - 1], seg_rt[i], 1, an, b[i] );
		}

		while ( m -- ) {
			int l, r, k;
			scanf( "%d%d%d", &l, &r, &k );
			//int sum = query( seg_rt[l - 1], 1, n, k );
			int pos = query( seg_rt[l - 1], seg_rt[r], 1, an, k );
			printf( "%d\n", a[pos] );
		}
	}

	return 0;	
}


