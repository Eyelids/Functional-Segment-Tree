#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define lson( rt ) seg_node[rt].ls
#define rson( rt ) seg_node[rt].rs
using namespace std;
const int N = (int)1e5 + 10;
struct seg {
	int ls, rs;
	int lnum, rnum;
	seg() { lnum = 0; rnum = 0; }
	seg( int _ls, int _rs, int _lnum, int _rnum ) {
		ls = _ls, rs = _rs, lnum = _lnum, rnum = _rnum;
	}
	seg operator + ( const seg &a ) const {
		return seg( 0, 0, lnum + a.lnum, rnum + a.rnum );
	}
}	seg_node[N * 33];

int n, m, an, seg_cnt;
int w[N], a[N], seg_rt[N * 33];
vector <int> vec[N];
queue <int> que;
void build( int &rt, int l, int r ) {
	rt = ++seg_cnt;
	seg_node[rt].lnum = seg_node[rt].rnum = 0;
	if ( l == r ) return;
	int mid = ( l + r )	>> 1;
	build( lson(rt), l, mid );
	build( rson(rt), mid + 1, r );
}
void update( int pre_rt, int &cur_rt, int l, int r, int val, int toR ) {
	cur_rt = ++seg_cnt;
	lson( cur_rt ) = lson( pre_rt );
	rson( cur_rt ) = rson( pre_rt );
	seg_node[cur_rt].lnum = seg_node[pre_rt].lnum;
	seg_node[cur_rt].rnum = seg_node[pre_rt].rnum;
	if ( toR ) seg_node[cur_rt].rnum ++; else seg_node[cur_rt].lnum ++;
	if ( l == r ) return;
	int mid = ( l + r ) >> 1;
	if ( val <= mid ) {
		update( lson(pre_rt), lson(cur_rt), l, mid, val, toR );
	} else {
		update( rson(pre_rt), rson(cur_rt), mid + 1, r, val, toR );
	}
}
void init() {
	seg_cnt = 0;
	scanf( "%d", &n );
	for ( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &w[i] );
		a[i] = w[i];
	}
	sort( a + 1, a + 1 + n );
	an = unique( a + 1, a + 1 + n ) - a - 1;
	for ( int i = 1; i <= n; i ++ ) {
		w[i] = lower_bound( a + 1, a + 1 + an, w[i] ) - a;
	}
	build( seg_rt[1], 1, an );
	scanf( "%d", &m );
	for ( int i = 1; i <= n; i ++ ) {
		vec[i].clear();
	}
	while ( m -- ) {
		int u, a, b;
		scanf( "%d%d%d", &u, &a, &b );
		vec[u].push_back( a );
		vec[u].push_back( b );
	}
	que.push( 1 );
	while ( !que.empty() ) {
		int u = que.front();
		que.pop();
		if ( vec[u].empty() ) continue;
		int a = vec[u][0], b = vec[u][1];
		que.push( a ), que.push( b );
		//cout <<u<<" "<<a<<" "<<b<<endl;

		update( seg_rt[u], seg_rt[a], 1, an, w[u], 0 );
		update( seg_rt[u], seg_rt[b], 1, an, w[u], 1 );
	}
}
seg query( int rt, int l, int r, int L, int R ) {
	if ( L > R ) return seg( 0, 0, 0, 0 );
	if ( L <= l && r <= R ) {
		return seg_node[rt];
	}
	int mid = ( l + r ) >> 1;
	seg ret = seg();
	if ( L <= mid ) ret = ret + query( lson(rt), l, mid, L, R );
	if ( R >  mid ) ret = ret + query( rson(rt), mid + 1, r, L, R );
	return ret;
}

int main() {
	//freopen( "B.in", "r", stdin );
	//freopen( "A.out", "w", stdout );

	int T;
	scanf( "%d", &T );
	while ( T -- ) {
		init();
		scanf( "%d", &m );
		while ( m -- ) {
			int u, val;
			scanf( "%d%d", &u, &val );
			int idx_pre = lower_bound( a + 1, a + 1 + an, val ) - a;
			if ( a[idx_pre] >= val ) idx_pre --;
			int idx_nxt = upper_bound( a + 1, a + 1 + an, val ) - a;
			
			seg small = query( seg_rt[u], 1, an, 1, idx_pre );
			seg large = query( seg_rt[u], 1, an, idx_nxt, an );
			seg sum = query( seg_rt[u], 1, an, 1, an );

			//cout <<a[idx_pre]<<" "<<a[idx_nxt]<<" "<<val<<endl;
			//cout <<"pre:  "<<idx_pre<<"  nxt:  "<<idx_nxt<<endl;
			//cout <<sum.lnum<<" "<<sum.rnum<<" "<<small.lnum<<" "<<small.rnum<<" "<<large.lnum<<" "<<large.rnum<<endl;
			if ( small.lnum + large.lnum != sum.lnum || small.rnum + large.rnum != sum.rnum ) {
				puts( "0" );
			} else {
				int ret_x = small.rnum;
				int ret_y = large.lnum + large.rnum + small.lnum * 3 + small.rnum * 3;
				printf( "%d %d\n", ret_x, ret_y );
			}
		}
	}

	return 0;
}
