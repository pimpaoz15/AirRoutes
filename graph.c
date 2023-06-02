#include "graph.h"

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define dfsR search

/******************************************************************************
******************************************************************************/
link *NEW(int v, link *next, double custo){
    link *x = (link *) malloc(sizeof(struct node));
    x->v = v;
    x->custo = custo;
    x->next = next;
    return x;
}
/******************************************************************************
******************************************************************************/
 Edge EDGE(int v, int w, double custo){
   Edge e;
   e.v = v;
   e.w = w;
   e.custo = custo;
   return e;
 }
/******************************************************************************
******************************************************************************/
Graph *GRAPHinit(int V){
    int v;
    Graph *G = (Graph*) malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->adj = (link**) malloc(V * sizeof(link*));
    for (v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}
/******************************************************************************
******************************************************************************/
void GRAPHinsertE( Graph *G, Edge e){
    int v = e.v, w = e.w;
    double custo = e.custo;
    G->adj[v-1] = NEW(w, G->adj[v-1], custo);
    G->adj[w-1] = NEW(v, G->adj[w-1],custo);
}
/******************************************************************************
******************************************************************************/
void removeE(Edge *a, Edge e, int E) {
    int i;
    for (i = 0; i < E; i++)
      if (CompareEdge(e, a[i]) == 1){
       a[i] = EDGE(0, 0, 0);
      }
}
/******************************************************************************
******************************************************************************/
void GRAPHremoveE(Graph *G, Edge e){
    int v = e.v, w = e.w;
    link *node, *aux = NULL;

    if(G->adj[v-1] == NULL || G->adj[w-1] == NULL)
        return;

    node = G->adj[v-1];
    if(node->v == w-1){
        aux = node->next;
        free(node);
        G->adj[v-1]= aux;
    }
    else if(node->v != w-1 && node->next==NULL)
        return;
    else{
        aux = node->next;
        while(aux->v != w-1){
            if(aux==NULL)
                return;
            node = node->next;
            aux = aux->next;
        }
        node->next = aux->next;
        free(aux);
    }

    node = G->adj[w-1];
    if(node->v == v-1){
        aux = node->next;
        free(node);
        G->adj[w-1] = aux;
    }
    else if(node->v != v-1 && node->next==NULL)
        return;
    else{
        aux = node->next;
        while(aux->v != v-1){
            if(aux == NULL)
                return;
            node = node->next;
            aux = aux->next;
        }
        node->next = aux->next;
        free(aux);
    }
}
/******************************************************************************
******************************************************************************/
void GRAPHdestroy(Graph *G){
  int i;
  link *node, *aux;
  for(i = 0; i < G->V; i++){
      node = G->adj[i];
      while (node != NULL){
          aux = node;
          node = node->next;
          free(aux);
      }
  }
  free(G->adj);
  free(G);
}

/******************************************************************************
******************************************************************************/

void dfsR(Graph *G, Edge e){
  link *t;
  int w = e.w;
  pre[w-1] = cnt++;
  for(t = G->adj[w-1]; t != NULL; t = t->next)
      if (pre[t->v-1] == -1)
        dfsR(G, EDGE(w, t->v, 0));
}
/******************************************************************************
******************************************************************************/
void GRAPHsearch(Graph *G){
  int v;
  cnt = 0;
  dfs = 0;
  for (v = 0; v < G->V; v++)
      pre[v] = -1;
  for (v = 0; v < G->V; v++)
    if (pre[v] == -1){
      search(G, EDGE(v+1,v+1,0));
      dfs++;
    }
}
/******************************************************************************
******************************************************************************/
int CompareEdge(Edge e1, Edge e2){
  int i = 1;
  if (e1.v != e2.v) i = 0;
  if (e1.w != e2.w) i = 0;
  return i;
}

/******************************************************************************
******************************************************************************/
void merge(Edge *a, int l, int m, int r){
  int i, j, k;
  Edge *aux;
  aux = (Edge*) malloc((r+1)*sizeof(Edge));
  for (i = m+1; i > l; i--)
    aux[i-1] = a[i-1];
  for (j = m; j < r; j++)
    aux[r+m-j] = a[j+1];
  for (k = l; k <= r; k++){
    if (less(aux[i].custo, aux[j].custo))
      a[k] = aux[i++];
    else
      {a[k] = aux[j--];}
    }
    free(aux);
}
/******************************************************************************
******************************************************************************/
void mergesort( Edge *a, int l, int r){
    int m = (r+l)/2;
    if (r<= l) return;
    mergesort(a, l, m);
    mergesort( a, m+1, r);
    merge (a, l, m, r);
}
/******************************************************************************
******************************************************************************/
void merge_f(Edge *a, int l, int m, int r){
  int i, j, k;
  Edge *aux;
  aux = (Edge*) malloc((r+1)*sizeof(Edge));
  for (i = m+1; i > l; i--)
    aux[i-1] = a[i-1];
  for (j = m; j < r; j++)
    aux[r+m-j] = a[j+1];
  for (k = l; k <= r; k++){
    if (aux[i].v == aux[j].v && less(aux[i].w, aux[j].w))
        a[k] = aux[i++];
    else if (less(aux[i].v, aux[j].v))
        a[k] = aux[i++];
    else if (aux[i].v == aux[j].v && !less(aux[i].w, aux[j].w))
        a[k] = aux[j--];
    else
      {a[k] = aux[j--];}
    }
    free(aux);
}
/******************************************************************************
******************************************************************************/
void mergesort_f( Edge *a, int l, int r){
    int m = (r+l)/2;
    if (r<= l) return;
    mergesort_f(a, l, m);
    mergesort_f( a, m+1, r);
    merge_f(a, l, m, r);
}
/******************************************************************************
******************************************************************************/
void UFinit(int V, int *id, int *sz){
  int i;
  for (i = 0; i < V; i++){
    id[i] = i; sz[i] = 1;
  }
}
/******************************************************************************
******************************************************************************/
int UFfind(int *i, int *j, int *id, int *sz, int v, int w){

  for (*i = v-1; *i != id[*(i)]; *i = id[*(i)]);
  for (*j = w-1; *j != id[*(j)]; *j = id[*(j)]);
  if (*i == *j) return 1;

  return 0;
}
/******************************************************************************
******************************************************************************/
void UFunion(int i, int j, int *id, int *sz){
  if (sz[i] < sz[j]) {
      id[i] = j;
      sz[j] += sz[i];
  }
  else {
      id[j] = i;
      sz[i] += sz[j];
  }
}
/******************************************************************************
******************************************************************************/
int GRAPHedges(Edge *a, Graph *G){
  int v, E = 0;
  link *t;
  for (v = 0; v < G->V; v++)
    for (t = G->adj[v]; t != NULL; t = t->next)
      if (v+1 < t->v )
        a[E++] = EDGE(v+1, t->v, t->custo);
  return E;
}

/******************************************************************************
******************************************************************************/

int GRAPHmstE(Graph *G, Edge *mst, Edge *a, int E){
  int i, k, x, y;
  int *id = (int*) malloc((G->V)*sizeof(int));
  int *sz = (int*) malloc((G->V)*sizeof(int));
  UFinit(G->V, id, sz);
  for (i = 0, k = 0; i < E && k < G->V-dfs; i++)
    if (!UFfind(&x, &y, id, sz, a[i].v, a[i].w)){
      UFunion(x, y, id, sz);
      mst[k++] = a[i];
  }
  /*free all the memory allocated*/
  free(id);
  free(sz);

  return k;
}
