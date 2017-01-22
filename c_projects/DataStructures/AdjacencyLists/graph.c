/**************************** graph.c  ***********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {FALSE, TRUE} bool;
#define MAXV 100
typedef struct edgenode {
	int y;
	int weight;
	struct edgenode *next;
} edgenodeT;

typedef struct {
	edgenodeT *edges[MAXV+1];
	int degree[MAXV+1];
	bool visited[MAXV+1];
	int nvertices;
	int nedges; // number of directed edges....
	bool directed;
} graphT;

void initialize_graph(graphT *g, bool directed);
void read_graph(graphT *g, char *filename);
void insert_edge(graphT *g, int x, int y, int w);
void delete_edge(graphT *g, int x, int y);
void print_graph(graphT *g, char *name);
void free_graph(graphT *g);
graphT *copy_graph(graphT *g);
// put prototypes for other functions here....
void print_degree(graphT *g);
void print_complement(graphT *g);
void eliminatelinks(graphT *g, int minW , int maxW);
void differentlinks(graphT *g1, graphT *g2);
void commonlinks(graphT *g1, graphT *g2);
void dfs_print(graphT *g, int v);
void reset_visited(graphT *g);
// For undirected only
bool isConnected(graphT *g);
int numofconncomp(graphT *g);

/* Private function prototypes */
int RandomInteger(int low, int high);
static void HelpCommand(void);

/* Main program */

main(int argc, char *argv[])
{
	int iCheck = 0, size = 0, iNums[3];
    char ch, cUser, *cNum, *cNums[3], cGraph;
    char lineBuffer[30];
    bool iChecks[3];
	graphT *myg1=NULL, *myg2=NULL;
	
	if(argc < 2){
		fprintf(stderr, "Usage: %s graph_filename", argv[0]);
		exit(-1);
	}
	myg1 = (graphT *) malloc(sizeof(graphT));
	if (myg1==NULL) {
		fprintf(stderr, "Cannot allocate memory for the graph");
		exit(-1);
	}
	
	initialize_graph(myg1, FALSE);
	read_graph(myg1, argv[1]);
	print_graph(myg1, "myg1");
	// first implement copy_graph function and call it here
	myg2 = copy_graph(myg1);
	print_graph(myg2, "myg2");
	// NOW in a loop get commands and
	// call related functions to perform them...
    
    while (1) { 
    
    	printf("Enter a Graph command (type H for help)\n");
		
		printf("> ");
		while((ch = getchar()) != '\n')
		{
			lineBuffer[size] = ch;
			size++;
		}
       	lineBuffer[size++] = '\0'; // Terminate string THEN increment size
        lineBuffer[0] = toupper(lineBuffer[0]);
        //printf("Line Buffer: |%s|\n", lineBuffer);
        
        if(strcmp(lineBuffer, "Quit") == 0)
        {
        	printf("Exiting Program\n");
			free_graph(myg1);
			free_graph(myg2);
          	exit(0);
        }
		else if(strncmp(lineBuffer, "Insert", 6) == 0)
		{
			cGraph = lineBuffer[10];
			cNums[0] = &lineBuffer[12];
			cNums[1] = &lineBuffer[14];
			cNums[2] = &lineBuffer[16];
			
			iChecks[0] = sscanf(cNums[0], "%d", &iNums[0]);
			iChecks[1] = sscanf(cNums[1], "%d", &iNums[1]);
			iChecks[2] = sscanf(cNums[2], "%d", &iNums[2]);
			
			//printf("Insert: %d(x) %d(y) %d(w)\n", iNums[0], iNums[1], iNums[2]);
			if((iChecks[0] + iChecks[1] + iChecks[2]) != 3 || iNums[0] < 0 || iNums[1] < 0 || iNums[2] < 0)
				printf("Invalid positive integer\n");
			else {
				switch(cGraph) {
				case '1': if(myg1->directed)
							insert_edge(myg1, iNums[0], iNums[1], iNums[2]); //graphT, x, y, weight
						  else {
							insert_edge(myg1, iNums[0], iNums[1], iNums[2]);
							insert_edge(myg1, iNums[1], iNums[0], iNums[2]); //graphT, y, x, weight
						  }
						  break;
				case '2': if(myg2->directed)
							insert_edge(myg2, iNums[0], iNums[1], iNums[2]); //graphT, x, y, weight
						  else {
							insert_edge(myg2, iNums[0], iNums[1], iNums[2]);
							insert_edge(myg2, iNums[1], iNums[0], iNums[2]); //graphT, y, x, weight
						  }
						  break;
				default: printf("Invalid Graph\n");
				}
			}
		}
		else if(strncmp(lineBuffer, "Delete", 6) == 0)
		{
			cGraph = lineBuffer[10];
			cNums[0] = &lineBuffer[12];
			cNums[1] = &lineBuffer[14];
			
			iChecks[0] = sscanf(cNums[0], "%d", &iNums[0]);
			iChecks[1] = sscanf(cNums[1], "%d", &iNums[1]);
			
			//printf("Insert: %d\n", iNum);
			if((iChecks[0] + iChecks[1]) != 2 || iNums[0] < 0 || iNums[1] < 0)
				printf("Invalid positive integer\n");
			else {
				switch(cGraph) {
				case '1': if(myg1->directed)
							delete_edge(myg1, iNums[0], iNums[1]); //graphT, x, y
						  else {
							delete_edge(myg1, iNums[0], iNums[1]); //graphT, x, y
							delete_edge(myg1, iNums[1], iNums[0]); //graphT, y, x
						  }
						  break;
				case '2': if(myg2->directed)
							delete_edge(myg2, iNums[0], iNums[1]); //graphT, x, y
						  else {
							delete_edge(myg2, iNums[0], iNums[1]); //graphT, x, y
							delete_edge(myg2, iNums[1], iNums[0]); //graphT, y, x
						  }
						  break;
				default: printf("Invalid Graph\n");
				}
			}
		}
		else if(strncmp(lineBuffer, "Eliminatelinks", 14) == 0)
		{
			cGraph = lineBuffer[18];
			cNums[0] = &lineBuffer[20];
			cNums[1] = &lineBuffer[22];
			
			iChecks[0] = sscanf(cNums[0], "%d", &iNums[0]);
			iChecks[1] = sscanf(cNums[1], "%d", &iNums[1]);
			
			//printf("Insert: %d\n", iNum);
			if((iChecks[0] + iChecks[1]) != 2 || iNums[0] < 0 || iNums[1] < 0)
				printf("Invalid positive integer\n");
			else {
				switch(cGraph) {
				case '1': eliminatelinks(myg1, iNums[0], iNums[1]); break;
				case '2': eliminatelinks(myg2, iNums[0], iNums[1]); break;
				default: printf("Invalid Graph\n");
				}
			}
		}
		else if(strncmp(lineBuffer, "Printgraph", 10) == 0)
		{
			cGraph = lineBuffer[14];
			
			switch(cGraph) {
			case '1': print_graph(myg1, "myg1"); break;
			case '2': print_graph(myg2, "myg2"); break;
			default: printf("Invalid Graph\n");
			}
		}
		else if(strncmp(lineBuffer, "Printdegree", 11) == 0)
		{
			cGraph = lineBuffer[15];
			
			switch(cGraph) {
			case '1': print_degree(myg1); break;
			case '2': print_degree(myg2); break;
			default: printf("Invalid Graph\n");
			}
		}
		else if(strncmp(lineBuffer, "Printcomplement", 15) == 0)
		{
			cGraph = lineBuffer[19];
			
			switch(cGraph) {
			case '1': print_complement(myg1); break;
			case '2': print_complement(myg2); break;
			default: printf("Invalid Graph\n");
			}
		}
		else if(strncmp(lineBuffer, "Differentlinks", 14) == 0)
		{
			cGraph = lineBuffer[18];
			
			switch(cGraph) {
			case '1': differentlinks(myg1, myg2); break;
			case '2': differentlinks(myg2, myg1); break;
			default: printf("Invalid Graph\n");
			}
		}
		else if(strncmp(lineBuffer, "Commonlinks", 11) == 0)
		{
			cGraph = lineBuffer[15];
			
			switch(cGraph) {
			case '1': 
			case '2': commonlinks(myg2, myg1); break;
			default: printf("Invalid Graph\n");
			}
		}
		else if(strncmp(lineBuffer, "Dfs_print", 9) == 0)
		{
			cGraph = lineBuffer[13];
			cNums[0] = &lineBuffer[15];
			iChecks[0] = sscanf(cNums[0], "%d", &iNums[0]);
			
			//printf("Insert: %d\n", iNum);
			if(iChecks[0] != 1 || iNums[0] < 0)
				printf("Invalid positive integer\n");
			else {
				switch(cGraph) {
				case '1': dfs_print(myg1, iNums[0]); reset_visited(myg1); break;
				case '2': dfs_print(myg2, iNums[0]); reset_visited(myg2); break;
				default: printf("Invalid Graph\n");
				}
			}
		}
		else if(strncmp(lineBuffer, "Isconnected", 11) == 0)
		{
			cGraph = lineBuffer[15];
			
			switch(cGraph) {
				case '1': if(myg1->directed)
						  	printf("Purchase the next version :)\n");
						  else { 
							printf("myg1 is%sconnnected\n",	isConnected(myg1) ? " " : " not ");
						  	reset_visited(myg1);
						  }
						  break;
				case '2': if(myg2->directed)
						  	printf("Purchase the next version :)\n");
						  else { 
							printf("myg2 is%sconnnected\n",	isConnected(myg2) ? " " : " not ");
						  	reset_visited(myg2);
						  }
						  break;
				default: printf("Invalid Graph\n");
			}
		}
		else if(strncmp(lineBuffer, "Numofconncomp", 13) == 0)
		{
			cGraph = lineBuffer[17];
			
			switch(cGraph) {
				case '1': if(myg1->directed)
						  	printf("Purchase the next version :)\n");
						  else { 
							printf("myg1 connnected components: %d\n",	numofconncomp(myg1));
						  	reset_visited(myg1);
						  }
						  break;
				case '2': if(myg2->directed)
						  	printf("Purchase the next version :)\n");
						  else { 
							printf("myg2 connnected components: %d\n",	numofconncomp(myg2));
						  	reset_visited(myg2);
						  }
						  break;
				default: printf("Invalid Graph\n");
			}
		}
        else 
          HelpCommand();
        
        size = 0;
    }
}

/* Private functions */
int RandomInteger(int low, int high)
{
    int k;
    double d;

    d = (double) rand() / ((double) RAND_MAX + 1);
    k = (int) (d * (high - low + 1));
    return (low + k);
}

/*
 * Function: HelpCommand
 * Usage: HelpCommand();
 * ---------------------
 * This function generates a help message for the user.
 */

static void HelpCommand(void)
{
    printf("  Quit -- Quit the program\n");
    printf("  Help -- Display this help message\n");
    printf("  Insert          [myg1 | myg2] x y w\n");
    printf("  Delete          [myg1 | myg2] x y\n");
    printf("  Printgraph      [myg1 | myg2]\n");
    printf("  Printdegree     [myg1 | myg2]\n");
    printf("  Printcomplement [myg1 | myg2]\n");
    printf("  Eliminatelinks  [myg1 | myg2] minW maxW\n");
    printf("  Differentlinks  [myg1 | myg2] [myg1 | myg2]\n");
    printf("  Commonlinks     [myg1 | myg2] [myg1 | myg2]\n");
    printf("  Dfs_print 	  [myg1 | myg2] x\n");
    printf("  Isconnected     [myg1 | myg2]\n");
    printf("  Numofconncomp   [myg1 | myg2]\n");
}

// Graph functions 
void initialize_graph(graphT *g, bool directed)
{
	int i;
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
	for (i=1; i<=MAXV; i++)
		g->edges[i] = NULL;
	for (i=1; i<=MAXV; i++) {
		g->degree[i] = 0;
		g->visited[i] = 0;
	}
}
void read_graph(graphT *g, char *filename)
{
	int i;
	int n, m, dir;
	int x, y, w;
	FILE *fp;
	if((fp=fopen(filename,"r"))==NULL){
		fprintf(stderr, "Cannot open the graph file");
		exit(-1);
	}
	fscanf(fp,"%d %d %d", &n, &m, &dir);
	g->nvertices = n;
	g->nedges = 0; // insert function will increase it;
	g->directed = dir;
	for (i=1; i<=m; i++) {
		fscanf(fp,"%d %d %d", &x, &y, &w);
		insert_edge(g, x, y, w);
		if(dir==FALSE)
			insert_edge(g, y, x, w);
	}
	fclose(fp);
}
void insert_edge(graphT *g, int x, int y, int w)
{
	edgenodeT *pe, *tmp;
	pe = malloc(sizeof(edgenodeT)); // check if NULL
	pe->weight = w;
	pe->y = y;

	tmp = g->edges[x];
	if(!tmp) {
		g->edges[x] = pe;
		pe->next = NULL;
	}
	else if(tmp->y > y) { //first number is bigger
		g->edges[x] = pe;
		pe->next = tmp;
	}
	else {
		while(tmp->next && tmp->next->y < y)
			tmp = tmp->next;

		if((tmp && tmp->y == y && tmp->weight == w) ||
		   (tmp->next && tmp->next->y == y && tmp->next->weight == w))
		   return;
		
		pe->next = tmp->next;
		tmp->next = pe;
	}
	
	g->degree[x]++;
	g->nedges++;
}

void delete_edge(graphT *g, int x, int y)
{
	edgenodeT *tmpB, *tmpA, *freeNode;
	tmpB = g->edges[x];

	if(!tmpB)
		return;
	else if(tmpB->y == y) {
		freeNode = tmpB;
		g->edges[x] = tmpB->next;
		free(freeNode);
	}
	else {
		while(tmpB->next && tmpB->next->y != y)
			tmpB = tmpB->next;

		if(!tmpB->next) // edge doesnt exist
			return;
		else {
			freeNode = tmpB->next;
			tmpA = freeNode->next;
			free(freeNode);
			tmpB->next = tmpA;
		}
	}

	g->degree[x]--;
	g->nedges--;
}

void print_graph(graphT *g, char *name)
{
	edgenodeT *pe;
	int i;
	if(!g) return;
	printf("Graph Name: %s\n", name);
	
	for(i=1; i<=g->nvertices; i++) {
		printf("Node %d: ", i);
		pe = g->edges[i];
		while(pe){
			// printf(" %d", pe->y);
			printf(" %d(w=%d),", pe->y, pe->weight);
			pe = pe->next;
		}
		printf("\n");
	}
}
void free_graph(graphT *g)
{
	edgenodeT *pe, *olde;
	int i;
	for(i=1; i<=g->nvertices; i++) {
		pe = g->edges[i];
		while(pe){
			olde = pe;
			pe = pe->next;
			free(olde);
		}
	}
	free(g);
}
graphT *copy_graph(graphT *g)
{
	edgenodeT *pe, *copy;
	int i;
	graphT *newg = (graphT *)malloc(sizeof(graphT));	
	if(!g || !newg) return;

	initialize_graph(newg, g->directed);
	newg->nvertices = g->nvertices;

	for(i=1; i<=g->nvertices; i++) {
		pe = g->edges[i];
		while(pe){
			insert_edge(newg, i, pe->y, pe->weight);
			pe = pe->next;
		}
	}
	return newg;
}
void print_degree(graphT *g)
{
	edgenodeT *pe;
	int i, j, counter;
	if(!g) return;
	
	if(g->directed) {
		for(i=1; i<=g->nvertices; i++) {
			counter = 0;
			for(j=1; j<=g->nvertices; j++) {
				pe = g->edges[j];
				while(pe){
					if(pe->y == i && i != j)
						counter++;
					pe = pe->next;
				}
			}
			printf("Node %d, Out-Degree: %d In-Degree: %d\n", i, g->degree[i], counter);
		}
	}
	else { 
		for(i=1; i<=g->nvertices; i++)
			printf("Node %d, Degree: %d\n", i, g->degree[i]);
	}
}

void print_complement(graphT *g)
{
	edgenodeT *pe;
	int i, j, counter;
	graphT *cg = (graphT *)malloc(sizeof(graphT));	
	if(!g || !cg) return;

	initialize_graph(cg, g->directed);
	cg->nvertices = g->nvertices;

	for(i=1; i<=g->nvertices; i++) { //create complete graph
		for(j=1; j<=g->nvertices; j++) {
			pe = g->edges[j];
			while(pe){
				insert_edge(cg, i, j, 1);
				pe = pe->next;
			}
		}
	}
	
	for(i=1; i<=g->nvertices; i++) { //delete the incommon links
		pe = g->edges[i];
		while(pe){
			delete_edge(cg, i, pe->y);
			pe = pe->next;
		}
	}

	print_graph(cg, "Complement Graph");
	free_graph(cg);
}

void eliminatelinks(graphT *g, int minW , int maxW)
{
	edgenodeT *pe;
	int i, j, counter;
	
	if(!g) return;

	for(i=1; i<=g->nvertices; i++) { //delete the incommon links
		pe = g->edges[i];
		while(pe){
			if(pe->weight < minW || pe->weight > maxW)
				delete_edge(g, i, pe->y);
			pe = pe->next;
		}
	}
}
void differentlinks(graphT *g1, graphT *g2)
{
	edgenodeT *pe1, *pe2;
	int i;
	
	if(!g1) return;

	for(i=1; i<=g1->nvertices; i++) { //delete the incommon links
		printf("Node %d: ", i);	
		pe1 = g1->edges[i];
		
		if(!g2)
			pe2 = NULL;
		else
			pe2 = g2->edges[i];

		while(pe1 && pe2){
			if(pe1->y < pe2->y) {
				printf(" %d(w=%d),", pe1->y, pe1->weight);
				pe1 = pe1->next;
			}
			else if((pe1->y == pe2->y) && (pe1->weight == pe2->weight)) {
				pe1 = pe1->next;
				pe2 = pe2->next;
			}
			else
				pe2 = pe2->next;
		}
		
		while(pe1) {
			printf(" %d(w=%d),", pe1->y, pe1->weight);
			pe1 = pe1->next;
		}
		printf("\n");
	}
}
void commonlinks(graphT *g1, graphT *g2)
{
	edgenodeT *pe1, *pe2;
	int i;
	
	if(!g1 || !g2) return;

	for(i=1; i<=g1->nvertices; i++) { //delete the incommon links
		printf("Node %d: ", i);	
		pe1 = g1->edges[i];
		pe2 = g2->edges[i];
		while(pe1 && pe2){
			if(pe1->y < pe2->y)
				pe1 = pe1->next;
			else if((pe1->y == pe2->y) && (pe1->weight == pe2->weight)) {
				printf(" %d(w=%d),", pe1->y, pe1->weight);
				pe1 = pe1->next;
				pe2 = pe2->next;
			}
			else
				pe2 = pe2->next;
		}
		printf("\n");
	}
}

void dfs_print(graphT *g, int v)
{
	edgenodeT *pe;
	
	if(!g) return;
	g->visited[v] = TRUE;
	printf("%d is visisted\n", v);

	pe = g->edges[v];
	while(pe) {
		if(g->visited[pe->y] == FALSE)
			dfs_print(g, pe->y);
		pe = pe->next;
		//if(pe)
		//	printf("Next %d\n", pe->y);
	}
}

void reset_visited(graphT *g)
{
	int i;
	if(!g) return;
	for (i=1; i<=MAXV; i++)
		g->visited[i] = 0;
}
// For undirected only
bool isConnected(graphT *g)
{
	edgenodeT *pe;
	int comp = 0, i;
	if(!g) return 0;

	for(i = 1; i<=g->nvertices; i++) {
		if(g->visited[i] == FALSE){
			dfs_print(g, i);
			comp++;
		}
	}
	//printf("Component %d\n", comp);
	return (comp == 1);
}
int numofconncomp(graphT *g)
{
	edgenodeT *pe;
	int comp = 0, i;
	if(!g) return 0;

	for(i = 1; i<=g->nvertices; i++) {
		if(g->visited[i] == FALSE){
			comp++;
			printf("Component %d\n", comp);
			dfs_print(g, i);
		}
	}
	return comp;
}
