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
* Usage: in component file:
* OUTPUT PARAMETERS (...,
* 	result_type, nx, ny, N, value, variant, data, pointer, n_data, n_pointer, n_result,
* 	...)
* 
* DECLARE:
* 	double* data;
* 	double** pointer;
* 	double** N;
* 	double** value;
* 	double** variant;
* 	int n_data; 
* 	int n_pointer; 
* 	int n_result; 
* 
* SHARE:
* 	%include "weighted_mean-lib"
* 
* INITIALIZE:
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
* TRACE:
* 	weighted_mean_input_data(result_type, probability, value, ix, iy, nx, ny, pointer);
* 
* SAVE:
* 	weighted_mean_calculate_result(result_type, nx, ny, pointer, data);
* 
* 	The results are stored in nx x ny matrice N[i][j], value[i][j], variant[i][j].
*
* 
****************************************************************************/
#ifndef WEIGHTED_MEAN_H
#define WEIGHTED_MEAN_H

int weighted_mean_allocation_sizes(int result_type, int nx, int ny, int*n_data, int*n_pointer, int*n_result);
int weighted_mean_initialise(int result_type, int nx, int ny, double**data, double***pointer, double***N, double***value, double***variant); 
void weighted_mean_input_data(int result_type, double prob, double value, int ix, int iy, int nx, int ny, double**pointer);
void weighted_mean_calculate_result(int result_type, int nx, int ny, double**pointer, double*data);

#endif
