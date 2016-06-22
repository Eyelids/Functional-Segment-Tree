#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = (int)1e5;
int seg_sum[(N + 10) << 2];
int n, m;
void pushup( int rt ) {
	seg_sum[rt] = seg_sum[rt << 1] + seg_sum[rt << 1 | 1];
}
int update( int l, int r, int rt, int pos, int val ) {
	//cout <<l<<" "<<r<<" "<<pos<<" "<<val<<endl;
	if ( l == r ) {
		if ( seg_sum[rt] + val < 0 ) return 0;
		seg_sum[rt] += val;
		return 1;
	}
	int mid = ( l + r ) >> 1;

	int ret;
	if ( pos <= mid ) {
		ret = update( l, mid, rt << 1, pos, val );
	} else {
		ret = update( mid + 1, r, rt << 1 | 1, pos, val );
	}
	pushup( rt );

	return ret;
}
int query_place( int l, int r, int rt, int val ) {
	if ( r <= val )	{
		return seg_sum[rt];
	}
	int mid = ( l + r ) >> 1;

	if ( val <= mid ) {
		return query_place( l, mid, rt << 1, val );
	} else {
		return seg_sum[rt << 1] + query_place( mid + 1, r, rt << 1 | 1, val );
	}
}
int query_kth( int l, int r, int rt, int k ) {
	//cout <<l<<" "<<r<<" "<<k<<endl;
	if ( l == r ) return l;
	int mid = ( l + r ) >> 1;

	if ( k > seg_sum[rt << 1] ) {
		return query_kth( mid + 1, r, rt << 1 | 1, k - seg_sum[rt << 1] );
	} else {
		return query_kth( l, mid, rt << 1, k );
	}
}

int main() {
	//freopen( "A.in", "r", stdin );

	while ( scanf( "%d", &m ) == 1 ) {
		memset( seg_sum, 0, sizeof(seg_sum) );
		while ( m -- ) {
			int op, a, k;
			scanf( "%d", &op );
			if ( op == 0 ) {
				scanf( "%d", &a );
				update( 1, N, 1, a, 1 );
			} else if ( op == 1 ) { 
				scanf( "%d", &a );
				int flag = update( 1, N, 1, a, -1 );
				if ( !flag ) puts( "No Elment!" );
			} else {
				scanf( "%d%d", &a, &k );
					
				k += query_place( 1, N, 1, a );

				//cout <<a<<" "<<k<<endl;
				int ret = query_kth( 1, N, 1, k );
				if ( ret != N ) {
					printf( "%d\n", ret );
				} else {
					puts( "Not Find!" );
				}
			}
		}
	}
		
	return 0;
}
