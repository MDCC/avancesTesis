/* sample PGM reader/writer for 24-354 General Robotics Lab 2
   
     fall 2000: amperez 
                 * original version)
   s
 pring 2002: bstolt 
                 * updated file reader
		 * removed hard-coded filenames (segfaults!)
		 * handle comments in headers
		 * added some basic error checking
		 * misc clean-up		 
    fall 2003: spieper
		* made it simpler to do all three operations in one shot.
		* improved names on output files.
*/


/* Dear reader, instead of reading in characters, read in ints. Your
   life will be a lot better. If you insist on reading in chars, then
   read in unsigned chars. Note that ints are bigger than chars 
*/

typedef struct pgm {
  int w;
  int h;
  int max;
  int* pData;
} pgm;
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/* 
   This LoadPGM function is an updated version that will deal with 
   comments in file headers and do at least some basic checking if the 
   file can be opened or is the correct format. It does assume the file 
   is actually a valid length once the header has been read. 

   You are of course free to use your own file reading functions.
*/

void LoadPGM( char* filename, pgm* pPgm ) {
  FILE* ifp;
  int word;
  int nRead = 0;
  char readChars[256];

  //open the file, check if successful
  ifp = fopen( filename, "r" );
  if (!ifp) {
    printf("Error: Unable to open file %s.\n\n", filename);
    exit(1);
  }

  //read headers from file
  printf ("Reading PGM file: %s...\n", filename);
  fscanf (ifp, "%s", readChars);

  if (strcmp(readChars, "P2") == 0) {
    //valid file type
    //get a word from the file
    fscanf (ifp, "%s", readChars);
    while (readChars[0] == '#') {
      //if a comment, get the rest of the line and a new word
      fgets (readChars, 255, ifp);
      fscanf (ifp, "%s", readChars);
    }
    
    //ok, comments are gone
    //get width, height, color depth
    sscanf (readChars, "%d", &pPgm->w);
    fscanf (ifp, "%d", &pPgm->h);
    fscanf (ifp, "%d", &pPgm->max);

    // allocate some memory, note that on the HandyBoard you want to 
    // use constant memory and NOT use calloc/malloc
    pPgm->pData = (int*)malloc(sizeof(int) * pPgm->w * pPgm->h);
    
    // now read in the image data itself    
    for (nRead = 0; nRead < pPgm->w * pPgm->h; nRead++) {
      fscanf(ifp, "%d" ,&word);
      pPgm->pData[nRead] = word;
      //printf("nRead = %d %d\n",nRead,pPgm->pData[nRead]);
    }

    printf ("Loaded PGM. Size: %dx%d, Greyscale: %d \n", 
	    pPgm->w, pPgm->h, pPgm->max + 1);
  }
  else {
    printf ("Error: Read file type %s. Format unsupported.\n\n", readChars);
    exit(1);
  }
  fclose(ifp);
}

/* Simply saves the PGM file to a file whose name is in filename */

void WritePGM( char* filename, pgm* pPgm ) {
  FILE* ofp;
  int w, h, max;
  int nWrite = 0;
  int i,j;

  ofp = fopen(filename, "w");
  if (!ofp) {
    printf("Error: Unable to open file %s.\n\n", filename);
    exit(1);
  }

  printf ("Writing ouput PGM: %s\n\n", filename);

  //write the header
  fprintf( ofp, "P2\n" );
  fprintf( ofp, "%d %d\n", pPgm->w, pPgm->h );
  fprintf( ofp, "%d\n", pPgm->max );

  //write the image data
  for (i = 0; i < pPgm->h;i++) {
    for (j = 0; j < pPgm->w; j++)
      fprintf(ofp,"%d ",*(pPgm->pData + i * pPgm->w + j));
    fprintf(ofp,"\n");
  }
  fclose(ofp);	
}

/* We gave you a freebie */
void Thresh( pgm* image, pgm *target, int n ) {
   int *imageBuff,*targetBuff;
   int size;

   size = image->w * image->h;
   imageBuff = image->pData;
   targetBuff = target->pData;

   while( size-- ) {
     if( *imageBuff < n ) {
       *targetBuff = 0;
     }
     else {
       *targetBuff = 255;
     }
     imageBuff++;
     targetBuff++;
   }
}

void Hist(pgm* image, pgm* target) {
    int *imageBuff,*targetBuff;
    int size;
    int buff;
    int hist[256] = {0};
    int hist_temp[256][256] = {{0}};
    int i, j, k;
    //int max = 0;
    
    size = image->w * image->h;
    imageBuff = image->pData;
    targetBuff = target->pData;

    while (size--) {
        buff = *imageBuff;
        //printf("%d\n", buff);
        hist[buff] +=1;
        imageBuff++;
    }
    
    
    for (j=0; j<256; j++) {
        buff = hist[j];
        for (i=0; i<256; i++) {
            k = 256-i;
            if (k>buff) {
                hist_temp[i][j] = 255;
            }
            else {
                hist_temp[i][j] = 0;
            }
        }
    }
 
    
    
    
    for (i=0; i<256; i++) {
        for (j=0; j<256; j++) {
            *targetBuff = hist_temp[i][j];
            //printf("%d\n", *targetBuff);
            targetBuff++;
                   }
    }
 
 
 
    }

void Contrast(pgm* image, pgm* target){
    
    int *imageBuff,*targetBuff;
    int size;
    int min, max = 127;
    
    size = image->w * image->h;
    imageBuff = image->pData;
    targetBuff = target->pData;
    
    while( size-- ) {
        
        if (*imageBuff < min) {
            min = *imageBuff;
        }
        
        if (*imageBuff > max) {
            max = *imageBuff;
        }
        
        imageBuff++;
        
    }
    
    size = image->w * image->h;
    
    while( size-- ) {
        
        *targetBuff = *imageBuff * ((256)/(max-min));
        printf("%d\n", *targetBuff);
        
        imageBuff++;
        targetBuff++;
    }
    
    
}


int main(int argc, char * argv[]) {

  pgm *image, *threshed, *contrasted, *histogram;
  char filename[256];
  int val;
  int errchk;
  int x;
  

  //check if a filename was given, if not, ask for one
  if (argc > 1) {
    strcpy(filename, argv[1]);
  }
  else {
    printf ("Enter filename: ");
    scanf ("%s", filename);
  }
  if(strlen(filename)>220)
  {
	printf("filename too long\n");
	exit(0);
  }


  //allocate memory for the pgm struct
  threshed = (pgm *) malloc (sizeof(pgm));
  histogram = (pgm *) malloc (sizeof(pgm));
  contrasted = (pgm *) malloc (sizeof(pgm));
  image = (pgm *) malloc (sizeof(pgm));
  
  //read the file
  LoadPGM(filename, image);
  contrasted->max=image->max;
  contrasted->w=image->w;
  contrasted->h=image->h;
  threshed->max=image->max;
  threshed->w=image->w;
  threshed->h=image->h;
  histogram->h=256;
  histogram->w=256;
  histogram->max=255;
  threshed->pData=malloc(sizeof(int)*threshed->w*threshed->h);
  contrasted->pData=malloc(sizeof(int)*contrasted->w*contrasted->h);
  histogram->pData=malloc(sizeof(int)*histogram->w*histogram->h);
    
  //int image_matrix[image->h][image->w];

  // --- now do something with the data ---

  //thresholding for instance...
  //get thresholding value
  if (argc > 2) {
    errchk = sscanf (argv[2], "%d", &val);
  }
  else {
    printf ("Enter threshold value: ");
    errchk = scanf ("%d", &val);
  }

  // make sure it's not really screwed up
  if (!errchk || val >= 255 || val < 0) {
    printf("Error: Bad thresholding value\n\n");
    exit(1);
  }

  
  //run contrasting
  //Contrast(image,contrasted);
    
    
  //create your histogram
  Hist(image,histogram);
    
  //run thresholding
  Thresh(image, threshed, val);  
    
  //Find some waldos
  //findwaldo_exact(threshed);

  //finally write the new files

  strcpy(filename+strcspn(filename, "."),"_threshed.pgm");
  WritePGM(filename, threshed);
  //strcpy(filename+strcspn(filename, ".")-strlen("_threshed"),"_contrasted.pgm");
  //WritePGM(filename, contrasted);
  strcpy(filename+strcspn(filename, "."),"_hist.pgm");
  WritePGM(filename, histogram);
  
  //all done
  printf("Done. Have a nice day...\n\n");
}
