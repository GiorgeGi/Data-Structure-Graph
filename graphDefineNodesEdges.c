#include <stdio.h>
#include <stdlib.h>

// domi grafos
struct Graph {
    int n; // arithmos ton kombon tou grafou
    int **a; // pinakas geitniasis dio diastaseon pou antiprosopeuei ton grafo
    int degree; // bathmos tou kathe kombou sto grafo
};

// katholikes metablites gia ton algorithmo BFS
int front; // metabliti gia tin arxi tis ouras
int rear; // metabliti gia to telos tis ouras
int *queue; // pinakas pou antiprosopeuei tin oura
int *mark; // pinakas gia na elegxei pioi komboi exoun eidi episkeftei

// sinartisi pou tiponei ton pinaka geitniasis tou grafou
void printGraphAdjacencyMatrix(struct Graph *g, int s);

// sinartisi pou ektelei prospelasi BFS ston grafo
void bfs(struct Graph *g, int k);

// sinartisi pou bazei enan kombo stin oura
int enqueue(struct Graph *g, int k);

// sinartisi pou bgazei enan kombo apo tin oura
int dequeue(int *k);

int main() {
    struct Graph g; // arxikopoiisi tis domis
    int s, i, j, edgesAdded;
    printf("Enter number of nodes in the graph: ");
    scanf("%d", &g.n); // diabase ton arithmo ton kombon tou grafou
    printf("Enter degree of the nodes: ");
    scanf("%d", &g.degree); // diabase ton bathmo kathe kombou sto grafo
    g.a = (int **)malloc(g.n * sizeof(int *)); // ekxorisi mnimis gia ton grafo
    for (i = 0; i < g.n; i++) {
        g.a[i] = (int *)malloc(g.n * sizeof(int));
    }
    mark = (int *)malloc(g.n*sizeof(int)); // ekxorisi mnimis gia ton pinaka elegxoun kombon pou exoun episkefthei
    for (i = 0; i < g.n; i++) {
        for (j = 0; j < g.n; j++) {
            g.a[i][j] = 0; // arxikopoiisi ton kelion tou pinaka geitniasis
        }
        edgesAdded = 0;
        while (edgesAdded < g.degree) {
            int randNode = rand() % g.n; // epilogi tixaiou kombou
            if (randNode != i && g.a[i][randNode] != 1) { // ean o tixaios kombos den einai o eidi epilegmenos kai den einai eidi sindedemenos
                g.a[i][randNode] = 1; // enose ton torino kombo me ton tixaio
                edgesAdded++;
            }
        }
    }
    printf("Give start node (1-%d) or 0 to end: ", g.n);
    scanf("%d", &s); // diabase ton arxiko kombo gia prospelasi, me 0 to programma termatizei
    while (s >= 1 && s <= g.n) {
        // arxikopoiisi tis ouras
        queue = (int *)malloc(g.n*g.n*sizeof(int)); // ekxorisi mnimis gia tin oura
        front = -1;
        rear = -1;
		for (i = 0; i < g.n; i++) {
			mark[i] = 0; // arxikopoiise ola ta kelia tou pinaka mark[] se 0
		}
		bfs(&g, s-1); // kane prospelasi BFS ston grafo
		printGraphAdjacencyMatrix(&g, s); // tipose ton pinaka geitniasis
		printf("Give start node (1-%d) or 0 to end: ", g.n);
		scanf("%d", &s);
		free(queue); // apeleutherose ton xoro mnimis pou kataxorithike gia tin oura
	}
	free(mark); // apeleutherose ton xoro mnimis pou kataxorithike gia ton pinaka mark[]
	return 0;
}


// Sinartisi Breadth First Search
void bfs(struct Graph *g, int k) {
    int i, j, flag;
    flag = enqueue(g, k); // bale ton proto kombo stin oura
    mark[k] = 1; // orise oti o protos kombos exei episkeftei
    while (flag == 1) {
        flag = dequeue(&i); // aferesai ton kombo apo tin oura
        if (flag == 1) {
            printf("Now in %d\n", i+1);
            for (j = 0; j < g->n; j++) {
                if (g->a[i][j] == 1 && mark[j] == 0) { // elenkse an o kombos einai geitonikos kai den exei episkeftei
                    flag = enqueue(g, j); // bale kombo stin oura
                    mark[j] = 1; // orise oti o kombos exei episkeftei
                }
            }
        }
    }
}

// sinartisi pou tiponei ton pinaka geitniasis
void printGraphAdjacencyMatrix(struct Graph *g, int s) {
	int i, j;
	printf("Adjacency matrix of the given graph:\n");
	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
		printf("%d ", g->a[i][j]);
		}
	printf("\n");
	}
}

// sinartisi pou bazei kombo stin oura
int enqueue(struct Graph *g, int k) {
	int f = 0;
	if (front == -1) {
		front = 0;
	}
	if (rear < g->n*g->n - 1) {
		rear = rear + 1;
		queue[rear] = k;
		f = 1;
	}
	return f;
}

// sinartisi pou bgazei kombo apo tin oura
int dequeue(int *k) {
	int f = 0;
	if (front != -1 && front <= rear) {
		*k = queue[front];
		front = front + 1;
		f = 1;
	}
	return f;
}
