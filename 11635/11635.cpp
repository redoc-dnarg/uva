#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int MAX_N = 10005;
const int MAX_H = 105;
const int MAX_TIME = 600;
const int INFINITE = 7000000;

class Vertex {
public:
	int number = 0, edgeWeight = 0;
	Vertex( int v, int w ) : number( v ), edgeWeight( w ) {}
};

vector< Vertex > adjList[ MAX_N ];
int destination[ MAX_N ];

void SPFA( int source ) {
	queue< Vertex > Q;	// initialize
	bool hasInQ[ MAX_N ] = {};
	for ( int d : destination ) {
		d = INFINITE;
	}
	destination[ source ] = 0;
	Q.push( Vertex( source, 0 ) );
	hasInQ[source] = true;

	while ( !Q.empty() ) {
		int now = Q.front().number;
		Q.pop();
		hasInQ[ now ] = false;
		for ( Vertex toNeighbor : adjList[ now ] ) {
			int value = destination[ now ] + toNeighbor.edgeWeight;
			if ( value < destination[ toNeighbor.number ] ) {
				destination[ toNeighbor.number ] = value;
				if ( !hasInQ[ toNeighbor.number ] )
					Q.push( Vertex( toNeighbor.number, toNeighbor.edgeWeight ) );
			}
		}
	}
}

int main() {
	int vertexNum, inputH, edgeNum, hotels[ MAX_N ];
	int hotelAdj[ MAX_H ][ MAX_H ];
	while ( cin >> vertexNum && vertexNum ) {
		cin >> inputH;
		hotels[ 1 ] = 1;
		hotels[ 2 ] = inputH;
		int hotelNum = 2;  // add source and end
		int thisHotel;
		for ( int i = 0; i < inputH; i++ ) {
			cin >> thisHotel;
			hotels[ ++hotelNum ] = thisHotel;
		}
		cin >> edgeNum;
		int a, b, w;
		for ( int i = 0; i < edgeNum; i++ ) {
			cin >> a >> b >> w;
			adjList[ a ].push_back( Vertex( b, w ) );
			adjList[ b ].push_back( Vertex( a, w ) );
		}
		for ( int i = 0; i < MAX_H; i++ )
			for ( int j = 0; j < MAX_H; j++ )
				hotelAdj[ i ][ j ] = INFINITE;

		for ( int i = 1; i <= hotelNum; i++ ) {
			hotelAdj[ i ][ i ] = 0;
			SPFA( hotels[ i ] );
			for ( int j = 1; j <= hotelNum; j++ )
				if ( i != j && destination[ hotels[ j ] ] <= MAX_TIME ){
					//cout<<destination[hotels[j]]<<endl;
					hotelAdj[ i ][ j ] = 1;
				}
		}
		for ( int k = 1; k <= hotelNum; k++ )
			for ( int i = 1; i <= hotelNum; i++ )
				for ( int j = 1; j <= hotelNum; j++ )
					if ( hotelAdj[ i ][ k ] + hotelAdj[ k ][ j ] < hotelAdj[ i ][ j ] )
						hotelAdj[ i ][ j ] = hotelAdj[ i ][ k ] + hotelAdj[ k ][ j ];

		if ( hotelAdj[ 1 ][ 2 ] != INFINITE )
			cout << hotelAdj[ 1 ][ 2 ] - 1 << endl;
		else
			cout << -1 << endl;
		for ( int i = 0; i < MAX_N; i++ ) {
			adjList[ i ].clear();
		}
		for ( int i = 0; i < MAX_H; i++ ) {
			hotels[ i ] = 0;
		}
	}
}
