#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define lson(rt) seg_node[rt].ls
#define rson(rt) seg_node[rt].rs
const int N = (int)1e5;
typedef long long lint;
struct sgt {
	int ls, rs, num;
	lint sum;
}	seg_node[N * 22];
int n, m, T, seg_cnt;
int seg_rt[N + 10], a[N + 10], b[N + 10];
lint s[N + 10];

void build( int &rt, int l, int r ) {
	rt = ++seg_cnt;
	seg_node[rt].num = 0;
	seg_node[rt].sum = 0;
	if ( l == r ) return;
	int mid = ( l + r )	>> 1;
	build( seg_node[rt].ls, l, mid );
	build( seg_node[rt].rs, mid + 1, r );
}
void update( int pre_rt, int &cur_rt, int l, int r, int val ) {	
	cur_rt = ++seg_cnt;
	seg_node[cur_rt].num = seg_node[pre_rt].num + 1;
	seg_node[cur_rt].sum = seg_node[pre_rt].sum + val;
	seg_node[cur_rt].ls = seg_node[pre_rt].ls;
	seg_node[cur_rt].rs = seg_node[pre_rt].rs;
	if ( l == r ) return;

	int mid = ( l + r ) >> 1;
	if ( val <= mid ) {
		update( lson(pre_rt), lson(cur_rt), l, mid, val );
	} else {
		update( rson(pre_rt), rson(cur_rt), mid + 1, r, val );
	}
}
lint small_sum;

int query( int pre_rt, int cur_rt, int l, int r, int k ) {
	if ( l == r ) {
		small_sum += seg_node[cur_rt].sum - seg_node[pre_rt].sum;
		return l;
	}
	int l_num = seg_node[lson(cur_rt)].num - seg_node[lson(pre_rt)].num;
	
	int mid = (l + r) >> 1;

	if ( k > l_num ) {
		small_sum += seg_node[lson(cur_rt)].sum - seg_node[lson(pre_rt)].sum;
		return query( rson(pre_rt), rson(cur_rt), mid + 1, r, k - l_num );
	} else {
		return query( lson(pre_rt), lson(cur_rt), l, mid, k );
	}
}

int an;
void init() {
	scanf( "%d", &n );
	s[0] = 0;
	for ( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		s[i] = s[i - 1] + a[i];
		b[i] = a[i];
	}
	sort( a + 1, a + 1 + n );
	an = unique( a + 1, a + n + 1 ) - a - 1;
	build( seg_rt[0], 1, an );
	for ( int i = 1; i <= n; i ++ ) {
		b[i] = lower_bound( a + 1, a + an + 1, b[i] ) - a;
		update( seg_rt[i - 1], seg_rt[i], 1, an, b[i] );
	}
}
int get_mid( int l, int r ) {
	int len = r - l + 1;
	return (1 + len) >> 1;
}

int main() {
	freopen( "A.in", "r", stdin );

	scanf( "%d", &T );
	for ( int cas = 1; cas <= T; cas ++ ) {
		printf( "Case #%d:\n", cas );
		init();

		scanf( "%d", &m );
		for ( int i = 1; i <= m; i ++ ) {
			int l, r;
			scanf( "%d%d", &l, &r );
			l ++, r ++;
			small_sum = 0;
			int ans = a[query( seg_rt[l - 1], seg_rt[r], 1, an, get_mid( l, r ) )];
			
			cout <<ans<<endl;
			if ( (r - l) & 1 ) {
				int tmp = a[query( seg_rt[l - 1], seg_rt[r], 1, an, get_mid( l, r + 1 ) )];
				ans = ( ans + tmp )	>> 1;
			}	
			printf( "%d\n", ans );
		}	
	}

	return 0;
}
