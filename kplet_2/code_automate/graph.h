#ifndef __GRAPH__
#define __GRAPH__
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
#define PI              3.14159
#define REG_GRAPH       1                   
#define QUAD_GRAPH      0                
#define K               4                   //number of neighbors.
#define MAX	            512                 
typedef list<int>::iterator adj_list_t;
typedef list<int>           int_list_t;
typedef map<int,int>	    matches_t;
typedef enum{
    WHITE = 0,GRAY,BLACK
}color_t;
typedef struct
{
	int lidx;
	int	ridx; 
	double score;
}pair_t;


typedef struct
{
    int npairs;
	pair_t pairs[MAX]; 
}match_pairs_t;


class graph
{
public:
	graph(int);
	~graph();
	void		add_edge(int x,int y);
	void		get_adj_list(int i,adj_list_t& start,adj_list_t& end);
	void		xyt2graph(const int x[],const int y[],const int t[],char type[],int n);
	void		get_xyt(int i,int* x,int* y,int *t,char* type);
	int		vertexcount(){return v.size();};
private:
	graph(){};
	vector<int_list_t> v;
	vector<int>		   x;
	vector<int>		   y;
	vector<int>		   t;
	vector<char>	           type;
};
#define MATCH_SCORE	 20
#define MISMATCH_SCORE  -20
#define DELTATHETA	 30 
#define DELTAPHI	 20 
#define DELTAR		 0.7
#define CTHETA		  10   
#define CPHI		  5    
#define CR		  0.048    
#define LOWNUM        15
typedef enum{UL,L,U} directions_t;
int  get_matching_score(int ax1,int ay1,int at1,char atype1,int ax2,int ay2,int at2,char atype2,int bx1,int by1,int bt1,char btype1, int bx2,int by2,int bt2,char btype2);
void get_matching_neighbors(graph& g,int x,color_t* gcolor,graph& h,int y,color_t* hcolor,matches_t& m);
void do_dual_bfs(graph& g,int i,graph& h,int j,int* match,int* depth,match_pairs_t* pResult);
void get_radial_coords(int ax1,int ay1,int at1,int ax2,int ay2,int at2,double*r, int* theta,int* phi);
double compute_scores(int xref[],int yref[],int refcnt,int xtst[],int ytst[],int tstcnt,match_pairs_t* result);
typedef struct{
	double	dist;
	int	idx;
}dist_element;
bool operator<(dist_element lhs,dist_element rhs);
#endif
