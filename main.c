#include "graph.h"

enum variant {A0, B0, C0, D0, A1, B1, C1, D1, E1};

int main(int argc, char *argv[]){
    int V, E, i, j, n, isIn = -1;
    int  vi, vj, V_aux, V_adj;
    int tamanho_nome, count, aux_count;
    double custo, total = 0, aux_total = 0;
    enum variant v = A0;
    char var[3] = "";
    char extOut[] = ".bbones";
    char *nomeFicheiroIn , *nomeFicheiroOut;
    Graph *graph;
    Edge e, *mst, *st, *a;
    FILE *fpIn, *fpOut;


    if(argc < 2) exit(0);

    nomeFicheiroIn = argv[1];
    tamanho_nome = strlen(nomeFicheiroIn) - strlen(".routes");
    nomeFicheiroOut = (char *) calloc((tamanho_nome + strlen(extOut) + 1), sizeof(char));
    strncpy(nomeFicheiroOut, nomeFicheiroIn, tamanho_nome);
    strcat(nomeFicheiroOut, extOut);

    /* open input and output files */
    fpIn  = fopen(nomeFicheiroIn,"r");
    fpOut = fopen (nomeFicheiroOut, "w");
    if(fpOut == NULL) {
        exit(0);
      }

    /* read input file, build graph list */
    while (1) {
        if (fscanf(fpIn, "%d %d %s", &V, &E, var) == 3) {


          if (strcmp(var, "A0") == 0)
              v = A0;
          else if (strcmp(var, "B0") == 0)
              v = B0;
          else if (strcmp(var, "C0") == 0)
              v = C0;
          else if (strcmp(var, "D0") == 0)
              v = D0;
          else if (strcmp(var, "A1") == 0)
              v = A1;
          else if (strcmp(var, "B1") == 0)
              v = B1;
          else if (strcmp(var, "C1") == 0)
              v = C1;
          else if (strcmp(var, "D1") == 0)
              v = D1;
          else if (strcmp(var, "E1") == 0)
              v = E1;

          if (v == A0 || v == C0 || v == D0 || v == D1)
            if (fscanf(fpIn, "%d", &vi) != 1)
              exit(0);
          if(v == B0 || v == B1 || v == C1)
            if(fscanf(fpIn, "%d %d", &vi, &vj) != 2)
              exit(0);




        /*construcao de uma estrutura com listas de adjacencias para representar o grafo*/

        graph = GRAPHinit(V);
        graph->E = E;
        for (i = 0; i < graph->E; i++){
            if (fscanf(fpIn, "%d %d %lf",&V_aux, &V_adj, &custo) == 3){
              e = EDGE(V_aux, V_adj, custo);
              GRAPHinsertE(graph, e);
          }
        }
        pre = (int*) malloc((graph->V)*sizeof(int));
        GRAPHsearch(graph);
        n = graph->V - dfs;
        mst = (Edge*) malloc(n*sizeof(Edge));
        st = (Edge*) malloc((graph->V - dfs)*sizeof(Edge));
        a = (Edge*) malloc((graph->E)*sizeof(Edge));
        E = GRAPHedges(a, graph);



        /* write out words to output file */

        /*variante B0*/

        if (v == B0){
            double c;
            c =b0(graph, vi, vj);
            if ((int)c == -1) fprintf(fpOut, "%d %d %s %d %d %d\n\n", V, E, var, vi, vj, (int)c);
            else{fprintf(fpOut, "%d %d %s %d %d %.2lf\n\n", V, E, var, vi, vj, c);}
          }

        /*variante A0*/

        if (v == A0){
          count = a0(graph, vi);
          fprintf(fpOut, "%d %d %s %d %d\n\n", V, E, var, vi,count);
        }

        /*variante C0*/

        if (v == C0){
          count = c0(graph, vi);
          fprintf(fpOut, "%d %d %s %d %d\n\n", V, E, var, vi,count);
        }

        /*variante D0*/

        if (v == D0){
          count = d0(graph, vi);
          fprintf(fpOut, "%d %d %s %d %d\n\n", V, E, var, vi,count);
          }

        /*variante A1*/

        if (v == A1){
          total = 0;
          mergesort(a, 0, E-1);
          count = a1(graph, mst, a, E);
          for (i = 0; i < n; i++)
              total += mst[i].custo;
          fprintf(fpOut, "%d %d %s %d %.2lf\n", V, E, var, count, total);
          mergesort_f(mst, 0, n-1);
          for(i = 0; i < n; i++)
              if(mst[i].custo != 0) fprintf(fpOut, "%d %d %.2lf\n", mst[i].v, mst[i].w, mst[i].custo);
          fprintf(fpOut, "\n");
        }

        /*variante B1*/

        if (v == B1){
          total = 0;
          isIn = 0;
          if (vi < vj) e = EDGE(vi, vj, 0);
          else {e = EDGE(vj, vi, 0);}
          mergesort(a, 0, E-1);
          count = a1(graph, mst, a, E);
          GRAPHremoveE(graph, e);
          aux_count = a1(graph, st, a, E);
          for (i = 0; i < n; i++)
            total += mst[i].custo;
          if (count != aux_count) isIn = -1;
          else {
            for (i = 0; i < E; i++)
              if (CompareEdge(mst[i], st[i]) == 0){
                isIn = 1;
                e = EDGE(st[i].v, st[i].w, st[i].custo);
                break;
              }
          }
          fprintf(fpOut, "%d %d %s %d %d %d %.2lf %d\n", V, E, var, vi, vj, count, total, isIn);
          mergesort_f(mst, 0, n-1);
          for(i = 0; i < n; i++)
            fprintf(fpOut, "%d %d %.2lf\n", mst[i].v, mst[i].w, mst[i].custo);
          if (isIn == 1) fprintf(fpOut, "%d %d %.2lf\n", e.v, e.w, e.custo);
          fprintf(fpOut, "\n");
        }

        /*variante C1*/

        if (v == C1){
          total = 0;
          aux_total = 0;
          mergesort(a, 0, E-1);
          count = a1(graph, mst, a, E);
          for (i = 0; i < n; i++)
            total += mst[i].custo;
          if (vi < vj) e = EDGE(vi, vj, 0);
          else {e = EDGE(vj, vi, 0);}
          for (i = 0; i < E; i++)
            if (CompareEdge(e, a[i]) == 1){
                isIn = 1;
                for (j = 0; j < n ; j++){
                    if (CompareEdge(a[i], mst[j]) == 1) {isIn = 1;break;}
                    else {isIn = -1;}
                  }
                break;
              }

          if (isIn == 1){
            removeE(a, e, E);
            aux_count = a1(graph, st, a, E);
            for (i = 0; i < n; i++)
              if(st[i].custo != 0) aux_total += st[i].custo;
          }
          if (isIn != 1) fprintf(fpOut, "%d %d %s %d %d %d %.2lf %d\n", V, E, var, vi, vj, count, total, isIn);
          else
          {fprintf(fpOut, "%d %d %s %d %d %d %.2lf %d %.2lf\n", V, E, var, vi, vj, count, total, aux_count, aux_total);}
          mergesort_f(mst, 0, n-1);
          for(i = 0; i < n; i++)
              fprintf(fpOut, "%d %d %.2lf\n", mst[i].v, mst[i].w, mst[i].custo);
          if (isIn == 1){
            mergesort_f(st, 0, n-1);
            for(i = 0; i < n; i++)
              if(st[i].custo != 0) fprintf(fpOut, "%d %d %.2lf\n", st[i].v, st[i].w, st[i].custo);
          }
          fprintf(fpOut, "\n");
        }

        /*variante D1*/

        if (v == D1){
          mergesort(a, 0, E-1);
          count = a1(graph, mst, a, E);
          d1(graph, st, vi, a, E);
          aux_count = a1(graph, st, a, E);
          for (i = 0; i < count; i++)
            total += mst[i].custo;
          fprintf(fpOut, "%d %d %s %d %d %.2lf\n", V, E, var, vi, count, total);
          for(i = 0; i < count; i++)
            fprintf(fpOut, "%d %d %.2lf\n", mst[i].v, mst[i].w, mst[i].custo);
          for(i = 0; i < n; i++){
            isIn = 0;
            for (j = 0; j < n; j++){
              if(CompareEdge(st[i], mst[j]) == 1) isIn = 1;
            }
            if (isIn == 0) fprintf(fpOut, "%d %d %.2lf\n", st[i].v, st[i].w, st[i].custo);
          }
          fprintf(fpOut, "\n\n");
        }
        /* free allocated memory for nodes in graph */

        free(a);
        free(mst);
        free(st);
        free(pre);
        GRAPHdestroy(graph);

    }

    else{
        break;
      }
    }
    /* close all open files*/
    fclose(fpIn);
    fclose(fpOut);

    /* free the name of the output file */
    free(nomeFicheiroOut);
    return 0;
}
