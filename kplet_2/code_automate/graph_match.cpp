#include "graph.h"
#include "time.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#define MAX      512 
#define DETAILED 0
double compute_scores(int xref[],int yref[],int refcnt,int xtst[],int ytst[],int tstcnt,match_pairs_t* result);
int IO_ReadFromXYT(const char* pcFileName,int* x,int *y,int *t,char* type,int *cnt)
{
    char acStr[256];
    char* pFileName    = NULL;
    int nCnt;
    FILE* fp = fopen(pcFileName,"r");
    if(fp == NULL)
    {
        return -1;
    }
	memset(x,0,sizeof(int)*MAX);
	memset(y,0,sizeof(int)*MAX);
	memset(t,0,sizeof(int)*MAX);
	memset(type,0,sizeof(char)*MAX);
	nCnt = 0;
	while(fgets(acStr,255,fp))
    {
        *strchr( acStr,'\n')=0;
		int  ndummy;
        sscanf(acStr,"%d %d %d %d",&x[nCnt],&y[nCnt],&t[nCnt],&ndummy);
		type[nCnt] = 'R';
		nCnt++;
	}
	*cnt = nCnt;

    fclose(fp);
    return 0;
}

int main(int argc,char* argv[])
{
	int	  xref[MAX];
	int	  yref[MAX];
	int	  tref[MAX];
	char  typeref[MAX];int	xtst[MAX];
	int	  ytst[MAX];
	int	  ttst[MAX];
	char  typetst[MAX];
	int	  ref_cnt;
	int	  tst_cnt;
	int	  i,j;
	if(argc !=3)
	{
		printf("Syntax: %s <probe_file> <gallery_file>\n",argv[0]);
		exit(2);
	}

	IO_ReadFromXYT(argv[1],xref,yref,tref,typeref,&ref_cnt);
	IO_ReadFromXYT(argv[2],xtst,ytst,ttst,typetst,&tst_cnt);	
	match_pairs_t   tmpResult;
	match_pairs_t	maxResult;
	graph*	g =new graph(ref_cnt);
	graph*	h =new graph(tst_cnt);
	//convert to graphs
	g->xyt2graph(xref,yref,tref,typeref,ref_cnt);
	h->xyt2graph(xtst,ytst,ttst,typetst,tst_cnt);

	int depth		=	0;	
	int count		=	0;	
	int maxdepth	=	0;	
	int maxcount	=	0;	
	int totalcount	=	0;	
	for(i=0;i<ref_cnt;i++)
	{
	  for(j=0;j<tst_cnt;j++)
	  {
		do_dual_bfs(*g,i,*h,j,&count,&depth,&tmpResult);
		totalcount+= count;
		if(count>maxcount)
		{
		  maxcount=count;
		  maxdepth=depth;
		  memcpy(&maxResult,&tmpResult,sizeof(tmpResult));
		}
	  }
	}

	int sum = 0;
 #if DETAILED
	for(i=0;i<maxcount;i++)
	{
		fprintf(fp,"%d-->%d\n",maxResult.pairs[i].lidx,maxResult.pairs[i].ridx);
	}
 #endif 
	double dscore = compute_scores(xref,yref,ref_cnt,xtst,ytst,tst_cnt,&maxResult);
	printf("%s %s %lf\n",argv[1],argv[2],dscore);
	delete g;
	delete h;
	return 0;
}