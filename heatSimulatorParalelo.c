#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <omp.h>

#define M 500
#define N 500





int main (int argc, char *argv[] ){
 

  
  double diff=0.0;
  double diffthread=0.0;
  float epsilon=0.0;
  FILE *fp;
  int i;
  int iterations;
  int iterations_print;
  int j;
  double mean;
  char output_file[80];
  int success;
  double u[M][N];
  double w[M][N];

  epsilon = atof(argv[1]);
  strcpy(output_file,argv[2]);
  int N_THREADS = atoi(argv[3]);
  diff = epsilon;


  omp_set_num_threads(N_THREADS);


#pragma omp parallel shared(w) private(i,j)
    {
#pragma omp for
  for ( i = 1; i < M - 1; i++ )
  {
    w[i][0] = 0.0;
  }
#pragma omp for
  for ( i = 1; i < M - 1; i++ )
  {
    w[i][N-1] = 0.0;
  }
#pragma omp for
  for ( j = 0; j < N; j++ )
  {
    w[M-1][j] = 100.0;
  }
#pragma omp for
  for ( j = 0; j < N; j++ )
  {
    w[0][j] = 0.0;
  }
    }


  iterations = 0;
  iterations_print = 1;
  printf ( "\n" );
  printf ( " Iteration  Change\n" );
  printf ( "\n" );
  double start = omp_get_wtime(); //inicio contagem do tempo

    while ( epsilon <= diff )
    {
# pragma omp parallel shared (u,w) private (i,j)
        {
            
# pragma omp for
            for ( i = 0; i < M; i++ )
            {
                for ( j = 0; j < N; j++ )
                {
                    u[i][j] = w[i][j];
                }
            }
            
# pragma omp for
            for ( i = 1; i < M - 1; i++ )
            {
                for ( j = 1; j < N - 1; j++ )
                {
                    w[i][j] = ( u[i-1][j] + u[i+1][j] + u[i][j-1] + u[i][j+1] ) / 4.0;
                }
            }
        }
       
        diff = 0.0;
# pragma omp parallel shared (diff,u,w) private (i,j,diffthread)
        {
            diffthread = 0.0;
# pragma omp for
            for ( i = 1; i < M - 1; i++ )
            {
                for ( j = 1; j < N - 1; j++ )
                {
                    if ( diffthread < fabs ( w[i][j] - u[i][j] ) )
                    {
                        diffthread = fabs ( w[i][j] - u[i][j] );
                    }
                }
            }
# pragma omp critical
            {
                if ( diff < diffthread )
                {
                    diff = diffthread;
                }
            }
        }
    iterations++;
    if ( iterations == iterations_print )
    {
      printf ( "  %8d  %f\n", iterations, diff );
      iterations_print = 2 * iterations_print;
    }
  } 
 double end = omp_get_wtime();  //fim da contagem do tempo

    
  printf ( "\n" );
  printf ( "  %8d  %f\n", iterations, diff );
  printf ( "\n" );
  printf ( "  Error tolerance achieved.\n" );
  printf("Concluido com %d threads em %f segundos.\n", N_THREADS, (end-start));

  fp = fopen ( output_file, "w" );

  fprintf ( fp, "%d\n", M );
  fprintf ( fp, "%d\n", N );

  for ( i = 0; i < M; i++ )
  {
    for ( j = 0; j < N; j++)
    {
      fprintf ( fp, "%6.2f ", w[i][j] );
    }
    fputc ( '\n', fp);
  }
  fclose ( fp );

  printf ( "\n" );
  printf ("  Solution written to the output file %s\n", output_file );

  printf ( "  Normal end of execution.\n" );

  return 0;


}
