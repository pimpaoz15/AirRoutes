#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph Graph;
typedef struct node link;
typedef struct edge Edge;


int *pre, cnt, dfs;
struct node{int v; double custo; link *next;};
struct graph{int V; int E; link **adj;};
struct edge{int v; int w; double custo;};


link *NEW(int, link *, double);
Graph *GRAPHinit(int);
Edge EDGE(int, int, double);
void GRAPHinsertE(Graph *, Edge);
void GRAPHremoveE(Graph *G, Edge e);
void removeE(Edge *, Edge, int);
void GRAPHdestroy(Graph *);
void dfsR(Graph *, Edge);
void GRAPHsearch(Graph *);
int CompareEdge(Edge, Edge);
void merge(Edge*, int, int, int);
void mergesort(Edge*, int, int);
void merge_f(Edge*, int, int, int);
void mergesort_f(Edge*, int, int);
void UFinit(int, int*, int*);
int UFfind(int *, int *, int *, int *, int, int);
void UFunion(int, int, int *, int *);
int GRAPHedges(Edge *, Graph *);
int GRAPHmstE(Graph *, Edge*, Edge *, int);


int a0(Graph *, int);
double b0(Graph *, int, int);
int c0(Graph *, int);
int d0(Graph *, int);
int a1(Graph *, Edge*, Edge *, int);
int b1(Edge *, Edge *, Edge, int, int);
void d1(Graph *, Edge*, int, Edge *, int);


#endif
