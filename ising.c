
/* insert libraries defining standard functions */
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

long int idum;

/* set maximum size of system */
#define SIDEMAX 1001

/* spin[x][y] stores the state of spin at lattice point (x,y) */
int spin[SIDEMAX][SIDEMAX];

int N_side,N; /* N=N_side*N_side */
float T;
float field;
int n_steps;
int start_flag;
char config_file[80];

/* fluctuating variables to be computed: */
/* netmag = net magnetization */
int netmag=0;
/* energy = total energy in units of J */
float energy=0.0;

void read_input();
void initialize();
void monte_carlo(int);
void trial_move(int,int);
void write_config(char cfile[]);
void read_config(char cfile[]);
void write_picture();
float ran2(long *idum);


int main() {
  read_input();
  initialize();
  monte_carlo(n_steps);
  write_config("config");
  write_picture();
}

void initialize() {
  int i,j,k;
  int x,y,up,right;

  /* use time on clock to initialize random number generator */
  idum=-time(NULL);

  if (start_flag==0) {
    /* initialize fully magnetized configuration */
    printf("Generating magnetized configuration...\n");
    for (x=1; x<=N_side; x++) {
      for (y=1; y<=N_side; y++) {
	spin[x][y]=1;
	netmag += 1;
      }
    }
    energy = -2.0*N;
  }
  else {
    /* otherwise, read configuration from file */
    printf("Reading configuration from file %s...\n",config_file);
    read_config(config_file);
    for (x=1; x<=N_side; x++) {
      for (y=1; y<=N_side; y++) {
      netmag += spin[x][y];

      /* use periodic boundary conditions to compute energy */
      if (x==N_side) right=spin[1][y];
      else right=spin[x+1][y];
      if (y==N_side) up=spin[x][1];
      else up=spin[x][y+1];

      energy -= spin[x][y]*(up+right);
      }
    }
  }

  /* add energy due to external field */
  energy -= field*netmag;

  printf("Initial magnetization per spin = %f\n", netmag/(float)N);
  printf("Initial energy per spin = %f\n\n", energy/(float)N);
}

void monte_carlo(int n_steps) {
  int i,j,k;
  int x,y;
  int step;
  float avmag=0.0,aven=0.0;

  FILE * trajfile;
  trajfile = fopen("trajectory","w");

  printf("Generating trajectory...\n");
  for (step=1; step <= n_steps; step++) {

  /* make N moves to advance the system one "time" step */
    for (j=1; j<=N; j++) {
      /* select a spin at random */
      x = (int)( N_side*ran2(&idum)+1);
      y = (int)( N_side*ran2(&idum)+1);

      /* attempt to flip and accept with appropriate probability */
      trial_move(x,y);
    }


    if (step%10==0) fprintf(trajfile,"%d %f %f\n",
       		    step,netmag/(float)N,energy/(float)N);
  }

  printf("Average magnetization per spin = %f\n",avmag);
  printf("Average energy per spin = %f\n",aven);
}

void trial_move(int x, int y) {
  int neighbor_mag=0,spinxy=spin[x][y];
  int up,down,right,left;
  float deltae;

  if (x==1) left=spin[N_side][y];
  else left=spin[x-1][y];
  if (x==N_side) right=spin[1][y];
  else right=spin[x+1][y];
  if (y==N_side) up=spin[x][1];
  else up=spin[x][y+1];
  if (y==1) down=spin[x][N_side];
  else down=spin[x][y-1];

}

/* save configuration to file */
void write_config(char cfile[]){
  int x,y;
  FILE *cf;
  cf = fopen(cfile,"w");
  for (x=1; x<=N_side; x++) {
    for (y=1; y<=N_side; y++) {
      fprintf(cf,"%d ",spin[x][y]);
    }
  }
  fclose(cf);
}

/* read configuration from file */
void read_config(char cfile[]){
  int x,y;
  FILE *cf;
  cf = fopen(cfile,"r");
  for (x=1; x<=N_side; x++) {
    for (y=1; y<=N_side; y++) {
    fscanf(cf,"%d",&spin[x][y]);
    }
  }
  fclose(cf);
}


void write_picture() {
  float scale[2+1]={0,0.5,0.5};
  float offset[2+1]={0,250,100}; // image offset
  float cval=0.0,inc=1000.0/N_side;
  int x,y;

  FILE *postscript;

  postscript = fopen("config.eps","w");

  fprintf(postscript,"%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(postscript,"%%%%BoundingBox: 0 0 %d %d\n",700,600);
  fprintf(postscript,"%f %f scale\n",scale[1],scale[2]);

  for (x=1; x<=N_side; x++) {
    for (y=1; y<=N_side; y++) {

      if (spin[x][y]>0) {

      fprintf(postscript,"%4.3f setgray\n",cval);
      fprintf(postscript,"newpath\n");

      fprintf(postscript,"%3.0f %3.0f moveto\n",x*inc+offset[1],
	      y*inc+offset[2]);
      fprintf(postscript,"%3.0f %3.0f lineto\n",x*inc+offset[1],
	      y*inc+offset[2]+inc);
      fprintf(postscript,"%3.0f %3.0f lineto\n",x*inc+offset[1]+inc,
	      y*inc+offset[2]+inc);
      fprintf(postscript,"%3.0f %3.0f lineto\n",x*inc+offset[1]+inc,
	      y*inc+offset[2]);

      fprintf(postscript,"closepath\nfill\n");
      }
    }
  }

  fprintf(postscript,"%%EOF\n");
  fclose(postscript);

}

/* read input parameters from file "input.txt" */
void read_input() {
  char line[101];
  int max_length = 100;
  FILE * input_file;
  input_file = fopen("input.txt","r");

  fgets(line,max_length,input_file);
  sscanf(line,"%d",&N_side);
  N = N_side*N_side;

  fgets(line,max_length,input_file);
  sscanf(line,"%f",&T);
  fgets(line,max_length,input_file);
  sscanf(line,"%f",&field);
  fgets(line,max_length,input_file);
  sscanf(line,"%d",&n_steps);
  fgets(line,max_length,input_file);
  sscanf(line,"%d",&start_flag);
  fgets(line,max_length,input_file);
  sscanf(line,"%s",&config_file);

  printf("N=%d\t\t T=%3.2f\t\t field=%3.2f\n",N,T,field);
  printf("n_steps=%d\t\n",n_steps);
}

/* ran2 is a function that draws a number between 0 and 1
at "random" from a uniform distribution.  The syntax for
usage is ran2(&idum). */

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

float ran2(long *idum)
{
  int j;
  long k;
  static long idum2=123456789;
  static long iy=0;
  static long iv[NTAB];
  float temp;

  if (*idum <= 0) {
    if (-(*idum) < 1) *idum=1;
    else *idum = -(*idum);
    idum2 = (*idum);
    for (j=NTAB+7;j>=0;j--) {
      k=(*idum)/IQ1;
      *idum=IA1*(*idum-k*IQ1)-k*IR1;
      if (*idum < 0) *idum += IM1;
      if (j < NTAB) iv[j] = *idum;
    }
    iy=iv[0];
  }
  k=(*idum)/IQ1;
  *idum=IA1*(*idum-k*IQ1)-k*IR1;
  if (*idum < 0) *idum += IM1;
  k=idum2/IQ2;
  idum2=IA2*(idum2-k*IQ2)-k*IR2;
  if (idum2 < 0) idum2 += IM2;
  j=iy/NDIV;
  iy=iv[j]-idum2;
  iv[j] = *idum;
  if (iy < 1) iy+= IMM1;
  if ((temp=AM*iy) > RNMX) return RNMX;
  else return temp;
}

