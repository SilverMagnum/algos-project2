/* the #define rows just define names for numerical constants */

#define M 100
#define N 100
#define NALIGN 200

#define STOP 0
#define UP 1
#define LEFT 2
#define DIAG 3

#define MATCHSCORE 10
#define MISMATCHSCORE -7
#define GAPSCORE -4

/* main is where the computer starts to run the program */

main() { 
  
  /* first we reserve memory for all the variables we will use */

  int i,j,m,n,minI,minJ,iAlign,dist,tmp,minDist;
  char Y[N-1] = "gatggtccgatcaatctacgatcggggctctaaatatatatatatacgctacgatcg";
  char X[M-1];           /* user input sequence */
  int distance[M][N];  /* distance label matrix */
  int trace[M][N];     /* trace matrix */
  char alignY[NALIGN]; /* aligned Y sequence */
  char alignX[NALIGN]; /* aligned X sequence */

  /* here the real program begins */

  printf("%s\n",Y);

  /* check how long Y is (a string in the language C ends with an extra 0) */
  n=0;
  while(Y[n] != 0) n++;

  while(1) { /* way to write that this should repeat forever */
     
    printf("Enter your string! ");
    scanf("%s",X); /* read string from keyboard */

    /* check length of X */
    m=0;
    while(X[m] != 0) m++;
    
    /* initialization */

    for(i=0;i<=m;i++) distance[i][0]=0; /* do this for i=0,1,...,m */
    for(j=0;j<=n;j++) distance[0][j]=0;
    for(i=0;i<=m;i++) trace[i][0]=STOP;
    for(j=0;j<=n;j++) trace[0][j]=STOP;

    minDist=0;
    minI=0;
    minJ=0;

    /* labeling of all nodes, this is the main loop of the algorithm  */

    for(i=1;i<=m;i++) {    /* note: we begin at i=1 ! */
      for(j=1;j<=n;j++) {
	
	dist=0; /* distance to node (i,j) from virtual start node */
	trace[i][j] = STOP;
	
	if(X[i-1]==Y[j-1]) tmp = distance[i-1][j-1]-MATCHSCORE;
	else tmp = distance[i-1][j-1]-MISMATCHSCORE;
	if(tmp<dist) {
	  dist=tmp;
	  trace[i][j] = DIAG;
	}

	tmp = distance[i-1][j]-GAPSCORE;
	if(tmp<dist) {
	  dist=tmp;
	  trace[i][j] = UP;
	}

	tmp = distance[i][j-1]-GAPSCORE;
	if(tmp<dist) {
	  dist=tmp;
	  trace[i][j] = LEFT;
	}

	distance[i][j]=dist;

	if(dist<minDist) { /* keep track of where the minimum score is */
	  minDist=dist;
	  minI=i;
	  minJ=j;
	}

      }
    }

    /* now create aligned sequences alignY and alignX */
    /* note: these are created in reverse order! */

    i=m;
    j=n;
    iAlign=0;

    /* unaligned ends */

    while(i>minI) {
      alignY[iAlign]='-';
      alignX[iAlign]=X[i-1];
      i--;
      iAlign++;
    }

    while(j>minJ) {
      alignY[iAlign]=Y[j-1];
      alignX[iAlign]='-';
      j--;
      iAlign++;
    }

    /* when we come here we know that i==minI and j==minJ */
    /* it is from this position we make the jump to the virtual stop node */
    
    while(trace[i][j] != STOP) {

      if(trace[i][j] == DIAG) {
	alignY[iAlign]=Y[j-1];
	alignX[iAlign]=X[i-1];
	i--;
	j--;
	iAlign++;
      }
      else if(trace[i][j] == LEFT) {
	alignY[iAlign]=Y[j-1];
	alignX[iAlign]='-';
	j--;
	iAlign++;
      }
      else if(trace[i][j] == UP) {
	alignY[iAlign]='-';
	alignX[iAlign]=X[i-1];
	i--;
	iAlign++;
      }

    }

    /* unaligned beginning */

    while(i>0) {
      alignY[iAlign]='-';
      alignX[iAlign]=X[i-1];
      i--;
      iAlign++;
    }

    while(j>0) {
      alignY[iAlign]=Y[j-1];
      alignX[iAlign]='-';
      j--;
      iAlign++;
    }

    /* print in reverse order */

    for(i=iAlign-1;i>=0;i--) printf("%c",alignY[i]);
    printf("\n");
    for(i=iAlign-1;i>=0;i--) printf("%c",alignX[i]);
    printf("\n");
    
  }
}