#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define lson(rt) seg_node[rt].ls
#define rson(rt) seg_node[rt].rs
using namespace std;
const int N = (int)2e5 + 10;
struct seg {
	int ls, rs, num;
	long long sum;
}	seg_node[N * 33];

int n, m, len, p, hn, seg_cnt;
int height[N], seg_rt[N];
vector <int> vec[N];
pair <int, int> point;
void build( int &rt, int l, int r ) {
	rt = ++seg_cnt;
	seg_node[rt].num = 0;
	seg_node[rt].sum = 0;
	if ( l == r ) return;
	int mid = ( l + r ) >> 1;
	build( lson(rt), l, mid );
	build( rson(rt), mid + 1, r );
}
void update( int pre_rt, int &cur_rt, int l, int r, int pos, int val ) {
	cur_rt = ++seg_cnt;
	lson( cur_rt ) = lson( pre_rt );
	rson( cur_rt ) = rson( pre_rt );
	seg_node[cur_rt].num = seg_node[pre_rt].num + ( val > 0 ? 1 : -1 );
	seg_node[cur_rt].sum = seg_node[pre_rt].sum + val;
	if ( l == r ) return;
	int mid = ( l + r ) >> 1;
	if ( pos <= mid ) {
		update( lson(pre_rt), lson(cur_rt), l, mid, pos, val );
	} else {
		update( rson(pre_rt), rson(cur_rt), mid + 1, r, pos, val );
	}
}
long long query( int rt, int l, int r, int k ) {
	//cout <<k<<" "<<l<<" "<<r<<" "<<seg_node[rt].num<<" "<<seg_node[rt].sum<<endl;
	if ( !k ) return 0;
	if ( seg_node[rt].num <= k ) return seg_node[rt].sum;
	int mid = ( l + r ) >> 1;
	if ( seg_node[lson(rt)].num >= k ) {
		return query( lson(rt), l, mid, k );
	} else {
		return seg_node[lson(rt)].sum + query( rson(rt), mid + 1, r, k - seg_node[lson(rt)].num );
	}
}

int main() {
	//freopen( "A.in", "r", stdin );

	while ( scanf( "%d%d%d%d", &n, &m, &len, &p ) == 4 ) {
		for ( int i = 1; i <= len; i ++ ) {
			vec[i].clear();
		}
		int pn = 0;
		for ( int i = 1; i <= n; i ++ ) {
			int l, r, h;
			scanf( "%d%d%d", &l, &r, &h );
			height[i] = h;
			vec[l].push_back( h );
			vec[r + 1].push_back( -h );
			//point[++pn] = make_pair( l, h );
			//point[++pn] = make_pair( r + 1, -h );
		}
		sort( height + 1, height + 1 + n );
		hn = unique( height + 1, height + 1 + n ) - height - 1;
	
		//sort( point + 1, point + 1 + pn );
		seg_cnt = 0;
		build( seg_rt[0], 1, hn );
		for ( int i = 1; i <= len; i ++ ) {
			int pre = seg_rt[i - 1];
			int cur = pre;
			for ( int j = 0; j < (int)vec[i].size(); j ++ )	{
				int h = vec[i][j];
				h = lower_bound( height + 1, height + 1 + hn, h ) - height;
				update( pre, cur, 1, hn, h, vec[i][j] );
				//cout <<cur<<" "<<vec[i][j]<<endl;
				pre = cur;
			}
			seg_rt[i] = cur;
		}
			
		int x, a, b, c, k;	
		long long pre = 1;
		while ( m -- ) {
			scanf( "%d%d%d%d", &x, &a, &b, &c );
			k = ((long long)(a % c) * (pre % c) + b) % c;
			long long ret = query( seg_rt[x], 1, hn, k );
			if ( pre >= p ) ret <<= 1;
			//printf( "%lld\n", ret );
			printf( "%I64d\n", ret );
			pre = ret;
		}
	}
	
	return 0;
}
