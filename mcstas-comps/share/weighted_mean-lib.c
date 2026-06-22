/*****************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright 1997-2006, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
*
* %Identification
* Written by: Hal Lee
* Date: December, 2022
* Origin: ESS
* Release: McStas 2.7x, 3.0x
* Version: $Revision$
*
* Function to calculate weighted mean, RMS deviation from weighted mean 
* and the variant of the respective quantities.
* The formula of the variant was quoted and shown to be a reasonable
* estimation in Gatz, Donald F.; Smith, Luther (June 1995). "The standard 
* error of a weighted mean concentration—I. Bootstrapping vs other methods". 
* Atmospheric Environment. 29 (11): 1185–1193. 
* doi:10.1016/1352-2310(94)00210-C.
* 
* INPUT:
* 	int result_type: 
*		0=average weight 
* 		1=weighted mean
* 		2=RMS deviation about weighted mean
* 		3=Maximum value with respect to weighted mean
* 		4=Minimum value with respect to weighted mean
* 		5=Maximum value
* 		6=Minimum value
* 	int nx, ny: dimensions of the data array. If one dimensional, use ny=0 or 1.
* 
* OUTPUT: 
* 	double** N;			//number of neutron hits
* 	double** value;		//resulting value
* 	double** variant;	//variant of value
*
* Usage: in component file
* OUTPUT PARAMETERS (...,
* 	result_type, nx, ny, N, value, variant, data, pointer, n_data, n_pointer, n_result,
* 	...)
* 
* DECLARE
* 	double* data;
* 	double** pointer;
* 	double** N;
* 	double** value;
* 	double** variant;
* 	int n_data; 
* 	int n_pointer; 
* 	int n_result; 
* 
* SHARE
* 	%include "weighted_mean-lib"
* 
* INITIALIZE
* 	//allocate memory for data, pointer, result
* 	weighted_mean_allocation_sizes(result_type, nx, ny, &n_data, &n_pointer, &n_result);
* 
* 	data =(double*)calloc(n_data,sizeof(double));		
* 	pointer=(double**)calloc(n_pointer,sizeof(double*));
* 	N=(double**)calloc(n_result,sizeof(double*));
* 	value=(double**)calloc(n_result,sizeof(double*));
* 	variant=(double**)calloc(n_result,sizeof(double*));
* 
* 	weighted_mean_initialise(result_type, nx, ny, &data, &pointer, &N, &value, &variant); 
* 
* TRACE
* 	weighted_mean_input_data(result_type, p, variable, ix, iy, nx, ny, pointer);
* 
* SAVE
* 	weighted_mean_calculate_result(result_type, nx, ny, pointer, data);
* 	The results are stored in N[i][j], value[i][j], variant[i][j].
*
* 
****************************************************************************/
#ifndef WEIGHTED_MEAN_H
%include "weighted_mean-lib.h"
#endif

//#ifndef LIB_DEBUG_WEIGHTED_SUM
//#define LIB_DEBUG_WEIGHTED_SUM
//#endif

#ifndef WEIGHTED_MEAN_C
#define WEIGHTED_MEAN_C

#define WEIGHT_TYPE_COUNT      3
#define WEIGHTED_MEAN_COUNT    9
#define RMS_DEV_COUNT         11
#define EXTREME_WEIGHTED_COUNT 5
#define EXTREME_UNWEIGHTED_COUNT 3

int weighted_mean_allocation_sizes (int result_type, int nx, int ny, int*n_data, int*n_pointer, int*n_result) {

	if (result_type<0 || result_type>6 || n_data==0 || n_pointer==0 || n_result==0) {
		printf("Error weighted_mean_allocation_sizes(..): require 0<=result_type<=6, n_data, n_pointer, n_result must not be 0.\n");
		return 0;
	}

	if (nx < 1) nx = 1;
	if (ny < 1) ny = 1;
	int ntype;
	switch(result_type) {
		case 0: ntype = WEIGHT_TYPE_COUNT; break;
		case 1: ntype = WEIGHTED_MEAN_COUNT; break;
		case 2: ntype = RMS_DEV_COUNT; break;
		case 3: 
		case 4: ntype = EXTREME_WEIGHTED_COUNT; break;
		case 5: 
		case 6: ntype = EXTREME_UNWEIGHTED_COUNT; break;
	}
	
	if (nx > 0 && ny > 0 && ntype > 0) {
        long long total = (long long)nx * ny * ntype;
        if (total > INT_MAX) {
            printf("Error: Requested allocation size too large\n");
            return 0;
        }
    }
	
	*n_data    = nx*ny*ntype;
	*n_pointer = nx*ntype;
	*n_result  = nx;
	
	return 1;
}

int weighted_mean_initialise (int result_type, int nx, int ny, double**data, double***pointer, double***N, double***value, double***variant) {

	if (result_type<0 || result_type>6 || data==0 || pointer==0 || N==0 || value==0 || variant==0) {
		printf("Error weighted_mean_initialise(..): require 0<=result_type<=6, pointer, data, N, value, variant must not be 0.\n");
		return 0;
	}

	if (nx < 1) nx = 1;
	if (ny < 1) ny = 1;	
	int ntype;
	switch(result_type) {
		case 0: ntype = WEIGHT_TYPE_COUNT; break;
		case 1: ntype = WEIGHTED_MEAN_COUNT; break;
		case 2: ntype = RMS_DEV_COUNT; break;
		case 3: 
		case 4: ntype = EXTREME_WEIGHTED_COUNT; break;
		case 5: 
		case 6: ntype = EXTREME_UNWEIGHTED_COUNT; break;
	}
	
	double *arr=*data;
	double **ptr=*pointer;
	double **n=*N;
	double **val=*value;
	double **var=*variant;
	
	int ix, itype;

	for (itype=0; itype<ntype; itype++) {
		for (ix=0; ix<nx; ix++) {
			ptr[ix+itype*nx] = &((arr)[ix*ny + itype*nx*ny]);
		}
	}
	
	for (ix = 0; ix < nx; ix++) {
		n[ix]   = &((arr)[ix*ny]);
		val[ix] = &((arr)[ix*ny + nx*ny]);
		var[ix] = &((arr)[ix*ny + 2*nx*ny]);
	} 
	return 1;
}

void weighted_mean_input_data (int result_type, double prob, double value, int ix, int iy, int nx, int ny, double**pointer) {
	if (nx < 1) nx=1;
	if (ny < 1) ny=1;
	
	if (result_type<0 || result_type>6 || ix<0 || ix>=nx || iy<0 || iy>=ny || pointer==0) {
		printf("Error weighted_mean_input_data(..): require 0<=result_type<=6, 0<=ix<=nx-1, 0<=iy<=ny-1, pointer must not be 0.\n");
		return;
	}

	unsigned long ii = ix*ny+iy;
	double **ptr = pointer; 
	double u, n, *val;

	switch (result_type) 
	{
		case 0: //weight only
			*(*(ptr     )+ii) += 1.0; 			//n
			*(*(ptr+  nx)+ii) += prob;			//w 
			*(*(ptr+2*nx)+ii) += prob*prob; 	//w2 
			break;
		case 1: //weighted average value
			*(*(ptr     )+ii) += 1.0; 			//n
			*(*(ptr+3*nx)+ii) += (u=prob);		//w 
			*(*(ptr+4*nx)+ii) += (u*=value); 	//wv 
			*(*(ptr+5*nx)+ii) += (u*=value); 	//wv2 
			*(*(ptr+6*nx)+ii) += (u=prob*prob); //w2 
			*(*(ptr+7*nx)+ii) += (u*=value); 	//w2v 
			*(*(ptr+8*nx)+ii) += (u*=value); 	//w2v2 
			break;
		case 2: //RMS deviation with respect to weigthed average value
			*(*(ptr     )+ii) += 1.0; 			//n 
			*(*(ptr+3*nx)+ii) += (u=prob);		//w 
			*(*(ptr+4*nx)+ii) += (u*=value); 	//wv 
			*(*(ptr+5*nx)+ii) += (u*=value); 	//wv2 
			*(*(ptr+6*nx)+ii) += (u=prob*prob); //w2 
			*(*(ptr+7*nx)+ii) += (u*=value); 	//w2v 
			*(*(ptr+8*nx)+ii) += (u*=value); 	//w2v2 
			*(*(ptr+9*nx)+ii) += (u*=value); 	//w2v3  
			*(*(ptr+10*nx)+ii) += (u*=value); 	//w2v4 
			break;
		case 3: // Maximum value with respect to weigthed average value
			*(*(ptr+3*nx)+ii) += prob;			//w 
			*(*(ptr+4*nx)+ii) += prob*value;	//wv 
			n = (*(*ptr+ii) += 1.0); 			//n  
			val = *(ptr+nx)+ii; 				//val
			if ((n == 1) || (value > *val)) 
			{
				*val = value;
			}
			break;
		case 4: // Minimum value with respect to weigthed average value
			*(*(ptr+3*nx)+ii) += prob;			//w 
			*(*(ptr+4*nx)+ii) += prob*value;	//wv 
			n = (*(*ptr+ii) += 1.0); 			//n  
			val = *(ptr+nx)+ii; 				//val
			if ((n == 1) || (value < *val)) 
			{
				*val = value;
			}
			break;
		case 5: // Maximum value
			n = (*(*ptr+ii) += 1.0); 			//n  
			val = *(ptr+nx)+ii; 
			if ((n == 1) || (value > *val)) 
			{
				*val = value; 					//val
			}
			break;
		case 6: // Minimum value
			n = (*(*ptr+ii) += 1.0); 			//n  
			val = *(ptr+nx)+ii; 
			if ((n == 1) || (value < *val)) 
			{
				*val = value; 					//val
			}
			break;
	}

}

void weighted_mean_calculate_result (int result_type, int nx, int ny, double**pointer, double*data) {

	if (result_type<0 || result_type>6 || pointer==0 || data==0) {
		printf("Error weighted_mean_calculate_result(..): require 0<=result_type<=6, pointer and data must not be 0.\n");
		return;
	}

	if (nx < 1) nx=1;
	if (ny < 1) ny=1;

	#ifdef USE_MPI
	if (mpi_node_count>1) {

		switch (result_type) {
			case 0: //weight only
				mc_MPI_Sum(data,(long)3*nx*ny);
				break;
			case 1: //weighted average 
				mc_MPI_Sum(data,(long)9*nx*ny);
				break;
			case 2: //RMS deviation about weighted average 
				mc_MPI_Sum(data,(long)11*nx*ny);
				break;
			case 3: // Maximum  from weighted average 
				mc_MPI_Max(data,(long)nx*ny); //n value = 1 if there is value
				mc_MPI_Max(data+nx*ny,(long)nx*ny); //find maximum
				mc_MPI_Sum(data+3*nx*ny,(long)2*nx*ny); //needed for calculating weight
				break;
			case 4: // Minimum  from weighted average 
				mc_MPI_Max(data,(long)nx*ny); //n value = 1 if there is value
				mc_MPI_Min(data+nx*ny,(long)nx*ny); //find minimum
				mc_MPI_Sum(data+3*nx*ny,(long)2*nx*ny); //needed for calculating weight
				break; 
			case 5: // Maximum value
				mc_MPI_Max(data,(long)nx*ny); //n value = 1 if there is value
				mc_MPI_Max(data+nx*ny,(long)nx*ny); //find maximum
				break;
			case 6: // Minimum value
				mc_MPI_Max(data,(long)nx*ny); //n value = 1 if there is value
				mc_MPI_Min(data+nx*ny,(long)nx*ny); //find minimum
				break;
			default:
				break;
		}
	}
	#endif
	
		unsigned long ii; unsigned long ix; unsigned long iy;
		double **ptr = pointer; 
		double*N; double*value; double*variant;
		double w; double wv; double wv2; double w2; double w2v; double w2v2; double w2v3; double w2v4;
		double n; double val; double var; double pv;
		
		switch (result_type) {

			case 0: //weight only
				break;
			case 1: //weighted average value
				for (ix=0; ix<nx; ix++) {
				for (iy=0; iy<ny; iy++) {
					ii = ix*ny+iy;
					N       = *(ptr)+ii; 	//n 
					value   = *(ptr+nx)+ii; //value
					variant = *(ptr+2*nx)+ii; //variant 
					
					n = *N;
					w    = *(*(ptr+3*nx)+ii); //w 
					wv   = *(*(ptr+4*nx)+ii); //wv 
					wv2  = *(*(ptr+5*nx)+ii); //wv2 
					w2   = *(*(ptr+6*nx)+ii); //w2 
					w2v  = *(*(ptr+7*nx)+ii); //w2v 
					w2v2 = *(*(ptr+8*nx)+ii); //w2v2 

					val = 0.0;
					var = 0.0;
					if (fabs(w) > 0) 
					{
						val = wv / w; 
						if (n > 1) 
						{
							var = w2v2 - 2.0*val*w2v + val*val*w2;
							if (var > 0) {
								var = sqrt(n *(var) / (n-1)) / w;
							}
						}
					}
					*value = val;
					*variant = var;
				}
				}
				break;
			case 2: //RMS deviation with respect to weigthed average value
				for (ix=0; ix<nx; ix++) {
				for (iy=0; iy<ny; iy++) {
					ii = ix*ny+iy;
					N       = *(ptr)+ii; 	//n 
					value   = *(ptr+nx)+ii; //value
					variant = *(ptr+2*nx)+ii; //variant 
					
					n = *N;
					w    = *(*(ptr+3*nx)+ii); //w 
					wv   = *(*(ptr+4*nx)+ii); //wv 
					wv2  = *(*(ptr+5*nx)+ii); //wv2 
					w2   = *(*(ptr+6*nx)+ii); //w2 
					w2v  = *(*(ptr+7*nx)+ii); //w2v 
					w2v2 = *(*(ptr+8*nx)+ii); //w2v2 
					w2v3 = *(*(ptr+9*nx)+ii); //w2v3  
					w2v4 = *(*(ptr+10*nx)+ii); //w2v4 

					val = 0.0;
					var = 0.0;
					if (fabs(w) > 0) 
					{
						pv = wv / w; 
						val = (wv2 - 2.0*pv*wv + pv*pv*w) / w;
						if (val > 0.0) {
							val = sqrt(val);
						
							if (n > 1 && fabs(val) > 0) {
								var = 	(	        	          w2v4 
											- 4.0 * pv          * w2v3 
											+ 6.0 * pv*pv	    * w2v2 
											- 4.0 * pv*pv*pv    * w2v
											+       pv*pv*pv*pv * w2)
										+ 2.0 * val *
											(               w2v2
											- 2.0 * pv    * w2v
											+       pv*pv * w2)
										+ val * val * w2;
								var = var > 0.0 ? sqrt(n * var / (n-1)) / (2 * w * val) : 0;

							}
							
						}
						else {
							val = 0.0;
						}
					}
					*value = val;
					*variant = var;
				}
				}
				break;
			case 3: // Maximum value with respect to weigthed average value
			case 4: // Minimum value with respect to weigthed average value
				for (ix=0; ix<nx; ix++) {
				for (iy=0; iy<ny; iy++) {
					ii = ix*ny+iy;
					N       = *(ptr)+ii; 	//n 
					value   = *(ptr+nx)+ii; //value
					variant = *(ptr+2*nx)+ii; //variant 
					
					w  = *(*(ptr+3*nx)+ii); 	//w 
					wv = *(*(ptr+4*nx)+ii); 	//wv 

					*N = 1;
					*variant = 0.0;
					if (w != 0.0)
					{
						*value -= wv / w;
					}
				}
				}
				break;
			case 5: // Maximum value
			case 6: // Minimum value
				for (ix=0; ix<nx; ix++) {
				for (iy=0; iy<ny; iy++) {
					ii = ix*ny+iy;
					N       = *(ptr)+ii; 	//n 
					variant = *(ptr+2*nx)+ii; //variant 
					
					*N = 1; 
					*variant = 0.0;
				}
				}
				break;
		}
}

#endif
