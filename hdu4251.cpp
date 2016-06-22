#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define lson(rt) seg_node[(rt)].ls
#define rson(rt) seg_node[(rt)].rs
const int N = (int)1e5;
struct segment_tree {
	int ls, rs, num;
}	seg_node[N * 22];

int n, m, seg_cnt, an;
int seg_rt[N + 10], a[N + 10], b[N + 10];

void build( int &rt, int l, int r ) {
	rt = ++seg_cnt;
	seg_node[rt].num = 0;
	if ( l == r ) return;
	int mid = ( l + r ) >> 1;
	build( seg_node[rt].ls, l, mid );
	build( seg_node[rt].rs, mid + 1, r );
}
void update( int pre_rt, int &cur_rt, int l, int r, int val ) {
	cur_rt = ++seg_cnt;
	seg_node[cur_rt].num = seg_node[pre_rt].num + 1;
	if ( l == r ) return;
	seg_node[cur_rt].ls = seg_node[pre_rt].ls;
	seg_node[cur_rt].rs = seg_node[pre_rt].rs;

	int mid = ( l + r ) >> 1;
	if ( val <= mid ) {
		update( seg_node[pre_rt].ls, seg_node[cur_rt].ls, l, mid, val );
	} else {
		update( seg_node[pre_rt].rs, seg_node[cur_rt].rs, mid + 1, r, val );
	}
}

void init( int cas ) {
	printf( "Case %d:\n", cas );
	for ( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		b[i] = a[i];
	}

	sort( a + 1, a + n + 1 );
	an = unique( a + 1, a + n + 1 ) - a - 1;
	seg_cnt = 0;
	build( seg_rt[0], 1, an );
	for ( int i = 1; i <= n; i ++ ) {
		b[i] = lower_bound( a + 1, a + an + 1, b[i] ) - a;

		//cout <<i<<" "<<b[i]<<endl;
		update( seg_rt[i - 1], seg_rt[i], 1, an, b[i] );
	}
}

int query( int pre_rt, int cur_rt, int l, int r, int k ) {
	if ( l == r ) return l;
	int	l_num = seg_node[lson(cur_rt)].num - seg_node[lson(pre_rt)].num;
	int mid = ( l + r ) >> 1;
	//cout <<l<<" "<<r<<" "<<l_num<<" "<<k<<endl;
	//cout <<seg_node[lson(cur_rt)].num<<" "<<seg_node[lson(pre_rt)].num<<endl;

	if ( k > l_num ) {
		return query( rson(pre_rt), rson(cur_rt), mid + 1, r, k - l_num );
	} else {
		return query( lson(pre_rt), lson(cur_rt), l, mid, k );
	}
}
int get_mid( int l, int r ) {
	int len = r - l + 1;
	return ( len + 1 ) >> 1;
}

int main() {
	//freopen( "A.in", "r", stdin );
	//freopen( "A.out", "w", stdout );
	
	int cas = 0;
	while ( scanf( "%d", &n ) == 1 ) {
		init( ++cas );
		scanf( "%d", &m );

		for ( int i = 1; i <= m; i ++ ) {
			int l, r;
			scanf( "%d%d", &l, &r );
			int ans = a[query( seg_rt[l - 1], seg_rt[r], 1, an, get_mid( l, r ) )];
			//cout <<(l + r) / 2<<endl;
			//cout <<"pos: "<<query( seg_rt[l - 1], seg_rt[r], 1, an, (r - l + 1) >> 1 )<<endl;
			
			if ( (r - l) & 1 ) {
				int tmp = a[query( seg_rt[l - 1], seg_rt[r], 1, an, get_mid( l, r + 1 ) )];	
				ans = ( ans + tmp ) / 2;
			}
			printf( "%d\n", ans );
		}
	}

	return 0;
}
