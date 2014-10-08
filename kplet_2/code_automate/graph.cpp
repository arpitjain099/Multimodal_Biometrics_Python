#include "graph.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
graph::graph(int n)
{
	v.resize(n);
	x.resize(n);
	y.resize(n);
	t.resize(n);
	type.resize(n);
}
graph::~graph()
{}
void graph::add_edge(int x,int y)
{
	v[x].push_back(y);
}
void graph::get_adj_list(int i,adj_list_t& start,adj_list_t& end)
{
	start = v[i].begin();
	end   = v[i].end();
}
#if REG_GRAPH
void graph::xyt2graph(const int x[],const int y[],const int t[],char type[],int n)
{
	dist_element dist[MAX];
	int i,j;
	copy(&x[0],&x[n],this->x.begin());
	copy(&y[0],&y[n],this->y.begin());
	copy(&t[0],&t[n],this->t.begin());
	copy(&type[0],&type[n],this->type.begin());
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			dist[j].idx		= j;
			dist[j].dist	= (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
		}
		sort(&dist[0],&dist[n]);
		//add K nearest neighbors to the adjacency list
		int cnt = 0;
		for(j=1;cnt<K && j<n;j++)
		{
			add_edge(i,dist[j].idx);
			cnt++;
		}
	}
}
#elif QUAD_GRAPH
void graph::xyt2graph(const int x[],const int y[],const int t[],char type[],int n)
{
	dist_element distUL[MAX];
	dist_element distUR[MAX];
	dist_element distLR[MAX];
	dist_element distLL[MAX];
	dist_element d;
	int	cntUL = 0;
	int	cntUR = 0;
	int	cntLL = 0;
	int	cntLR = 0;
	int i,j;
	int x1,x2,y1,y2,t1,t2;
	char type1,type2;
	double r;
	int theta;
	int phi;
	copy(&x[0],&x[n],this->x.begin());
	copy(&y[0],&y[n],this->y.begin());
	copy(&t[0],&t[n],this->t.begin());
	copy(&type[0],&type[n],this->type.begin());
	//compute distances
	for(i=0;i<n;i++)
	{
		cntUL = 0;
		cntUR = 0;
		cntLL = 0;
		cntLR = 0;
		get_xyt(i,&x1,&y1,&t1,&type1);	
		for(j=0;j<n;j++)
		{
			if(i==j) continue;
			get_xyt(j,&x2,&y2,&t2,&type2);
			get_radial_coords(x1,y1,t1,x2,y2,t2,&r,&theta,&phi);
			d.dist	 = r;
			d.idx	 = j;
			if(phi<90) //Quad I
			{
				distUR[cntUR++]= d;
			}
			else if(phi<180) //Quad II
			{
				distUL[cntUL++]= d;
			}
			else if(phi< 270) //Quad III
			{
				distLL[cntLL++]= d;
			}
			else //Quad IV
			{
				distLR[cntLR++]=d;
			}
		}
		sort(&distUL[0],&distUL[cntUL]);
		sort(&distUR[0],&distUR[cntUR]);
		sort(&distLL[0],&distLL[cntLL]);
		sort(&distLR[0],&distLR[cntLR]);
		int cnt = 0;
		int iUL = 0;
		int iUR = 0;
		int iLL = 0;
		int iLR = 0;
		while(cnt<K && cnt<(n-1)&&(iUL<cntUL||iUR<cntUR||iLL<cntLL||iLR<cntLR))
		{
			if(iUL<cntUL)
			{
				{
					add_edge(i,distUL[iUL].idx);
					cnt++;
				}
				iUL++;
				
			}
			if(iUR<cntUR)
			{
				{
					add_edge(i,distUR[iUR].idx);
					cnt++;
				}
				iUR++;
				
			}
			if(iLL<cntLL)
			{
				{
					add_edge(i,distLL[iLL].idx);
					cnt++;
				}
				iLL++;
			}
			if(iLR<cntLR)
			{
				{
					add_edge(i,distLR[iLR].idx);
					cnt++;
				}
				iLR++;
			}
		}
	}
	
}
#endif
void graph::get_xyt(int i,int* x,int* y,int* t,char* type)
{
	*x		=	this->x[i];
	*y		=	this->y[i];
	*t		=	this->t[i];
	*type	=	this->type[i];
}
void get_radial_coords(int ax1,int ay1,int at1,int ax2,int ay2,int at2,
					   double*r, int* theta,int* phi)
{
	const double pi  = 3.14159;
	double		 dt	 = atan2(ay2-ay1,ax2-ax1);
	if(dt < 0)   dt  += 2*pi;
	dt  = dt*180.00/PI;
	dt  =  dt-at1;
	if(dt <0)dt  += 360;

	*r       = sqrt((ax1-ax2)*(ax1-ax2)+(ay1-ay2)*(ay1-ay2));
	*theta	 = at2-at1;

	if(*theta<0) *theta += 360;
	*phi	= (int)dt;
}
int get_matching_score(int ax1,int ay1,int at1,char atype1,int ax2,int ay2,int at2,char atype2,int bx1,int by1,int bt1,char btype1,int bx2,int by2,int bt2,char btype2)
{
	double	r1		=	0;
	double	r2		=	0;
	int		theta1	=	0;
	int		theta2	=	0;
	int		phi1	=	0;
	int		phi2	=	0;
	int		dtheta	=	0;
	int		dphi	=	0;
	double  dr		=	0;
	#if 1
	if(atype1 != btype1)
		return MISMATCH_SCORE;
	if(atype2 != btype2)
		return MISMATCH_SCORE;
	#endif
	get_radial_coords(ax1,ay1,at1,ax2,ay2,at2,&r1,&theta1,&phi1);
	get_radial_coords(bx1,by1,bt1,bx2,by2,bt2,&r2,&theta2,&phi2);
	dr			=	fabs(log(r1)-log(r2));
	dtheta			=	abs(theta1-theta2);
	dphi			=	abs(phi1-phi2);
	if(dtheta> (360-dtheta)) dtheta = 360-dtheta;
	if(dphi  > (360-dphi))   dphi	= 360-dphi;
	if(dr<fabs(log(DELTAR)) && dtheta <=DELTATHETA && dphi<=DELTAPHI)
	{
		double theta_cost = dtheta*dtheta/(2*CTHETA*CTHETA);
		double phi_cost   = dphi*dphi/(2*CPHI*CPHI);
		double r_cost	  = dr*dr/(2*CR*CR);
		return MATCH_SCORE*exp(-(theta_cost+phi_cost+r_cost));
	}
	return MISMATCH_SCORE;
}
void get_matching_neighbors(graph& g,int x,color_t*gcolor,graph& h,int y,color_t* hcolor,matches_t& matches)
{	
	int		v[2*K][2*K]	=	{0};	
	directions_t	d[2*K][2*K];
	int		gv[2*K]		=	{0}; //vertices of g
	int		hv[2*K]		=	{0}; //vertices of h
	int		lscore		=	 0;
	int		uscore		=	0;
	int		ulscore		=	0;
	int		i		=	0;
	int		j		=	0;
	int		ax1,ay1,at1;
	int		ax2,ay2,at2;
	char		atype1,atype2;
	int		bx1,by1,bt1;
	int		bx2,by2,bt2;
	char		btype1,btype2;
	adj_list_t	gnbr,gend;
	adj_list_t	hnbr,hend;
	matches.clear(); 
	g.get_xyt(x,&ax1,&ay1,&at1,&atype1);
	h.get_xyt(y,&bx1,&by1,&bt1,&btype1);
	g.get_adj_list(x,gnbr,gend);
	for(i=1;gnbr!=gend;gnbr++,i++)
	{
		g.get_xyt(*gnbr,&ax2,&ay2,&at2,&atype2);
		gv[i]	=	*gnbr;
		h.get_adj_list(y,hnbr,hend);
		for(j=1;hnbr!=hend;hnbr++,j++)
		{
			hv[j]= *hnbr;
			h.get_xyt(*hnbr,&bx2,&by2,&bt2,&btype2);
			uscore	=	v[i-1][j];
			lscore	=	v[i][j-1];
			if(hcolor[*hnbr]!= WHITE || gcolor[*gnbr]!= WHITE)
			{
				ulscore =	v[i-1][j-1]+MISMATCH_SCORE;
			}
			else
			{
				
				ulscore	=	v[i-1][j-1]+get_matching_score(ax1,ay1,at1,atype1,ax2,ay2,at2,atype2,
								  bx1,by1,bt1,btype1,bx2,by2,bt2,btype2);
			}

			if((ulscore > uscore) && (ulscore > lscore))
			{
				d[i][j] = UL;
				v[i][j] = ulscore;
			}
			else if((uscore > lscore) && (uscore > ulscore))
			{
				d[i][j] = U;
				v[i][j] = uscore;
			}
			else 
			{
				d[i][j] = L;
				v[i][j] = lscore;
			}
		}
	}
	int M= --i;
	int N= --j;
	while(i>0 && j>0)
	{
		if(d[i][j] == UL)
		{
		
			matches[gv[i]]=hv[j]; 
			i--;
			j--;
		}
		else if(d[i][j] == L)
		{
			j--;
		}
		else if(d[i][j] == U)
		{
			i--;
		}
	}
}
void do_dual_bfs(graph& g,int i,graph& h,int j,int *match,int* maxdepth,match_pairs_t* pResult)
{
	color_t			gcolor[MAX]	=	{WHITE};
	color_t			hcolor[MAX]	=	{WHITE};
	vector<int>		gdepth;
	vector<int>		hdepth;
	list<int>		gQ;
	list<int>		hQ;
	map<int,int>::const_iterator ii;
	matches_t		m;
	int			count		=	1;
	int			gu		=	0;
	int			hu		=	0;	
	gdepth.resize(g.vertexcount()+1);
	hdepth.resize(h.vertexcount()+1);
	gdepth.assign(gdepth.size(),0);
	hdepth.assign(hdepth.size(),0);
	gQ.push_back(i); gcolor[i]=GRAY;
	hQ.push_back(j); hcolor[i]=GRAY;
	pResult->pairs[0].lidx = i;
	pResult->pairs[0].ridx = j;
	while(!gQ.empty() && !hQ.empty())
	{
		gu = gQ.front();gQ.pop_front(); 
		hu = hQ.front();hQ.pop_front();
		m.clear();
		get_matching_neighbors(g,gu,gcolor,h,hu,hcolor,m);
		for(ii=m.begin();ii!=m.end();ii++)
		{
			if((gcolor[ii->first] == WHITE) &&
			   (hcolor[ii->second]== WHITE))
			{
				gdepth[ii->first] = gdepth[gu]+1;
				hdepth[ii->second]= hdepth[hu]+1;

				if(*maxdepth < (gdepth[ii->first]+hdepth[ii->second]))
				{
					*maxdepth = (gdepth[ii->first]+hdepth[ii->second]);
				}

				gQ.push_back(ii->first);
				hQ.push_back(ii->second);
				pResult->pairs[count].lidx = ii->first;
				pResult->pairs[count].ridx = ii->second;
				count++;
			}
			gcolor[ii->first] = GRAY;
			hcolor[ii->second]= GRAY;
		}
		gcolor[gu] = BLACK; 
		hcolor[hu] = BLACK;
	}
	*match = count;
	pResult->npairs=count;
	gdepth.clear();hdepth.clear();
	gQ.clear();hQ.clear();
	m.clear();
}

bool operator<(dist_element lhs,dist_element rhs)
{
	return (lhs.dist < rhs.dist);
}
double compute_scores(int xref[],int yref[],int refcnt,int xtst[],int ytst[],int tstcnt,match_pairs_t * result)
{
	int i =0;
	int j=0;
	int	   match_cnt=result->npairs;
	double s1 = (double)(match_cnt)/(tstcnt);
	double s2 = (double)(match_cnt)/(refcnt);

	if(refcnt < LOWNUM || tstcnt < LOWNUM)
	{
		if(s1>s2) {/*printf("Case no 1, score = %lf",s1);*/ return s1;} // max(m/Mr,m/Mt)
		/*printf("Case no 1, score = %lf",s2);*/ return s2;
	}
	else
	{
		/*printf("Case no 2, score = %lf",s1*s2);*/
		return (s1*s2);  // if Mr >= Mth and Mt >=Mth
	}
}
