
#include "graph.h"

/******************************************************************************
******************************************************************************/
int a0(Graph *G, int v){
    int count;
    link *node;
    if (v < 1 || v > G->V)
    	return -1;
    node = G->adj[v-1];
    if (node == NULL) return -1;
    count = 0;
    while(node != NULL){
        count++;
        node = node->next;
    }
    return count;
}
/******************************************************************************
******************************************************************************/
double b0(Graph *G, int v1, int v2){
    link *node;
    if(v1 < 1 || v1 > G->V || v2 < 1 || v2 > G->V)
    	return -1;
    node = G->adj[v1-1];
    while (node != NULL){
        if (node->v == v2) return node->custo;
        node = node->next;
    }
    return -1;
}
/******************************************************************************
******************************************************************************/
int c0(Graph *G, int v){
  link *node, *aux, *next;
  int i;
  if (v < 1 || v > G->V)
    	return -1;
  node = G->adj[v-1];
  if (node == NULL) return -1;
  while (node != NULL){
    i = node->v;
    for (next = node->next; next != NULL;next = next->next)
      for(aux = G->adj[i-1]; aux != NULL; aux = aux->next){
        if (aux->v == next->v) return 1;
      }
    node = node->next;
  }
  return 0;
}

/******************************************************************************
******************************************************************************/
int d0(Graph *G, int v){
  link *node, *aux, *next;
  int i, count = 0;
  if (v < 1 || v > G->V)
    	return -1;
  node = G->adj[v-1];
  if (node == NULL) return -1;
  while (node != NULL){
    i = node->v;
    for (next = node->next; next != NULL;next = next->next)
      for(aux = G->adj[i-1]; aux != NULL; aux = aux->next){
        if (aux->v == next->v) count++;
      }
    node = node->next;
  }
  if(count == 0) return 0;
  return count;
}

/******************************************************************************
******************************************************************************/

int a1(Graph *G, Edge *mst, Edge *a, int E){
  int i;
  i = GRAPHmstE(G, mst, a, E);
  return i;
}

/******************************************************************************
******************************************************************************/
int b1(Edge *a, Edge *st, Edge e, int n, int E){
  int v = e.v, w = e.w;
  int i, j, isIn = -1;
  for(i = 0; i < E; i++)
    if ((a[i].w == v && a[i].v == w) || (a[i].w == v && a[i].v == w)){
      isIn = 1;
      for (j = 0; j < n; j++){
        if (st[j].custo == 0) st[j] = a[i];
        break;
      }
      break;
    }
  return isIn;
}


/******************************************************************************
******************************************************************************/
void d1(Graph *G, Edge *mst, int v, Edge *a, int E){
  int i, count;
  count = GRAPHmstE(G, mst, a, E);
  for (i = 0; i < count; i++)
    if (mst[i].v == v || mst[i].w == v) removeE(a, mst[i], E);
}
/******************************************************************************
******************************************************************************/
