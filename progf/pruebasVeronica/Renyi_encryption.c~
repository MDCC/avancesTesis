/*
 *  Renyi_encryption.c
 *  
 *
 *  Created by Verónica Suaste on 09/04/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define MAXINT (1ULL<<32)-1
#define Renyi(var_k, par_b) var_k *par_b
#define Renyi_int(var_k, par_b) (var_k *par_b + (var_k>>2)) % (1ULL<<32-1)

//number of chaotics maps
int NN = 4;
// weights
//float *W = new float[NN];
//float W[NN];
//perturbation parameter
float ep=0.5;
// betha reny Map parameter
//float *be = new float[NN];
//unsigned int *betha = new unsigned int[NN];
int lSize;


int main () {
	//weights
	float W[NN];
	//beta renyi parameters
	float be[NN];
	unsigned int beta[NN];

	//initial conditions(seed)
	float IC[NN];
	float Key[NN];
	unsigned int W_int[NN+1];
	unsigned int IC_int[NN];
	
	srand(time(NULL));
	int i,j,k;
	
	for( i=0; i<NN; i++)
	{
		W[i] = (float)i/(float)NN;
		W_int[i] = W[i] * MAXINT;
		IC[i] = (rand() % 100)/100.0;
		Key[i] = IC[i];
		be[i] = 2.0+i;
	}
	
	float h;
	unsigned int NumIt_i = 7;
	//Initialize chaotic maps(real)
	for(j=0; j<NumIt_i; j++)
	{
		h=0;
		for(k = 0; k<NN; k++)
			h+= W[k]*IC[k]; 
		for(i=0; i<NN; i++)
			IC[i] = (1.0 -ep)*Renyi(IC[i],be[i]) + ep*h;
	}
	
	//Initialize chaotic maps(interger)
	for(i=0; i<NN; i++)
	{
		IC_int[i] = (unsigned int) IC[i];
		Key[i] = IC_int[i];
	}
	
	FILE *pFile;
	FILE *oFile;
	
	//long long lSize;
	//int lSize;
	
	pFile = fopen("/Users/veronicasuaste/Documents/Tesis/Idea1/test.mov", "rb");
	//pFile = fopen("test.mov", "rb");
	if(pFile==NULL) printf("No se pudo abrir el archivo \n");
	
	fseek(pFile,0,SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);	
	char * Dat = (char *)malloc(lSize*sizeof(char));
	char *ShufDat = (char *)malloc(lSize*sizeof(char));
	if(fread(Dat,1,lSize,pFile)!=lSize) printf("No se pudo leer el archivo \n");
	for(i=0; i<lSize; i++)
	ShufDat[i] = Dat[i];
	
	unsigned int Pack_Size = 400;
	unsigned int BlockSize = 8;
	unsigned int pos_f = 0;
	unsigned int Num_Blocks = 20;
	unsigned int Num_bits_encry = 32;
	unsigned int Bl_Size_byte = Pack_Size/Num_Blocks;
	unsigned int Bl_Size_bit = Bl_Size_byte*8;
	unsigned int Num_It = Bl_Size_bit/Num_bits_encry;
	unsigned int rand_Bl,temp;
	unsigned int pos_byte;
	
	unsigned int Num_pack = lSize/400;
	char *Pack_temp;
	Pack_temp = Dat;
	
	int hh = 0;
	int count = 0;
	int p,step;
	unsigned int Blocks[Num_Blocks];
	int pos_pack=0;
	int bl,bl1=0;
	
	char PText[(Num_bits_encry/8)];
	//initialize Plain Text
	for(i=0; i<(Num_bits_encry/8); i++)
		PText[i] = (char)'a'+i;
	
	for(i=0; i<Num_Blocks; i++)
		Blocks[i] = i;
	
	//counting TIME
	
	struct timeval tv1,tv2;
	float tsec,tusec;
	
	if (gettimeofday(&tv1,0) == -1) {
		printf("ERROR time1\n");
		exit(1);
    }
    printf("secs = %ld, usec = %ld\n",tv1.tv_sec,tv1.tv_usec);
	
	//Encryption process
	int n_P,ii,jj;
	
	for( n_P = 0; n_P< Num_pack; n_P++)
	{
		for(i=0; i<Num_Blocks; i++)
			Blocks[i] = i;
		
		for(i=Num_Blocks; i>0; i--)
		{
			rand_Bl = IC_int[0]%i;
			
			//shuffling 
			temp = Blocks[i-1];
			Blocks[i-1] = Blocks[rand_Bl];
			Blocks[rand_Bl] = temp;
			
			pos_byte = Blocks[i-1]*Bl_Size_byte; 
			
			for(j=0; j<Num_It; j++)
			{
				pos_f = 0;
				hh = 0;
				for(jj=0; jj<NN; jj++)
					hh+=W_int[jj]^IC_int[jj]^PText[jj];
				
				hh = hh%20;
				for(jj=0; jj<NN; jj++)
				{
					IC_int[jj] = Renyi_int(IC_int[jj],beta[jj]) + hh;
					//PText[jj] = Dat[pos_byte + jj];
					PText[jj] = Pack_temp[pos_byte + jj];
				}
				
				//block fliping
				while(pos_f + BlockSize < Num_bits_encry)
				{
					if(count >= NN)
					{
						count = 0;
						hh =0;
						for(ii=0; ii<NN; ii++)
							hh+= W_int[ii]^IC_int[ii];
						hh=hh%20;
						for(ii=0; ii<NN; ii++)
							IC_int[ii] = Renyi_int(IC_int[ii],beta[ii]) + hh;
					}
					
					p = IC_int[count]&7;
					pos_f+= p;
					
					if(p&1)
					{
						step = IC_int[count+1]%p;
						pos_f -= step;
					}else{
						step = IC_int[count+1]%(BlockSize - p);
						pos_f += step;
					}
					
					Pack_temp[pos_byte + (pos_f/8)]^= 1<<(8 - (pos_f&7));
					count+=2;
				}
				
				pos_byte+= 4; //Num of bytes to encrypt
				
			}
			
		}
		
		//Writing the shuffling
		bl1 =0;
		for( i=0; i<Num_Blocks; i++)
		{
			bl = Blocks[i]*Bl_Size_byte;
			bl1 = i*Bl_Size_byte;
			
			for( j=0; j<Bl_Size_byte; j++)
				ShufDat[pos_pack+bl1+j] = Pack_temp[bl+j];
		}
		
		Pack_temp+=400;
		pos_pack+=400;
	}	
	
	if (gettimeofday(&tv2,0) == -1) {
		printf("ERROR time2\n");
		exit(1);
	}
	printf("secs = %ld, usec = %ld\n",tv2.tv_sec,tv2.tv_usec);
	
	//elapsed time
	if (tv1.tv_usec > tv2.tv_usec) {  
		tv2.tv_usec += 1000000;
		tv2.tv_sec--; 
	} 
	tsec = (tv2.tv_sec - tv1.tv_sec)*1000.; // in milliseconds
	tusec = (tv2.tv_usec - tv1.tv_usec)/1000.;
	
	printf("tsec = %f, tusec = %f, elapsed time = %f milliseconds\n",tsec,tusec,tsec+tusec);
	printf("Megabits/sec = %f \n",((Num_pack*Pack_Size*8)/(1000.0*1000.0))/((tsec + tusec)/1000.));
	
	oFile =  fopen("/Users/veronicasuaste/Documents/Tesis/Idea7/test2.mov", "wb");
	//oFile =  fopen("test2.mov", "wb");
	// fwrite(Dat, 1, lSize,oFile);
	fwrite(ShufDat, 1, lSize,oFile);
	fclose(pFile);
	fclose(oFile);
	
	//DECRYPTION PROCESS
	
	for(i=0; i<NN; i++)
		IC_int[i] = (unsigned int) Key[i];
	
	for(i=0; i<(Num_bits_encry/8); i++)
		PText[i] = (char)'a'+i;
	
	for(i=0; i<Num_Blocks; i++)
		Blocks[i] = i;
	
	pFile = fopen("/Users/veronicasuaste/Documents/Tesis/Idea7/test2.mov", "rb");
	//pFile = fopen("test2.mov", "rb");
	if(pFile==NULL)printf("No se pudo abrir el archivo \n");
	
	fseek(pFile,0,SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	if(fread(Dat,1,lSize,pFile)!=lSize) printf("No se pudo leer el archivo \n");
	for(i=0; i<lSize; i++)
		ShufDat[i] = Dat[i];
	count=0;
	
	Pack_temp = Dat;
	pos_pack =0;
	
	for( n_P = 0; n_P< Num_pack; n_P++)
	{
		for(i=0; i<Num_Blocks; i++)
			Blocks[i] = i;
		
		for(i=Num_Blocks; i>0; i--)
		{
			rand_Bl = IC_int[0]%i;
			
			temp = Blocks[i-1];
			Blocks[i-1] = Blocks[rand_Bl];
			Blocks[rand_Bl] = temp;
			
			pos_byte = (i-1)*Bl_Size_byte;
			
			for(j=0; j<Num_It; j++)
			{
				pos_f = 0;
				hh = 0;
				for(jj=0; jj<NN; jj++)
					hh+=W_int[jj]^IC_int[jj]^PText[jj];
				hh = hh%20;
				for(jj=0; jj<NN; jj++)
					IC_int[jj] = Renyi_int(IC_int[jj],beta[jj]) + hh;
				
				
				while(pos_f + BlockSize < Num_bits_encry)
				{
					if(count >= NN)
					{
						count = 0;
						hh =0;
						for(ii=0; ii<NN; ii++)
							hh+= W_int[ii]^IC_int[ii];
						hh = hh%20;
						for(ii=0; ii<NN; ii++)
							IC_int[ii] = Renyi_int(IC_int[ii],beta[ii]) + hh;
					}
					
					//p = IC_int[count]%BlockSize;
					p = IC_int[count]&7;
					pos_f+= p;
					
					if(p&1)
					{
						step = IC_int[count+1]%p;
						pos_f -= step;
					}else{
						step = IC_int[count+1]%(BlockSize - p);
						pos_f += step;
					}
					
					Pack_temp[pos_byte + pos_f/8] ^= 1<<(8 - (pos_f&7));
					count+=2;
				}
				for(jj=0; jj<NN; jj++)
					PText[jj] = Pack_temp[pos_byte + jj];
				pos_byte+= 4;
				
			}
		}

		//Shuffling...		
		for(i=0; i<Num_Blocks; i++)
		{
			bl = Blocks[i]*Bl_Size_byte;
			bl1 = i*Bl_Size_byte;
			for(j=0; j<Bl_Size_byte; j++)
				ShufDat[pos_pack+bl + j] = Pack_temp[bl1+j];
		}
		
		Pack_temp+=400;
		pos_pack+=400;
	}
	
	oFile =  fopen("/Users/veronicasuaste/Documents/Tesis/Idea7/test3.mov", "wb");
    //oFile =  fopen("test3.mov", "wb");
	fwrite(ShufDat, 1, lSize,oFile);
	fclose(pFile);
	fclose(oFile);
	
	free(Dat);
	free(ShufDat);
}
