/****************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright 1997-2003, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* In library: share/supermirror.h
* Depends on "polyhedron" (which depends on "plane")
*
* Usage: in SHARE
* %include "supermirror"
*
* %I
* Written by: Wai Tung Lee
* Date: May 2025
* Origin: ESS
*
* %D
* Calculate the neutron reflection and transmission of a flat supermirror with parallel mirror surfaces.
* The following can be specified: 
* 1. reflection from either mirror coating or substrate surface, mirror coating can be single-side, double-side, 
* 2. absorber coating:  beneath mirror coating, single-side coated, double-side coated, or uncoated,
* 3. refraction and total reflection at substrate surface,
* 4. attenuation and internal reflection inside substrate. 
*
* More details in "supermirror.h"
*
*******************************************************************************/

#ifndef SUPERMIRROR_LIB_H
#include "supermirror-lib.h"
#endif

#ifndef ZERO_THRESHOLD
//low enough to avoid false identification of zero
//high enough to account for a chain of operations
#define ZERO_THRESHOLD ZERO_THRESHOLD*10 
#endif

#ifndef LEXICON_LIB
#define LEXICON_LIB
%include "lexicon"
#endif


#ifndef SUPERMIRROR_LIB_C
#define SUPERMIRROR_LIB_C

#ifndef Qc_Ni
#define Qc_Ni 0.0217656
#endif

/*
#define DEBUG_REF_LIB_TRACK 
#define DEBUG_REF_LIB_CATCH_ANOMALY
#define DEBUG_REF_LIB_SAVE
*/

/*************************************/
/* Definition of internal paramaters */
/*************************************/
typedef struct SimState {
	//neutron state parameters
	int ray_count;
	char location[CHAR_BUF_LENGTH];
	char event[CHAR_BUF_LENGTH];
	double w; 
	double t; 
	Coords p; 
	Coords v; 
	Coords s;
	double ws[2]; //index=spin+,spin-
	
	double v_len;
	double vn_len;
	
	//intersect parameters
	int side; int plane; int layer; 
	int side_at_plane[2]; //index=plane number, side corresponding to plane
	Coords fn; //surface normal of intersected plane

	int n_mirror_intersect; //number of intersects to a mirror 
	int n_surface_intersect; //number of intersects to a surface

	double last_time; Coords last_point; int last_plane;
	
	//parameters indexing on plane number
	int set_surface_parameters; //0=not set, 1=set
	
	Coords v_in_vac_inward_at_plane[2]; //index=plane number {0, 1}, v before enter from air/vacuum
	Coords v_in_vac_outward_at_plane[2]; //index=plane number {0, 1}, v after exit to air/vacuum
	double v_in_vac_len_at_plane[2];
	double vn_in_vac_len_at_plane[2];
	double Rm_vac_to_mir_at_plane[2][2];  //1st index=plane number {0, 1}, 2nd index=spin+,spin-, mirror reflectivity

	Coords v_sub_to_mir_at_plane[2][2]; //index=plane number {0, 1}, v in multilayer from substrate
	double v_sub_to_mir_len_at_plane[2][2];
	double vn_sub_to_mir_len_at_plane[2][2];
	double Rm_sub_to_mir_at_plane[2][2];  //1st index=plane number {0, 1}, 2nd index=spin+,spin-, mirror reflectivity
	int Rm_sub_to_mir_total_refl_at_plane[2][2]; //total reflection or not determined by refraction calculation

	Coords v_in_sub_inward_at_plane[2]; //index=plane number {0, 1} 
	Coords v_in_sub_outward_at_plane[2]; //index = plane number {0, 1} 
	double v_in_sub_inward_len_at_plane[2]; //index = plane number {0, 1} 
	double v_in_sub_outward_len_at_plane[2]; //index = plane number {0, 1} 
	double vn_in_sub_inward_len_at_plane[2]; //index = plane number {0, 1} 
	double vn_in_sub_outward_len_at_plane[2]; //index = plane number {0, 1} 

	double Rs_vac_to_sub_at_plane[2]; //index = plane number, substrate surface reflectivity for incident beam from air/vacuum to substrate
	double Rs_sub_to_vac_at_plane[2]; //index = plane number, substrate surface reflectivity for exit beam from substrate to air/vacuum
	
	int set_L_attn_mir; 
	double T_attn_mir; //mirror layer attenuation length

	int set_L_attn_abs; //0=not set, 1=set
	double L_attn_abs_at_plane[2]; //index=plane number {0, 1}, absorber layer attenuation length
	double t_prop_abs_at_plane[2]; //index=plane number {0, 1}, time through absorber layer
	double T_prop_abs_at_plane[2]; //index = plane number {0, 1}, transmission through absorber layer
	
	int set_L_attn_sub; //0=not set, 1=set
	double T; //temperature for calculating TDS
	double L_attn_sub; //substrate attenuation length
	double t_prop_sub; //time through substrate
	double T_prop_sub; //transmission through substrate
		
} SimState;

typedef enum SupermirrorLocationAndEventCode { 
	//sm->proc->layer
	sm_MirrorLayer = 0, 
	sm_AbsorberLayer = 1, 
	sm_SubstrateSurfaceLayer = 2,
	sm_SubstrateLayer = 3,
	
	//sm->proc->side
	sm_ReflectedSide = 0, 
	sm_TransmittedSide = 1, 
	sm_EdgeSide = 2,
	
	//sm->proc->plane, numerical definition in struct Supermirror
	//must not reorder
	sm_SurfacePlane1 = 0,
	sm_SurfacePlane2 = 1,
	sm_EdgeFrontPlane = 2,
	sm_EdgeBackPlane = 3, 
	sm_EdgeSidePlane1 = 4, 
	sm_EdgeSidePlane2 = 5,
			
	//sm->proc->event, numbering continue from events listed in supermirror-lib.h
	sm_Reflected = 5,
	sm_Transmitted = 6, 
	sm_ReflectedOutward = 7,
	sm_TransmittedOutward = 8, 
	sm_ReflectedInward = 9,
	sm_TransmittedInward = 10, 
	sm_TotalReflected = 11,
	sm_Zigzag = 12,
	
	//directional, not recorded
	going_inward = 0,
	going_outward = 1,
	ignore_reflection = 2, 
	keep_reflection =3,
	
	//types
	sm_refl_type_refl = 0x1, 
	sm_abs_type_attn = 0x1,
	sm_sub_type_attn = 0x1,
	sm_sub_type_front_edge_attn = 0x2,
	sm_sub_type_back_edge_attn = 0x4,
	sm_subsurface_type_refl = 0x1,
	sm_subsurface_type_total_refl = 0x2,
	sm_subsurface_type_refract = 0x4

} SupermirrorLocationAndEventCode; 

/***************************/
/* General Tools functions */
/***************************/
FILE *sm_open_file(	char *path_in, char *filename, char *mode, char **path_out, int *file_location_option);

/*****************************/
/* Debugging print functions */
/*****************************/
// At the top of supermirror-lib.c

// ============================================================================
// Debug printing control for GPU/Multi-threading
// ============================================================================

// Determine if we're in a multi-threaded GPU environment
#if defined(__CUDACC__) || defined(_OPENMP_OFFLOAD) || (defined(_OPENMP) && !defined(__CUDA_ARCH__))
    #define SM_MULTI_THREADED 1
#else
    #define SM_MULTI_THREADED 0
#endif

// Debug prefix variables - only used in single-threaded context or with thread-local
#if SM_MULTI_THREADED
    // Multi-threaded: Use thread-local storage if supported
    #if defined(__CUDACC__)
        // CUDA: Disable debug printing entirely (GPU printf is unreliable for this use case)
        #define SM_DEBUG_ENABLED 0
        static int supermirror_flat_i_prefix = 0;  // Unused but defined to avoid errors
        static char supermirror_flat_s_prefix[CHAR_BUF_LENGTH];
        
    #elif defined(_OPENMP)
        // OpenMP: Use threadprivate
        static int supermirror_flat_i_prefix = 0;
        static char supermirror_flat_s_prefix[CHAR_BUF_LENGTH];
        #pragma omp threadprivate(supermirror_flat_i_prefix, supermirror_flat_s_prefix)
        #define SM_DEBUG_ENABLED 1
        
    #else
        // Other multi-threading: Fallback to global (may have races)
        static int supermirror_flat_i_prefix = 0;
        static char supermirror_flat_s_prefix[CHAR_BUF_LENGTH];
        #define SM_DEBUG_ENABLED 1
        #warning "supermirror-lib: Multi-threaded but no thread-local support - debug output may be corrupted"
    #endif
#else
    // Single-threaded (MPI only): Safe to use globals
    static int supermirror_flat_i_prefix = 0;
    static char supermirror_flat_s_prefix[CHAR_BUF_LENGTH];
    #define SM_DEBUG_ENABLED 1
#endif

// Wrap debug print functions
#if SM_DEBUG_ENABLED
    #define SM_DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
    #define SM_DEBUG_PRINTF(...)  // No-op on GPU
#endif

char* set_supermirror_flat_prefix(int number_of_tabs);
char*supermirror_flat_inc_prefix();
char*supermirror_flat_dec_prefix();
void sm_print_state(char*header, SimState*state, Supermirror*sm);
void sm_print_intersect(char*subheader, int num_intersect, double*dtime, Coords*dpoint, double*time, Coords*point, int*plane, int*type);
void sm_print_refl(char *event, SimState*state, Supermirror*sm);
void sm_print_error(SimState*state, Supermirror *sm, char*topic, char*error_message, int outcome);
#if defined(DEBUG_REF_LIB_TRACK)
char track_msg[65536];
#endif
#if defined(DEBUG_REF_LIB_SAVE)
void sm_save_state(char*event, SimState*state, Supermirror*sm);
#endif

/*********************************/
/* Internal initialise functions */
/*********************************/

int set_supermirror_flat_geometry (

		double length, //m supermirror length projection along z-axis
		double thickness_in_mm, //mm
		Coords side_edge_1_normal, Coords side_edge_1_point, 
		Coords side_edge_2_normal, Coords side_edge_2_point, 
		char*initial_placement_at_origin,	//"TopFrontEdge","FrontSubstrateCentre","BottomFrontEdge"
		char*tilt_y_axis_location, 	//"TopFrontEdge","TopMirrorCentre","TopBackEdge"
									//"FrontSubstrateCentre","SubstrateCentre","BackSubstrateCentre", 
									//"BottomFrontEdge","BottomMirrorCentre","BottomBackEdge"
		double tilt_about_y_first_in_degree,  //first, tile about y_axis at selected location 
		Coords translation_second,  //second, translate reference point 
		double rot_about_z_third_in_degree, //third, rotate about global z-axis 
		Polyhedron*geo, CoordOp*co);
int load_substrate_material_parameters(char*substrate_material_name, double*data);
static double debye_integral_phi(double x);
static double calculate_R_series(double x);
double calculate_phonon_a_mph(double S_coh, double A);
double calculate_phonon_b_mph(double A, double T_D, double T, double C2);
double calculate_phonon_a_sph(double S_coh, double A, double T_D, double T);
int set_substrate_material_parameters(char*substrate_material_name, 
	double substrate_L_abs, double substrate_L_inc, double substrate_SLD, 
	double substrate_S_coh, double substrate_A, double substrate_T_D, double substrate_T, double substrate_n, double substrate_C2, 
	double thickness_in_mm, char*substrate_edge_block, SubstrateParameters*sub, RefractionParameters*subsurface); 
int load_mirror_material_parameters(char*mirror_material_name, double*data);
int set_mirror_material_parameters(char*mirror_material_name, double*mirror_material_spec, double mirror_m, ReflectionParameters*mir, RefractionParameters*subsurface);
int load_absorber_material_parameters(char*substrate_material_name, double*data);
int set_absorber_material_parameters(char*absorber_material_name, double absorber_L_abs, double absorber_L_inc, double absorber_thickness_in_micron, AbsorptionParameters*abs);
void set_process_parameters(int is_tracking, Supermirror*sm, SupermirrorProcess *proc);
void set_location(SimState *state, Supermirror*sm);
void set_event(SimState *state, Supermirror*sm, int event_code); 

/*******************************/
/* Ray-Tracing Tools functions */
/*******************************/

void sm_initialise_state(SimState*state);

double sm_calc_dRdq(double q, double Qc, double alpha, double m, double W, double beta); 

//Reflectivity at substrate surfaces
double sm_calc_Rs (RefractionParameters*subsurface, double vn_len);
//refraction going through substrate surface
Coords sm_get_refracted_v (RefractionParameters*subsurface, Coords v_in, Coords fn, int going_inward_or_outward_of_sm);
Coords sm_get_refracted_v_from_SLD (int has_refra, double SLD_from, double SLD_to, Coords v_in, Coords fn, int*total_reflection);
//calculate Rm, Rs, v-inward/outward at mirror and substrate surfaces
void sm_calc_surface_parameters(SimState*state, Supermirror*sm, int ignore_or_keep_reflection);

//reflection & transmission at mirrors
int sm_reflect_or_transmit_at_mirror (SimState*state, Supermirror*sm, int going_inward_or_outward_of_sm, int ignore_or_keep_reflection); 

//reflection & transmission at substrate surface
int sm_reflect_or_transmit_at_substrate_surface (SimState*state, Supermirror*sm, int going_inward_or_outward_of_sm, int ignore_or_keep_reflection);

//attenuation and transmission at absorbers and at substrate
double sm_get_L_attn_abs_at_plane (AbsorptionParameters*abs, double v_len);
void sm_get_prop_abs_at_plane (AbsorptionParameters*abs, double v_len, double vn_len, double*L_attn_abs_at_plane, double*t_prop_abs_at_plane, double*T_prop_abs_at_plane); 
int sm_transmit_through_absorber_at_plane (SimState*state, Supermirror*sm);

double sm_get_L_attn_sub (SubstrateParameters*sub, double v_len);
int sm_transmit_through_substrate (SimState*state, Supermirror*sm); 


//internal reflection
void sm_set_internal_reflection_parameters (SimState*state, Supermirror*sm);
int sm_internal_reflection_w (SimState*state, int n, double*w_out);

/************************/
/* Trajectory functions */
/************************/

int sm_external_intersect(SimState *state, Supermirror *sm); 
int sm_internal_intersect(SimState *state, Supermirror *sm); 
int sm_internal_reflections(SimState *state, Supermirror *sm); 

/***************************/
/* General Tools functions */
/***************************/

/********************************************************************************************************/
/* 	FILE *sm_open_file(	char  *path_in, char *filename, char *mode,				*/
/*						char **path_out, int *file_location_option)	        */
/*													*/
/*     Search for a file in user workspace and a number of McStas directories, open file if found       */
/*     return opened file handle or NULL								*/
/*     file_location_option's value (not pointer) = -1 if all options are exhausted and file not found	*/
/*                                                                                               	*/
/* 	HOW TO USE 											*/
/*		path_in, filename, mode either set or enter as strings in function call. 	       	*/
/* 		if not provided, path_in can be 0.							*/
/* 		int file_location_option=0;								*/
/*		char *path_out=NULL;								        */
/* 		FILE *fp;										*/
/* 		while (!(fp=sm_open_file(path_in, filename, mode, &path_out, &file_location_option)) {	*/
/* 			if (file_location_option == -1) {					       	*/
/* 				//failed to open file						       	*/
/* 				break;									*/
/* 			}										*/
/* 			//succeed in opening file						       	*/
/* 			...									       	*/
/* 		}											*/
/* 												      	*/
/* 		At a minimum, sm_open_file(0, filename, mode, 0, &file_location_option)			*/
/* 													*/
/* 	INPUT												*/
/* 		filename:  	file name, must be provided					       	*/
/* 		mode: 		"r", "w", "a" or any valid fopen mode, must be provided		       	*/
/* 		path_in: 	directory where the file may be, optional 0=not use			*/
/* 												        */
/* 	OUTPUT												*/
/* 		path_out:	returns full path where file is found, optional 0=not use	       	*/
/*					char *path_out=NULL; 						*/
/* 					if used, must initialise as above 			       	*/
/* 					must not be static, i.e., char path_out[256] will crash	       	*/
/* 			  if memory is already allocated, it will be freed and replaced with full path 	*/
/* 	I/O iterative										        */
/*		file_location_option: keep track of the option to find file	                   	*/
/* 					int file_location_option=0; 		                        */
/* 					if used, must initialise as above 				*/
/* 												       	*/
/* Function modified from Open_file in read_table-lib.c							*/
/********************************************************************************************************/

int sm_form_fullpath(char *path, char *filename, char **fullpath) {
	
	//check filename
	char *fname = NULL;
	if (validate_filename(filename,&fname) == 0) {
		//invalid filename
		free(fname); fname = NULL;
		return 0;
	}
	
	//filename is valid, there will be output to fullpath
	if (*fullpath) free(*fullpath);
	*fullpath = (char*)calloc(PATH_MAX, sizeof(char));
	//check path
	char *lc=NULL;
	int path_length = trim_space_from_both_ends(path, &lc);
	if (path_length > 0) {
		while (lc[path_length-1] == MC_PATHSEP_C && path_length > 0) {
			--path_length;
		}
		lc[path_length] = '\0';
	}
	if (path_length > 0) {
		snprintf(*fullpath, PATH_MAX, "%s%c%s", lc, MC_PATHSEP_C, fname);
	}
	else {
		snprintf(*fullpath, PATH_MAX, "%s", fname);
	}
	free(lc); lc=NULL; 
	free(fname); fname=NULL;
	return 1;
}

FILE *sm_open_filepath(char *path, char *filename, char *mode, char **fullpath) {
	if (!filename || !mode) {
		return NULL;
    }
	
	char *filepath = NULL;
	if (!sm_form_fullpath(path, filename, &filepath)) {
		free(filepath); filepath = NULL;
		return NULL;
	}

	FILE *fp = fopen(filepath, mode);
	if (fp) {
		#ifdef DEBUG_sm_open_file
		printf("try fullpath=%s --- found\n", filepath);
		#endif
		
		if (fullpath) {
			if (*fullpath) free(*fullpath);
			*fullpath = filepath;
			filepath = NULL;
		}
	}
	
	if(filepath) {
		free(filepath); filepath=NULL;
	}
	return fp;
}

void sm_transfer_text_reference(char **in, char**out) {
	//if out exist, transfer in to out.
	//*in will either get its pointer transferred or simplet freed, and become NULL. 
	if (in) {
		if (out) {
			//transfer
			if (*out) free(*out);
			*out = *in;
			*in=NULL;
		}
		else {
			//simply delete in
			if (*in) free(*in); 
			*in=NULL;
		}
	}
}

FILE *sm_open_file(	char *path_in, char *filename, char *mode, char **path_out, int *file_location_option) {

	if (!file_location_option) return NULL;
	if (*file_location_option < 0) return NULL;
	
	if (validate_filename(filename,0) == 0) {
		//invalid filename
		return NULL;
	}
	
	FILE *fp = NULL;
	char *fullpath = NULL;
	char dir[PATH_MAX];
	
	// search in current or full path
	switch(*file_location_option) {
		case 0: 
			#ifdef DEBUG_sm_open_file
			printf("sm_open_file: *file_location_option=%d ", *file_location_option);
			#endif
			
			++(*file_location_option);
			// search in user supplied path_in
			fp = sm_open_filepath(path_in, filename, mode, &fullpath);
			if (fp) {

				#ifdef DEBUG_sm_open_file
				printf("find \"%s\"", fullpath);
				#endif

				sm_transfer_text_reference(&fullpath, path_out);
				return fp;
			}
			
			free(fullpath); 
			fullpath=NULL;
			/* FALLTHRU */
		case 1:
			#ifdef DEBUG_sm_open_file
			printf("sm_open_file: *file_location_option=%d ", *file_location_option);
			#endif
			
			++(*file_location_option);
			// search in instrument source location
			if (instrument_source[0] != '\0') {
				fp = sm_open_filepath(instrument_source, filename, mode, &fullpath);
				if (fp) {

					#ifdef DEBUG_sm_open_file
					printf("find \"%s\"", fullpath);
					#endif
					
					sm_transfer_text_reference(&fullpath, path_out);
					return fp;
				}
			}
			
			free(fullpath); 
			fullpath=NULL;
			/* FALLTHRU */
		case 2: 
			#ifdef DEBUG_sm_open_file
			printf("sm_open_file: *file_location_option=%d ", *file_location_option);
			#endif
			
			++(*file_location_option);
			// search in PWD instrument executable location
			if (instrument_exe[0] != '\0') {
				fp = sm_open_filepath(instrument_exe, filename, mode, &fullpath);
				if (fp) {

					#ifdef DEBUG_sm_open_file
					printf("find \"%s\"", fullpath);
					#endif

					sm_transfer_text_reference(&fullpath, path_out);
					return fp;
				}
			}

			free(fullpath); 
			fullpath=NULL;
			/* FALLTHRU */
		case 3: 
			#ifdef DEBUG_sm_open_file
			printf("sm_open_file: file_location_option=%d ", *file_location_option);
			#endif
			
			++(*file_location_option);
			// search in HOME or . 
			snprintf(dir, PATH_MAX, "%s", (getenv("HOME") ? getenv("HOME") : "."));
			fp = sm_open_filepath(dir, filename, mode, &fullpath);
			if (fp) {

				#ifdef DEBUG_sm_open_file
				printf("find \"%s\"", fullpath);
				#endif

				sm_transfer_text_reference(&fullpath, path_out);
				return fp;
			}

			free(fullpath); 
			fullpath=NULL;
			/* FALLTHRU */
		case 4: 
			#ifdef DEBUG_sm_open_file
			printf("sm_open_file: *file_location_option=%d ", *file_location_option);
			#endif
			
			++(*file_location_option);
			// search in MCSTAS/data 
			snprintf(dir, PATH_MAX, "%s%c%s", 
					(getenv(FLAVOR_UPPER) ? getenv(FLAVOR_UPPER) : MCSTAS), 
					MC_PATHSEP_C, 
					"data");
			fp = sm_open_filepath(dir, filename, mode, &fullpath);
			if (fp) {

				#ifdef DEBUG_sm_open_file
				printf("find \"%s\"", fullpath);
				#endif

				sm_transfer_text_reference(&fullpath, path_out);
				return fp;
			}

			free(fullpath); 
			fullpath=NULL;
			/* FALLTHRU */
		case 5: 
			#ifdef DEBUG_sm_open_file
			printf("sm_open_file: *file_location_option=%d ", *file_location_option);
			#endif
			
			++(*file_location_option);
			// search in MCSTAS/contrib 
			snprintf(dir, PATH_MAX, "%s%c%s", 
					(getenv(FLAVOR_UPPER) ? getenv(FLAVOR_UPPER) : MCSTAS), 
					MC_PATHSEP_C, 
					"contrib");
			fp = sm_open_filepath(dir, filename, mode, &fullpath);
			if (fp) {

				#ifdef DEBUG_sm_open_file
				printf("find \"%s\"", fullpath);
				#endif

				sm_transfer_text_reference(&fullpath, path_out);
				return fp;
			}

			free(fullpath); 
			fullpath=NULL;
			/* FALLTHRU */
		case 6: 
			#ifdef DEBUG_sm_open_file
			printf("sm_open_file: *file_location_option=%d ", *file_location_option);
			#endif
			
			++(*file_location_option);
			// search in MVCSTAS/share 
			snprintf(dir, PATH_MAX, "%s%c%s", 
					(getenv(FLAVOR_UPPER) ? getenv(FLAVOR_UPPER) : MCSTAS), 
					MC_PATHSEP_C, 
					"share");
			fp = sm_open_filepath(dir, filename, mode, &fullpath);
			if (fp) {

				#ifdef DEBUG_sm_open_file
				printf("find \"%s\"", fullpath);
				#endif

				sm_transfer_text_reference(&fullpath, path_out);
				return fp;
			}
			
			free(fullpath); 
			fullpath=NULL;
			/* FALLTHRU */
		default: 
			*file_location_option = -1;
			fprintf(stderr, "sm_Error: Could not open input file '%s' (sm_open_file)\n", filename);
			#ifdef DEBUG_sm_open_file
			printf("sm_Error: Could not open input file '%s' (sm_open_file)\n", filename);
			#endif
			return NULL;
	}

} // end sm_open_file 


// Helper function to calculate factorials using the gamma function from math.h
static double factorial(int n) {
    return tgamma(n + 1);
}

/*****************************/
/* Debugging print functions */
/*****************************/
char* set_supermirror_flat_prefix(int number_of_tabs) {
    #if SM_DEBUG_ENABLED
    supermirror_flat_i_prefix = number_of_tabs; 
    supermirror_flat_s_prefix[number_of_tabs]=0;
    for (; number_of_tabs>0; number_of_tabs--) {
        supermirror_flat_s_prefix[number_of_tabs-1]='\t';
    }
    return supermirror_flat_s_prefix;
    #else
    return NULL;
    #endif
}
char* supermirror_flat_inc_prefix() {
	#if SM_DEBUG_ENABLED
	supermirror_flat_s_prefix[supermirror_flat_i_prefix]='\t';
	++supermirror_flat_i_prefix;
	supermirror_flat_s_prefix[supermirror_flat_i_prefix]=0;
	return supermirror_flat_s_prefix;
    #else
    return NULL;
    #endif
}
char* supermirror_flat_dec_prefix() {
	#if SM_DEBUG_ENABLED
	if (supermirror_flat_i_prefix == 0) return supermirror_flat_s_prefix;
	--supermirror_flat_i_prefix;
	supermirror_flat_s_prefix[supermirror_flat_i_prefix]=0;
	return supermirror_flat_s_prefix;
    #else
    return NULL;
    #endif
}
void sm_print_error(SimState*state, Supermirror *sm, char*topic, char*error_message, int outcome) {

	#if SM_DEBUG_ENABLED
	#ifdef USE_MPI
	//Only print mpi root node's state
	if (mpi_node_rank != mpi_node_root) 
		return;
	#endif
	
	char header[CHAR_BUF_LENGTH];
	header[CHAR_BUF_LENGTH-1]='\0';
	switch(outcome) {
		case sm_Error: //something's wrong
		{
			set_event(state, sm, sm_Error);
			
			#if defined(NEUTRON_HISTORY_LIB)
			if ((sm->proc).is_tracking) {
				#if defined(DEBUG_sm_print_error)
				printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
				#endif
				
				neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
			}
			#endif
				
			snprintf(header, CHAR_BUF_LENGTH-1, "%s%s: ERROR. Return sm_Error.", supermirror_flat_s_prefix, topic);
			printf("%s\n", header);
			if (strlen(error_message) > 0) {
				printf("%s\n", error_message);
			}
			sm_print_state (header, state, sm);

			break; 
		}
		default: 
		{
			snprintf(header, CHAR_BUF_LENGTH-1, "%s%s: ERROR outcome=%d is out of range. Return sm_Error.", supermirror_flat_s_prefix, topic, outcome);
			sm_print_state (header, state, sm);
			printf("%s \n", header);

			break; 
		}
	}
	#endif // SM_DEBUG_ENABLED

}
void sm_print_state(char*subheader, SimState*state, Supermirror*sm) { 

	#if SM_DEBUG_ENABLED
	#ifdef USE_MPI
	//Only print mpi root node's state
	if (mpi_node_rank != mpi_node_root) 
		return;
	#endif
	
	int i;

	printf("%s sm_print_state: %s\n", supermirror_flat_s_prefix, subheader);
	printf("%s ray_count=%d\n", supermirror_flat_s_prefix, state->ray_count);
	supermirror_flat_inc_prefix();
	
	printf("%s neutron state parameters\n", supermirror_flat_s_prefix);
	supermirror_flat_inc_prefix();
		if (state->plane==I_INDETERMINED) {
			printf("%s location/event=indetermined\n", supermirror_flat_s_prefix);
		}
		else {
			printf("%s location/event=%s/%s\n", supermirror_flat_s_prefix, 
					state->location, state->event);
		}
		printf("%s w, ws+,ws-,ws = %5e, (% 10.4f,% 10.4f),% 10.4f\n", supermirror_flat_s_prefix,
				state->w, state->ws[0], state->ws[1], state->ws[0]+state->ws[1]); 
		printf("%s t,p,v:|v|,s3-dot-fa:s:s2 = % 7.4f,(% 7.4f,% 7.4f,% 7.4f),(% 7.4f,% 7.4f,% 7.4f):% 7.4f,(% 7.4f,% 7.4f,% 7.4f)dot(% 7.4f,% 7.4f,% 7.4f):% 7.4f:(% 7.4f,% 7.4f)\n", supermirror_flat_s_prefix,
				state->t, state->p.x, state->p.y, state->p.z, state->v.x, state->v.y, state->v.z, coords_len(state->v), 
				state->s.x, state->s.y, state->s.z, ((sm->co).fa).x, ((sm->co).fa).y, ((sm->co).fa).z, 
				coords_sp((sm->co).fa, state->s), (1+coords_sp((sm->co).fa, state->s))/2, (1-coords_sp((sm->co).fa, state->s))/2);
	supermirror_flat_dec_prefix();

	printf("%s intersect parameters\n", supermirror_flat_s_prefix);
	supermirror_flat_inc_prefix();
		printf("%s n_mirror_intersected=%d\n", supermirror_flat_s_prefix, state->n_mirror_intersect);
		if (state->plane==I_INDETERMINED) {
			printf(	"%s side =indetermined\n"
					"%s plane=indetermined\n"
					"%s layer=indetermined\n", 
					supermirror_flat_s_prefix, supermirror_flat_s_prefix, supermirror_flat_s_prefix);
		}
		else {
			printf(	"%s side =%s(%d)\n"
					"%s plane=%s(%d)\n"
					"%s layer=%s(%d)\n",  
					supermirror_flat_s_prefix, ((sm->proc).side)[state->side], state->side, 
					supermirror_flat_s_prefix, ((sm->proc).plane)[state->plane], state->plane, 
					supermirror_flat_s_prefix, ((sm->proc).layer)[state->layer], state->layer);
		}
		if (state->fn.x == F_INDETERMINED || state->fn.x == D_INDETERMINED)
			printf("%s fn = indetermined\n", supermirror_flat_s_prefix);
		else
			printf("%s fn = (% 7.4f,% 7.4f,% 7.4f)\n", supermirror_flat_s_prefix,
					state->fn.x, state->fn.y, state->fn.z); 
		if (state->last_time == F_INDETERMINED || state->last_time == D_INDETERMINED)
			printf("%s last t,p=indetermined\n", supermirror_flat_s_prefix);
		else
			printf("%s last t,p=% 7.4f,(% 7.4f,% 7.4f,% 7.4f)\n", supermirror_flat_s_prefix, state->last_time, state->last_point.x, state->last_point.y, state->last_point.z);
	supermirror_flat_dec_prefix();

	printf("%s parameters indexing on plane number\n", supermirror_flat_s_prefix);
	supermirror_flat_inc_prefix();
		if (state->set_surface_parameters == 0) {
			printf("%s v_in_sub_outward_at_plane, v_in_sub_outward_len_at_plane, vn_in_sub_outward_len_at_plane [0,1] = indetermined\n", supermirror_flat_s_prefix);
			printf("%s v_in_sub_inward_at_plane, v_in_sub_inward_len_at_plane, vn_in_sub_inward_len_at_plane [0,1]  = indetermined\n", supermirror_flat_s_prefix);
			printf("%s Rs_vac_to_sub_at_plane[0,1] = indetermined\n", supermirror_flat_s_prefix);
			printf("%s Rs_sub_to_vac_at_plane[0,1]  = indetermined\n", supermirror_flat_s_prefix);
			printf("%s v_in_vac_outward_at_plane[0,1] = indetermined\n", supermirror_flat_s_prefix);
			printf("%s v_in_vac_inward_at_plane[0,1]  = indetermined\n", supermirror_flat_s_prefix);
			printf("%s v_in_vac_len_at_plane[0,1] = indetermined, vn_in_vac_len_at_plane[0,1] = indetermined\n", supermirror_flat_s_prefix);
			printf("%s Rm0+,Rm0-, Rm1+,Rm1- = indetermined\n", supermirror_flat_s_prefix);
		}
		else {
			for (i=0; i<2; i++) {
				printf("%s plane=%d\n", supermirror_flat_s_prefix, i);
				supermirror_flat_inc_prefix();
				printf(	"%s v_in_sub_outward_at_plane:v,vn = (% 7.4f,% 7.4f,% 7.4f):% 7.4f,% 7.4f\n",
						supermirror_flat_s_prefix,
						(state->v_in_sub_outward_at_plane[i]).x, (state->v_in_sub_outward_at_plane[i]).y, (state->v_in_sub_outward_at_plane[i]).z,
						state->v_in_sub_outward_len_at_plane[i], state->vn_in_sub_outward_len_at_plane[i]);
				printf(	"%s v_in_sub_inward_at_plane:v,vn  = (% 7.4f,% 7.4f,% 7.4f):% 7.4f,% 7.4f\n",
						supermirror_flat_s_prefix,
						(state->v_in_sub_inward_at_plane[i]).x, (state->v_in_sub_inward_at_plane[i]).y, (state->v_in_sub_inward_at_plane[i]).z, 
						state->v_in_sub_inward_len_at_plane[i], state->vn_in_sub_inward_len_at_plane[i]);

				printf("%s Rs_vac_to_sub_at_plane = % 7.4f\n", supermirror_flat_s_prefix, 
						state->Rs_vac_to_sub_at_plane[i]);
				printf("%s Rs_sub_to_vac_at_plane  = % 7.4f\n", supermirror_flat_s_prefix, 
						state->Rs_sub_to_vac_at_plane[i]);
						
				printf("%s v_in_vac_outward_at_plane = (% 7.4f,% 7.4f,% 7.4f):% 7.4f,% 7.4f\n", supermirror_flat_s_prefix,
						(state->v_in_vac_outward_at_plane[i]).x, (state->v_in_vac_outward_at_plane[i]).y, (state->v_in_vac_outward_at_plane[i]).z, 
						coords_len(state->v_in_vac_outward_at_plane[i]), fabs(coords_sp(state->v_in_vac_outward_at_plane[i], state->fn))); 
				printf("%s v_in_vac_inward_at_plane  = (% 7.4f,% 7.4f,% 7.4f):% 7.4f,% 7.4f\n", supermirror_flat_s_prefix,
						(state->v_in_vac_inward_at_plane[i]).x, (state->v_in_vac_inward_at_plane[i]).y, (state->v_in_vac_inward_at_plane[i]).z, 
						coords_len(state->v_in_vac_inward_at_plane[i]), fabs(coords_sp(state->v_in_vac_inward_at_plane[i], state->fn))); 
				printf("%s v_in_vac_len_at_plane,vn_in_vac_len_at_plane = % 7.4f,% 7.4f\n", supermirror_flat_s_prefix,
						state->v_in_vac_len_at_plane[i],state->vn_in_vac_len_at_plane[i]);

				printf("%s (Rm+,Rm-) = (% 7.4f,% 7.4f)\n", supermirror_flat_s_prefix, 
						state->Rm_vac_to_mir_at_plane[i][0], state->Rm_vac_to_mir_at_plane[i][1]);
				supermirror_flat_dec_prefix();
			}
		}

		if (state->L_attn_abs_at_plane[0] == F_INDETERMINED || state->L_attn_abs_at_plane[0] == D_INDETERMINED) 
			printf("%s L_attn_abs_at_plane[0] = indetermined, ", supermirror_flat_s_prefix);
		else
			printf("%s L_attn_abs_at_plane[0] = % 10.4f, ", supermirror_flat_s_prefix, state->L_attn_abs_at_plane[0]);
		if (state->L_attn_abs_at_plane[1] == F_INDETERMINED || state->L_attn_abs_at_plane[1] == D_INDETERMINED) 
			printf("L_attn_abs_at_plane[1] = indetermined\n");
		else
			printf("L_attn_abs_at_plane[1] = % 10.4f\n", state->L_attn_abs_at_plane[1]);
		if (state->t_prop_abs_at_plane[0] == F_INDETERMINED || state->t_prop_abs_at_plane[0] == D_INDETERMINED) 
			printf("%s t_prop_abs_at_plane[0] = indetermined, ", supermirror_flat_s_prefix);
		else
			printf("%s t_prop_abs_at_plane[0] = % 10.4f, ", supermirror_flat_s_prefix, state->t_prop_abs_at_plane[0]);
		if (state->t_prop_abs_at_plane[1] == F_INDETERMINED || state->t_prop_abs_at_plane[1] == D_INDETERMINED) 
			printf("t_prop_abs_at_plane[1] = indetermined\n");
		else
			printf("t_prop_abs_at_plane[1] = % 10.4f\n", state->t_prop_abs_at_plane[1]);
		if (state->T_prop_abs_at_plane[0] == F_INDETERMINED || state->T_prop_abs_at_plane[0] == D_INDETERMINED) 
			printf("%s T_prop_abs_at_plane[0] = indetermined, ", supermirror_flat_s_prefix);
		else
			printf("%s T_prop_abs_at_plane[0] = % 10.4f, ", supermirror_flat_s_prefix, state->T_prop_abs_at_plane[0]);
		if (state->T_prop_abs_at_plane[1] == F_INDETERMINED || state->T_prop_abs_at_plane[1] == D_INDETERMINED) 
			printf("T_prop_abs_at_plane[1] = indetermined\n");
		else
			printf("T_prop_abs_at_plane[1] = % 10.4f\n", state->T_prop_abs_at_plane[1]);

		if (state->L_attn_sub == F_INDETERMINED || state->L_attn_sub == D_INDETERMINED) 
			printf("%s L_attn_sub = indetermined\n", supermirror_flat_s_prefix);
		else
			printf("%s L_attn_sub = % 10.4f\n", supermirror_flat_s_prefix, state->L_attn_sub);
		if (state->t_prop_sub == F_INDETERMINED || state->t_prop_sub == D_INDETERMINED) 
			printf("%s t_prop_sub = indetermined\n", supermirror_flat_s_prefix);
		else
			printf("%s t_prop_sub = % 10.4f\n", supermirror_flat_s_prefix, state->t_prop_sub);
		if (state->T_prop_sub == F_INDETERMINED || state->T_prop_sub == D_INDETERMINED) 
			printf("%s T_prop_sub = indetermined\n", supermirror_flat_s_prefix);
		else
			printf("%s T_prop_sub = % 10.4f\n", supermirror_flat_s_prefix, state->T_prop_sub);
	supermirror_flat_dec_prefix();
	
	supermirror_flat_dec_prefix();
	#endif
	
}
void sm_print_intersect(char*event, int num_intersect, double*dtime, Coords*dpoint, double*time, Coords*point, int*plane, int*type) {

	#if SM_DEBUG_ENABLED
	if (num_intersect > 0) {
		printf("%s\tsm_print_intersect: %s\n", supermirror_flat_s_prefix, event);
		for (int i = 0; i < num_intersect; i++) {
			printf("%s\tn.intersect=%d/%d", supermirror_flat_s_prefix, i, num_intersect);
			if (plane) printf(", plane=%d ", plane[i]);
			if (dtime) printf(", dt=% 7.4f ", dtime[i]);
			if (dpoint) printf(", dp=(% 7.4f,% 7.4f,% 7.4f) ", (dpoint[i]).x, (dpoint[i]).y, (dpoint[i]).z);
			if (time) printf(", t=% 7.4f ", time[i]);
			if (point) printf(", p=(% 7.4f,% 7.4f,% 7.4f) ", (point[i]).x, (point[i]).y, (point[i]).z);
			if (type) printf(", type=%d ", type[i]); 
			printf("\n"); 
		}
	}
	#endif
}
void sm_print_refl(char *event, SimState*state, Supermirror*sm) {

	#if SM_DEBUG_ENABLED
	#ifdef USE_MPI
	//Only save mpi root node's state
	if (mpi_node_rank != mpi_node_root) 
		return;
	#endif

	printf("%s%s mirror=%d, Rm_vac_to_mir_at_plane+:%s=% 10.4f Rm_vac_to_mir_at_plane-:%s=% 10.4f, subSLD:%s=%5e\n", 
			supermirror_flat_s_prefix, event,
			state->plane, 
			((sm->mat).mir[state->plane][0]).name, state->Rm_vac_to_mir_at_plane[state->plane][0],
			((sm->mat).mir[state->plane][1]).name, state->Rm_vac_to_mir_at_plane[state->plane][1],
			(sm->mat).sub.name, (sm->mat).sub.SLD);

	#endif
}
#if defined(DEBUG_REF_LIB_SAVE) && SM_DEBUG_ENABLED
void sm_save_state(char*event, SimState*state, Supermirror*sm) { 
	#ifdef USE_MPI
	//Only save mpi root node's state
	if (mpi_node_rank != mpi_node_root) 
		return;
	#endif

	FILE *fpp = fopen("trace.csv","a+");
	if (fpp != 0) {
		
		int i;
		
		fprintf(fpp,"%s,",event);
		
		fprintf(fpp,"%20e,, %20e,, %20e,%20e,%20e,, %20e,%20e,%20e,%20e,%20e,, %20e,%20e,%20e,, ",
			state->w,  
			state->t, 
			state->p.x, state->p.y, state->p.z, 
			state->v.x, state->v.y, state->v.z, state->v_len, state->vn_len,
			state->ws[0], state->ws[1], state->ws[0]+state->ws[1]);

		fprintf(fpp,"%20e,%20e,%20e,%20e,, %20e,%20e,%20e,, %20e,%20e,%20e,,", 
			state->s.x, state->s.y, state->s.z, coords_len(state->s), 
			((sm->co).fa).x, ((sm->co).fa).y, ((sm->co).fa).z,
			coords_sp((sm->co).fa, state->s), (1+coords_sp((sm->co).fa, state->s))/2, (1-coords_sp((sm->co).fa, state->s))/2);

		if (state->plane!=I_INDETERMINED) {
			fprintf(fpp,"%d,%d,,%s,%s,,%s,%d,,%s,%d,,%s,%d,,%20e,%20e,%20e,,", 
				state->n_surface_intersect, state->n_mirror_intersect, 
				state->location, state->event, 
				(sm->proc).side[state->side], state->side, 
				(sm->proc).plane[state->plane], state->plane, 
				(sm->proc).layer[state->layer], state->layer, 
				state->fn.x, state->fn.y, state->fn.z);
		}
		else { 
			fprintf(fpp,",,,,,,,,,,,,,,,,,,,");
		}

		fprintf(fpp,",");
		if ((state->v_in_vac_inward_at_plane[0]).x == F_INDETERMINED || (state->v_in_vac_inward_at_plane[0]).x == D_INDETERMINED)
			fprintf(fpp,",,,,,,,,");
		else
			fprintf(fpp,"% 7.4f,% 7.4f,% 7.4f,,% 7.4f,% 7.4f,% 7.4f,,", 
					(state->v_in_vac_inward_at_plane[0]).x, (state->v_in_vac_inward_at_plane[0]).y, (state->v_in_vac_inward_at_plane[0]).z, 
					(state->v_in_vac_inward_at_plane[1]).x, (state->v_in_vac_inward_at_plane[1]).y, (state->v_in_vac_inward_at_plane[1]).z); 
		if ((state->v_in_vac_outward_at_plane[0]).x == F_INDETERMINED || (state->v_in_vac_outward_at_plane[0]).x == D_INDETERMINED)
			fprintf(fpp,",,,,,,,,");
		else
			fprintf(fpp,"% 7.4f,% 7.4f,% 7.4f,,% 7.4f,% 7.4f,% 7.4f,,", 
					(state->v_in_vac_outward_at_plane[0]).x, (state->v_in_vac_outward_at_plane[0]).y, (state->v_in_vac_outward_at_plane[0]).z, 
					(state->v_in_vac_outward_at_plane[1]).x, (state->v_in_vac_outward_at_plane[1]).y, (state->v_in_vac_outward_at_plane[1]).z); 
		if ((state->v_in_sub_inward_at_plane[0]).x == F_INDETERMINED || (state->v_in_sub_inward_at_plane[0]).x == D_INDETERMINED)
			fprintf(fpp,",,,,,,,,");
		else
			fprintf(fpp,"% 7.4f,% 7.4f,% 7.4f,,% 7.4f,% 7.4f,% 7.4f,,", 
					(state->v_in_sub_inward_at_plane[0]).x, (state->v_in_sub_inward_at_plane[0]).y, (state->v_in_sub_inward_at_plane[0]).z, 
					(state->v_in_sub_inward_at_plane[1]).x, (state->v_in_sub_inward_at_plane[1]).y, (state->v_in_sub_inward_at_plane[1]).z); 
		if ((state->v_in_sub_outward_at_plane[0]).x == F_INDETERMINED || (state->v_in_sub_outward_at_plane[0]).x == D_INDETERMINED)
			fprintf(fpp,",,,,,,,,");
		else
			fprintf(fpp,"% 7.4f,% 7.4f,% 7.4f,,% 7.4f,% 7.4f,% 7.4f,,", 
					(state->v_in_sub_outward_at_plane[0]).x, (state->v_in_sub_outward_at_plane[0]).y, (state->v_in_sub_outward_at_plane[0]).z, 
					(state->v_in_sub_outward_at_plane[1]).x, (state->v_in_sub_outward_at_plane[1]).y, (state->v_in_sub_outward_at_plane[1]).z); 
		if (state->Rm_vac_to_mir_at_plane[0][0] == F_INDETERMINED || state->Rm_vac_to_mir_at_plane[0][0] == D_INDETERMINED) 
			fprintf(fpp,",,,");
		else
			fprintf(fpp,"% 10.4f,% 10.4f,,", state->Rm_vac_to_mir_at_plane[0][0], state->Rm_vac_to_mir_at_plane[0][1]);
		if (state->Rm_vac_to_mir_at_plane[1][0] == F_INDETERMINED || state->Rm_vac_to_mir_at_plane[1][0] == D_INDETERMINED) 
			fprintf(fpp,",,,");
		else
			fprintf(fpp,"% 10.4f,% 10.4f,,", state->Rm_vac_to_mir_at_plane[1][0], state->Rm_vac_to_mir_at_plane[1][1]);
		if (state->L_attn_abs_at_plane[0] == F_INDETERMINED || state->L_attn_abs_at_plane[0] == D_INDETERMINED) 
			fprintf(fpp,",");
		else
			fprintf(fpp,"% 10.4f,", state->L_attn_abs_at_plane[0]);
		if (state->L_attn_abs_at_plane[1] == F_INDETERMINED || state->L_attn_abs_at_plane[1] == D_INDETERMINED) 
			fprintf(fpp,",");
		else
			fprintf(fpp,"% 10.4f,", state->L_attn_abs_at_plane[1]);
		if (state->t_prop_abs_at_plane[0] == F_INDETERMINED || state->t_prop_abs_at_plane[0] == D_INDETERMINED) 
			fprintf(fpp,",");
		else
			fprintf(fpp,"% 10.4f,", state->t_prop_abs_at_plane[0]);
		if (state->t_prop_abs_at_plane[1] == F_INDETERMINED || state->t_prop_abs_at_plane[1] == D_INDETERMINED) 
			fprintf(fpp,",");
		else
			fprintf(fpp,"% 10.4f,", state->t_prop_abs_at_plane[1]);
		if (state->T_prop_abs_at_plane[0] == F_INDETERMINED || state->T_prop_abs_at_plane[0] == D_INDETERMINED) 
			fprintf(fpp,",");
		else
			fprintf(fpp,"% 10.4f,", state->T_prop_abs_at_plane[0]);
		if (state->T_prop_abs_at_plane[1] == F_INDETERMINED || state->T_prop_abs_at_plane[1] == D_INDETERMINED) 
			fprintf(fpp,",");
		else
			fprintf(fpp,"% 10.4f,,", state->T_prop_abs_at_plane[1]);
		
		if (state->Rs_vac_to_sub_at_plane[0] == F_INDETERMINED || state->Rs_vac_to_sub_at_plane[0] == D_INDETERMINED) 
			fprintf(fpp,",");
		else
			fprintf(fpp,"% 10.4f,", state->Rs_vac_to_sub_at_plane[0]);
		if (state->Rs_vac_to_sub_at_plane[1] == F_INDETERMINED || state->Rs_vac_to_sub_at_plane[1] == D_INDETERMINED) 
			fprintf(fpp,",");
		else
			fprintf(fpp,"% 10.4f,", state->Rs_vac_to_sub_at_plane[1]);
		if (state->L_attn_sub == F_INDETERMINED || state->L_attn_sub == D_INDETERMINED) 
			fprintf(fpp,",");
		else
			fprintf(fpp,"% 10.4f,", state->L_attn_sub);
		if (state->t_prop_sub == F_INDETERMINED || state->t_prop_sub == D_INDETERMINED) 
			fprintf(fpp,",");
		else
			fprintf(fpp,"% 10.4f,", state->t_prop_sub);
		if (state->T_prop_sub == F_INDETERMINED || state->T_prop_sub == D_INDETERMINED) 
			fprintf(fpp,",,");
		else
			fprintf(fpp,"% 10.4f,,", state->T_prop_sub);

		fclose(fpp);
	}
}
#endif

/*********************************/
/* Internal initialise functions */
/*********************************/

int set_supermirror_flat_geometry (

		double length, //m supermirror length projection along z-axis
		double thickness_in_mm, //mm
		Coords side_edge_1_normal, Coords side_edge_1_point, 
		Coords side_edge_2_normal, Coords side_edge_2_point, 
		char*initial_placement_at_origin,	//"TopFrontEdge","FrontSubstrateCentre","BottomFrontEdge"
		char*tilt_y_axis_location, 	//"TopFrontEdge","TopMirrorCentre","TopBackEdge"
									//"FrontSubstrateCentre","SubstrateCentre","BackSubstrateCentre", 
									//"BottomFrontEdge","BottomMirrorCentre","BottomBackEdge"
		double tilt_about_y_first_in_degree,  //first, tile about y_axis at selected location 
		Coords translation_second,  //second, translate reference point 
		double rot_about_z_third_in_degree, //third, rotate about global z-axis 
		Polyhedron*geo, CoordOp*co) 
{	
//	#define DEBUG_set_supermirror_flat_geometry
	#if defined(DEBUG_set_supermirror_flat_geometry)
	MPI_MASTER (
	printf(	"set_supermirror_flat_geometry (\n"
			"length=% 7.4f\n"
			"thickness_in_mm=% 7.4f\n"
			"side_edge_1_normal=(% 7.4f, % 7.4f, % 7.4f), side_edge_1_point=(% 7.4f, % 7.4f, % 7.4f)\n"
			"side_edge_2_normal=(% 7.4f, % 7.4f, % 7.4f), side_edge_2_point=(% 7.4f, % 7.4f, % 7.4f)\n"
			"initial_placement_at_origin=%s\n"
			"tilt_y_axis_location=%s\n"
			"tilt_about_y_first_in_degree=% 7.4f\n"
			"translation_second=(% 7.4f, % 7.4f, % 7.4f)\n"
			"rot_about_z_third_in_degree=% 7.4f)\n", 
			length, thickness_in_mm,
			side_edge_1_normal.x, side_edge_1_normal.y, side_edge_1_normal.z, 
			side_edge_1_point.x,  side_edge_1_point.y,  side_edge_1_point.z, 
			side_edge_2_normal.x, side_edge_2_normal.y, side_edge_2_normal.z, 
			side_edge_2_point.x,  side_edge_2_point.y,  side_edge_2_point.z, 
			initial_placement_at_origin, tilt_y_axis_location, tilt_about_y_first_in_degree, 
			translation_second.x, translation_second.y, translation_second.z, 
			rot_about_z_third_in_degree); 
	)	
	#endif

	if (geo == 0) {
		MPI_MASTER(printf("set_supermirror_flat_geometry: error, pointer to Polyhedron variable \"geo\" must not be NULL.\n");) 
		return 0;
	}
	if (co == 0) {
		MPI_MASTER(printf("set_supermirror_flat_geometry: error, pointer to CoordOp variable \"co\" must not be NULL.\n");)
		return 0;
	}
	
////////////////////////////////////////////////////////////////////////
//Follow-on coding: supermirror with no thickness, set as error for now
////////////////////////////////////////////////////////////////////////
	if (thickness_in_mm <= ZERO_THRESHOLD) {
		MPI_MASTER(printf("set_supermirror_flat_geometry: error, thickness_in_mm must have thickness.\n")); 
		return 0;
	}
	if (initial_placement_at_origin == 0) {
		MPI_MASTER(printf("set_supermirror_flat_geometry: error, pointer to initial_placement_at_origin name must not be NULL.\n")); 
		return 0;
	}
	if (tilt_y_axis_location == 0) {
		MPI_MASTER(printf("set_supermirror_flat_geometry: error, pointer to tilt_y_axis_location name must not be NULL.\n")); 
		return 0;
	}
	
	int i;
	char *lc = 0;
	
	Coords plane_normal[6], plane_point[6];
	plane_normal[0] = coords_set(1,0,0);
	plane_normal[1] = coords_set(-1,0,0);
	plane_normal[2] = coords_set(0,0,-1);
	plane_normal[3] = coords_set(0,0,1);
	plane_normal[4] = side_edge_1_normal; //+y side
	plane_normal[5] = side_edge_2_normal; //-y side
	for (i = 0; i < 6; i++) 
		coords_norm(&(plane_normal[i]));
	
	Coords fsc_wrt_origin; // front substrate-centre location w.r.t. device initial_placement_at_origin  

	if (to_lower_case(initial_placement_at_origin, &lc) == 0) {
		return 0;
	}
	if (strcmp(lc,"frontsubstratecentre") == 0 || strcmp(lc,"frontsubstratecenter") == 0 ) {
		plane_point[0] = coords_set( thickness_in_mm/1000/2, 0, 0);
		plane_point[1] = coords_set(-thickness_in_mm/1000/2, 0, 0);
		plane_point[2] = coords_set(0,0,0);
		plane_point[3] = coords_set(0,0,length);
		fsc_wrt_origin = coords_set(0, 0, 0); 
	}
	else if (strcmp(lc,"topfrontedgecentre") == 0 || strcmp(lc,"topfrontedgecenter") == 0) {
		plane_point[0] = coords_set(0,0,0);
		plane_point[1] = coords_set(-thickness_in_mm/1000, 0, 0);
		plane_point[2] = coords_set(0,0,0);
		plane_point[3] = coords_set(0,0,length);
		fsc_wrt_origin = coords_set(-thickness_in_mm/1000/2, 0, 0);
	}
	else if (strcmp(lc,"bottomfrontedgecentre") == 0 || strcmp(lc,"bottomfrontedgecenter") == 0) {
		plane_point[0] = coords_set(thickness_in_mm/1000, 0, 0);
		plane_point[1] = coords_set(0,0,0);
		plane_point[2] = coords_set(0,0,0);
		plane_point[3] = coords_set(0,0,length);
		fsc_wrt_origin = coords_set(thickness_in_mm/1000/2, 0, 0);
	}
	else if (strcmp(lc,"topsurfacecentre") == 0) {
		plane_point[0] = coords_set(0,0,0);
		plane_point[1] = coords_set(-thickness_in_mm/1000, 0, 0);
		plane_point[2] = coords_set(0,0,-length/2);
		plane_point[3] = coords_set(0,0,length/2);
		fsc_wrt_origin = coords_set(-thickness_in_mm/1000/2, 0, -length/2);
	}
	else if (strcmp(lc,"bottomsurfacecentre") == 0) {
		plane_point[0] = coords_set(thickness_in_mm/1000, 0, 0);
		plane_point[1] = coords_set(0,0,0);
		plane_point[2] = coords_set(0,0,-length/2);
		plane_point[3] = coords_set(0,0,length/2);
		fsc_wrt_origin = coords_set(thickness_in_mm/1000/2, 0, -length/2);
	}
	else {
		MPI_MASTER(printf("set_supermirror_flat_geometry: error initial_placement_at_origin=%s - "
							"must be \"FrontSubstrateCentre\", \"TopFrontEdgeCentre\" or \"BottomFrontEdgeCentre\" (not case-sensitive)\n", 
							initial_placement_at_origin);
		)
		if (lc != 0) {
			free(lc);
			lc = 0;
		}
		return 0;
	}
	if (lc != 0) {
		free(lc);
		lc = 0;
	}
	plane_point[4] = side_edge_1_point; //+y side
	plane_point[5] = side_edge_2_point; //-y side
		
	//normal vector should have length
	for (i = 0; i < 6; i++) {
		if (coords_len(plane_normal[i]) < ZERO_THRESHOLD) {
			MPI_MASTER(printf("set_supermirror_flat_geometry: ERROR plane %d normal vector magnitude too small, normal=(% 7.4f,% 7.4f,% 7.4f), point=(% 7.4f,% 7.4f,% 7.4f)\n", i, 
				plane_point[i].x, plane_point[i].y, plane_point[i].z, 
				plane_normal[i].x, plane_normal[i].y, plane_normal[i].z);) 
			return 0;
		}
	}
	
	#if defined (DEBUG_set_supermirror_flat_geometry)
	MPI_MASTER (
	printf("plane input to form_polyhedron.\n"); 
	for (i = 0; i < 6; i++) {
			printf("in: plane %d normal = (% 7.4f, % 7.4f, % 7.4f) point = (% 7.4f, % 7.4f, % 7.4f)\n", i, 
				plane_normal[i].x, plane_normal[i].y, plane_normal[i].z, 
				plane_point[i].x, plane_point[i].y, plane_point[i].z); 
	} 
	)	
	#endif

	i = form_polyhedron(6, plane_normal, plane_point, geo);
	if (i < 6) { 
		MPI_MASTER(printf("set_supermirror_flat_geometry: ERROR number of planes expected = 6, number of plane in polyhedron = %d\n", i);
		) 
		empty_polyhedron(geo);
		return 0;
	}
	
	#if defined(DEBUG_set_supermirror_flat_geometry)
	MPI_MASTER (
//	Polyhedron*geo_out = (Polyhedron*)geo;
	printf("geo plane after form_polyhedron, before rotY-trans-rotZ\n"); 
	for (i = 0; i < 6; i++) {
			printf("geo plane %d normal = (% 7.4f, % 7.4f, % 7.4f) point = (% 7.4f, % 7.4f, % 7.4f)\n", i, 
				(geo->fn[i]).x, (geo->fn[i]).y, (geo->fn[i]).z, 
				(geo->fp[i]).x, (geo->fp[i]).y, (geo->fp[i]).z); 
	}
	)	
	#endif
	
	Coords field_axis = coords_set(0,1,0); 

	#if defined(DEBUG_set_supermirror_flat_geometry)
	MPI_MASTER (printf("co field axis before rotY-rotZ = (% 7.4f, % 7.4f, % 7.4f)\n", 
		field_axis.x, field_axis.y, field_axis.z);) 
	#endif

	Coords tilt_y_axis_wrt_fsc; //tilt y_axis location w.r.t. device initial_placement_at_origin = tilt axis wrt fsc + fsc wrt initial_placement_at_origin
	to_lower_case(tilt_y_axis_location, &lc);
	if      (strcmp(lc,"topfrontedge") == 0) 			tilt_y_axis_wrt_fsc = coords_set( thickness_in_mm/1000/2, 0, 0       );
	else if (strcmp(lc,"fronttopedge") == 0) 			tilt_y_axis_wrt_fsc = coords_set( thickness_in_mm/1000/2, 0, 0       );
	else if (strcmp(lc,"frontsubstratecentre") == 0)	tilt_y_axis_wrt_fsc = coords_set( 0,                                0, 0       );
	else if (strcmp(lc,"frontsubstratecenter") == 0)	tilt_y_axis_wrt_fsc = coords_set( 0,                                0, 0       );
	else if (strcmp(lc,"substratefrontcentre") == 0)	tilt_y_axis_wrt_fsc = coords_set( 0,                                0, 0       );
	else if (strcmp(lc,"substratefrontcenter") == 0)	tilt_y_axis_wrt_fsc = coords_set( 0,                                0, 0       );
	else if (strcmp(lc,"substratecentrefront") == 0)	tilt_y_axis_wrt_fsc = coords_set( 0,                                0, 0       );
	else if (strcmp(lc,"substratecenterfront") == 0)	tilt_y_axis_wrt_fsc = coords_set( 0,                                0, 0       );
	else if (strcmp(lc,"bottomfrontedge") == 0) 		tilt_y_axis_wrt_fsc = coords_set(-thickness_in_mm/1000/2, 0, 0       );
	else if (strcmp(lc,"frontbottomedge") == 0) 		tilt_y_axis_wrt_fsc = coords_set(-thickness_in_mm/1000/2, 0, 0       );
	else if (strcmp(lc,"topmirrorcentre") == 0) 		tilt_y_axis_wrt_fsc = coords_set( thickness_in_mm/1000/2, 0, length/2);
	else if (strcmp(lc,"topmirrorcenter") == 0) 		tilt_y_axis_wrt_fsc = coords_set( thickness_in_mm/1000/2, 0, length/2);
	else if (strcmp(lc,"substratecentre") == 0)			tilt_y_axis_wrt_fsc = coords_set( 0,                                0, length/2);
	else if (strcmp(lc,"substratecenter") == 0)			tilt_y_axis_wrt_fsc = coords_set( 0,                                0, length/2);
	else if (strcmp(lc,"bottommirrorcentre") == 0) 		tilt_y_axis_wrt_fsc = coords_set(-thickness_in_mm/1000/2, 0, length/2);
	else if (strcmp(lc,"bottommirrorcenter") == 0) 		tilt_y_axis_wrt_fsc = coords_set(-thickness_in_mm/1000/2, 0, length/2);
	else if (strcmp(lc,"topbackedge") == 0) 			tilt_y_axis_wrt_fsc = coords_set( thickness_in_mm/1000/2, 0, length  );
	else if (strcmp(lc,"backtopedge") == 0) 			tilt_y_axis_wrt_fsc = coords_set( thickness_in_mm/1000/2, 0, length  );
	else if (strcmp(lc,"backsubstratecentre") == 0)		tilt_y_axis_wrt_fsc = coords_set( 0,                                0, length  );
	else if (strcmp(lc,"backsubstratecenter") == 0)		tilt_y_axis_wrt_fsc = coords_set( 0,                                0, length  );
	else if (strcmp(lc,"substratebackcentre") == 0)		tilt_y_axis_wrt_fsc = coords_set( 0,                                0, length  );
	else if (strcmp(lc,"substratebackcenter") == 0)		tilt_y_axis_wrt_fsc = coords_set( 0,                                0, length  );
	else if (strcmp(lc,"substratecentreback") == 0)		tilt_y_axis_wrt_fsc = coords_set( 0,                                0, length  );
	else if (strcmp(lc,"substratecenterback") == 0)		tilt_y_axis_wrt_fsc = coords_set( 0,                                0, length  );
	else if (strcmp(lc,"bottombackedge") == 0) 			tilt_y_axis_wrt_fsc = coords_set(-thickness_in_mm/1000/2, 0, length  );
	else if (strcmp(lc,"backbottomedge") == 0) 			tilt_y_axis_wrt_fsc = coords_set(-thickness_in_mm/1000/2, 0, length  );
	else {
		MPI_MASTER(printf(	"set_supermirror_flat_geometry: ERROR tilt_y_axis_location=\"%s\" must be one of the following\n"
					"                               \"TopFrontEdge\",\"TopMirrorCentre\",\"TopBackEdge\"\n"
					"                               \"FrontSubstrateCentre\",\"SubstrateCentre\",\"BackSubstrateCentre\"\n" 
					"                               \"BottomFrontEdge\",\"BottomMirrorCentre\",\"BottomBackEdge\" (case-insensitive)\n",lc
					);)
		if (lc != 0) {
			free(lc);
			lc = 0;
		}
		return 0;
	}
	if (lc != 0) {
		free(lc);
		lc = 0;
	}

//	//Keep for reference, code replaced by the polyhedron function calls below
//	
//	rot_set_rotation(co->ry,-tilt_about_y_first_in_degree*DEG2RAD,0,0);
//	co->tr = translation_second;
//	rot_set_rotation(co->rz,0,0,-rot_about_z_third_in_degree*DEG2RAD);
//	
//	for (i = 0; i < 6; i++) {
//		geo->fn[i] = rot_apply(co->ry, geo->fn[i]);
//		geo->fn[i] = rot_apply(co->rz, geo->fn[i]);
//		geo->fp[i] = rot_apply(co->ry, geo->fp[i]);
//		geo->fp[i] = coords_add(geo->fp[i], co->tr);
//		geo->fp[i] = rot_apply(co->rz, geo->fp[i]);
//	}

	co->ty = coords_add(tilt_y_axis_wrt_fsc, fsc_wrt_origin); //tilt y-axis location w.r.t. device initial_placement_at_origin = tilt axis wrt fsc + fsc wrt initial_placement_at_origin
	co->rty = coords_neg(co->ty);
	translate_polyhedron (geo, co->rty); 
	rotate_polyhedron_about_axis (geo, coords_set(0,1,0), tilt_about_y_first_in_degree, &(co->ry));
	translate_polyhedron (geo, co->ty); 
	translate_polyhedron (geo, translation_second); co->tr = translation_second;
	rotate_polyhedron_about_axis (geo, coords_set(0,0,1), rot_about_z_third_in_degree, &(co->rz));
	
	co->fa = rot_apply(co->ry, field_axis);
	co->fa = rot_apply(co->rz, co->fa);

	rot_transpose(co->ry, co->rry); 
	co->rtr = coords_neg(co->tr);
	rot_transpose(co->rz, co->rrz); 
	
	#if defined(DEBUG_set_supermirror_flat_geometry)
		MPI_MASTER (
			printf("co +y = (% 7.4f, % 7.4f, % 7.4f) rot+y = % 7.4f, % 7.4f, % 7.4f rot+z = (% 7.4f, % 7.4f, % 7.4f) +t = (% 7.4f, % 7.4f, % 7.4f) \n",  
				(co->ty).x, (co->ty).y, (co->ty).z, 
				co->ry[0][0], co->ry[0][1], co->ry[0][2], 
				co->rz[0][0], co->rz[0][1], co->rz[0][2],
				(co->tr).x, (co->tr).y, (co->tr).z); 
			for (i = 1; i < 3; i++) {
				printf("co                                                % 7.4f, % 7.4f, % 7.4f         (% 7.4f, % 7.4f, % 7.4f)\n",  
					co->ry[i][0], co->ry[i][1], co->ry[i][2], 
					co->rz[i][0], co->rz[i][1], co->rz[i][2]); 
				}
			printf("co -y = (% 7.4f, % 7.4f, % 7.4f) rot-y = % 7.4f, % 7.4f, % 7.4f rot-z = (% 7.4f, % 7.4f, % 7.4f) -t = (% 7.4f, % 7.4f, % 7.4f) \n",  
				(co->rty).x, (co->rty).y, (co->rty).z, 
				co->rry[0][0], co->rry[0][1], co->rry[0][2], 
				co->rrz[0][0], co->rrz[0][1], co->rrz[0][2],
				(co->rtr).x, (co->rtr).y, (co->rtr).z); 
			for (i = 1; i < 3; i++) {
				printf("co                                                % 7.4f, % 7.4f, % 7.4f         (% 7.4f, % 7.4f, % 7.4f)\n",  
						co->rry[i][0], co->rry[i][1], co->rry[i][2], 
						co->rrz[i][0], co->rrz[i][1], co->rrz[i][2]); 
			}
		)
	#endif
						
	#if defined(DEBUG_set_supermirror_flat_geometry)
		MPI_MASTER (
//			Polyhedron*geo_out = (Polyhedron*)geo;
			printf("set_supermirror_flat_geometry: sm->geo: plane after rotY-trans-rotZ\n"); 
			for (i = 0; i < 6; i++) {
					printf("geo plane %d point = (% 7.4f, % 7.4f, % 7.4f) normal = (% 7.4f, % 7.4f, % 7.4f)\n", i, 
						(geo->fp[i]).x, (geo->fp[i]).y, (geo->fp[i]).z, 
						(geo->fn[i]).x, (geo->fn[i]).y, (geo->fn[i]).z); 
			}
					
			printf("set_supermirror_flat_geometry: sm->co: field-axis after rotX-trans-rotZ = (% 7.4f, % 7.4f, % 7.4f)\n", 
						(co->fa).x, (co->fa).y, (co->fa).z); 
		)
	#endif

	return 1; //initialisation successful
}

int load_substrate_material_parameters(char*material_name, double*data) 
{
//#define DEBUG_load_substrate_material_parameters
	int found = 0;	
	FILE *file; 
	int file_location_option = 0; 
	char *name_from_function = 0;
	to_lower_case(material_name, &name_from_function); //convert to lower case	
	char name_from_file[CHAR_BUF_LENGTH];
	int n;
	char line[CHAR_BUF_LENGTH]; 
	
	while (file_location_option != -1) {
		if (file = sm_open_file(0, "Supermirror_substrate_materials.txt", "r", 0, &file_location_option)) 
		{
			while(fgets(line, sizeof(line), file) != NULL) {

				//skip lines that have been commented out
				if (strlen(line) == 0) continue;
				if (line[0] == '#' || line[0] == '\\' || line[0] == '/') continue;
				if (isBlank(line)) continue;			
				
				#if defined(DEBUG_load_substrate_material_parameters)
				printf("get_substrate_material_parameters: line %s", line);
				#endif
				n = sscanf(line, " %99[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", name_from_file, data, data+1, data+2, data+3, data+4, data+5, data+6, data+7);
				
				#ifdef DEBUG_load_substrate_material_parameters
				printf("get_substrate_material_parameters: sscanf n (name, L_abs, L_inc, SLD, S_coh, A, T_D, n, C2) = %d (%s=", n, name_from_file);
				#endif
				to_lower_case(name_from_file, 0); //convert to lower case
				#ifdef DEBUG_load_substrate_material_parameters
				printf("%s , % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f)\n", 
						name_from_file, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
				#endif
				if (n == 9) {
					if (strcmp(name_from_file, name_from_function) == 0) {
						#ifdef DEBUG_load_substrate_material_parameters
						printf("%s , % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f)\n", 
								name_from_file, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
						printf("found\n\n");
						#endif
						found = 1;
						break;
					}
				}
			}
			fclose(file);	
			if (found) {
				#ifdef DEBUG_load_substrate_material_parameters
				MPI_MASTER(
				printf("load_substrate_material_parameters: %s found\n", material_name);
				)
				#endif
				break;
			}
		}
	}
	if (name_from_function != 0) {
		free(name_from_function);
		name_from_function = 0;
	}
	return found;
}

/**
 * @brief Calculates the Debye integral phi(x) using a series expansion with Bernoulli numbers.
 * @param x Dimensionless parameter (T_D / T).
 * @return The value of phi(x).
 */
static double debye_integral_phi(double x) {
//#define DEBUG_debye_integral_phi
    // Bernoulli numbers B_2k for k=1, 2, ...
    const double B_2k[] = {1.0/6.0, -1.0/30.0, 1.0/42.0, -1.0/30.0, 5.0/66.0, 
		-691/2730, 7/6, -3617/510, 43867/798, -174611/330, 854513/138, 
		-236364091/2730, 8553103/6, -23749461029/870, 8615841276005/14322};
    const int num_terms = sizeof(B_2k) / sizeof(B_2k[0]);
    
    double sum = 0.0, term1 = 1.0, term2;
    for (int k = 1; k <= num_terms; ++k) {
		term1 *= x*x/(2*k*(2*k-1));
		term2 = B_2k[k-1] / (2*k + 1) * term1;
        sum += term2;
		
		#ifdef DEBUG_debye_integral_phi
		printf("debye_integral_phi(x=%lf): k=%d term1=%lf, term2=%lf, sum=%lf\n",x,k,term1,term2,sum);
		#endif
    }
	#ifdef DEBUG_debye_integral_phi
	printf("debye_integral_phi(x=%lf): intg = %lf\n", x, 1.0 - x / 4.0 + sum);
	#endif
    
    return 1.0 - x / 4.0 + sum;
}

/**
 * @brief Calculates the series sum R(x) using Bernoulli numbers.
 * @param x Dimensionless parameter (T_D / T).
 * @return The value of the sum R.
 */
static double calculate_R_series(double x) {
//#define DEBUG_calculate_R_series
    // Bernoulli numbers B_n for n=0, 1, 2, 4, 6,...
    const double B_n[] = {1.0, -1.0/2.0, 1.0/6.0, 0.0, -1.0/30.0, 0.0, 1.0/42.0, 0,0
		-1.0/30.0, 0.0, 5.0/66.0, 0.0, 691/2730, 0.0, 7/6, 0.0, 
		-3617/510, 0.0, 43867/798, 0.0, -174611/330, 0.0, 854513/138};
    const int num_terms = sizeof(B_n) / sizeof(B_n[0]);
    
	int n = 0;
    double sum = 0.0, term1, term2;
	//n=0
	term1 = 1.0/x; term2 = B_n[0] * term1 / (n+2.5); sum = term2;
	for (n = 1; n < num_terms - 1; ++n) {
		term1 *= x / n;
        if (B_n[n] == 0.0) continue;
        term2 = B_n[n] * term1 / (n + 2.5);
        sum += term2;
		#ifdef DEBUG_calculate_R_series
		printf("debye_integral_phi(x=%lf): n=%d term1=%lf, term2=%lf, sum=%lf\n",x,n,term1,term2,sum);
		#endif
    }
	//n=22
	term1 *= x / n;
    term2 = B_n[n] * term1 / (n + 2.5);
	sum += term2/2;

	#ifdef DEBUG_calculate_R_series
	printf("debye_integral_phi(x=%lf): n=%d term1=%lf, term2=%lf, sum=%lf\n",x,n,term1,term2,sum);
	#endif
    return sum;
}

/**
 * @brief Calculates the a_mph parameter (free-atom cross-section).
 * @param S_coh Bound atom scattering cross-section [barns].
 * @param A Atomic mass number [amu].
 * @return The a_mph parameter [barns].
 */
double calculate_phonon_a_mph(double S_coh, double A) {
//#define DEBUG_calculate_phonon_a_mph
	#ifdef DEBUG_calculate_phonon_a_mph
	printf("calculate_phonon_a_mph: S_coh=%lf,A=%lg,a_mph=%lf\n",S_coh,A,S_coh * pow(A / (A + 1.0), 2.0));
	#endif
    
    return S_coh * pow(A / (A + 1.0), 2.0);
}

/**
 * @brief Calculates the b_mph parameter for the exponent.
 * @param A Atomic mass number [amu].
 * @param T_D Debye temperature [K].
 * @param C2 Material-specific fitting parameter [Å⁻²eV⁻¹].
 * @param T Temperature [K].
 * @return The b_mph parameter [Å²].
 */
double calculate_phonon_b_mph(double A, double T_D, double T, double C2) {
//#define DEBUG_calculate_phonon_b_mph

    // Calculate intermediate Debye-Waller terms
    double B0 = 2873 / (A * T_D);
    double x = T_D / T;
    double phi_x = debye_integral_phi(x);
    double BT = 4.0 * B0 * phi_x / x;
	double b_mph = -(B0 + BT) * C2 * EOverVSquare_meV_m_s;
	
	#ifdef DEBUG_calculate_phonon_b_mph
	printf("calculate_phonon_b_mph: A=%lf,T_D=%lg,T=%lg,B0=%lf,BT=%lf,C2=%lf,b_mph=%lf\n",A,T_D,T,B0,BT,C2, -(B0 + BT) * C2 * EOverVSquare_meV_m_s);
	#endif
    
    return b_mph;
}

/**
 * @brief Calculates the a_sph parameter (single-phonon coefficient).
 * @param sigma_bat Bound atom scattering cross-section [barns].
 * @param A Atomic mass number [amu].
 * @param T_D Debye temperature [K].
 * @param T Temperature [K].
 * @return The a_sph parameter [barns/Å].
 */
double calculate_phonon_a_sph(double S_coh, double A, double T_D, double T) {
//#define DEBUG_calculate_phonon_a_sph

    double x = T_D / T;
    
    // Calculate the temperature-dependent coefficient a_sph
    double R_x = calculate_R_series(x);
    double a_sph = 3 * S_coh * pow(kB_meV_K * T_D / EOverVSquare_meV_m_s, 0.5) * R_x / A;
	
	#ifdef DEBUG_calculate_phonon_a_sph
	printf("calculate_phonon_a_sph: S_coh=%lf, A=%lf,T_D=%lg,T=%lg,R_x=%lf,a_sph=%lf\n",S_coh,A,T_D,T,R_x,a_sph);
	#endif

    return a_sph;
}

int set_substrate_material_parameters(char*substrate_material_name, 
	double substrate_L_abs, double substrate_L_inc, double substrate_SLD, 
	double substrate_S_coh, double substrate_A, double substrate_T_D, double substrate_T, double substrate_n, double substrate_C2, 
	double thickness_in_mm, char*substrate_edge_block, SubstrateParameters*sub, RefractionParameters*subsurface) 
{
	if (sub == 0 || subsurface == 0) {
		MPI_MASTER(printf("set_substrate_material_parameters: error, pointers to SubstrateParameters & RefractionParameters variables must both not be 0.\n");) 
		return 0;
	}
	
	if (substrate_T == -1) substrate_T=298.15; //20 degree-C is used as laboratory standard temperature
	
	//start with nothing
	strcpy(sub->name,"empty");
	strcpy(subsurface[0].name,"empty");
	strcpy(subsurface[1].name,"empty");
	sub->L_abs = -1;
	sub->L_inc = -1;
	sub->SLD = 0;
	sub->S_coh = 0;
	sub->A = 0;
	sub->T_D = -1;
	sub->n = 0;
	sub->C2 = 0;
	subsurface[0].Qc_sub = subsurface[1].Qc_sub = 0;
	subsurface[0].delta_n_2 = subsurface[1].delta_n_2 = 0;
	sub->sub_type = 0;
	subsurface[0].subsurface_type = subsurface[1].subsurface_type = 0;
	
	//substrate_material_spec specified?
	if (substrate_L_abs != -1 || substrate_L_inc != -1 || substrate_SLD != 0 || 
		substrate_S_coh != 0 || substrate_A != 0 || substrate_T_D != -1 || substrate_n != 0 || substrate_C2 != 0) {
		strcpy(sub->name,"UserDefine");
		strcpy(subsurface[0].name,"UserDefine");
		strcpy(subsurface[1].name,"UserDefine");
		if (substrate_material_name != 0) {
			if (strlen(substrate_material_name) > 0) {
				strcpy(sub->name, substrate_material_name);
				strcpy(subsurface[0].name,substrate_material_name);
				strcpy(subsurface[1].name,substrate_material_name);
			}
		}
		sub->L_abs = substrate_L_abs;
		sub->L_inc = substrate_L_inc;
		sub->SLD = substrate_SLD;
		sub->S_coh = substrate_S_coh;
		sub->A = substrate_A;
		sub->T_D = substrate_T_D;
		sub->n = substrate_n;
		sub->C2 = substrate_C2;
		subsurface[0].Qc_sub = subsurface[1].Qc_sub = sqrt(16 * M_PI * fabs(substrate_SLD));
		subsurface[0].delta_n_2 = subsurface[1].delta_n_2 = LambdaV_AA_m_s * LambdaV_AA_m_s * substrate_SLD / M_PI;
	}

	//Look up name from Supermirror_substrate_materials.txt.
	//If found, replace substrate parameters
	if (substrate_material_name != 0)
	if (strlen(substrate_material_name) > 0) {

		int found = 0;
		double d_temp[8];
		MPI_MASTER (
			found = load_substrate_material_parameters(substrate_material_name, d_temp);
		)
		#if USE_MPI
		//broadcast the value of found to all processes
		MPI_Bcast(&found, 1, MPI_INT, mpi_node_root, MPI_COMM_WORLD);
		#endif
		if (found) {
			#if USE_MPI
			//broadcast to all processes
			MPI_Bcast(d_temp, 8, MPI_DOUBLE, mpi_node_root, MPI_COMM_WORLD);
			#endif
			
			sprintf(sub->name,"%s",substrate_material_name);
			sprintf(subsurface[0].name,"%s",substrate_material_name);
			sprintf(subsurface[1].name,"%s",substrate_material_name);
			
			sub->L_abs = d_temp[0];
			sub->L_inc = d_temp[1];
			sub->SLD = d_temp[2];
			sub->S_coh = d_temp[3];
			sub->A = d_temp[4];
			sub->T_D = d_temp[5];
			sub->n = d_temp[6];
			sub->C2 = d_temp[7];
			subsurface[0].Qc_sub = subsurface[1].Qc_sub = sqrt(16 * M_PI * d_temp[2]);
			subsurface[0].delta_n_2 = subsurface[1].delta_n_2 = LambdaV_AA_m_s * LambdaV_AA_m_s * d_temp[2] / M_PI;
		}
		else {
			MPI_MASTER (printf("set_substrate_material_parameters: No file \"Supermirror_substrate_materials.txt\" or \"%s\" not on file\n",substrate_material_name);)
			return 0;
		}
	}
	
	//check if parameters entered or loaded indicated that substrate is empty
	char *name_from_function = 0;
	to_lower_case(sub->name, &name_from_function); //convert to lower case
	if (strcmp(name_from_function, "empty") == 0 || 
		(sub->L_abs == -1 && sub->L_inc == -1 && sub->SLD == 0 &&
		 sub->S_coh == 0 && sub->A == 0 && sub->T_D == -1 && sub->n == 0 && sub->C2 == 0)
		) {
		strcpy(sub->name,"empty");
		sub->L_abs = -1;
		sub->L_inc = -1;
		sub->SLD = 0;
		sub->S_coh = 0;
		sub->A = 0;
		sub->T_D = -1;
		sub->n = 0;
		sub->C2 = 0;
		subsurface[0].Qc_sub = subsurface[1].Qc_sub = 0;
		subsurface[0].delta_n_2 = subsurface[1].delta_n_2 = 0;
	}
	if (name_from_function != 0) {
		free(name_from_function);
		name_from_function = 0;
	}
	
	//Convert L_abs & L_inc to SI from cm
	sub->L_abs = sub->L_abs == -1 ? -1 : sub->L_abs/100;
	sub->L_inc = sub->L_inc == -1 ? -1 : sub->L_inc/100;
	
	//determine sub->sub_type and subsurface[SM_Num_Mirror_Planes].subsurface_type
	if (sub->L_abs != -1 || sub->L_inc != -1) {
		sub->sub_type = sm_sub_type_attn; //has attenuation
	}
	if (sub->SLD != 0) {
		subsurface[0].subsurface_type = subsurface[1].subsurface_type = sm_subsurface_type_refl | sm_subsurface_type_total_refl | sm_subsurface_type_refract; //has reflection, total reflection, and refraction  
	}
	sub->a_sph = calculate_phonon_a_sph(sub->S_coh, sub->A, sub->T_D, substrate_T);
	sub->a_mph = calculate_phonon_a_mph(sub->S_coh, sub->A);
	sub->b_mph = calculate_phonon_b_mph(sub->A, sub->T_D, substrate_T, sub->C2);
	
	sub->thickness_in_mm = thickness_in_mm;
	
	if (strcmp(substrate_edge_block,"front") == 0) {
		sub->sub_type |= sm_sub_type_front_edge_attn;
	}
	if (strcmp(substrate_edge_block,"back") == 0) {
		sub->sub_type |= sm_sub_type_back_edge_attn;
	}

	return 1;
}

int load_mirror_material_parameters(char*mirror_material_name, double*data) 
{
//#define DEBUG_load_mirror_material_parameters

	int found = 0;	
	FILE *file; 
	int file_location_option = 0; 
	char *name_from_function = 0;
	to_lower_case(mirror_material_name, &name_from_function); //convert to lower case	
	char name_from_file[CHAR_BUF_LENGTH];
	int n;
	char line[CHAR_BUF_LENGTH]; 
	
	while (file_location_option != -1) {
		if (file = sm_open_file(0, "Supermirror_reflective_coating_materials.txt", "r", 0, &file_location_option)) 
		{
			while(fgets(line, sizeof(line), file) != NULL) {

				//skip lines that have been commented out
				if (line[0] == '#' || line[0] == '\\' || line[0] == '/') continue;

				#ifdef DEBUG_load_mirror_material_parameters
				printf("get_mirror_material_parameters: line %s", line);
				#endif
				n = sscanf(line, " %99[^,],%lf,%lf,%lf,%lf,%lf,%lf", name_from_file, data, data+1, data+2, data+3, data+4, data+5);
				
				#ifdef DEBUG_load_mirror_material_parameters
				printf("get_mirror_material_parameters: sscanf n (name,R0,Qc,alpha,m,W,beta) = %d (%s(", n, name_from_file);
				#endif
				to_lower_case(name_from_file, 0); //convert to lower case
				#ifdef DEBUG_load_mirror_material_parameters
				printf("%s ), % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f)\n", name_from_file, data[0], data[1], data[2], data[3], data[4], data[5]);
				#endif
				if (n == 7) {
					if (strcmp(name_from_file, name_from_function) == 0) {
						found = 1;
						break;
					}
				}
			}
			fclose(file);	
			if (found) {
				#ifdef DEBUG_load_mirror_material_parameters
				MPI_MASTER(
				printf("load_mirror_material_parameters: %s found\n", mirror_material_name);
				)
				#endif
				break;
			}
		}
	}
	if (name_from_function != 0) {
		free(name_from_function);
		name_from_function = 0;
	}
	return found;
}

int set_mirror_material_parameters(char*mirror_material_name, double*mirror_material_spec, double mirror_m, ReflectionParameters*mir, RefractionParameters*subsurface) 
{
//#define DEBUG_set_mirror_material_parameters

	if (mir == 0) {
		MPI_MASTER(printf("set_mirror_material_parameters: error, pointer to ReflectionParameters variable must not be NULL.\n");) 
		return 0;
	}
	
	//start with nothing
	strcpy(mir->name, "NoSurfaceBoundary");
	mir->R0 = 0;
	mir->Qc = 0;
	mir->alpha = 0;
	mir->m = 0;
	mir->W = 0;
	mir->beta = 0;
	
	if (mirror_material_name == 0 && mirror_material_spec == 0) {
		MPI_MASTER(printf("set_mirror_material_parameters: pointers of mirror_material_name and mirror_material_spec are both not given.\n");)
	}
	
	//mirror_material_spec specified?
	if (mirror_material_spec != 0) {
		strcpy(mir->name,"UserDefine");
		if (mirror_material_name != 0) {
			if (strlen(mirror_material_name) > 0) {
				strcpy(mir->name, mirror_material_name);
			}
		}
		mir->R0 = mirror_material_spec[0];
		mir->Qc = mirror_material_spec[1];
		mir->alpha = mirror_material_spec[2];
		mir->m = mirror_material_spec[3];
		mir->W = mirror_material_spec[4];
		mir->beta = mirror_material_spec[5];
	}
	
	//look for mirror_material_name in file 	
	if (mirror_material_name != 0)
	if (strlen(mirror_material_name) > 0) {
		
		int found = 0; //assume name is not found in Supermirror_reflective_coating_materials.txt
		double d_temp[6];
		MPI_MASTER (	
			found = load_mirror_material_parameters(mirror_material_name, d_temp);
		)
		#if USE_MPI
		//broadcast the value of found to all processes
		MPI_Bcast(&found, 1, MPI_INT, mpi_node_root, MPI_COMM_WORLD);
		#endif
		if (found) {
			#if USE_MPI
			//broadcast to all processes
			MPI_Bcast(d_temp, 6, MPI_DOUBLE, mpi_node_root, MPI_COMM_WORLD);
			#endif
			
			strcpy(mir->name,mirror_material_name);
			mir->R0 = d_temp[0];
			mir->Qc = d_temp[1];
			mir->alpha = d_temp[2];
			mir->m = d_temp[3];
			mir->W = d_temp[4];
			mir->beta = d_temp[5];
		}
		else {
			MPI_MASTER (printf("set_mirror_material_parameters: No file \"Supermirror_reflective_coating_materials.txt\" or \"%s\" not on file\n",mirror_material_name);)
			return 0;
		}
	}
	
	//if mirror_m == -1, use value in file for mir->m. 
	//else mir->m = mirror_m. 
	if (mirror_m != -1) {
		mir->m = mirror_m;
	}
	
	//check for name & spec consistency
	//determine type
	char *name_from_function = 0;
	to_lower_case(mir->name, &name_from_function); //convert to lower case
	
	#if defined(DEBUG_set_mirror_material_parameters)
	printf("set_mirror_material_parameters: name_from_function=%s\n", name_from_function);
	printf("set_mirror_material_parameters: input: subsurface->subsurface_type=%x\n", subsurface->subsurface_type);
	#endif
	
	if (strcmp(name_from_function,"nosurfaceboundary") == 0 || 
		strcmp(name_from_function,"noreflection") == 0 || 
		strcmp(name_from_function,"empty") == 0) {
		mir->R0 = 0;
		mir->Qc = 0;
		mir->alpha = 0;
		mir->m = 0;
		mir->W = 0;
		mir->beta = 0;
		
		mir->refl_type = 0; //No reflection from mirror or substrate
		subsurface->subsurface_type = 0; //No substrate reflection, total reflection or 
	}
	else if (strcmp(name_from_function,"substrate") == 0 || 
			 strcmp(name_from_function,"substratesurface") == 0 || 
			 mir->R0 <= 0 || mir->Qc <= 0 || mir->m <= 0) {
		mir->R0 = 0;
		mir->Qc = 0;
		mir->alpha = 0;
		mir->m = 0;
		mir->W = 0;
		mir->beta = 0;
		mir->refl_type = mir->refl_type & ~sm_refl_type_refl; //set to no mirror surface reflection
		//substrate interface reflection, total reflection & refraction types determined in set_substrate_material_parameters
	}
	else {
		//reflection from mirror, not from bare substrate interface
		//total reflection and refraction from substrate will be based on substrate's own parameters
		mir->refl_type = mir->refl_type | sm_refl_type_refl; //set to mirror surface reflection
		subsurface->subsurface_type = subsurface->subsurface_type & ~sm_subsurface_type_refl; //override substrate interface type to no substrate reflection
		//substrate total reflection & refraction types determined in set_substrate_material_parameters
	}
	if (name_from_function != 0) {
		free(name_from_function);
		name_from_function = 0;
	}

	if ((mir->refl_type & sm_refl_type_refl) == sm_refl_type_refl) {
		//initialise_mirror_material_parameters
		
		// If mir->Qc < subsurface->Qc_sub, use substrate Qc_sub for total reflection
		mir->Qc = mir->Qc > subsurface->Qc_sub ? mir->Qc : subsurface->Qc_sub;
		
		// If W and alpha are set to 0, use parametrization from Henrik Jacobsen's approach. The values depend on m only:
		// 	double m_value=m*0.9853+0.1978;
		// 	double W=-0.0002*m_value+0.0022;
		// 	For m <= 3,
		// 		double alpha=m_value;
		// 		double beta=0;
		// 	For m > 3,
		// 		double alpha=0.2304*m_value+5.0944;
		// 		double beta=-7.6251*m_value+68.1137;
		if (mir->W==0 && mir->alpha==0) {
			mir->m=mir->m*0.9853+0.1978;
			mir->W=-0.0002*mir->m+0.0022;
			if (mir->m<=3) {
				mir->alpha=mir->m;
				mir->beta=0;
			}
			else {
				mir->alpha=0.2304*mir->m+5.0944;
				mir->beta=-7.6251*mir->m+68.1137;
			}
		}
	}
	
	#if defined(DEBUG_set_mirror_material_parameters)
	MPI_MASTER (
	printf("set_mirror_material_parameters: (name,R0,Qc,alpha,m,W,beta,type) = (%s, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, %x)  ", 
		mir->name, mir->R0, mir->Qc, mir->alpha, mir->m, mir->W, mir->beta, mir->refl_type);
	printf("set_mirror_material_parameters: update subsurface->subsurface_type = %x\n", subsurface->subsurface_type);
	)
	#endif
	
	return 1;
}

int load_absorber_material_parameters(char*material_name, double*data) 
{
//#define DEBUG_load_absorber_material_parameters

	int found = 0;	
	FILE *file; 
	int file_location_option = 0; 
	char *name_from_function = 0;
	to_lower_case(material_name, &name_from_function); //convert to lower case	
	char name_from_file[CHAR_BUF_LENGTH];
	int n;
	char line[CHAR_BUF_LENGTH]; 
	
	while (file = sm_open_file(0, "Supermirror_absorber_coating_materials.txt", "r", 0, &file_location_option)) {
		while(fgets(line, sizeof(line), file) != NULL) {

			//skip lines that have been commented out
			if (strlen(line) == 0) continue;
			if (line[0] == '#' || line[0] == '\\' || line[0] == '/') continue;
			if (isBlank(line)) continue;			
			
			#if defined(DEBUG_load_absorber_material_parameters)
			printf("get_substrate_material_parameters: line %s", line);
			#endif
			n = sscanf(line, " %99[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", name_from_file, data, data+1, data+2, data+3, data+4, data+5, data+6, data+7);
			
			#ifdef DEBUG_load_absorber_material_parameters
			printf("get_substrate_material_parameters: sscanf n (name, L_abs, L_inc, SLD, S_coh, A, T_D, n, C2) = %d (%s=", n, name_from_file);
			#endif
			to_lower_case(name_from_file, 0); //convert to lower case
			#ifdef DEBUG_load_absorber_material_parameters
			printf("%s, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f)\n", 
					name_from_file, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
			#endif
			if (n == 9) {
				if (strcmp(name_from_file, name_from_function) == 0) {
					#ifdef DEBUG_load_absorber_material_parameters
					printf("found\n\n");
					#endif
					found = 1;
					break;
				}
			}
		}
		fclose(file);	
		if (found) {
			#ifdef DEBUG_load_absorber_material_parameters
			MPI_MASTER (
			printf("load_absorber_material_parameters: %s found\n", material_name);
			)
			#endif
			break;
		}
		#ifdef DEBUG_load_absorber_material_parameters
		else {
			printf("load_absorber_material_parameters: material %s not found\n", material_name);
		}
		#endif
	}
	if (name_from_function != 0) {
		free(name_from_function);
		name_from_function = 0;
	}
	return found;
}

int set_absorber_material_parameters(char*absorber_material_name, double absorber_L_abs, double absorber_L_inc, double absorber_thickness_in_micron, AbsorptionParameters*abs) 
{
//define DEBUG_set_absorber_material_parameters

	if (abs == 0) {
		MPI_MASTER(printf("set_absorber_material_parameters: error, pointer to SubstrateParameters variable must not be NULL.\n");) 
		return 0;
	}
	
	//start with nothing
	strcpy(abs->name,"NoAbsorber");
	abs->L_abs = -1;
	abs->L_inc = -1;
	abs->thickness_in_micron = 0;
	
	//absorber parameters given?
	if ((absorber_L_abs != -1 || absorber_L_inc != -1) && absorber_thickness_in_micron != 0) {
		strcpy(abs->name,"UserDefine");
		abs->L_abs = absorber_L_abs;
		abs->L_inc = absorber_L_inc;
		abs->thickness_in_micron = absorber_thickness_in_micron;
	}

	//look for absorber name in substrate parameter file
	if (absorber_material_name != 0)
	if (strlen(absorber_material_name) > 0) {
		
		int found = 0;
		double d_temp[7];
		MPI_MASTER (
			found = load_absorber_material_parameters(absorber_material_name, d_temp);
		)
		#if USE_MPI
		//broadcast the value of found to all processes
		MPI_Bcast(&found, 1, MPI_INT, mpi_node_root, MPI_COMM_WORLD);
		#endif
		if (found) {
			#if USE_MPI
			//broadcast to all processes
			MPI_Bcast(d_temp, 7, MPI_DOUBLE, mpi_node_root, MPI_COMM_WORLD);
			#endif
			
			sprintf(abs->name,"%s",absorber_material_name);
			
			abs->L_abs = d_temp[0];
			abs->L_inc = d_temp[1];
		}
		else {
			MPI_MASTER (printf("set_absorber_material_parameters: No file \"Supermirror_absorber_coating_materials.txt\" or \"%s\" not on file\n",absorber_material_name);)
			return 0;
		}
	}
	abs->thickness_in_micron = absorber_thickness_in_micron;
	
	//check for name & spec consistency
	//determine type
	char *name_from_function = 0;

	#ifdef DEBUG_set_absorber_material_parameters
	printf("set_absorber_material_parameters: %s Labs=%g, Linc=%g, thickness_in_micron=%g\n", 
			abs->name, abs->L_abs, abs->L_inc, abs->thickness_in_micron);
	#endif

	to_lower_case(abs->name, &name_from_function); //convert to lower case
	if (strcmp(name_from_function,"nocoating") == 0 ||
		strcmp(name_from_function,"noabsorber") == 0 || 
		strcmp(name_from_function,"empty") == 0 || 
		(abs->L_abs == -1 && abs->L_inc == -1) || 
		abs->thickness_in_micron == 0) {
		strcpy(abs->name,"NoAbsorber");
		abs->L_abs = -1;
		abs->L_inc = -1;
		abs->thickness_in_micron = 0;
		abs->abs_type = 0;
	}
	else {
		abs->abs_type = sm_abs_type_attn;
	}
	if (name_from_function != 0) {
		free(name_from_function);
		name_from_function = 0;
	}
	
	//Convert L_abs & L_inc to SI from cm
	abs->L_abs = abs->L_abs == -1 ? -1 : abs->L_abs/100;
	abs->L_inc = abs->L_inc == -1 ? -1 : abs->L_inc/100;
	
	return 1;
}

void set_process_parameters(int is_tracking, Supermirror*sm, SupermirrorProcess *proc) 
{
//define DEBUG_set_process_parameters

	proc->is_tracking = is_tracking;
	#if defined(DEBUG_set_process_parameters) 
	MPI_MASTER (printf("set_process_parameters: is_tracking = %d\n", proc->is_tracking);)
	#endif
	
	strcpy(proc->side[sm_ReflectedSide],"ReflectedSide");
	strcpy(proc->side[sm_TransmittedSide],"TransmittedSide");
	strcpy(proc->side[sm_EdgeSide],"EdgeSide");
	
	strcpy(proc->plane[sm_SurfacePlane1],"Surface1");
	strcpy(proc->plane[sm_SurfacePlane2],"Surface2");
	strcpy(proc->plane[sm_EdgeFrontPlane],"EdgeFront");
	strcpy(proc->plane[sm_EdgeBackPlane],"EdgeBack");
	strcpy(proc->plane[sm_EdgeSidePlane1],"EdgeSide1");
	strcpy(proc->plane[sm_EdgeSidePlane2],"EdgeSide2");
	
	strcpy(proc->layer[sm_MirrorLayer],"MirrorLayer");
	strcpy(proc->layer[sm_AbsorberLayer],"AbsorberLayer");
	strcpy(proc->layer[sm_SubstrateSurfaceLayer],"SubstrateSurfaceLayer");
	strcpy(proc->layer[sm_SubstrateLayer],"SubstrateLayer");
	
	int side,plane,layer;
	for (side=0; side<SM_Num_Side; side++)
	for (plane=0; plane<SM_Num_Plane; plane++)
	for (layer=0; layer<SM_Num_Layer; layer++) {
		sprintf((proc->location)[side][plane][layer],"%s/%s/%s/%s",
			sm->name, (proc->side)[side], (proc->plane)[plane], (proc->layer)[layer]);
	}
	
	strcpy(proc->event[sm_Error],"Error");
	strcpy(proc->event[sm_Exited],"Exited");
	strcpy(proc->event[sm_Absorbed],"Absorbed");
	strcpy(proc->event[sm_Intersected],"Intersected");
	strcpy(proc->event[sm_Missed],"Missed");
	strcpy(proc->event[sm_Reflected],"Reflected");
	strcpy(proc->event[sm_Transmitted],"Transmitted");
	strcpy(proc->event[sm_ReflectedOutward],"ReflectedOutward");
	strcpy(proc->event[sm_TransmittedOutward],"TransmittedOutward");
	strcpy(proc->event[sm_ReflectedInward],"ReflectedInward");
	strcpy(proc->event[sm_TransmittedInward],"TransmittedInward"); 
	strcpy(proc->event[sm_TotalReflected],"sm_TotalReflected"); 
	strcpy(proc->event[sm_Zigzag],"Zigzag");
	
	strcpy(proc->proc[going_inward],"going_inward_to_sm");
	strcpy(proc->proc[going_outward],"going_outward_from_sm");
	strcpy(proc->proc[ignore_reflection],"ignore_reflection");
	strcpy(proc->proc[keep_reflection],"keep_reflection");

	#if defined(DEBUG_set_process_parameters) 
	MPI_MASTER (printf("entered names of sides and names of planes\n");)
	#endif
	
}

void set_location(SimState *state, Supermirror*sm) 
{
	strcpy(state->location, ((sm->proc).location)[state->side][state->plane][state->layer]);
}

void set_event(SimState *state, Supermirror*sm, int event_code) 
{
	strcpy(state->event, ((sm->proc).event)[event_code]);
}
	

/*******************************/
/* Ray-Tracing Tools functions */
/*******************************/

void sm_initialise_state(SimState*state) {

	Coords null_vector = coords_set(F_INDETERMINED,F_INDETERMINED,F_INDETERMINED);

	state->ray_count = mcget_run_num();
		
	state->location[0]='\0';
	state->event[0] ='\0'; 
	
	state->w = F_INDETERMINED; 
	state->t = F_INDETERMINED; 
	state->p = null_vector; 
	state->v = null_vector; 
	state->s = null_vector;
	state->ws[0] = state->ws[1] = F_INDETERMINED;
	
	state->v_len = F_INDETERMINED;
	state->vn_len = F_INDETERMINED;
	
	state->side = I_INDETERMINED; 
	state->plane = I_INDETERMINED; 
	state->layer = I_INDETERMINED; 
	state->side_at_plane[0] = state->side_at_plane[1] = I_INDETERMINED; 
	state->fn = null_vector; 
	
	state->n_mirror_intersect = 0;
	state->n_surface_intersect = 0;
	
	state->last_time = F_INDETERMINED; 
	state->last_point = null_vector; 
	state->last_plane = I_INDETERMINED;

	state->set_surface_parameters = 0;
	
	state->v_in_vac_inward_at_plane[0] = state->v_in_vac_inward_at_plane[1] = null_vector;
	state->v_in_vac_outward_at_plane[0] = state->v_in_vac_outward_at_plane[1] = null_vector;
	state->v_in_vac_len_at_plane[0] = state->v_in_vac_len_at_plane[1] = F_INDETERMINED;
	state->vn_in_vac_len_at_plane[0] = state->vn_in_vac_len_at_plane[1] = F_INDETERMINED;
	state->Rm_vac_to_mir_at_plane[0][0] = state->Rm_vac_to_mir_at_plane[0][1] = state->Rm_vac_to_mir_at_plane[1][0] = state->Rm_vac_to_mir_at_plane[1][1] = F_INDETERMINED; 

	state->v_sub_to_mir_at_plane[0][0] = state->v_sub_to_mir_at_plane[0][1] = state->v_sub_to_mir_at_plane[1][0] = state->v_sub_to_mir_at_plane[1][1] = null_vector;
	state->Rm_sub_to_mir_at_plane[0][0] = state->Rm_sub_to_mir_at_plane[0][1] = state->Rm_sub_to_mir_at_plane[1][0] = state->Rm_sub_to_mir_at_plane[1][1] = F_INDETERMINED; 
	state->Rm_sub_to_mir_total_refl_at_plane[0][0] = state->Rm_sub_to_mir_total_refl_at_plane[0][1] = state->Rm_sub_to_mir_total_refl_at_plane[1][0] = state->Rm_sub_to_mir_total_refl_at_plane[1][1] = I_INDETERMINED; 

	state->v_in_sub_inward_at_plane[0] = state->v_in_sub_inward_at_plane[1] = null_vector;
	state->v_in_sub_inward_len_at_plane[0] = state->v_in_sub_inward_len_at_plane[1] = F_INDETERMINED;
	state->vn_in_sub_inward_len_at_plane[0] = state->vn_in_sub_inward_len_at_plane[1] = F_INDETERMINED; 
	state->v_in_sub_outward_at_plane[0] = state->v_in_sub_outward_at_plane[1] = null_vector;
	state->v_in_sub_outward_len_at_plane[0] = state->v_in_sub_outward_len_at_plane[1] = F_INDETERMINED; 
	state->vn_in_sub_outward_len_at_plane[0] = state->vn_in_sub_outward_len_at_plane[1] = F_INDETERMINED; 
	state->Rs_sub_to_vac_at_plane[0] = state->Rs_sub_to_vac_at_plane[1] = F_INDETERMINED;  
	state->Rs_vac_to_sub_at_plane[0] = state->Rs_vac_to_sub_at_plane[1] = F_INDETERMINED; 

	state->set_L_attn_mir = 0;
	state->T_attn_mir = F_INDETERMINED;
	
	state->set_L_attn_abs = 0;
	state->L_attn_abs_at_plane[0] = state->L_attn_abs_at_plane[1] = F_INDETERMINED; 
	state->t_prop_abs_at_plane[0] = state->t_prop_abs_at_plane[1] = F_INDETERMINED; 
	state->T_prop_abs_at_plane[0] = state->T_prop_abs_at_plane[1] = F_INDETERMINED; 

	state->set_L_attn_sub = 0;
	state->T = F_INDETERMINED;
	state->L_attn_sub = F_INDETERMINED; 
	state->t_prop_sub = F_INDETERMINED; 
	state->T_prop_sub = F_INDETERMINED; 

}

/***********************************************************************/
/* calculate Rm, Rs, v-inward/outward at mirror and substrate surfaces */
/***********************************************************************/
//Calculate q from R
double sm_calc_q(double R, double Qc, double alpha, double m, double W, double beta, 
				 double tolerance, int max_iterations, int *converged) 
{
//define DEBUG_sm_calc_q

	#ifdef DEBUG_sm_calc_q
	printf("R, Qc, alpha, m, W, beta, tolerance, max_iterations = %lg, %lg, %lg, %lg, %lg, %lg, %lg, %d\n", 
			R, Qc, alpha, m, W, beta, tolerance, max_iterations);
	#endif

    double q = m * Qc_Ni;
    if (converged != 0) *converged = 0;
    
    for (int i = 0; i < max_iterations; i++) {
        double R_calc = sm_calc_Rm(q, Qc, 1, alpha, m, W, beta);
        double error = R_calc - R;
        
		#ifdef DEBUG_sm_calc_q
		printf("i, q, R_calc, error = %d, %lg, %lg, %lg, %lg\n", 
				i, q, R_calc, R, error);
		#endif

        // Check for convergence
        if (fabs(error) < tolerance) {
            if (converged != 0) 
				*converged = 1;
            return q;
        }
        
        // Calculate derivative
        double dR_dq = sm_calc_dRdq(q, Qc, alpha, m, W, beta);
        
        // Check for zero derivative (would cause division by zero)
        if (fabs(dR_dq) < 1e-15) {
            printf("Warning: Derivative too small, iteration stopped at q = %f\n", q);
            break;
        }
        
        // Newton-Raphson update: q_new = q - f(q)/f'(q)
        q = q - error / dR_dq;
    }
    
    return q;
}

double sm_calc_dRdq(double q, double Qc, double alpha, double m, double W, double beta) 
{
    double arg = (q - m * Qc_Ni) / W;
    double tanh_val = tanh(arg);
    double sech2_val = 1 - tanh_val * tanh_val;  // sech^2(x) = 1 - tanh^2(x)
    
    double quad_term = 1 - alpha * (q - Qc) + beta * (q - Qc) * (q - Qc);
    double dquad_dq = -alpha + 2 * beta * (q - Qc);
    
    // dR/dq = -0.5 * sech^2 * (1/W) * quad_term + 0.5 * (1 - tanh) * dquad_dq
    return -0.5 * sech2_val * (1.0 / W) * quad_term + 0.5 * (1 - tanh_val) * dquad_dq;
}

//Reflectivity at mirror surfaces
double sm_calc_Rm(double q, double Qc, double R0, double alpha, double m, double W, double beta) 
/******************************************************************************************************************************
sm_calc_Rm calculates reflectivity from supermirror parameters
Modified from algorithm used by McStas and VITESS. 
Now: Qc = the actual supermirror critical Qc for total reflection. Previous: Must use Qc = 0.0217 [1/Å], i.e. m=1 definition.
Now: arg = (q - m * Qc natural Ni)/W with Qc natural Ni = 0.0217 [1/Å]. Previous: arg = (q - m * Qc)/W
uses: 		
update:   
return: 	Rm
output: 
called by: 	sm_calc_surface_parameters
			InitialiseStdSupermirrorFlat_detail (to output reflectivities to file)
calls: 
********************************************************************************************************************************/
{
//define DEBUG_sm_calc_Rm

	#if defined(DEBUG_sm_calc_Rm)
	printf(	"%s double sm_calc_Rm(double q, double Qc, double R0, double alpha, double m, double W, double beta)\n"
			"%s q=% 7.4f, Qc=% 7.4f, R0=% 7.4f, alpha=% 7.4f, m=% 7.4f, W=% 7.4f, beta=% 7.4f\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, q, Qc,R0,alpha,m,W,beta);
	supermirror_flat_inc_prefix();
	#endif

	//Reflection from mirror-coating
	double Qcm  = m * Qc_Ni; //m * Qc for natural Ni (0.0217 [1/Å]
	
	// apply the formulation:
	// arg = (q - m * Qc_Ni)/w, 
	// reflectivity Rm_vac_to_mir_at_plane = R0*0.5*(1-tanh(arg))*(1-alpha*(q-Qcm)+beta*(q-Qcm)*(q-Qcm));
	
	double arg = W > 0 ? (q - Qcm)/W : 11;
	
	if (arg > 10 || m <= 0 || Qcm <= 0 || R0 <= 0) {
		#if defined(DEBUG_sm_calc_Rm)
		printf("%s reflect from mirror q,Rm_vac_to_mir_at_plane = % 10.4f,0, Qcm,m,W,arg>10?,alpha,beta = % 10.4f,% 10.4f,% 10.4f,% 10.4f,% 10.4f,% 10.4f\n",
				supermirror_flat_s_prefix, q,Qcm,m,W,arg,alpha,beta);
		supermirror_flat_dec_prefix();
		#endif

		return 0;
	}
	
	//Note: total reflection. 
	if (q <= Qc) {
		#if defined(DEBUG_sm_calc_Rm)
		printf("%s reflect from mirror q,Rm_vac_to_mir_at_plane = %5f,1, q<=Qcm, m,W,arg,alpha,beta = q<=%5f,%5f,%5f,%5f,%5f,%5f\n", 
				supermirror_flat_s_prefix, q,Qcm,m,W,arg,alpha,beta);
		supermirror_flat_dec_prefix();
		#endif

		return R0;
	}
	else {
		#if defined(DEBUG_sm_calc_Rm)
		printf("%s reflect from mirror q,Rm_vac_to_mir_at_plane = %5f,%5f, q> Qcm,m,W,arg,alpha,beta = q> %5f,%5f,%5f,%5f,%5f,%5f\n",
			supermirror_flat_s_prefix, q,R0*0.5*(1 - tanh(arg))*(1 - alpha*(q - Qc) + beta*(q - Qc)*(q - Qc)),Qcm,m,W,arg,alpha,beta);
		supermirror_flat_dec_prefix();
		#endif

		q -= Qc;
		return R0*0.5*(1 - tanh(arg))*(1 - alpha*q + beta*q*q);
	}
}

//Reflectivity at substrate surfaces
double sm_calc_Rs (RefractionParameters*subsurface, double vn_len) 
/******************************************************************************************************************************
calculates the reflectivity of substrate surface, Check if user select Rs to be 0 
If there is mirror coating, Rs only checks total reflection
uses: 
update:   
return: 
output: 	Rs
called by: 	sm_calc_surface_parameters 
calls: 
********************************************************************************************************************************/
{
//#define DEBUG_sm_calc_Rs
	#if defined(DEBUG_sm_calc_Rs)
	printf(	"%s void sm_calc_Rs (RefractionParameters*subsurface;, double vn_len) \n"
			"%s subsurface=%X, vn_len=%lf\n",
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, subsurface, vn_len);
	supermirror_flat_inc_prefix();
	#endif
	
	double Rs = 0;
	
	double q = 2 * vn_len * V2Q;
	double Qc_sub = subsurface->Qc_sub;
	if (fabs(q) > ZERO_THRESHOLD) {
		if ((subsurface->subsurface_type & sm_subsurface_type_total_refl ) == sm_subsurface_type_total_refl || 
			(subsurface->subsurface_type & sm_subsurface_type_refl ) == sm_subsurface_type_refl) {
			//has either total reflection from sm-coated substrate surface, 
			//or reflection from uncoated substrate surface
			if ((subsurface->subsurface_type & sm_subsurface_type_refl ) == sm_subsurface_type_refl) {
				//Uncoated substrate surface
				if (q <= Qc_sub) { 
					#if defined(DEBUG_sm_calc_Rs)
					printf("%s total reflection from substrate, q=%lg <= Qc_sub=%lg, return 1.\n", 
							supermirror_flat_s_prefix, q, Qc_sub);
							supermirror_flat_dec_prefix();
					#endif
					Rs = 1; 
				}
				else {
					double dd = sqrt(q*q - Qc_sub*Qc_sub);	
					dd = (q - dd) / (q + dd);	
					
					#if defined(DEBUG_sm_calc_Rs)
					printf("%s reflect from substrate q=%lg, Qc_sub=%lg [1/A], dd=sqrt(q^2-Qc_sub^2)=%lg, return [(q-dd)/(q+dd)]^2=%lg^2=%lg\n", 
							supermirror_flat_s_prefix, q, Qc_sub, sqrt(q*q - Qc_sub*Qc_sub), dd, dd*dd);
					#endif
					
					Rs = dd * dd;
				}
			}
			else {
				//sm-coated substrate surface, only total reflection
				Rs = q <= subsurface->Qc_sub? 1 : 0; 
			}
		}
	}
	
	#if defined(DEBUG_sm_calc_Rs)
	printf("%s Rs=% 7.4f\n",
			supermirror_flat_s_prefix, Rs);
	supermirror_flat_dec_prefix();
	#endif

	return Rs;
}

//refraction going through substrate surface
Coords sm_get_refracted_v (RefractionParameters*subsurface, Coords v_in, Coords fn, int going_inward_or_outward_of_sm) 
/******************************************************************************************************************************
Purpose:	calculate v refracted into sm_SubstrateSurfaceLayer, check if user selected "no refraction". 
uses:  		 
update: 	
return: 	
output:		v_out
called by: 	sm_calc_surface_parameters
calls: 		
********************************************************************************************************************************/
{
//#define DEBUG_sm_get_refracted_v
	#if defined(DEBUG_sm_get_refracted_v)
	printf(	"%s void sm_get_refracted_v (RefractionParameters*subsurface, Coords v_in, Coords fn, int going_inward_or_outward_of_sm)\n"
			"%s subsurface=%X, v_in=(%lf, %lf, %lf), fn=(%lf, %lf, %lf), going_inward_or_outward_of_sm=%d\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, subsurface, v_in.x, v_in.y,v_in.z, fn.x, fn.y,fn.z, going_inward_or_outward_of_sm);
	supermirror_flat_inc_prefix();
	#endif

	Coords v_out = v_in; //default: no refraction

	#if defined(DEBUG_sm_get_refracted_v)
	printf("%s subsurface->subsurface_type=%X, sm_subsurface_type_refract=%X, &=%X\n", supermirror_flat_s_prefix, 
	subsurface->subsurface_type, sm_subsurface_type_refract, subsurface->subsurface_type & sm_subsurface_type_refract);
	#endif
	
	if ((subsurface->subsurface_type & sm_subsurface_type_refract) == 0) {
		//no refraction by selection
		
		#if defined(DEBUG_sm_get_refracted_v)
		printf("%s no refraction by selection.\n", supermirror_flat_s_prefix);
		supermirror_flat_dec_prefix();
		supermirror_flat_dec_prefix();
		#endif

		return v_out;
	}

	double vn_len = coords_sp(v_in, fn); 
	
	if (fabs(vn_len) < ZERO_THRESHOLD) {
		//|vn_len| = 0, neutron flies along surface, no refraction.
		
		#if defined(DEBUG_sm_get_refracted_v)
		printf("%s |vn_len| = 0, neutron flies along surface, no refraction.\n", supermirror_flat_s_prefix);
				supermirror_flat_dec_prefix();
		supermirror_flat_dec_prefix();
		#endif

		return v_out;
	}

	//calculate material index of refraction
	double v_len_2 = coords_sp(v_in, v_in); 
	double one_minus_n_sub_square = subsurface->delta_n_2 / v_len_2; //1 - (n(substrate))^2, delta_n_2 = LambdaV_AA_m_s * LambdaV_AA_m_s * SLD / M_PI
	double sgn_vn = vn_len < 0? -1 : 1;
	double one_minus_n_from_over_n_to_square, n_from_over_n_to_square, v_len_2_minus_v2s_len_2;
	
	#if defined(DEBUG_sm_get_refracted_v)
	double delta_n_2 = (LambdaV_AA_m_s * LambdaV_AA_m_s / v_len_2) * subsurface->SLD / M_PI; //delta_n_2 = lambda^2 * SLD / M_PI
	#endif
	
	#if defined(DEBUG_sm_get_refracted_v)
	printf("%s n(substrate) = sqrt(1 - lambda^2*SLD/PI) = sqrt(1 - %lg) = %12.9f\n",
			supermirror_flat_s_prefix, subsurface->delta_n_2 / v_len_2, sqrt(1-one_minus_n_sub_square));
	#endif
	
	if (going_inward_or_outward_of_sm == going_inward) { 
		//going_inward
		//n_from=n(air)=1, n_to=n(substrate)
		//one_minus_n_from_over_n_to_square = 1-(1/(1-one_minus_n_sub_square)) = -one_minus_n_sub_square / (1-one_minus_n_sub_square)
		one_minus_n_from_over_n_to_square = -one_minus_n_sub_square/(1-one_minus_n_sub_square); 
		
		if (fabs(one_minus_n_from_over_n_to_square) > ZERO_THRESHOLD) {

			n_from_over_n_to_square = 1 - one_minus_n_from_over_n_to_square; 
			v_len_2_minus_v2s_len_2 = v_len_2*one_minus_n_from_over_n_to_square + vn_len*vn_len - one_minus_n_from_over_n_to_square*vn_len*vn_len;

			if (v_len_2_minus_v2s_len_2 >= 0) {
				//Now calculate refraction, refracted vn_len has same sign as incoming vn_len
				#if defined(DEBUG_sm_get_refracted_v)
				printf("%s v_len_2 * one_minus_n_from_over_n_to_square + n_from_over_n_to_square * vn_len * vn_len = %lg * %lg + %lg * (%lg)^2 ="
						"%lg + %lg * %lg = %lg --- vn_len = (sgn(vn_len)=%lg) * sqrt( (n_from_over_n_to_square=%lg) * (v_len_2_minus_v2s_len_2=%lg) ) = %lg\n", 
						supermirror_flat_s_prefix, v_len_2, one_minus_n_from_over_n_to_square, n_from_over_n_to_square, vn_len, v_len_2 * one_minus_n_from_over_n_to_square, n_from_over_n_to_square, vn_len * vn_len, v_len_2_minus_v2s_len_2, 
						sgn_vn, n_from_over_n_to_square, v_len_2_minus_v2s_len_2, sgn_vn * sqrt( n_from_over_n_to_square * v_len_2_minus_v2s_len_2)  );
				#endif

				vn_len = sgn_vn * sqrt( n_from_over_n_to_square * v_len_2_minus_v2s_len_2 );
				v_out = coords_add( coords_scale(coords_xp(coords_xp(fn, v_in), fn), n_from_over_n_to_square), coords_scale(fn, vn_len) ); //v = vs + vn

				#if defined(DEBUG_REF_LIB_CATCH_ANOMALY)
				if (v_out.z <= 0)  {
					printf("%s ERROR: vz = %f\n",v_out.z);
					printf("%s n(air)/n(substrate) = 1 / sqrt(1 - lambda^2*SLD/PI) = 1 / sqrt(1 - %lg) = %12.9f, n_from_over_n_to_square=%12.9f\n",
							supermirror_flat_s_prefix, subsurface->delta_n_2 / v_len_2, sqrt(n_from_over_n_to_square), n_from_over_n_to_square);
					printf("%s fn = (%lg,%lg,%lg)\n", supermirror_flat_s_prefix, fn.x, fn.y, fn.z);
					printf("%s v_len_2_minus_v2s_len_2 = v_len_2 - n_from_over_n_to_square*(v_len_2 - vn_len^2) = %lg - %lg*(%lg - (%lg)^2) = %12.9f\n", 
							supermirror_flat_s_prefix, v_len_2, n_from_over_n_to_square, v_len_2, vn_len, v_len_2_minus_v2s_len_2);
				}
				#endif

				#if defined(DEBUG_sm_get_refracted_v)
				Coords vs = coords_scale(coords_xp(coords_xp(fn, v_out), fn) , n_from_over_n_to_square);
				Coords vn = coords_scale(fn, coords_sp(fn, v_out));
				printf("%s after  v_out=vn+vs: (% 7.4f,% 7.4f,% 7.4f)=(% 7.4f,% 7.4f,% 7.4f)+(% 7.4f,% 7.4f,% 7.4f), vn_len=% 7.4f, vs_len=%10f, v_len=%10f, fn=(% 7.4f,% 7.4f,% 7.4f)\n",
						supermirror_flat_s_prefix, 
						v_out.x,v_out.y,v_out.z, vn.x,vn.y,vn.z, vs.x,vs.y,vs.z, 
						coords_len(vn), coords_len(vs), coords_len(v_out), fn.x,fn.y,fn.z);
				vs = coords_xp(coords_xp(fn, v_in), fn);
				vn = coords_scale(fn, coords_sp(fn, v_in));
				printf("%s before v_in=vn+vs: (% 7.4f,% 7.4f,% 7.4f)=(% 7.4f,% 7.4f,% 7.4f)+(% 7.4f,% 7.4f,% 7.4f), vn_len=% 7.4f, vs_len=%10f, v_len=%10f, fn=(% 7.4f,% 7.4f,% 7.4f)\n",
						supermirror_flat_s_prefix, 
						v_in.x,v_in.y,v_in.z, vn.x,vn.y,vn.z, vs.x,vs.y,vs.z, 
						coords_len(vn), coords_len(vs), coords_len(v_out), fn.x,fn.y,fn.z);
				printf("%s n=v_len_after/v_len_before=% 7.4f/% 7.4f=% 7.4f\n", supermirror_flat_s_prefix, coords_len(v_out), coords_len(v_in), coords_len(v_out)/coords_len(v_in));
				supermirror_flat_dec_prefix();
				#endif				
			}
			#if defined(DEBUG_sm_get_refracted_v) || defined(DEBUG_REF_LIB_CATCH_ANOMALY)
			else {
				//total reflection somehow sneak through!? Ignore. 
				printf("%s sm_Error: total reflection from substrate. Should not get here as q <= Qc_sub should have been checked." 
						"Found: n^2 * (v^2 - vn_len^2) = %lg * ((%lg)^2 - (%lg)^2) = %lg > v^2 = %lg!!! q=%lf, Qc_sub=%lf\n",
						supermirror_flat_s_prefix, n_from_over_n_to_square, sqrt(v_len_2), vn_len, n_from_over_n_to_square * (v_len_2 -vn_len * vn_len), v_len_2, 
						2 * fabs(coords_sp(v_in, fn)) * V2Q, subsurface->Qc_sub);
				printf("%s n(air)/n(substrate) = 1 / sqrt(1 - lambda^2*SLD/PI) = 1 / sqrt(1 - %lg) = %12.9f\n",
						supermirror_flat_s_prefix, subsurface->delta_n_2 / v_len_2, sqrt(n_from_over_n_to_square));
				printf("%s 1 - (n_from/n_to)^2 = 1 - (n(air)/n(substrate))^2 = %12.9f\n", supermirror_flat_s_prefix, one_minus_n_from_over_n_to_square);
				supermirror_flat_dec_prefix();
			}
			#endif

		}
		#if defined(DEBUG_sm_get_refracted_v)
		else {
			printf("%s n(air)/n(substrate) = 1, no refraction.\n", supermirror_flat_s_prefix);
			supermirror_flat_dec_prefix();
		}
		#endif

	}
	else { //going_outward
	
		//n_from=n(substrate), n_to=n(air)=1
		//one_minus_n_from_over_n_to_square = 1-((1-one_minus_n_sub_square)/1) = one_minus_n_sub_square
		one_minus_n_from_over_n_to_square = one_minus_n_sub_square;
		
		if (fabs(one_minus_n_from_over_n_to_square) > ZERO_THRESHOLD) {

			n_from_over_n_to_square = 1 - one_minus_n_from_over_n_to_square; //n^2
			v_len_2_minus_v2s_len_2 = v_len_2*one_minus_n_from_over_n_to_square + vn_len*vn_len - one_minus_n_from_over_n_to_square*vn_len*vn_len;

			if (v_len_2_minus_v2s_len_2 >= 0) {
				//Now calculate refraction, refracted vn_len has same sign as incoming vn_len
				#if defined(DEBUG_sm_get_refracted_v)
				printf(	"%s v_len_2 * one_minus_n_from_over_n_to_square + n_from_over_n_to_square * vn_len * vn_len = %lg * %lg + %lg * (%lg)^2 ="
						"%lg + %lg * %lg = %lg --- vn_len = (sgn(vn_len)=%lg) * sqrt( (n_from_over_n_to_square=%lg) * (v_len_2_minus_v2s_len_2=%lg) ) = %lg\n", 
						supermirror_flat_s_prefix, v_len_2, one_minus_n_from_over_n_to_square, n_from_over_n_to_square, vn_len, v_len_2 * one_minus_n_from_over_n_to_square, n_from_over_n_to_square, vn_len * vn_len, v_len_2_minus_v2s_len_2, 
						sgn_vn, n_from_over_n_to_square, v_len_2_minus_v2s_len_2, sgn_vn * sqrt( n_from_over_n_to_square * v_len_2_minus_v2s_len_2)  );
				#endif

				vn_len = sgn_vn * sqrt( n_from_over_n_to_square * v_len_2_minus_v2s_len_2 );
				v_out = coords_add( coords_scale(coords_xp(coords_xp(fn, v_in), fn), n_from_over_n_to_square), coords_scale(fn, vn_len) ); //v = vs + vn

				#if defined(DEBUG_REF_LIB_CATCH_ANOMALY)
				if (v_out.z <= 0)  {
					printf("%s ERROR: vz = %f\n",v_out.z);
					printf("%s n(substrate)/n(air) = sqrt(1 - lambda^2*SLD/PI) = sqrt(1 - %lg) / 1 = %12.9f, n_from_over_n_to_square=%12.9f\n",
							supermirror_flat_s_prefix, subsurface->delta_n_2 / v_len_2, sqrt(n_from_over_n_to_square), n_from_over_n_to_square);
					printf("%s fn = (%lg,%lg,%lg)\n", supermirror_flat_s_prefix, fn.x, fn.y, fn.z);
					printf("%s v_len_2_minus_v2s_len_2 = v_len_2 - n_from_over_n_to_square*(v_len_2 - vn_len^2) = %lg - %lg*(%lg - (%lg)^2) = %12.9f\n", 
							supermirror_flat_s_prefix, v_len_2, n_from_over_n_to_square, v_len_2, vn_len, v_len_2_minus_v2s_len_2);
				}
				#endif

				#if defined(DEBUG_sm_get_refracted_v)
				Coords vs = coords_scale(coords_xp(coords_xp(fn, v_out), fn) , n_from_over_n_to_square);
				Coords vn = coords_scale(fn, coords_sp(fn, v_out));
				printf("%s after  v_out=vn+vs: (% 7.4f,% 7.4f,% 7.4f)=(% 7.4f,% 7.4f,% 7.4f)+(% 7.4f,% 7.4f,% 7.4f), vn_len=% 7.4f, vs_len=%10f, v_len=%10f, fn=(% 7.4f,% 7.4f,% 7.4f)\n",
						supermirror_flat_s_prefix, 
						v_out.x,v_out.y,v_out.z, vn.x,vn.y,vn.z, vs.x,vs.y,vs.z, 
						coords_len(vn), coords_len(vs), coords_len(v_out), fn.x,fn.y,fn.z);
				vs = coords_xp(coords_xp(fn, v_in), fn);
				vn = coords_scale(fn, coords_sp(fn, v_in));
				printf("%s before v_in=vn+vs: (% 7.4f,% 7.4f,% 7.4f)=(% 7.4f,% 7.4f,% 7.4f)+(% 7.4f,% 7.4f,% 7.4f), vn_len=% 7.4f, vs_len=%10f, v_len=%10f, fn=(% 7.4f,% 7.4f,% 7.4f)\n",
						supermirror_flat_s_prefix, 
						v_in.x,v_in.y,v_in.z, vn.x,vn.y,vn.z, vs.x,vs.y,vs.z, 
						coords_len(vn), coords_len(vs), coords_len(v_out), fn.x,fn.y,fn.z);
				printf("%s n=v_len_after/v_len_before=% 7.4f/% 7.4f=% 7.4f\n", supermirror_flat_s_prefix, coords_len(v_out), coords_len(v_in), coords_len(v_out)/coords_len(v_in));
				supermirror_flat_dec_prefix();
				#endif

			}
			#if defined(DEBUG_sm_get_refracted_v) || defined(DEBUG_REF_LIB_CATCH_ANOMALY)
			else {
				//total reflection somehow sneak through!? Ignore. 
				printf("%s sm_Error: total reflection from substrate. Should not get here as q <= Qc_sub should have been checked." 
						"Found: n^2 * (v^2 - vn_len^2) = %lg * ((%lg)^2 - (%lg)^2) = %lg > v^2 = %lg!!! q=%lf, Qc_sub=%lf\n",
						supermirror_flat_s_prefix, n_from_over_n_to_square, sqrt(v_len_2), vn_len, n_from_over_n_to_square * (v_len_2 -vn_len * vn_len), v_len_2,
						2 * fabs(coords_sp(v_in, fn)) * V2Q, subsurface->Qc_sub);
				printf("%s n(substrate) = sqrt(1 - lambda^2*SLD/PI) = sqrt(1 - %lg) = %12.9f\n",
						supermirror_flat_s_prefix, subsurface->delta_n_2 / v_len_2, sqrt(1-subsurface->delta_n_2 / v_len_2));
				printf("%s 1 - (n_from/n_to)^2 = 1 - (n(substrate)/n(air))^2 = %12.9f\n", supermirror_flat_s_prefix, one_minus_n_from_over_n_to_square);
				supermirror_flat_dec_prefix();
			}
			#endif

		}
		#if defined(DEBUG_sm_get_refracted_v)
		else {
			printf("%s n(substrate) = n(air) = 1, no refraction.\n", supermirror_flat_s_prefix);
			supermirror_flat_dec_prefix();
		}
		#endif

	}
	
	return v_out; //calculation done
}

//refraction going through substrate surface
Coords sm_get_refracted_v_from_SLD (int has_refra, double SLD_from, double SLD_to, Coords v_in, Coords fn, int*total_reflection) 
/******************************************************************************************************************************
Purpose:	calculate v refracted into sm_SubstrateSurfaceLayer, check if user selected "no refraction". 
uses:  		 
update: 	
return: 	
output:		v_out
called by: 	sm_calc_surface_parameters
calls: 		
********************************************************************************************************************************/
{
//#define DEBUG_sm_get_refracted_v_from_SLD
	#if defined(DEBUG_sm_get_refracted_v_from_SLD)
	printf(	"%s void sm_get_refracted_v_from_SLD (int has_refra, double SLD_from, double SLD_to, Coords v_in, Coords fn)\n"
			"%s has_refra=%d, SLD_from=%lg, SLD_to=%lg, v_in=(%lf, %lf, %lf), fn=(%lf, %lf, %lf)\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, has_refra, SLD_from, SLD_to, v_in.x, v_in.y,v_in.z, fn.x, fn.y,fn.z);
	supermirror_flat_inc_prefix();
	#endif

	Coords v_out = v_in; //default: no refraction
	*total_reflection = 0;

	#if defined(DEBUG_sm_get_refracted_v_from_SLD)
	printf("%s has_refra=%d\n", supermirror_flat_s_prefix, has_refra);
	#endif
	
	if (has_refra == 0) {
		//no refraction by selection
		
		#if defined(DEBUG_sm_get_refracted_v_from_SLD)
		printf("%s no refraction by selection.\n", supermirror_flat_s_prefix);
		supermirror_flat_dec_prefix();
		supermirror_flat_dec_prefix();
		#endif

		return v_out;
	}

	double vn_len = coords_sp(v_in, fn); 
	
	if (fabs(vn_len) < ZERO_THRESHOLD) {
		//|vn_len| = 0, neutron flies along surface, no refraction.
		
		#if defined(DEBUG_sm_get_refracted_v_from_SLD)
		printf("%s |vn_len| = 0, neutron flies along surface, no refraction.\n", supermirror_flat_s_prefix);
				supermirror_flat_dec_prefix();
		supermirror_flat_dec_prefix();
		#endif

		return v_out;
	}

	//calculate material index of refraction
	double v_len_2 = coords_sp(v_in, v_in); 
	double one_minus_n_from_over_n_to_square = (LambdaV_AA_m_s * LambdaV_AA_m_s / v_len_2 / M_PI) * (SLD_from - SLD_to); //1 - (n(from->to))^2 = delta_n_2 = (LambdaV_AA_m_s * LambdaV_AA_m_s / v-square) * (SLD_to - SLD_from) / M_PI
	double sgn_vn = vn_len < 0? -1 : 1; 
	double n_from_over_n_to_square, v_len_2_minus_v2s_len_2; 
	
	#if defined(DEBUG_sm_get_refracted_v_from_SLD)
	printf("%s sqrt(n_from_over_n_to_square) = sqrt(1 - one_minus_n_from_over_n_to_square) = sqrt(1 - %lg) = sqrt(%12.9f) = %12.9f\n",
			supermirror_flat_s_prefix, one_minus_n_from_over_n_to_square, 1-one_minus_n_from_over_n_to_square, sqrt(1-one_minus_n_from_over_n_to_square));
	#endif
	
	if (fabs(one_minus_n_from_over_n_to_square) > ZERO_THRESHOLD) {

		n_from_over_n_to_square = 1 - one_minus_n_from_over_n_to_square; 
		v_len_2_minus_v2s_len_2 = v_len_2*one_minus_n_from_over_n_to_square + vn_len*vn_len - one_minus_n_from_over_n_to_square*vn_len*vn_len;

		if (v_len_2_minus_v2s_len_2 >= 0) {
			//Now calculate refraction, refracted vn_len has same sign as incoming vn_len
			#if defined(DEBUG_sm_get_refracted_v_from_SLD)
			printf("%s v_len_2 * one_minus_n_from_over_n_to_square + n_from_over_n_to_square * vn_len * vn_len = %lg * %lg + %lg * (%lg)^2 ="
					"%lg + %lg * %lg = %lg --- vn_len = (sgn(vn_len)=%lg) * sqrt( (n_from_over_n_to_square=%lg) * (v_len_2_minus_v2s_len_2=%lg) ) = %lg\n", 
					supermirror_flat_s_prefix, v_len_2, one_minus_n_from_over_n_to_square, n_from_over_n_to_square, vn_len, v_len_2 * one_minus_n_from_over_n_to_square, n_from_over_n_to_square, vn_len * vn_len, v_len_2_minus_v2s_len_2, 
					sgn_vn, n_from_over_n_to_square, v_len_2_minus_v2s_len_2, sgn_vn * sqrt( n_from_over_n_to_square * v_len_2_minus_v2s_len_2)  );
			#endif

			vn_len = sgn_vn * sqrt( n_from_over_n_to_square * v_len_2_minus_v2s_len_2 );
			v_out = coords_add( coords_scale(coords_xp(coords_xp(fn, v_in), fn), n_from_over_n_to_square), coords_scale(fn, vn_len) ); //v = vs + vn

			#if defined(DEBUG_REF_LIB_CATCH_ANOMALY)
			if (v_out.z <= 0)  {
				printf("%s ERROR: vz = %f\n",v_out.z);
				printf("%s sqrt(n_from_over_n_to_square) = sqrt(1 - one_minus_n_from_over_n_to_square) = sqrt(1 - %lg) = sqrt(%12.9f) = %12.9f\n",
						supermirror_flat_s_prefix, one_minus_n_from_over_n_to_square, 1-one_minus_n_from_over_n_to_square, sqrt(1-one_minus_n_from_over_n_to_square));
				printf("%s fn = (%lg,%lg,%lg)\n", supermirror_flat_s_prefix, fn.x, fn.y, fn.z);
				printf("%s v_len_2_minus_v2s_len_2 = v_len_2 - n_from_over_n_to_square*(v_len_2 - vn_len^2) = %lg - %lg*(%lg - (%lg)^2) = %12.9f\n", 
						supermirror_flat_s_prefix, v_len_2, n_from_over_n_to_square, v_len_2, vn_len, v_len_2_minus_v2s_len_2);
			}
			#endif

			#if defined(DEBUG_sm_get_refracted_v_from_SLD)
			Coords vs = coords_scale(coords_xp(coords_xp(fn, v_out), fn) , n_from_over_n_to_square);
			Coords vn = coords_scale(fn, coords_sp(fn, v_out));
			printf("%s refra: after  v_out=vn+vs: (% 7.4f,% 7.4f,% 7.4f)=(% 7.4f,% 7.4f,% 7.4f)+(% 7.4f,% 7.4f,% 7.4f), vn_len=% 7.4f, vs_len=%10f, v_len=%10f, fn=(% 7.4f,% 7.4f,% 7.4f)\n",
					supermirror_flat_s_prefix, 
					v_out.x,v_out.y,v_out.z, vn.x,vn.y,vn.z, vs.x,vs.y,vs.z, 
					coords_len(vn), coords_len(vs), coords_len(v_out), fn.x,fn.y,fn.z);
			vs = coords_xp(coords_xp(fn, v_in), fn);
			vn = coords_scale(fn, coords_sp(fn, v_in));
			printf("%s refra: before v_in=vn+vs: (% 7.4f,% 7.4f,% 7.4f)=(% 7.4f,% 7.4f,% 7.4f)+(% 7.4f,% 7.4f,% 7.4f), vn_len=% 7.4f, vs_len=%10f, v_len=%10f, fn=(% 7.4f,% 7.4f,% 7.4f)\n",
					supermirror_flat_s_prefix, 
					v_in.x,v_in.y,v_in.z, vn.x,vn.y,vn.z, vs.x,vs.y,vs.z, 
					coords_len(vn), coords_len(vs), coords_len(v_out), fn.x,fn.y,fn.z);
			printf("%s refra: n=v_len_after/v_len_before=% 7.4f/% 7.4f=% 12.9g\n", supermirror_flat_s_prefix, coords_len(v_out), coords_len(v_in), coords_len(v_out)/coords_len(v_in));
			supermirror_flat_dec_prefix();
			#endif				
		}
		else {
			//total reflection 
			//leave v_out = v_in, output total_reflection = 1.0
			*total_reflection = 1; 
			
			#if defined(DEBUG_sm_get_refracted_v_from_SLD) || defined(DEBUG_REF_LIB_CATCH_ANOMALY)
			printf("%s total reflection" 
					"Found: n^2 * (v^2 - vn_len^2) = %lg * ((%lg)^2 - (%lg)^2) = %lg > v^2 = %lg\n",
					supermirror_flat_s_prefix, n_from_over_n_to_square, sqrt(v_len_2), vn_len, n_from_over_n_to_square * (v_len_2 -vn_len * vn_len), v_len_2);
			printf("%s sqrt(n_from_over_n_to_square) = sqrt(1 - one_minus_n_from_over_n_to_square) = sqrt(1 - %lg) = sqrt(%12.9f) = %12.9f\n",
					supermirror_flat_s_prefix, one_minus_n_from_over_n_to_square, 1-one_minus_n_from_over_n_to_square, sqrt(1-one_minus_n_from_over_n_to_square));
			supermirror_flat_dec_prefix();
			#endif
		}

	}
	#if defined(DEBUG_sm_get_refracted_v_from_SLD)
	else {
		printf("%s SLD the same, no refraction.\n", supermirror_flat_s_prefix);
		supermirror_flat_dec_prefix();
	}
	#endif

	return v_out; //calculation done
}

//calculate Rm, Rs, v-inward/outward at mirror and substrate surfaces
void sm_calc_surface_parameters(SimState*state, Supermirror*sm, int going_inward_or_outward_of_sm) 
/******************************************************************************************************************************
Function "sm_calc_surface_parameters" calculates surface parameters.
The function is called once per sampling, after neutron reaches a surface for the 1st time. 
Has mirror coating: Rs_vac_to_sub_at_plane=total reflection below Qc_sub only, Rs_sub_to_vac_at_plane=0
No mirror coating, substrate surface:  Calculate both Rs_vac_to_sub_at_plane and Rs_sub_to_vac_at_plane
NoSurfaceBoundary: Rm=Rs=0
uses: 		state->	plane, fn, v, v_len, vn_len, ws
update: 	state-> Rm_vac_to_mir_at_plane, Rm_sub_to_mir_at_plane, 
					v_in_vac_inward_at_plane, v_in_vac_outward_at_plane, 
					v_in_vac_len_at_plane, vn_in_vac_len_at_plane,
					Rs_sub_to_vac_at_plane, Rs_vac_to_sub_at_plane, 
					v_in_sub_inward_at_plane, v_in_sub_inward_len_at_plane, vn_in_sub_inward_len_at_plane, 
					v_in_sub_outward_at_plane,  v_in_sub_outward_len_at_plane, vn_in_sub_outward_len_at_plane,
					v, v_len, vn_len, ws, last_time, last_point, last_plane, layer, location, event
return: 	
Output:		
called by: 	sm_external_intersect - 1.4 sm_SubstrateSurfaceLayer(mirror to substrate)
			sm_internal_intersect - n.2 sm_SubstrateSurfaceLayer(substract to mirror)
calles: 	sm_calc_surface_parameters
********************************************************************************************************************************/
{
//#define DEBUG_sm_calc_surface_parameters
	#if defined(DEBUG_sm_calc_surface_parameters)
	printf(	"%s void sm_calc_surface_parameters (SimState*state, Supermirror*sm, int going_inward_or_outward_of_sm)\n"
			"%s state=%X, sm=%X, going_inward_or_outward_of_sm=%s(%d)\n",
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, state, sm, 
			((sm->proc).proc)[going_inward_or_outward_of_sm],going_inward_or_outward_of_sm);
	supermirror_flat_inc_prefix();
	#endif

//////Calculate set_surface_parameters once for each trajectory. 
	if (state->set_surface_parameters != 0) {
		#if defined(DEBUG_sm_calc_surface_parameters)
		printf("%s sm_calc_surface_parameters(..) already done, return.\n\n", supermirror_flat_s_prefix);
		#endif
		
		return;
	}
	
	state->set_surface_parameters = 1;
	
	int plane, i;
	Coords v_in, fn;
	plane = state->plane;
	v_in = state->v;
	fn = state->fn;
	
	#if defined(DEBUG_sm_calc_surface_parameters)
	printf("%s plane=%d\n", supermirror_flat_s_prefix, plane);
	#endif
	
	//First determine substrate surface parameters, then use them for mirror surface parameters
	RefractionParameters*subsurface[2];
	subsurface[plane] = &(((sm->mat).subsurface)[plane]);
	subsurface[1-plane] = &(((sm->mat).subsurface)[1-plane]);
	
	double layer_next_to_sub_SLD[2];
	layer_next_to_sub_SLD[0] = 0; //air/vacuum
	layer_next_to_sub_SLD[1] = 0; //air/vacuum
	
	int iplane, ispin;

	#if defined(DEBUG_sm_calc_surface_parameters)
	printf("sm_calc_surface_parameters: subsurface[0,1]->subsurface_type = %X, %X\n", (subsurface[0])->subsurface_type, (subsurface[1])->subsurface_type);
	#endif

			
	if (going_inward_or_outward_of_sm == going_inward) { 
		//v_in going inward to substrate. 
		//neutron going from outside and impinge on surface 
		state->v_in_vac_inward_at_plane[plane] = v_in; 
		state->v_in_vac_outward_at_plane[plane] = coords_mirror(v_in, fn); 
		
		if (((subsurface[plane])->subsurface_type & sm_subsurface_type_refract) == sm_subsurface_type_refract) {
			//refract at entrance plane 
			
			#if defined(DEBUG_sm_calc_surface_parameters)
			printf("sm_calc_surface_parameters: enter at %s mirror, from outside going inward, refract at entrance plane = %d\n", sm->name, plane);
			#endif

			state->v_in_sub_inward_at_plane[plane] = sm_get_refracted_v (subsurface[plane], state->v_in_vac_inward_at_plane[plane], fn, going_inward);
			state->v_in_sub_outward_at_plane[plane] = coords_mirror(state->v_in_sub_inward_at_plane[plane], fn); 

			if (strcmp(((sm->mat).mir[plane][0]).name,"FeSiPlus") == 0) {
				layer_next_to_sub_SLD[0] = 1.31049631612838E-05; //Fe+
				layer_next_to_sub_SLD[1] = 2.94314422355161E-06; //Fe-
			}
			if (strcmp(((sm->mat).mir[plane][0]).name,"NiTi") == 0) {
				layer_next_to_sub_SLD[0] = layer_next_to_sub_SLD[1] = 9.41806009272869E-06; //Ni
			}
			for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
				state->v_sub_to_mir_at_plane[plane][ispin] = sm_get_refracted_v_from_SLD (1, 
																(((sm->mat).sub).SLD), layer_next_to_sub_SLD[ispin], 
																state->v_in_sub_outward_at_plane[plane], fn, 
																&(state->Rm_sub_to_mir_total_refl_at_plane[plane][ispin])); 
			}
			
		}
		else {
			//not refract at entrance plane 
			
			#if defined(DEBUG_sm_calc_surface_parameters)
			printf("sm_calc_surface_parameters: enter at %s mirror, from outside going inward, not refract at entrance plane = %d\n", sm->name, plane);
			#endif

			state->v_in_sub_inward_at_plane[plane] = state->v_in_vac_inward_at_plane[plane];
			state->v_in_sub_outward_at_plane[plane] = coords_mirror(state->v_in_sub_inward_at_plane[plane], fn); 

			for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
				state->v_sub_to_mir_at_plane[plane][ispin] = state->v_in_sub_outward_at_plane[plane];
			}
		}
		
		state->v_in_sub_inward_at_plane[1-plane] = state->v_in_sub_outward_at_plane[plane];
		state->v_in_sub_outward_at_plane[1-plane] = state->v_in_sub_inward_at_plane[plane];

		if (((subsurface[1-plane])->subsurface_type & sm_subsurface_type_refract) == sm_subsurface_type_refract) {
			//refract at exit plane 
			
			#if defined(DEBUG_sm_calc_surface_parameters)
			printf("sm_calc_surface_parameters: enter at %s mirror, from inside going outward, refract at exit 1-plane = %d\n", sm->name, 1-plane);
			#endif

			state->v_in_vac_outward_at_plane[1-plane] = sm_get_refracted_v (subsurface[1-plane], state->v_in_sub_outward_at_plane[1-plane], fn, going_outward); 
			state->v_in_vac_inward_at_plane[1-plane] = coords_mirror(state->v_in_vac_outward_at_plane[1-plane], fn);

			if (strcmp(((sm->mat).mir[1-plane][0]).name,"FeSiPlus") == 0) {
				layer_next_to_sub_SLD[0] = 1.31049631612838E-05; //Fe+
				layer_next_to_sub_SLD[1] = 2.94314422355161E-06; //Fe-
			}
			if (strcmp(((sm->mat).mir[1-plane][0]).name,"NiTi") == 0) {
				layer_next_to_sub_SLD[0] = layer_next_to_sub_SLD[1] = 9.41806009272869E-06; //Ni
			}
			for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
				state->v_sub_to_mir_at_plane[1-plane][ispin] = sm_get_refracted_v_from_SLD (1, 
																(((sm->mat).sub).SLD), layer_next_to_sub_SLD[ispin], 
																state->v_in_sub_outward_at_plane[1-plane], fn, 
																&(state->Rm_sub_to_mir_total_refl_at_plane[1-plane][ispin])); 
			}
		}
		else {
			//not refract at exit plane 
			
			#if defined(DEBUG_sm_calc_surface_parameters)
			printf("sm_calc_surface_parameters: enter at %s mirror, from inside going outward, not refract at exit 1-plane = %d\n", sm->name, 1-plane);
			#endif

			state->v_in_vac_outward_at_plane[1-plane] = state->v_in_sub_outward_at_plane[1-plane];
			state->v_in_vac_inward_at_plane[1-plane] = coords_mirror(state->v_in_vac_outward_at_plane[1-plane], fn); 

			for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
				state->v_sub_to_mir_at_plane[1-plane][ispin] = state->v_in_sub_outward_at_plane[1-plane];
			}
		}
				
	}
	else { 
		//v_in going outward from substrate. 
		//neutron enters from substrate edge, going outward when impinge on surface 
		state->v_in_sub_outward_at_plane[plane] = v_in; 
		state->v_in_sub_inward_at_plane[plane] = coords_mirror(v_in, fn); 
		
		if (((subsurface[plane])->subsurface_type & sm_subsurface_type_refract) == sm_subsurface_type_refract) {
			//refract at plane from inside going outward
			
			#if defined(DEBUG_sm_calc_surface_parameters)
			printf("sm_calc_surface_parameters: enter at edge %s, going from inside going outward, refract at exit plane = %d\n", sm->name, plane);
			#endif

			state->v_in_vac_outward_at_plane[plane] = sm_get_refracted_v (subsurface[plane], state->v_in_sub_outward_at_plane[plane], fn, going_outward);
			state->v_in_vac_inward_at_plane[plane] = coords_mirror(state->v_in_vac_outward_at_plane[plane], fn);
			
			if (strcmp(((sm->mat).mir[plane][0]).name,"FeSiPlus") == 0) {
				layer_next_to_sub_SLD[0] = 1.31049631612838E-05; //Fe+
				layer_next_to_sub_SLD[1] = 2.94314422355161E-06; //Fe-
			}
			if (strcmp(((sm->mat).mir[plane][0]).name,"NiTi") == 0) {
				layer_next_to_sub_SLD[0] = layer_next_to_sub_SLD[1] = 9.41806009272869E-06; //Ni
			}
			for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
				state->v_sub_to_mir_at_plane[plane][ispin] = sm_get_refracted_v_from_SLD (1, 
																(((sm->mat).sub).SLD), layer_next_to_sub_SLD[ispin], 
																state->v_in_sub_outward_at_plane[plane], fn, 
																&(state->Rm_sub_to_mir_total_refl_at_plane[plane][ispin]));
			}
		}
		else {
			//not refract at plane 
			
			#if defined(DEBUG_sm_calc_surface_parameters)
			printf("sm_calc_surface_parameters: enter at %s edge, going from inside going outward, not refract at plane = %d\n", sm->name, plane);
			#endif

			state->v_in_vac_outward_at_plane[plane] = state->v_in_sub_outward_at_plane[plane];
			state->v_in_vac_inward_at_plane[plane] = coords_mirror(state->v_in_vac_outward_at_plane[plane], fn);
			
			for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
				state->v_sub_to_mir_at_plane[plane][ispin] = state->v_in_sub_outward_at_plane[plane];
			}
		}

		state->v_in_sub_inward_at_plane[1-plane] = state->v_in_sub_outward_at_plane[plane];
		state->v_in_sub_outward_at_plane[1-plane] = state->v_in_sub_inward_at_plane[plane];

		if (((subsurface[1-plane])->subsurface_type & sm_subsurface_type_refract) == sm_subsurface_type_refract) {
			//refract at 1-plane from inside going outward
			
			#if defined(DEBUG_sm_calc_surface_parameters)
			printf("sm_calc_surface_parameters: enter at %s edge, going from inside going outward, refract at exit 1-plane = %d\n", sm->name, 1-plane);
			#endif

			state->v_in_vac_outward_at_plane[1-plane] = sm_get_refracted_v (subsurface[1-plane], state->v_in_sub_outward_at_plane[1-plane], fn, going_outward);
			state->v_in_vac_inward_at_plane[1-plane] = coords_mirror(state->v_in_vac_outward_at_plane[1-plane], fn);
			
			if (strcmp(((sm->mat).mir[1-plane][0]).name,"FeSiPlus") == 0) {
				layer_next_to_sub_SLD[0] = 1.31049631612838E-05; //Fe+
				layer_next_to_sub_SLD[1] = 2.94314422355161E-06; //Fe-
			}
			if (strcmp(((sm->mat).mir[1-plane][0]).name,"NiTi") == 0) {
				layer_next_to_sub_SLD[0] = layer_next_to_sub_SLD[1] = 9.41806009272869E-06; //Ni
			}
			
			for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
				state->v_sub_to_mir_at_plane[1-plane][ispin] = sm_get_refracted_v_from_SLD (1, 
																(((sm->mat).sub).SLD), layer_next_to_sub_SLD[ispin], 
																state->v_in_sub_outward_at_plane[1-plane], fn, 
																&(state->Rm_sub_to_mir_total_refl_at_plane[1-plane][ispin]));
			}
		}
		else {
			//not refract at plane 
			
			#if defined(DEBUG_sm_calc_surface_parameters)
			printf("sm_calc_surface_parameters: enter at %s edge, going from inside going outward, not refract at exit 1-plane = %d\n", sm->name, 1-plane);
			#endif

			state->v_in_vac_outward_at_plane[1-plane] = state->v_in_sub_outward_at_plane[1-plane];
			state->v_in_vac_inward_at_plane[1-plane] = coords_mirror(state->v_in_vac_outward_at_plane[1-plane], fn);
			
			for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
				state->v_sub_to_mir_at_plane[1-plane][ispin] = state->v_in_sub_outward_at_plane[1-plane];
			}
		}
	}
	
	for (iplane = 0; iplane < SM_Num_Mirror_Planes; iplane++) {
		//update v_mir..len & vn_mir..len
		state->v_in_vac_len_at_plane[iplane] = coords_len(state->v_in_vac_inward_at_plane[iplane]);
		state->vn_in_vac_len_at_plane[iplane] = fabs(coords_sp(state->v_in_vac_inward_at_plane[iplane], fn));
			
		//update v_sub..len & vn_sub..len
		state->v_in_sub_inward_len_at_plane[iplane] = coords_len(state->v_in_sub_inward_at_plane[iplane]);
		state->vn_in_sub_inward_len_at_plane[iplane] = fabs(coords_sp(state->v_in_sub_inward_at_plane[iplane], fn));
		state->v_in_sub_outward_len_at_plane[iplane] = coords_len(state->v_in_sub_outward_at_plane[iplane]);
		state->vn_in_sub_outward_len_at_plane[iplane] = fabs(coords_sp(state->v_in_sub_outward_at_plane[iplane], fn));
		
		for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
			state->v_sub_to_mir_len_at_plane[iplane][ispin] = coords_len(state->v_sub_to_mir_at_plane[iplane][ispin]);
			state->vn_sub_to_mir_len_at_plane[iplane][ispin] = fabs(coords_sp(state->v_sub_to_mir_at_plane[iplane][ispin], fn));
		}
	}
		
	//update Rs[plane]
	for (iplane = 0; iplane < SM_Num_Mirror_Planes; iplane++) {
		//from outside: Rs from air/vacuum to substrate, before refraction - refraction already included in reflectivity profile
		(state->Rs_vac_to_sub_at_plane)[iplane] = sm_calc_Rs (subsurface[iplane], state->vn_in_vac_len_at_plane[iplane]);
		//from inside: Rs from substrate to air/vacuum, after refraction - refraction not included in reflectivity profile
		(state->Rs_sub_to_vac_at_plane)[iplane] = sm_calc_Rs (subsurface[iplane], state->vn_in_vac_len_at_plane[iplane]); 
	}
		
	//update Rm[plane][spin]
	for (iplane = 0; iplane < SM_Num_Mirror_Planes; iplane++) {
		for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
			(state->Rm_vac_to_mir_at_plane)[iplane][ispin] = 0;
			(state->Rm_sub_to_mir_at_plane)[iplane][ispin] = 0;
		}
	}
	double q;
	ReflectionParameters *mir[SM_Num_Spin_States],*refl;
	
	for (iplane = 0; iplane < 2; iplane++) {

		for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
			mir[ispin] = &((((sm->mat).mir)[iplane])[ispin]);
		}
		
		if ((mir[0]->refl_type & sm_refl_type_refl) == sm_refl_type_refl && 
			(mir[1]->refl_type & sm_refl_type_refl) == sm_refl_type_refl) {	
			
			//from outside: Rm from air/vacuum to mirror, before refraction - refraction already included in reflectivity profile
			q = 2 * state->vn_in_vac_len_at_plane[iplane] * V2Q;
			if (fabs(q) > ZERO_THRESHOLD) {
				for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
					refl = mir[ispin];
					(state->Rm_vac_to_mir_at_plane)[iplane][ispin] = sm_calc_Rm(q, refl->Qc, refl->R0, refl->alpha, refl->m, refl->W, refl->beta);
				}
			}
			
			//from inside: Rm from substrate to mirror, after refraction - refraction not included in reflectivity profile
			for (ispin = 0; ispin < SM_Num_Spin_States; ispin++) {
				if (state->Rm_sub_to_mir_total_refl_at_plane[plane][ispin] == 1) {
					(state->Rm_sub_to_mir_at_plane)[iplane][ispin] = refl->R0;
				}
				else {
					q = 2 * state->vn_sub_to_mir_len_at_plane[iplane][ispin] * V2Q;
					if (fabs(q) > ZERO_THRESHOLD) {
						refl = mir[ispin];
						(state->Rm_sub_to_mir_at_plane)[iplane][ispin] = sm_calc_Rm(q, refl->Qc, refl->R0, refl->alpha, refl->m, refl->W, refl->beta);
					}
				}
			}
		}
	}
		
	state->set_surface_parameters = 1;
	
	#if defined(DEBUG_sm_calc_surface_parameters)
	if (going_inward_or_outward_of_sm == going_inward) { //going_inward
		printf("%s going inward at plane %d\n", supermirror_flat_s_prefix, plane);
	}
	else {
		printf("%s going outward at plane %d\n", supermirror_flat_s_prefix, plane);
	}
	for (i=0; i<2; i++) {
		printf("%s v_in_sub_inward_at_plane[plane=%d]=(% 7.4f,% 7.4f,% 7.4f), |v|=% 7.4f, vn=% 7.4f\n", 
				supermirror_flat_s_prefix, 
				i, 	
				(state->v_in_sub_inward_at_plane[i]).x,(state->v_in_sub_inward_at_plane[i]).y,(state->v_in_sub_inward_at_plane[i]).z, 
				state->v_in_sub_inward_len_at_plane[i], state->vn_in_sub_inward_len_at_plane[i]
				);			
		printf("%s v_in_sub_outward_at_plane[plane=%d]=(% 7.4f,% 7.4f,% 7.4f), |v|=% 7.4f, vn=% 7.4f\n", 
				supermirror_flat_s_prefix, 
				i, 
				(state->v_in_sub_outward_at_plane[i]).x,(state->v_in_sub_outward_at_plane[i]).y,(state->v_in_sub_outward_at_plane[i]).z, 
				state->v_in_sub_outward_len_at_plane[i], state->vn_in_sub_outward_len_at_plane[i]
				);			

		printf("%s (state->Rs_sub_to_vac_at_plane)[plane=%d]=% 7.4f\n", 
				supermirror_flat_s_prefix, 
				i, (state->Rs_sub_to_vac_at_plane)[i]
				);			
		printf("%s (state->Rs_vac_to_sub_at_plane)[plane=%d]=% 7.4f\n", 
				supermirror_flat_s_prefix, 
				i, (state->Rs_vac_to_sub_at_plane)[i]
				);			

		printf("%s v_in_vac_inward_at_plane[plane=%d]=(% 7.4f,% 7.4f,% 7.4f), |v|=% 7.4f, vn=% 7.4f\n", 
				supermirror_flat_s_prefix, 
				i, 
				(state->v_in_vac_inward_at_plane[i]).x,(state->v_in_vac_inward_at_plane[i]).y,(state->v_in_vac_inward_at_plane[i]).z, 
				state->v_in_vac_len_at_plane[i], state->vn_in_vac_len_at_plane[i]
				);			
		printf("%s v_in_vac_outward_at_plane[plane=%d]=(% 7.4f,% 7.4f,% 7.4f), |v|=% 7.4f, vn=% 7.4f\n", 
				supermirror_flat_s_prefix, 
				i, 
				(state->v_in_vac_outward_at_plane[i]).x,(state->v_in_vac_outward_at_plane[i]).y,(state->v_in_vac_outward_at_plane[i]).z, 
				state->v_in_vac_len_at_plane[i], state->vn_in_vac_len_at_plane[i]
				);			

		printf("%s Rm[plane=%d][+/-]=(% 7.4f,% 7.4f)\n",
				supermirror_flat_s_prefix, 
				i, (state->Rm_vac_to_mir_at_plane)[i][0], (state->Rm_vac_to_mir_at_plane)[i][1]
				);
	}
	supermirror_flat_dec_prefix();
	#endif

} 

/************************************************************/
/* Reflection by mirror surface 							*/
/* Reflectivity Rm is calculated once for each trajectory 	*/
/************************************************************/
int sm_reflect_or_transmit_at_mirror (SimState*state, Supermirror*sm, int going_inward_or_outward_of_sm, int ignore_or_keep_reflection) 
/******************************************************************************************************************************
uses: 		state->	plane, fn, v, v_len, vn_len, ws, t, p, 
					Rm_vac_to_mir_at_plane, Rm_sub_to_mir_at_plane,
					v_in_vac_inward_at_plane, v_in_vac_outward_at_plane, v_in_vac_len_at_plane, vn_in_vac_len_at_plane
update: 	state-> v, v_len, vn_len, ws, s, last_time, last_point, last_plane, layer, location, event
return: 	sm_Reflected, sm_Transmitted, sm_Error.
output:		
called by: 	sm_external_intersect - 1.2 sm_MirrorLayer(external to mirror)
calls: 		
********************************************************************************************************************************/
{
//define DEBUG_sm_reflect_or_transmit_at_mirror
	#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
	printf(	"%s int sm_reflect_or_transmit_at_mirror (SimState*state, Supermirror*sm, int going_inward_or_outward_of_sm, int ignore_or_keep_reflection)\n"
			"%s state=%X, sm=%X, going_inward_or_outward_of_sm=%s(%d), ignore_or_keep_reflection=%s(%d)\n",
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, state, sm, 
			((sm->proc).proc)[going_inward_or_outward_of_sm],going_inward_or_outward_of_sm,
			((sm->proc).proc)[ignore_or_keep_reflection],ignore_or_keep_reflection);
	supermirror_flat_inc_prefix();
	#endif

	state->layer = sm_MirrorLayer; 
	
	int plane = state->plane;

	double Rm_plus, Rm_minus;
	double *ws = state->ws, ws_sum, ws_boundary, ws_rand;
	int outcome, outcome_detail_1, outcome_detail_2=-1; 
	
	double L_abs, L_inc; //cm
	double coeff_attn_mir;
	double path_length;
	double T_attn_mir = 1;
	if (strcmp(((sm->mat).mir[plane][0]).name,"FeSiPlus") == 0) {
		//Fe attenuation
		L_abs = 8.27240177685387E+00; L_inc = 2.959533258746990E+01; //cm
		coeff_attn_mir = LambdaV_AA_m_s / state->v_len / L_abs + 1 / L_inc;
		path_length = 1.7442375926495E-01 * pow( ((sm->mat).mir[plane][0]).m, 2.76940645) * state->v_len / fabs(coords_sp(state->v, state->fn)); //micron
		T_attn_mir *= exp( -coeff_attn_mir * path_length * 1E-4); // 1/micron * cm * dimension correction

		//Si attenuation
		L_abs = 2.105599065218980E+02; L_inc = 1.00131529414229E+04; //cm
		coeff_attn_mir = LambdaV_AA_m_s / state->v_len / L_abs + 1 / L_inc;
		path_length = 7.56293998558167E-02 * pow( ((sm->mat).mir[plane][0]).m, 3.281668545) * state->v_len / fabs(coords_sp(state->v, state->fn)); //micron
		T_attn_mir *= exp( -coeff_attn_mir * path_length * 1E-4); // 1/micron * cm * dimension correction
			
		////Fe Si combined attenuation
		//L_abs = 1.59183280787096E+01; L_inc = 5.90144149006447E+01; //cm
		//coeff_attn_mir = LambdaV_AA_m_s / state->v_len / L_abs + 1 / L_inc;
		//path_length = 2.74016555354710E-01 * pow( ((sm->mat).mir[plane][0]).m, 3) * state->v_len / fabs(coords_sp(state->v, state->fn)); //micron
		//T_attn_mir = exp( -coeff_attn_mir * path_length * 1E-4); // 1/micron * cm * dimension correction

		#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
		printf("sm=%s plane=%d, lambda=%lg, m=%lg, path=%lg micron, attn_length=%lg mm, T_attn_mir = %le\n", 
				sm->name, plane, LambdaV_AA_m_s / state->v_len, ((sm->mat).mir[plane][0]).m, 
				path_length, 1/coeff_attn_mir, T_attn_mir);
		#endif
	}
	else if (strcmp(((sm->mat).mir[plane][0]).name,"NiTi") == 0) {
		L_abs = 4.75994751526319E+00; L_inc = 3.13385891272540E+00; //cm
		coeff_attn_mir = LambdaV_AA_m_s / state->v_len / L_abs + 1 / L_inc;
		path_length = 1.47984998658286E-01 * pow( ((sm->mat).mir[plane][0]).m, 3) * state->v_len / fabs(coords_sp(state->v, state->fn)); //micron
		T_attn_mir = exp( -coeff_attn_mir * path_length * 1E-4); // 1/micron * cm * dimension correction
			
		#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
		printf("sm=%s plane=%d, lambda=%lg, m=%lg, path=%lg micron, attn_length=%lg mm, T_attn_mir = %le\n", 
				sm->name, plane, LambdaV_AA_m_s / state->v_len, ((sm->mat).mir[plane][0]).m, 
				path_length, 1/coeff_attn_mir, T_attn_mir);
		#endif
	}

	
	if (going_inward_or_outward_of_sm == going_inward) { //going_inward
		
		Rm_plus  = ignore_or_keep_reflection == ignore_reflection ? 0 : (state->Rm_vac_to_mir_at_plane)[plane][0];
		Rm_minus = ignore_or_keep_reflection == ignore_reflection ? 0 : (state->Rm_vac_to_mir_at_plane)[plane][1];

		#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
		printf("%s Rm[plane=%d][+/-]=(% 7.4f,% 7.4f)\n",
				supermirror_flat_s_prefix, plane, Rm_plus, Rm_minus);
		supermirror_flat_dec_prefix();
		#endif
		
		//weight range: reflected-out = [0, ws_boundary), transmitted-in = [ws_boundary, 1)
		ws_boundary  = (Rm_plus * ws[0] + Rm_minus * ws[1]) / (ws[0] + ws[1]);
		ws_rand = rand01();
		
		#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
		printf("%s going_inward: mcget_run_num()=%d, ws=(% 7.4f,% 7.4f)=% 7.4f, Rm=(%lg, %lg), ws_boundary=%lg, ws_rand=% 7.4f, reflect-out=[0 to % 7.4f],transmit-in=(% 7.4f to 1]\n",
				supermirror_flat_s_prefix, mcget_run_num(), 
				ws[0],ws[1],ws[0]+ws[1], Rm_plus,Rm_minus, ws_boundary, ws_rand, ws_boundary, ws_boundary);
		#endif
	
		//check if the outcome is reflect out or transmit through at interface
		if (ws_boundary > 0 && ws_rand <= ws_boundary) {
			//from outside substrate, reflected out
			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("%s v=(% 7.4f,% 7.4f,% 7.4f) towards substrate, reflected out at mirror =>",
					supermirror_flat_s_prefix,
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
			
			outcome = sm_Reflected;
			outcome_detail_1 = sm_ReflectedOutward;
			if (ws_boundary == 0) outcome_detail_2 = sm_TotalReflected;
			
			state->v = state->v_in_vac_outward_at_plane[plane];
			state->v_len = state->v_in_vac_len_at_plane[plane];
			state->vn_len = state->vn_in_vac_len_at_plane[plane];

			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("v=(% 7.4f,% 7.4f,% 7.4f)\n",
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
		}
		else {
			//from outside substrate, transmitted in
			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("%s v=(% 7.4f,% 7.4f,% 7.4f) towards substrate, transmitted in through mirror =>",
					supermirror_flat_s_prefix,
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
			
			outcome = sm_Transmitted;
			outcome_detail_1 = sm_TransmittedInward;
			
			state->v = state->v_in_vac_inward_at_plane[plane];
			state->v_len = state->v_in_vac_len_at_plane[plane];
			state->vn_len = state->vn_in_vac_len_at_plane[plane];

			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("v=(% 7.4f,% 7.4f,% 7.4f)\n",
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
		}
	}
	else { //going_outward
		
		Rm_plus  = ignore_or_keep_reflection == ignore_reflection ? 0 : (state->Rm_sub_to_mir_at_plane)[plane][0];
		Rm_minus = ignore_or_keep_reflection == ignore_reflection ? 0 : (state->Rm_sub_to_mir_at_plane)[plane][1];

		#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
		printf("%s Rm[plane=%d][+/-]=(% 7.4f,% 7.4f)\n",
				supermirror_flat_s_prefix, plane, Rm_plus, Rm_minus);
		supermirror_flat_dec_prefix();
		#endif
		
		//weight range: reflected-in = [0, ws_boundary), transmitted-out = [ws_boundary, 1)
		ws_boundary = (Rm_plus * ws[0] + Rm_minus * ws[1]) / (ws[0] + ws[1]);
		ws_rand = rand01();
		
		#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
		printf("%s going_outward: mcget_run_num()=%d, ws=(% 7.4f,% 7.4f)=% 7.4f, Rm=(%lg, %lg), ws_boundary=%lg, ws_rand=% 7.4f, reflect-in=[0 to % 7.4f],transmit-out=(% 7.4f to 1]\n",
				supermirror_flat_s_prefix, mcget_run_num(), 
				ws[0],ws[1],ws[0]+ws[1], Rm_plus,Rm_minus, ws_boundary, ws_rand, ws_boundary, ws_boundary);
		#endif
	
		//check if the outcome is reflect back in or transmit out at interface
		if (ws_boundary > 0 && ws_rand <= ws_boundary) {
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("%s v=(% 7.4f,% 7.4f,% 7.4f) away from substrate, reflected back in at mirror =>", 
					supermirror_flat_s_prefix,
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
			
			outcome = sm_Reflected;
			outcome_detail_1 = sm_ReflectedInward;
			if (Rm_plus == 1 && Rm_minus == 1) outcome_detail_2 = sm_TotalReflected;
			
			state->v = state->v_in_vac_inward_at_plane[plane];
			state->v_len = state->v_in_vac_len_at_plane[plane];
			state->vn_len = state->vn_in_vac_len_at_plane[plane];

			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("v=(% 7.4f,% 7.4f,% 7.4f)\n",
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
		}
		else {
			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("%s v=(% 7.4f,% 7.4f,% 7.4f) away from substrate, transmitted out through mirror =>",
					supermirror_flat_s_prefix,
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
			
			outcome = sm_Transmitted;
			outcome_detail_1 = sm_TransmittedOutward;
			
			state->v = state->v_in_vac_outward_at_plane[plane];
			state->v_len = state->v_in_vac_len_at_plane[plane];
			state->vn_len = state->vn_in_vac_len_at_plane[plane];

			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("v=(% 7.4f,% 7.4f,% 7.4f)\n",
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
		}
	}
	
	if (outcome == sm_Transmitted) {
		//weight range: transmitted = [0, ws_boundary), attenuated = [ws_boundary, 1)
		ws_boundary = T_attn_mir;
		ws_rand = rand01();
		
		#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
		printf("sm=%s, plane=%d, T_attn_mir=%lg transmitted = [0, ws_boundary), attenuated = [ws_boundary, 1) ws_rand=%lg\n", 
				sm->name, plane, T_attn_mir, ws_rand);
		#endif
		
		if (ws_rand > ws_boundary) {
			outcome = sm_Absorbed; 
		}
	}
	
//////update ws, s, last_time/point/plane, layer, location
	switch (outcome) {
		case sm_Reflected: 
			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("%s ws=(% 7.4f,% 7.4f)--times--Rm=(% 7.4f,% 7.4f) => ", supermirror_flat_s_prefix, 
					ws[0],ws[1], Rm_plus,Rm_minus);			
			#endif

			ws[0] *= Rm_plus; 
			ws[1] *= Rm_minus;
			ws_sum = ws[0] + ws[1];
			ws[0] /= ws_sum;
			ws[1] /= ws_sum;

			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("sm_reflect_or_transmit_at_mirror sm_Reflected Rm=%lg, %lg, ws=%lg,%lg\n", Rm_plus, Rm_minus, ws[0],ws[1]);			
			#endif
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("normalised ws=(% 7.4f,% 7.4f)", ws[0],ws[1]);			
			#endif

			if (Rm_plus != Rm_minus) {
				state->s = coords_scale((sm->co).fa, ws[0]-ws[1]);

				#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
				printf(", s=(ws+ - ws-)=% 7.4f:s3=(% 7.4f,% 7.4f,% 7.4f)",
						ws[0]-ws[1], (state->s).x,(state->s).y,(state->s).z);			
				#endif
			}
			
			break;
		case sm_Transmitted: 
			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("%s ws=(% 7.4f,% 7.4f)--times--1-Rm=(% 7.4f,% 7.4f) => ", supermirror_flat_s_prefix, 
					ws[0],ws[1], 1-Rm_plus,1-Rm_minus);			
			#endif
			
			ws[0] *= 1-Rm_plus; 
			ws[1] *= 1-Rm_minus;
			ws_sum = ws[0] + ws[1];
			ws[0] /= ws_sum;
			ws[1] /= ws_sum;
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("sm_reflect_or_transmit_at_mirror sm_Transmitted ws=%lg,%lg\n", ws[0],ws[1]);			
			#endif

			#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
			printf("normalised ws=(% 7.4f,% 7.4f)", ws[0],ws[1]);			
			#endif

			if (Rm_plus != Rm_minus) {
				state->s = coords_scale((sm->co).fa, ws[0]-ws[1]);

				#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
				printf(", s=(ws+ - ws-)=% 7.4f:s3=(% 7.4f,% 7.4f,% 7.4f)",
						ws[0]-ws[1], (state->s).x,(state->s).y,(state->s).z);			
				#endif
			}
			
			break;
		case sm_Absorbed: 
			break;
	}
	
	#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
	printf("\n");			
	#endif

	state->last_time  = state->t;
	state->last_point = state->p;
	state->last_plane = plane;
	
	
	#if defined(NEUTRON_HISTORY_LIB)
	if ((sm->proc).is_tracking) { 
		#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
		printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
		#endif
		
		set_location(state, sm);
		set_event(state, sm, outcome);
		neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
		set_event(state, sm, outcome_detail_1);
		neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
		if (outcome_detail_2 == sm_TotalReflected) {
			set_event(state, sm, outcome_detail_2);
			neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
		}
	}
	#endif
	
	#if defined(DEBUG_sm_reflect_or_transmit_at_mirror)
	printf("%s return outcome=%s(%d), %s(%d)",
			supermirror_flat_s_prefix, 
			((sm->proc).event)[outcome], outcome, 
			((sm->proc).event)[outcome_detail_1], outcome_detail_1);
	if (outcome_detail_2 == sm_TotalReflected) {
		printf(" %s(%d)", ((sm->proc).event)[outcome_detail_2], outcome_detail_2);
	}
	printf("\n");
	supermirror_flat_dec_prefix();
	#endif

	return outcome;
}

/***********************************/
/* Reflection by substrate surface */
/***********************************/
int sm_reflect_or_transmit_at_substrate_surface (SimState*state, Supermirror*sm, int going_inward_or_outward_of_sm, int ignore_or_keep_reflection) 
/******************************************************************************************************************************
Reflection is calculated if substrate has no mirror coating. 
Otherwise only total reflection below Qc_sub is accounted for to prevent error when calculating refraction of beam transmitted through substrate surface. 
uses: 		state->	plane, fn, v, v_len, vn_len, ws, t, p, 
					v_in_sub_inward_at_plane, v_in_sub_inward_len_at_plane, vn_in_sub_inward_len_at_plane, 
					v_in_sub_outward_at_plane, v_sub_outside_len, vn_sub_outside_len, 
					Rs_vac_to_sub_at_plane, Rs_sub_to_vac_at_plane
update: 	state-> v, v_len, vn_len, ws, last_time, last_point, last_plane, layer, location, event
return: 	sm_Reflected, sm_Transmitted, sm_Error.
Output:		
called by: 	sm_external_intersect - 1.4 sm_SubstrateSurfaceLayer(mirror to substrate)
			sm_internal_intersect - n.2 sm_SubstrateSurfaceLayer(substract to mirror)
calles: 	
********************************************************************************************************************************/
{
//#define DEBUG_sm_reflect_or_transmit_at_substrate_surface
	#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
	printf(	"%s int sm_reflect_or_transmit_at_substrate_surface (SimState*state, Supermirror*sm, int going_inward_or_outward_of_sm, int ignore_or_keep_reflection)\n"
			"%s state->plane=%d, sm=%s, going_inward_or_outward_of_sm=%s(%d), ignore_or_keep_reflection=%s(%d)\n",
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, state->plane, sm->name,  
			((sm->proc).proc)[going_inward_or_outward_of_sm],going_inward_or_outward_of_sm,
			((sm->proc).proc)[ignore_or_keep_reflection],ignore_or_keep_reflection);
	supermirror_flat_inc_prefix();
	#endif

	state->layer = sm_SubstrateSurfaceLayer; 

	int plane = state->plane;

//////set Rs, v_sub values once for each trajectory
	double Rs, *ws = state->ws, ws_sum, ws_rand, ws_boundary;
	int outcome, outcome_detail_1, outcome_detail_2=-1; 
	
	if (going_inward_or_outward_of_sm == going_inward) { 
		
		//going_inward
		
		Rs = ignore_or_keep_reflection == ignore_reflection ? 0 : (state->Rs_vac_to_sub_at_plane)[plane];
		
		#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
		printf("%s Rs=% 7.4f\n",
				supermirror_flat_s_prefix, Rs);
		supermirror_flat_dec_prefix();
		#endif
		
		//weight range: reflected-out = [0, ws_boundary], transmitted-in = (ws_boundary, 1)
		ws_boundary = Rs;
		ws_rand = rand01();
		
		#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
		printf(	"%s going_inward: mcget_run_num()=%d, ws=(% 7.4f,% 7.4f)=% 7.4f, Rs=%lg, ws_boundary=%lg, ws_rand=% 7.4f, reflect-out=[0 to % 7.4f),transmit-in=[% 7.4f to 1]\n",  
				supermirror_flat_s_prefix, mcget_run_num(), 
				ws[0],ws[1],ws[0]+ws[1],Rs, ws_boundary, ws_rand, ws_boundary, ws_boundary);
		#endif
		
		//check if the outcome is reflect out or transmit through at interface
		if (ws_boundary > 0 && ws_rand <= ws_boundary) { 
		
			//from outside substrate going inward, reflected out
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("%s v=(% 7.4f,% 7.4f,% 7.4f) towards substrate, reflected out at substrate surface =>",
					supermirror_flat_s_prefix,
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif

			outcome = sm_Reflected;
			outcome_detail_1 = sm_ReflectedOutward;
			if (Rs == 1) outcome_detail_2 = sm_TotalReflected;
			
			state->v = state->v_in_vac_outward_at_plane[plane];
			state->v_len = state->v_in_vac_len_at_plane[plane];
			state->vn_len = state->vn_in_vac_len_at_plane[plane];
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("v=(% 7.4f,% 7.4f,% 7.4f)\n",
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
		}
		else {
			
			//from outside substrate going inward, transmitted in
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("%s v=(% 7.4f,% 7.4f,% 7.4f) towards substrate, transmitted in at substrate surface =>",
					supermirror_flat_s_prefix,
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif

			outcome = sm_Transmitted;
			outcome_detail_1 = sm_TransmittedInward;
			
			state->v = state->v_in_sub_inward_at_plane[plane];
			state->v_len = state->v_in_sub_inward_len_at_plane[plane];
			state->vn_len = state->vn_in_sub_inward_len_at_plane[plane];
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("v=(% 7.4f,% 7.4f,% 7.4f)\n",
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
		}
	}
	else { //going_outward
		
		Rs = ignore_or_keep_reflection == ignore_reflection ? 0 : (state->Rs_sub_to_vac_at_plane)[plane];
		
		#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
		printf("%s Rs=% 7.4f\n",
				supermirror_flat_s_prefix, Rs);
		supermirror_flat_dec_prefix();
		#endif
		
		//Here: exiting event=transmitted out => probability weight boundary ws_boundary = probably weight when reflected by interface  
		//weight range: transmitted-out = [ws_start, ws_boundary], reflected-in = (ws_boundary, 0)
		ws_boundary = Rs;
		ws_rand = rand01();
		
		#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
		printf(	"%s going_outward: mcget_run_num()=%d, ws=(% 7.4f,% 7.4f)=% 7.4f, Rs=%lg, ws_boundary=%lg, ws_rand=% 7.4f, reflect-in=[0 to % 7.4f),transmit-out=(% 7.4f to 1]\n", 
				supermirror_flat_s_prefix, mcget_run_num(), 
				ws[0],ws[1],ws[0]+ws[1], Rs, ws_boundary, ws_rand, ws_boundary, ws_boundary);
		#endif
		
		//check if the outcome is reflect back in or transmit out at interface
		if (ws_boundary > 0 && ws_rand <= ws_boundary) {
			//from inside substrate going outward, reflected back in			
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("%s v=(% 7.4f,% 7.4f,% 7.4f) going outward from inside substrate, reflected back in at substrate surface =>", 
					supermirror_flat_s_prefix,
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
			
			outcome = sm_Reflected;
			outcome_detail_1 = sm_ReflectedInward;
			if (Rs == 1) outcome_detail_2 = sm_TotalReflected;
			
			state->v = state->v_in_sub_inward_at_plane[plane];
			state->v_len = state->v_in_sub_inward_len_at_plane[plane];
			state->vn_len = state->vn_in_sub_inward_len_at_plane[plane];
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("v=(% 7.4f,% 7.4f,% 7.4f)\n",
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
		}
		else {
			//from inside substrate going outward, transmitted out			
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("%s v=(% 7.4f,% 7.4f,% 7.4f) going outward from inside substrate, transmitted out at substrate surface =>", 
					supermirror_flat_s_prefix,
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
			
			outcome = sm_Transmitted;
			outcome_detail_1 = sm_TransmittedOutward;

			state->v = state->v_in_vac_outward_at_plane[plane];
			state->v_len = state->v_in_vac_len_at_plane[plane];
			state->vn_len = state->vn_in_vac_len_at_plane[plane];
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("v=(% 7.4f,% 7.4f,% 7.4f)\n",
					(state->v).x,(state->v).y,(state->v).z 
					);
			#endif
		}
	}

//////update ws, last_time/point/plane, layer, location
	switch (outcome) {
		case sm_Reflected:	
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("%s ws=(% 7.4f,% 7.4f)--times--Rs=% 7.4f => ", supermirror_flat_s_prefix, 
					ws[0],ws[1], Rs);			
			#endif

			ws[0] *= Rs; 
			ws[1] *= Rs;
			ws_sum = ws[0] + ws[1];
			ws[0] /= ws_sum;
			ws[1] /= ws_sum;
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("sm_reflect_or_transmit_at_substrate_surface sm_Reflected ws=%lg,%lg\n", ws[0],ws[1]);			
			#endif
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("ws=(% 7.4f,% 7.4f)\n", ws[0],ws[1]);			
			#endif

			break;
		
		case sm_Transmitted:
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("%s ws=(% 7.4f,% 7.4f)--times--1-Rs=% 7.4f => ",supermirror_flat_s_prefix,
					ws[0],ws[1], 1-Rs);			
			#endif
			
			ws[0] *= 1 - Rs; 
			ws[1] *= 1 - Rs;
			ws_sum = ws[0] + ws[1];
			ws[0] /= ws_sum;
			ws[1] /= ws_sum;
			
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("sm_reflect_or_transmit_at_substrate_surface sm_Transmitted ws=%lg,%lg\n", ws[0],ws[1]);			
			#endif
			
			#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
			printf("ws=(% 7.4f,% 7.4f)\n", ws[0],ws[1]);			
			#endif
			
			break;
	}
	
	state->last_time  = state->t;
	state->last_point = state->p;
	state->last_plane = plane;
	
	
	#if defined(NEUTRON_HISTORY_LIB)
	if ((sm->proc).is_tracking) { 
		#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
		printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
		#endif
		
		set_location(state, sm);
		set_event(state, sm, outcome);
		neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
		set_event(state, sm, outcome_detail_1);
		neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);	
		if (outcome_detail_2 == sm_TotalReflected) {
			set_event(state, sm, outcome_detail_2);
			neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
		}
	}
	#endif
	
	#if defined(DEBUG_sm_reflect_or_transmit_at_substrate_surface)
	printf("%s return outcome=%s(%d), %s(%d)",
			supermirror_flat_s_prefix, 
			((sm->proc).event)[outcome], outcome, 
			((sm->proc).event)[outcome_detail_1], outcome_detail_1);
	if (outcome_detail_2 == sm_TotalReflected) {
		printf(" %s(%d)", ((sm->proc).event)[outcome_detail_2], outcome_detail_2);
	}
	printf("\n");
	supermirror_flat_dec_prefix();
	#endif

	return outcome;
}

/***********************************/
/* Transmit through absorber layer */
/***********************************/
double sm_get_L_attn_abs_at_plane (AbsorptionParameters*abs, double v_len) 
/******************************************************************************************************************************
Purpose:	calculate L_attn_abs through absorber, check if user select no absorption
uses:  
update: 
return: 	L_attn_abs
output:		
called by: 	sm_get_prop_abs_at_plane
calls: 
********************************************************************************************************************************/
{
//#define DEBUG_sm_get_L_attn_abs_at_plane
	#if defined(DEBUG_sm_get_L_attn_abs_at_plane)
	printf(	"%s double sm_get_L_attn_abs_at_plane (AbsorptionParameters*abs, double v_len)\n"
			"%s abs=%X, v_len=%lf\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, abs, v_len);
	supermirror_flat_inc_prefix();
	#endif

//////////obtain L_abs, L_inc
	
	if ((abs->abs_type & sm_abs_type_attn) == 0) {
		#if defined (DEBUG_sm_get_L_attn_abs_at_plane)
		printf("%s no attenuation by selection.\n", supermirror_flat_s_prefix);
		supermirror_flat_dec_prefix();
		#endif

		return -1;
	}
	
	//obtain L_abs
	double L_abs = abs->L_abs; 
	double L_inc = abs->L_inc; 
	
	if (L_abs == -1 && L_inc == -1) {
		#if defined (DEBUG_sm_get_L_attn_abs_at_plane)
		printf("%s no attenuation by selection (L_abs == -1. L_inc == -1).\n", supermirror_flat_s_prefix);
		supermirror_flat_dec_prefix();
		#endif
		
		return -1;
	}

//////get L_attn, here either L_abs != -1 or L_inc != -1
	//default L_attn=-1, no attenuation
	double L_attn = -1; 
	
	#if defined(DEBUG_sm_get_L_attn_abs_at_plane)
	printf("%s sm_get_attnuation_length: startL_attn=% 10.4f, L_abs=% 10.4f, L_inc=% 10.4f\n", 
			supermirror_flat_s_prefix, L_attn, L_abs, L_inc);
	#endif
	
	if (L_abs >= 0) {
		L_attn = (v_len * L_abs) / LambdaV_AA_m_s;
	}
	
	#if defined(DEBUG_sm_get_L_attn_abs_at_plane)
	printf("%s after L_abs: L_attn=% 10.4f, L_abs=% 10.4f, L_inc=% 10.4f\n", 
			supermirror_flat_s_prefix, L_attn, L_abs, L_inc);
	#endif
	
	if (L_attn != 0 && L_inc >= 0) {
	if (L_attn == -1) {
			L_attn = L_inc;
		}
		else {
			L_attn *= L_inc / (L_attn + L_inc);
		}
	}
	#if defined(DEBUG_sm_get_L_attn_abs_at_plane)
	printf("%s after L_inc: L_attn=% 10.4f, L_abs=% 10.4f, L_inc=% 10.4f\n", 
			supermirror_flat_s_prefix, L_attn, L_abs, L_inc);
	supermirror_flat_dec_prefix();
	#endif
	
	return L_attn; 
}
void sm_get_prop_abs_at_plane (AbsorptionParameters*abs, double v_len, double vn_len, double*L_attn_abs_at_plane, double*t_prop_abs_at_plane, double*T_prop_abs_at_plane) 
/******************************************************************************************************************************
Purpose:	calculate time & transmission through absorber layer, top & bottom surfaces only, i.e. side edges not taken into account.
uses: 		
update: 	
return:		
output: 	L_attn_abs_at_plane, t_prop_abs_at_plane, T_prop_abs_at_plane.
called by: 	sm_transmit_through_absorber_at_plane
calls: 		sm_get_L_attn_abs_at_plane
********************************************************************************************************************************/
{
//define DEBUG_sm_get_prop_abs_at_plane
	#if defined (DEBUG_sm_get_prop_abs_at_plane)
	printf(	"%s void sm_get_prop_abs_at_plane (AbsorptionParameters*abs, double v_len, double vn_len, double*L_attn_abs_at_plane, double*t_prop_abs_at_plane, double*T_prop_abs_at_plane)\n" 
			"%s abs=%X, v_len=%lf, vn_len=%lf, L_attn_abs_at_plane=%X, t_prop_abs_at_plane=%X, T_prop_abs_at_plane=%X\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, abs, v_len, vn_len, L_attn_abs_at_plane, t_prop_abs_at_plane, T_prop_abs_at_plane);
	supermirror_flat_inc_prefix();
	#endif

	double L_attn, t_prop, T_prop;

	if (vn_len <= ZERO_THRESHOLD) {
		//neutron flying parallel to surface, no intersect
		//neutron flying parallel to surface, no intersect
		#if defined (DEBUG_sm_get_prop_abs_at_plane)
		printf("%s neutron flying parallel to surface, no intersect\n", supermirror_flat_s_prefix);
		supermirror_flat_inc_prefix();
		#endif

		L_attn = -1;
		t_prop = F_INDETERMINED;
		T_prop = 1;
	}
	else {

		//get t_prop
		t_prop = fabs(abs->thickness_in_micron * 1E-6 / vn_len);
		
		//calculate L_attn
		L_attn = sm_get_L_attn_abs_at_plane (abs, v_len);
		
		//calculate T_prop
		if (L_attn != -1) {
			T_prop = L_attn > ZERO_THRESHOLD? exp(-t_prop * v_len / L_attn) : 0;
		}
		else {
			//no absorption
			T_prop = 1;
		}
	}

	*L_attn_abs_at_plane = L_attn;
	*t_prop_abs_at_plane = t_prop;
	*T_prop_abs_at_plane = T_prop;
	
	#if defined (DEBUG_sm_get_prop_abs_at_plane)
	if (*t_prop_abs_at_plane != F_INDETERMINED) {
		printf("%s L_attn_abs_at_plane=%lf, t_prop_abs_at_plane=%lf, (L_prop_abs_at_plane=%lf), T_prop_abs_at_plane=%lf\n", 
				supermirror_flat_s_prefix, *L_attn_abs_at_plane, *t_prop_abs_at_plane, *t_prop_abs_at_plane*v_len, *T_prop_abs_at_plane);
	}
	else {
		printf("%s L_attn_abs_at_plane=%lf, t_prop_abs_at_plane=F_INDETERMINED, (L_prop_abs_at_plane=F_INDETERMINED), T_prop_abs_at_plane=1\n", 
				supermirror_flat_s_prefix, *L_attn_abs_at_plane);
	}
	supermirror_flat_dec_prefix();
	#endif
}
int sm_transmit_through_absorber_at_plane (SimState*state, Supermirror*sm) 
/******************************************************************************************************************************
Purpose:	calculate transmittion through absorber at plane
Uses: 		state->L_attn_abs_at_plane[state->plane]
			state->t_prop_abs_at_plane[state->plane]
			state->T_prop_abs_at_plane[state->plane]
			state-> plane, p, v, fn
Update: 	state-> t, p, ws, last_time, last_point, last_plane, side, plane, layer 
Return: 	sm_Transmitted, sm_Exited, sm_Absorbed. 
called by: 	sm_external_intersect - 1.3 sm_AbsorberLayer(mirror to substrate) 
			sm_external_intersect - 1.5 sm_AbsorberLayer(substrate to mirror) 
calls: 		sm_get_prop_abs_at_plane
********************************************************************************************************************************/
{
//define DEBUG_sm_transmit_through_absorber_at_plane
	#if defined (DEBUG_sm_transmit_through_absorber_at_plane)
	printf(	"%s int sm_transmit_through_absorber (SimState*state, Supermirror*sm)\n"
			"%s state=%X, sm=%X\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, state, sm);
	supermirror_flat_inc_prefix();
	#endif

	state->layer = sm_AbsorberLayer; 
	
	int plane;
	
	if (state->set_L_attn_abs == 0) {
		//For flat mirror, for each sampling, the path length through the absorber is the same. 
		//So propagation parameters only need to calculate once. 
		//Different sampling have different path length so need to re-calculate
		//Non-flat but symmetric (e.g. spherical curved) mirror will need to calculate two planes differently
		//Non symmtric mirror will need to calculate each time, based on the new angle of incident on the absorber. 
		for (plane = 0; plane < 2; plane++) {
			sm_get_prop_abs_at_plane (&(((sm->mat).abs)[plane]), state->v_len, state->vn_len, 
										&((state->L_attn_abs_at_plane)[plane]), 
										&((state->t_prop_abs_at_plane)[plane]), 
										&((state->T_prop_abs_at_plane)[plane]));
		}
		state->set_L_attn_abs = 1;
	}
	
	plane = state->plane;

	int outcome; 
	double L_attn_abs = state->L_attn_abs_at_plane[plane];
	double t_prop_abs = state->t_prop_abs_at_plane[plane]; //time to propagate through entire absorber layer
	double T_prop_abs = state->T_prop_abs_at_plane[plane];
	
	#if defined (DEBUG_sm_transmit_through_absorber_at_plane)
	printf("%s t_prop_abs=%lf\n", 
			supermirror_flat_s_prefix, t_prop_abs);
	#endif
	
//////////Determine outcome: absoprtion or transmit through mirror-side surfaces or edge  

	//absorbed [0, ws_boundary), transmitted [ws_boundary, 1]
	double ws_boundary = 1 - T_prop_abs;
	
	#if defined(DEBUG_sm_transmit_through_absorber_at_plane)
	printf("%s t_prop_abs=%lf, L abs=%lf, L_attn_abs=%lf\n", 
			supermirror_flat_s_prefix, t_prop_abs, t_prop_abs*state->v_len, L_attn_abs);
	#endif
	
	double w_abs = rand01(); //probability of absorption
	if (w_abs < ws_boundary) { 
		//neutron absorbed
		outcome = sm_Absorbed;
	}
	else {
		//neutron transmitted
		outcome = sm_Transmitted;
	}

	#if defined (DEBUG_sm_transmit_through_absorber_at_plane)
	printf("%s dt=%lf, state->v_len=%lf, dt*v=%lf, L_attn_abs=%lf\n", 
			supermirror_flat_s_prefix, dt, state->v_len, dt*state->v_len, L_attn_abs);
	#endif

	#if defined (DEBUG_sm_transmit_through_absorber_at_plane)
	else {
		//no absorption by selection
		printf("%s no absorber layer by selection.\n", supermirror_flat_s_prefix);
	}
	#endif

//////update state variables
	switch (outcome) {
		case sm_Transmitted: 
		{
#if defined(DEBUG_REF_LIB_TRACK)	
sprintf(track_msg,"%sAT1 ",track_msg);
#endif
			state->last_time  = state->t;
			state->last_point = state->p;
			state->last_plane = state->plane;
			
			break;
		}
		case sm_Absorbed:
		{
#if defined(DEBUG_REF_LIB_TRACK)	
sprintf(track_msg,"%sAA1 ",track_msg);
#endif
			break;
		}
		case sm_Error:
		{
#if defined(DEBUG_REF_LIB_TRACK)	
sprintf(track_msg,"%sAE1 ",track_msg);
#endif
			break;
		}
	}
	
	#if defined(NEUTRON_HISTORY_LIB)
	if ((sm->proc).is_tracking) {
		#if defined(DEBUG_sm_transmit_through_absorber_at_plane)
		printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
		#endif
		
		set_location(state, sm);	
		set_event(state, sm, outcome);
		neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
	}
	#endif
			
	#if defined(DEBUG_sm_transmit_through_absorber_at_plane)
	switch (outcome) { 
		case sm_Transmitted: 
			printf("%s plane,t,p=%d, %lg, (%lg,%lg,%lg), location=%s, outcome=sm_Transmitted\n", 
					supermirror_flat_s_prefix, state->plane, state->t, state->p.x, state->p.y, state->p.z, state->location);
			printf("%s sm_Transmitted through absorber layer. Return sm_Transmitted (stay in module).\n", supermirror_flat_s_prefix);
			break; 
		case sm_Exited: 
			printf("%s plane,t,p=%d, %lg, (%lg,%lg,%lg), location=%s, outcome=sm_Exited\n", 
					supermirror_flat_s_prefix, state->plane, state->t, state->p.x, state->p.y, state->p.z, state->location);
			printf("%s sm_Exited absorber layer through supermirror edge. Return sm_Exited (exit module).\n", supermirror_flat_s_prefix);
			break; 
		case sm_Absorbed: 
			printf("%s plane,t,p=%d, %lg, (%lg,%lg,%lg), location=%s, outcome=sm_Absorbed\n", 
					supermirror_flat_s_prefix, state->plane, state->t, state->p.x, state->p.y, state->p.z, state->location);
			printf("%s sm_Absorbed in absorber layer. Return sm_Absorbed (exit module).\n", supermirror_flat_s_prefix);
			break; 
		case sm_Error: 
			printf("%s plane,t,p=%d, %lg, (%lg,%lg,%lg), location=%s, outcome=sm_Error\n", 
					supermirror_flat_s_prefix, state->plane, state->t, state->p.x, state->p.y, state->p.z, state->location);
			printf("%s sm_Error. Return sm_Error (exit module).\n", supermirror_flat_s_prefix);
			break; 
	}
	printf("%s Done sm_transmit_through_absorber\n", supermirror_flat_s_prefix);
	supermirror_flat_dec_prefix();
	#endif

	return outcome; //Return outcome.
}

/******************************/
/* Transmit through substrate */
/******************************/
double sm_get_L_attn_sub (SubstrateParameters*sub, double v_len) 
/******************************************************************************************************************************
Purpose:	calculate L_attn_sub through substrate, check if user select no absorption
uses:  
update: 
return: 	L_attn_sub
output:		
called by: 	sm_get_prop_sub_at_plane
calls: 
********************************************************************************************************************************/
{
//define DEBUG_sm_get_L_attn_sub
	#if defined (DEBUG_sm_get_L_attn_sub)
	printf(	"%s double sm_get_L_attn_sub (SubstrateParameter*sub, double v_len)\n"
			"%s sub=%X, state=%lf\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, sub, v_len);
	supermirror_flat_inc_prefix();
	#endif

//////////determine t_prop_at_layer, L_prop_at_layer, obtain L_abs, L_inc
	
	//default: no attentuation
	if ((sub->sub_type & sm_sub_type_attn) == 0) {
		#if defined (DEBUG_sm_get_L_attn_sub)
		printf("%s no attenuation by selection, return -1.\n", supermirror_flat_s_prefix);
		supermirror_flat_dec_prefix();
		#endif

		return -1;
	}
	
	//obtain L_abs
	double L_abs = sub->L_abs; 
	double L_inc = sub->L_inc; 
	
	if (L_abs == -1 && L_inc == -1 && sub->S_coh == 0) {
		#if defined (DEBUG_sm_get_L_attn_sub)
		printf("%s no attenuation by selection (L_abs == -1. L_inc == -1), return -1.\n", supermirror_flat_s_prefix);
		supermirror_flat_dec_prefix();
		#endif
		
		return -1;
	}
	
	if (L_abs == 0 || L_inc == 0) {
		return 0;
	}

//////get L_attn, here either L_abs != -1 or L_inc != -1
	//default L_attn=-1, no attenuation
	double L_attn = -1; 
	#if defined(DEBUG_sm_get_L_attn_sub)
	printf("%s start: L_attn=% 10.4f, L_abs=% 10.4f, L_inc=% 10.4f\n", 
			supermirror_flat_s_prefix, L_attn, L_abs, L_inc);
	#endif
	
	if (L_abs > 0) {
		L_attn = (v_len * L_abs) / LambdaV_AA_m_s;
	}
	#if defined(DEBUG_sm_get_L_attn_sub)
	printf("%s after L_abs: L_attn=% 10.4f, L_abs=% 10.4f, L_inc=% 10.4f\n", 
			supermirror_flat_s_prefix, L_attn, L_abs, L_inc);
	#endif
	
	if (L_inc > 0) {
		if (L_attn == -1) {
			L_attn = L_inc;
		}
		else {
			L_attn *= L_inc / (L_attn + L_inc);
		}
	}
	//TDS (phonon scattering)
	double mu_phonon;
	if (sub->S_coh > 0) {
		// sigma_phonon = sub->a_mph*(1-exp(b_mph*v_len*v_len) + sub->a_sph/v_len;
		// mu_phonon = sub->n * sigma_phonon; 
		mu_phonon = sub->n * (sub->a_mph*(1-exp(sub->b_mph*v_len*v_len)) + sub->a_sph/v_len) * 100; //times 100 to convert from 1/cm to SI 1/m
		if (mu_phonon > ZERO_THRESHOLD) {
			if (L_attn == -1) {
					L_attn = 1/mu_phonon;
			}
			else {
				L_attn /= 1 + mu_phonon * L_attn;
			}
		}
	}
	
	#if defined (DEBUG_sm_get_L_attn_sub)
	if (strcmp(sub->name,"Si") == 0) {
		printf(	"%s", supermirror_flat_s_prefix);
		printf(	"%s, ", sub->name);
		printf( "lambda=%lf, E=%lf", LambdaV_AA_m_s / v_len, EOverVSquare_meV_m_s * v_len * v_len);
		if (L_attn != -1) { 
			printf(", L_attn[cm]=%lf", L_attn * 100); 
			if (L_abs != -1) printf(", L_abs[cm]=%lf, L_abs(lambda)[cm]=%lf", L_abs*100, L_abs*100 * v_len / LambdaV_AA_m_s ); 
			if (L_inc != -1) printf(", L_inc[cm]=%lf", L_inc*100);
			if (mu_phonon > ZERO_THRESHOLD) printf(", L_tds[cm]=%lf", 100/mu_phonon);
			if (L_abs > ZERO_THRESHOLD) printf(", mu_abs(lambda)[1/cm]=%lf", LambdaV_AA_m_s / (L_abs*100 * v_len));
			if (L_inc > ZERO_THRESHOLD) printf(", mu_inc[1/cm]=%lf", 1/(L_inc*100));
			printf(", mu_tds[1/cm]=%lf", mu_phonon/100);
			printf(", s_tds[b]=%le", sub->a_mph*(1-exp(sub->b_mph*v_len*v_len)) + sub->a_sph/v_len);
			printf(", s_abs[b]=%le", LambdaV_AA_m_s / (v_len * (L_abs*100) * sub->n));
			printf(", s_tds+abs[b]=%le", sub->a_mph*(1-exp(sub->b_mph*v_len*v_len)) + sub->a_sph/v_len + LambdaV_AA_m_s / (v_len * (L_abs*100) * sub->n));
		}
		else {
			printf(", L_attn=-1 => no attenuation");
		}
		printf("\n");
		supermirror_flat_dec_prefix();
	}
	#endif
	
	return L_attn; 
}
int sm_transmit_through_substrate (SimState*state, Supermirror*sm) 
/******************************************************************************************************************************
Purpose:	calculate transmittion through substrate
Uses: 		state->L_attn_sub
			state-> t, p, v, ws
update: 	state-> t, p, plane, fn, ws, last_time, last_point, last_plane, side, plane, layer 
			state-> t_prop_sub, T_prop_sub
return: 	sm_Transmitted, sm_Exited, sm_Absorbed. 
output:		
called by: 	sm_internal_intersect - n.1 sm_SubstrateLayer 
calls: 		line_polyhedron_intersect
			sm_get_L_attn_sub. 
********************************************************************************************************************************/
{
//define DEBUG_sm_transmit_through_substrate
	#if defined (DEBUG_sm_transmit_through_substrate)
	printf(	"%s int sm_transmit_through_substrate (SimState*state, Supermirror*sm)\n"
			"%s state=%X, sm=%X\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, state, sm);
	supermirror_flat_inc_prefix();
	#endif

	state->layer = sm_SubstrateLayer;

	if (state->set_L_attn_sub == 0) {
		state->L_attn_sub = sm_get_L_attn_sub (&((sm->mat).sub), state->v_len);
		state->set_L_attn_sub = 1;
	}

	int outcome = I_INDETERMINED; 
	double L_attn_sub = state->L_attn_sub;
	
//////calculate time & transmission through substrate

	#if defined (DEBUG_sm_transmit_through_substrate)
	printf("%s Call line_polyhedron_intersect to find intersect\n", supermirror_flat_s_prefix);
	supermirror_flat_inc_prefix();
	#endif
	
	//itype[0]: 1=x plane, 2=x edge, 3=x vertex, 4=on plane, 5=on edge
	int iplane, itype; double idt;
	int num_intersect = 1; //only use values of the first intersect
	//Skip the current plane in finding intersect, neutron should propagate to other planes.
	//Also, refraction may result in trajectory almost parallel to current plane, can unphysically transmit out due to numerical precision limit. 
	int n_skip_plane = 1; int skip_plane[n_skip_plane];
	skip_plane[0] = state->plane;  
	line_polyhedron_intersect(state->t, state->p, state->v, &(sm->geo), Maximum_On_Plane_Distance, n_skip_plane, skip_plane,  
								state->last_time, state->last_point, state->last_plane, 
								&num_intersect, &idt, 0, 0, 0, &iplane, &itype); 
	
	#if defined(DEBUG_sm_transmit_through_substrate)
	supermirror_flat_dec_prefix();
	printf("%s sm_transmit_through_substrate, intersect n=%d idt=%lg iplane=%d itype=%d\n", supermirror_flat_s_prefix, 
			num_intersect, idt, iplane, itype);
	#endif
	
	//For transmitted beam from inside, 
	//must have 1 valid intersects and not riding on surface or edge, 
	if (num_intersect > 0 && itype < 4) {
		
//////////Determine outcome 1: going through substrate, absorbed by substrate material?
		if (L_attn_sub != -1) 
		{
			//absorbed [0, ws_boundary), transmitted [ws_boundary, 1]
			double ws_boundary = 1 - exp(-idt * state->v_len / L_attn_sub);

			double ws_rand = rand01(); //probability of absorption
			if (ws_rand < ws_boundary) { 
				//neutron absorbed
				outcome = sm_Absorbed;
				//calculate how far absorbed neutron propagates
				idt = -log(1-ws_rand) * L_attn_sub / state->v_len; 
			}
			
			#if defined(DEBUG_sm_transmit_through_substrate)
			printf("%s idt=%lf, state->v_len=%lf, idt*v=%lf, L_attn_sub=%lf\n", 
					supermirror_flat_s_prefix, idt, state->v_len, idt * state->v_len, L_attn_sub);
			#endif
		}
		#if defined (DEBUG_sm_transmit_through_substrate)
		else {
			//no absorption by selection, no change to dt
			printf("%s no substrate absorption by selection.\n", supermirror_flat_s_prefix);
		}
		#endif
		
//////Determine outcome 2: pass substrate without being absorbed, path through mirror-side surfaces or edge (blocked?) 

		if (outcome != sm_Absorbed) {
			
			if (iplane < SM_Num_Mirror_Planes) {
				//intersect mirror surface
				outcome = sm_Transmitted; 

				#if defined(DEBUG_sm_transmit_through_substrate)		
				printf("%s transmitted, reach substrate surface\n", supermirror_flat_s_prefix);
				#endif
			}
			else {
				//intersect edge, exit supermirror
				if ( (((sm->mat).sub).sub_type & sm_sub_type_back_edge_attn) == sm_sub_type_back_edge_attn) {
					outcome = sm_Absorbed;

					#if defined(DEBUG_sm_transmit_through_substrate)
					printf("%s mcget_run_num()=%d blocked at back edge %d %d %d\n", supermirror_flat_s_prefix,
							mcget_run_num(), ((sm->mat).sub).sub_type, sm_sub_type_back_edge_attn, (((sm->mat).sub).sub_type) & sm_sub_type_back_edge_attn);
					#endif
				}
				else {
					outcome = sm_Exited; 
					
					#if defined(DEBUG_sm_transmit_through_substrate)
					printf("%s exit through back edge %d %d %d\n", supermirror_flat_s_prefix, 
							((sm->mat).sub).sub_type, sm_sub_type_back_edge_attn, ((sm->mat).sub).sub_type & sm_sub_type_back_edge_attn);
					#endif
				}
			}
		}
	}
	else { //something's not right
		printf(	"%s sm_transmit_through_substrate: Inside module but found no intersect, \n"
				"%s maybe riding along edge surface or line outside(itype=%d), \n", 
				supermirror_flat_s_prefix, 
				supermirror_flat_s_prefix, itype);
/*
		#if defined(DEBUG_REF_LIB_CATCH_ANOMALY)
		line_polyhedron_intersect_debug(state->t, state->p, state->v, &(sm->geo), Maximum_On_Plane_Distance, 0, 0, 
								state->last_time, state->last_point, state->last_plane, 
								&num_intersect, 0, 0, 0, 0, 0, 0);
		#endif
*/
		printf(	"sm_transmit_through_substrate something's wrong. Return sm_Error(0). Exit module)\n");

		outcome = sm_Error; 
	}

//////update state variables
	state->t += idt; 
	state->p = coords_add(state->p, coords_scale(state->v, idt));
			
	switch (outcome) {
		case sm_Transmitted: 
		{ //neutron hits mirror surface from inside

#if defined(DEBUG_REF_LIB_TRACK)	
sprintf(track_msg,"%sST1 ",track_msg);
#endif
			
			state->plane = iplane;
			state->fn = (sm->geo).fn[iplane];
			
			//update state variables at 2nd surface intersect
			if (state->n_surface_intersect == 1) {
				//2nd surface intersect that is a mirror is always at the transmitted side
				state->side = sm_TransmittedSide;
			}
			else {
				//otherwise switch between transmitted and reflected side
				state->side = state->side == sm_ReflectedSide? sm_TransmittedSide : sm_ReflectedSide;
			}
			
			//update substrate transmission parameters until 2nd mirror intersect = mirror to mirror neutron transmission
			if (state->n_mirror_intersect < SM_Num_Mirror_Planes) {
				state->t_prop_sub = idt;
				if (L_attn_sub == -1) {
					state->T_prop_sub = 1;
				}
				else if (L_attn_sub > ZERO_THRESHOLD) {
					state->T_prop_sub = exp(-(idt * state->v_len /L_attn_sub));
				}
				else {
					state->T_prop_sub = 0;
				}
			}
	
			state->last_time  = state->t;
			state->last_point = state->p;
			state->last_plane = state->plane;
				
			break;
		}
		case sm_Exited:
		{
#if defined(DEBUG_REF_LIB_TRACK)	
sprintf(track_msg,"%sSX1 ",track_msg);
#endif
			
			state->side = sm_EdgeSide;
			state->plane = iplane;
			state->fn = (sm->geo).fn[iplane];

			state->last_time  = state->t;
			state->last_point = state->p;
			state->last_plane = state->plane;
			
			break;
		}
		case sm_Absorbed:
		{
#if defined(DEBUG_REF_LIB_TRACK)	
sprintf(track_msg,"%sSA1 ",track_msg);
#endif
			
			break;
		}
		case sm_Error:
		{
#if defined(DEBUG_REF_LIB_TRACK)	
sprintf(track_msg,"%sSE1 ",track_msg);
#endif
			
			break;
		}
	}

	#if defined(NEUTRON_HISTORY_LIB)
	if ((sm->proc).is_tracking) { 
		#if defined(DEBUG_sm_transmit_through_substrate)
		printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
		#endif
		
		set_location(state, sm);
		set_event(state, sm, outcome);
		neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
	}
	#endif
	
	#if defined(DEBUG_sm_transmit_through_substrate)
	switch (outcome) { 
		case sm_Transmitted: 
			printf("%s plane,t,p=%d, %lg, (%lg,%lg,%lg), location=%s, outcome=sm_Transmitted\n", 
					supermirror_flat_s_prefix, state->plane, state->t, state->p.x, state->p.y, state->p.z, state->location);
			printf("%s sm_Transmitted through substrate. Return sm_Transmitted (stay in module).\n", supermirror_flat_s_prefix);
			break; 
		case sm_Exited: 
			printf("%s plane,t,p=%d, %lg, (%lg,%lg,%lg), location=%s, outcome=sm_Exited\n", 
					supermirror_flat_s_prefix, state->plane, state->t, state->p.x, state->p.y, state->p.z, state->location);
			printf("%s sm_Exited substrate through supermirror edge. Return sm_Exited (exit module).\n", supermirror_flat_s_prefix);
			break; 
		case sm_Absorbed: 
			printf("%s plane,t,p=%d, %lg, (%lg,%lg,%lg), location=%s, outcome=sm_Absorbed\n", 
					supermirror_flat_s_prefix, state->plane, state->t, state->p.x, state->p.y, state->p.z, state->location);
			printf("%s sm_Absorbed in substrate. Return sm_Absorbed (exit module).\n", supermirror_flat_s_prefix);
			break; 
		case sm_Error: 
			printf("%s plane,t,p=%d, %lg, (%lg,%lg,%lg), location=%s, outcome=sm_Error\n", 
					supermirror_flat_s_prefix, state->plane, state->t, state->p.x, state->p.y, state->p.z, state->location);
			printf("%s sm_Error. Return sm_Error (exit module).\n", supermirror_flat_s_prefix);
			break; 
	}
	printf("%s Done sm_transmit_through_substrate\n", supermirror_flat_s_prefix);
	supermirror_flat_dec_prefix();
	#endif

	return outcome; //Return outcome.
}


/************************/
/* Trajectory functions */
/************************/

int sm_external_intersect(SimState *state, Supermirror *sm) 
//1st intersect comes from neutrons outside of the supermirror
{
//#define DEBUG_sm_external_intersect
	#if defined(DEBUG_sm_external_intersect)
	printf(	"%s int sm_external_intersect(SimState *state, Supermirror *sm)\n"
			"%s state=%X, sm=%X\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, state, sm);
	supermirror_flat_inc_prefix();
	#endif
	#if defined(DEBUG_sm_external_intersect)
	printf(	"%s w,t,p,v:|v| = %5e,% 7.4f,(% 7.4f,% 7.4f,% 7.4f),(% 7.4f,% 7.4f,% 7.4f):% 7.4f\n"
			"%s s3:|s|:s2 = (% 7.4f,% 7.4f,% 7.4f):% 7.4f:(% 7.4f,% 7.4f)\n", 
			supermirror_flat_s_prefix, state->w, state->t, (state->p).x,(state->p).y,(state->p).z,(state->v).x,(state->v).y,(state->v).z, coords_len(state->v), 
			supermirror_flat_s_prefix, (state->s).x,(state->s).y,(state->s).z, coords_sp((sm->co).fa, state->s),(1+coords_sp((sm->co).fa, state->s))/2,(1-coords_sp((sm->co).fa, state->s))/2);
	#endif
	
//////1.1 intersect from external to supermirror
	#if defined(DEBUG_sm_external_intersect)
	sm_print_state ("1.1: find intersect from external to supermirror", state, sm);
	#endif
	
//////1.1 find line-polyhedron intersects
	#if defined (DEBUG_sm_external_intersect)
	printf("%s 1.1: Call line_polyhedron_intersect to find intersect\n", supermirror_flat_s_prefix);
	supermirror_flat_inc_prefix();
	#endif
	
	//polyhedron intersect parameters
	int num_intersect = 2; //only use values of the first two intersects
	double idtime[2];
	Coords idpoint[2];
	double itime[2];
	Coords ipoint[2];
	int iplane[2];
	int itype[2]; ////type: 1=x plane, 2=x edge, 3=x vertex, 4=on plane, 5=on edge
	line_polyhedron_intersect(state->t, state->p, state->v, &(sm->geo), Maximum_On_Plane_Distance, 0, 0, 
								state->last_time, state->last_point, state->last_plane, 
								&num_intersect, idtime, idpoint, itime, ipoint, iplane, itype); 
	
	#if defined(DEBUG_sm_external_intersect)
	sm_print_intersect("1.1: find intersect from external to supermirror",
						num_intersect, idtime, idpoint, itime, ipoint, iplane, itype);
	supermirror_flat_dec_prefix();
	#endif
	
	//For incident beam on supermirror from outside, 
	//must have 2 valid intersects and not riding on surface or edge to go in, 
	//otherwise miss supermirror
	if (num_intersect < 2 || itype[0] > 3 || itype[1] > 3) {
		//incident neutron passes corner or edge without going in
		
		#if defined(DEBUG_sm_external_intersect)
		printf("%s 1.1: sm_Missed, must have 2 valid intersects and not riding on surface or edge, num_intersect=%d, itype[0]=%d, itype[1]=%d. Return sm_Missed (exit module)\n", 
				supermirror_flat_s_prefix, num_intersect, itype[0], itype[1]);
		#endif
		
		#if defined(NEUTRON_HISTORY_LIB)
		if ((sm->proc).is_tracking) {
			#if defined(DEBUG_sm_external_intersect)
			printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
			#endif
			
			set_event(state, sm, sm_Missed);
			neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
		}
		#endif
		
		return sm_Missed; //neutron misses module, , exit calculation
	}
	
//////1.1 Intersect found, propagate to intersect, update state variables
	
	state->plane = iplane[0];
	if (state->plane < SM_Num_Mirror_Planes) {
		state->layer = sm_MirrorLayer;
		state->side = sm_ReflectedSide;
		state->side_at_plane[state->plane] = sm_ReflectedSide;
		state->side_at_plane[1-state->plane] = sm_TransmittedSide;
	}
	else {
		state->layer = sm_SubstrateLayer;
		state->side = sm_EdgeSide;
	}
	set_location(state, sm);
	
	state->fn = (sm->geo).fn[iplane[0]];
	
	state->t = itime[0];
	state->p = ipoint[0];
	
	state->last_time  = itime[0];
	state->last_point = ipoint[0];
	state->last_plane = iplane[0];

	double s_pol = coords_sp((sm->co).fa, state->s);
	state->s = coords_scale((sm->co).fa, s_pol);
	state->ws[0] = (1 + s_pol) / 2; //plus intensity 
	state->ws[1] = (1 - s_pol) / 2; //minus intensity

	#if defined(DEBUG_sm_external_intersect)
	printf("sm_external_intersect 1 ws=%lg,%lg\n", state->ws[0], state->ws[1]);
	#endif
	
	#if defined(DEBUG_sm_external_intersect)
	printf("%s here is_tracking=%d\n", supermirror_flat_s_prefix, (sm->proc).is_tracking);
	#endif
	#if defined(NEUTRON_HISTORY_LIB)
	if ((sm->proc).is_tracking) {
		#if defined(DEBUG_sm_external_intersect)
		printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
		#endif
		
		set_event(state, sm, sm_Intersected);
		neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
	}
	#endif

	#if defined(DEBUG_sm_external_intersect)
	printf(	"%s 1.1: find intersect from external to supermirror\n"
			"%s intersect plane,t,p=%d, %lg, (%lg,%lg,%lg), location/event=%s/%s\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, state->plane, state->t, state->p.x, state->p.y, state->p.z, state->location, state->event);
	#endif
	#if defined(DEBUG_sm_external_intersect)
	supermirror_flat_inc_prefix();
	sm_print_state("1.1: incident intersect", state, sm);
	supermirror_flat_dec_prefix();
	#endif
	
//////1.1 
//////    if surface plane: reflect out? transmit in?
//////    else: not surface plane, transmit in. 

	double v_len = state->v_len = coords_len(state->v); 
	double vn_len = state->vn_len = fabs(coords_sp(state->v, state->fn));
	
	int outcome;

	switch (state->layer) {
		
//////////1.1 sm_MirrorLayer(external to mirror)
		case sm_MirrorLayer: 
		{
			state->layer = sm_MirrorLayer;
			#if defined(DEBUG_sm_external_intersect)
			printf(	"%s 1.1: sm_Intersected, sm_MirrorLayer.\n\n"
					"%s 1.2: sm_MirrorLayer(external to mirror), call sm_reflect_or_transmit_at_interface."
					"sm_Reflected-exit, sm_Transmitted-continue\n", 
					supermirror_flat_s_prefix, supermirror_flat_s_prefix);
			supermirror_flat_inc_prefix();
			#endif

//////////////update internal reflection state variables
			state->n_surface_intersect = 1;
			state->n_mirror_intersect = 1;

//////////////1.2 sm_MirrorLayer(external to mirror), sm_Reflected-sm_Exited or sm_Transmitted-continue
			#if defined(DEBUG_sm_external_intersect)
			printf(	"%s 1.2: sm_MirrorLayer(external to mirror), call sm_calc_surface_parameters, sm_reflect_or_transmit_at_mirror, "
					"sm_Absorbed, sm_Reflected-sm_Exited, or sm_Transmitted-continue.\n",
					supermirror_flat_s_prefix);
			#endif
			
			sm_calc_surface_parameters(state, sm, going_inward);
			outcome = sm_reflect_or_transmit_at_mirror(state, sm, going_inward, keep_reflection);
			switch (outcome) {  
			
//////////////////1.2 sm_MirrorLayer(external to mirror), sm_Absorbed, return sm_Absorbed (exit module).
				case sm_Absorbed: 
				{
					#if defined(DEBUG_sm_external_intersect)
					printf("%s 1.2: sm_MirrorLayer(external to mirror) ", supermirror_flat_s_prefix);
					sm_print_state("sm_reflect_or_transmit_at_mirror: sm_Absorbed, return sm_Absorbed (exit module).", state, sm);
					printf("\n\n");	
					#endif

					//location: ReflectSide, sm_MirrorLayer, external to mirror
					#if defined(NEUTRON_HISTORY_LIB)
					if ((sm->proc).is_tracking) {
						set_event(state, sm, sm_Absorbed);
						neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
						
						#if defined(DEBUG_sm_external_intersect)
						printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
						#endif
					}
					#endif

					return sm_Absorbed; //sm_Absorbed, return sm_Absorbed (exit module)
					break; 
				}

//////////////////1.2 sm_MirrorLayer(external to mirror), sm_Reflected, sm_Exited, return sm_Exited (exit module).
				case sm_Reflected:	
				{
					//v = v_in_vac_outward_at_plane
					#if defined(DEBUG_sm_external_intersect)
					sm_print_refl("1.2: sm_MirrorLayer(external to mirror), sm_Reflected", state, sm);
					printf("%s 1.2: sm_MirrorLayer(external to mirror) ", supermirror_flat_s_prefix);
					sm_print_state("sm_reflect_or_transmit_at_mirror: sm_Reflected, sm_Exited, return sm_Exited (exit module).", state, sm);
					printf("\n\n");							
					#endif

					//location: ReflectSide, sm_MirrorLayer, external to mirror
					#if defined(NEUTRON_HISTORY_LIB)
					if ((sm->proc).is_tracking) {
						set_event(state, sm, sm_Reflected);
						neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
						
						#if defined(DEBUG_sm_external_intersect)
						printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
						#endif
						
						set_event(state, sm, sm_Exited);
						neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
						
						#if defined(DEBUG_sm_external_intersect)
						printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
						#endif
					}
					#endif

					return sm_Exited; //sm_Exited, return sm_Exited (exit module)
					break;
				}

//////////////////1.2 sm_MirrorLayer(external to mirror), sm_Transmitted, continue.
				case sm_Transmitted:
				{
					//v = v_in_vac_inward_at_plane
					#if defined(DEBUG_sm_external_intersect)
					sm_print_refl("1.2: sm_MirrorLayer(external to mirror), sm_Transmitted", state, sm);
					printf("%s 1.2: sm_MirrorLayer(external to mirror) ", supermirror_flat_s_prefix);
					sm_print_state("sm_reflect_or_transmit_at_mirror: sm_Transmitted, continue (stay in module).", state, sm);
					printf("\n\n");							
					#endif

					//Location: ReflectSide, sm_MirrorLayer(mirror to substrate)
					#if defined(NEUTRON_HISTORY_LIB)
					if ((sm->proc).is_tracking) {
						set_event(state, sm, sm_Transmitted);
						neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
						
						#if defined(DEBUG_sm_external_intersect)
						printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
						#endif
					}
					#endif
	
//////////////////////1.3 sm_AbsorberLayer(mirror to substrate), sm_Absorbed or sm_Transmitted-continue. 
					state->layer = sm_AbsorberLayer;
					#if defined(DEBUG_sm_external_intersect)
					printf(	"%s 1.3: sm_AbsorberLayer(mirror to substrate), call sm_transmit_through_absorber_at_plane, "
							"sm_Absorbed, sm_Exited, or sm_Transmitted-continue.\n",
							supermirror_flat_s_prefix);
					#endif
					
					//location: ReflectSide, sm_AbsorberLayer(external to mirror)
					outcome = sm_transmit_through_absorber_at_plane (state, sm);
					switch (outcome) {  
					
//////////////////////////1.3 sm_AbsorberLayer(mirror to substrate), sm_Absorbed. 
						case sm_Absorbed: //sm_AbsorberLayer(mirror to substrate), sm_Absorbed, return sm_Absorbed (exit module).
						{
							#if defined(DEBUG_sm_external_intersect)
							printf("%s 1.3 sm_AbsorberLayer(mirror to substrate) ", supermirror_flat_s_prefix);
							sm_print_state("sm_transmit_through_absorber_at_plane: sm_Absorbed, return sm_Absorbed (exit module).", state, sm);
							printf("\n\n");	
							#endif

							//location: ReflectSide, sm_AbsorberLayer(mirror to substrate)
							#if defined(NEUTRON_HISTORY_LIB)
							if ((sm->proc).is_tracking) {
								set_event(state, sm, sm_Absorbed);
								neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
								
								#if defined(DEBUG_sm_external_intersect)
								printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
								#endif
							}
							#endif

							return sm_Absorbed;
							break; 
						}

//////////////////////////1.3 sm_AbsorberLayer(mirror to substrate), sm_Exited. 
						case sm_Exited: //sm_AbsorberLayer(mirror to substrate), sm_Exited, return sm_Exited (exit module).
						{
							#if defined(DEBUG_sm_external_intersect)
							printf("%s 1.3: sm_AbsorberLayer(mirror to substrate) ", supermirror_flat_s_prefix);
							sm_print_state("sm_transmit_through_absorber_at_plane: sm_Exited, return sm_Exited (exit module).", state, sm);
							printf("\n\n");	
							#endif

							//location: ReflectSide, sm_AbsorberLayer(mirror to substrate)
							#if defined(NEUTRON_HISTORY_LIB)
							if ((sm->proc).is_tracking) {
								set_event(state, sm, sm_Exited);
								neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
								
								#if defined(DEBUG_sm_external_intersect)
								printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
								#endif
							}
							#endif

							return sm_Exited; //sm_Exited, return sm_Exited (exit module)
							break;
						}
						
//////////////////////////1.3 sm_AbsorberLayer(mirror to substrate), sm_Transmitted, continue. 
						case sm_Transmitted: //sm_AbsorberLayer(mirror to substrate), sm_Transmitted, continue.
						{
							#if defined(DEBUG_sm_external_intersect)
							printf("%s 1.3: sm_AbsorberLayer(mirror to substrate) ", supermirror_flat_s_prefix);
							sm_print_state("sm_transmit_through_absorber_at_plane: sm_Transmitted, continue.", state, sm);
							#endif

							//location: ReflectSide, sm_AbsorberLayer(mirror to substrate)
							#if defined(NEUTRON_HISTORY_LIB)
							if ((sm->proc).is_tracking) {
								set_event(state, sm, sm_Transmitted);
								neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
								
								#if defined(DEBUG_sm_external_intersect)
								printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
								#endif
							}
							#endif

//////////////////////////////1.4 sm_SubstrateSurfaceLayer(mirror to substrate), sm_Reflected-continue or sm_Transmitted-continue
							state->layer = sm_SubstrateSurfaceLayer;
							#if defined(DEBUG_sm_external_intersect)
							printf(	"%s 1.4: sm_SubstrateSurfaceLayer(mirror to substrate), call sm_reflect_or_transmit_at_interface, "
									"sm_Reflected-continue or sm_Transmitted-continue.\n", supermirror_flat_s_prefix);
							#endif

							//location: ReflectSide, sm_SubstrateSurfaceLayer(mirror to substrate)
							outcome = sm_reflect_or_transmit_at_substrate_surface (state, sm, going_inward, keep_reflection);
							switch (outcome) {
								
//////////////////////////////////1.4 sm_SubstrateSurfaceLayer(mirror to substrate), sm_Reflected, continue.
								case sm_Reflected: 
								{
									#if defined(DEBUG_sm_external_intersect)
									sm_print_refl("1.4: sm_SubstrateSurfaceLayer(mirror to substrate), sm_Reflected, continue.", state, sm);
									printf("%s 1.4: sm_SubstrateSurfaceLayer(mirror to substrate) ", supermirror_flat_s_prefix, state->n_surface_intersect);
									sm_print_state("sm_reflect_or_transmit_at_substrate_surface: sm_Reflected, continue.", state, sm);
									printf("\n\n");
									#endif
									
									//location: ReflectSide, sm_SubstrateSurfaceLayer(mirror to substrate)
									#if defined(NEUTRON_HISTORY_LIB)
									if ((sm->proc).is_tracking) {
										set_event(state, sm, sm_Reflected);
										neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
										
										#if defined(DEBUG_sm_external_intersect)
										printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
										#endif
									}
									#endif

//////////////////////////////////////1.5 Absorber Layer(substrate to mirror), sm_transmit_through_absorber_at_plane
									state->layer = sm_AbsorberLayer;
									#if defined(DEBUG_sm_external_intersect)
									printf(	"%s 1.5: sm_AbsorberLayer(substrate to mirror), sm_transmit_through_absorber_at_plane, "
											"sm_Absorbed, sm_Exited, or sm_Transmitted-continue.\n",supermirror_flat_s_prefix);
									#endif
									
									outcome = sm_transmit_through_absorber_at_plane (state, sm);
									switch (outcome) { 
//////////////////////////////////////////1.5 sm_AbsorberLayer(substrate to mirror), sm_Absorbed, return sm_Absorbed (exit module).
										case sm_Absorbed: 
										{
											#if defined(DEBUG_sm_external_intersect)
											printf("%s 1.5: sm_AbsorberLayer(substrate to mirror) ", supermirror_flat_s_prefix, state->n_surface_intersect);
											sm_print_state("sm_transmit_through_absorber_at_plane: sm_Absorbed, return sm_Absorbed (exit module).", state, sm);
											printf("\n\n");
											#endif

											//location: ReflectSide, sm_AbsorberLayer(substrate to mirror)
											#if defined(NEUTRON_HISTORY_LIB)
											if ((sm->proc).is_tracking) {
												set_event(state, sm, sm_Absorbed);
												neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
												
												#if defined(DEBUG_sm_external_intersect)
												printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
												#endif
											}
											#endif

											return sm_Absorbed;
											break; 
										}

//////////////////////////////////////////1.5 sm_AbsorberLayer(substrate to mirror), sm_Transmitted, continue.
										case sm_Transmitted: //sm_AbsorberLayer(substrate to mirror), sm_Transmitted, continue.
										{
											#if defined(DEBUG_sm_external_intersect)
											printf("%s 1.5: sm_AbsorberLayer(substrate to mirror) ", supermirror_flat_s_prefix);
											sm_print_state("sm_transmit_through_absorber_at_plane: sm_Transmitted, continue (stay in module).", state, sm);
											#endif

											//location: ReflectSide, sm_AbsorberLayer(substrate to mirror)
											#if defined(NEUTRON_HISTORY_LIB)
											if ((sm->proc).is_tracking) {
												set_event(state, sm, sm_Transmitted);
												neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
												
												#if defined(DEBUG_sm_external_intersect)
												printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
												#endif
											}
											#endif

//////////////////////////////////////////////1.6 sm_MirrorLayer(substrate to mirror), sm_Absorbed, sm_Transmitted-sm_Exited.
											state->layer = sm_MirrorLayer;
											#if defined(DEBUG_sm_external_intersect)
											printf(	"%s 1.6 sm_MirrorLayer(substrate to mirror), sm_reflect_or_transmit_at_mirror, ignore reflection"
													"sm_Absorbed, sm_Transmitted-continue.\n",supermirror_flat_s_prefix);
											#endif
									
											outcome = sm_reflect_or_transmit_at_mirror(state, sm, going_outward, ignore_reflection); 
											switch (outcome) { 
//////////////////////////////////////////////////1.6 sm_MirrorLayer(substrate to mirror), sm_Absorbed, return sm_Absorbed (exit module).
												case sm_Absorbed: 
												{
													#if defined(DEBUG_sm_external_intersect)
													printf("%s 1.6 sm_MirrorLayer(substrate to mirror) ", supermirror_flat_s_prefix, state->n_surface_intersect);
													sm_print_state("sm_reflect_or_transmit_at_mirror: sm_Absorbed, return sm_Absorbed (exit module).", state, sm);
													printf("\n\n");
													#endif

													//location: ReflectSide, sm_AbsorberLayer(substrate to mirror)
													#if defined(NEUTRON_HISTORY_LIB)
													if ((sm->proc).is_tracking) {
														set_event(state, sm, sm_Absorbed);
														neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
														
														#if defined(DEBUG_sm_external_intersect)
														printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
														#endif
													}
													#endif

													return sm_Absorbed;
													break; 
												}

//////////////////////////////////////////////////1.6 sm_MirrorLayer(substrate to mirror), sm_Transmitted-sm_Exited, return sm_Exited (exit module).
												case sm_Transmitted: 
												{
													#if defined(DEBUG_sm_external_intersect)
													printf("%s 1.6 sm_MirrorLayer(substrate to mirror) ", supermirror_flat_s_prefix, state->n_surface_intersect);
													sm_print_state("sm_reflect_or_transmit_at_mirror: sm_Transmitted-sm_Exited, return sm_Exited (exit module).", state, sm);
													printf("\n\n");
													#endif

													//location: ReflectSide, sm_MirrorLayer(substrate to mirror)
													#if defined(NEUTRON_HISTORY_LIB)
													if ((sm->proc).is_tracking) { 
													
														set_event(state, sm, sm_Transmitted);
														neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
														
														#if defined(DEBUG_sm_external_intersect)
														printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
														#endif

														set_event(state, sm, sm_Exited);
														neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);

														#if defined(DEBUG_sm_external_intersect)
														printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
														#endif	
													}
													#endif
													
													return sm_Exited;
													break; 
												}

												default: 
												{
													#if defined(DEBUG_sm_external_intersect) || defined(DEBUG_REF_LIB_CATCH_ANOMALY)
													sm_print_error(state, sm, "1.6 sm_MirrorLayer(substrate to mirror)", "sm_reflect_or_transmit_at_mirror return out of range.", outcome);
													#endif
													
													return sm_Error;
													break; 
												}
											}
											
											break; 
										}
										
										default: 
										{
											#if defined(DEBUG_sm_external_intersect) || defined(DEBUG_REF_LIB_CATCH_ANOMALY)
											sm_print_error(state, sm, "1.5 sm_AbsorberLayer(substrate to mirror)", "sm_transmit_through_layer return out of range.", outcome);
											#endif
											
											return sm_Error;
											break; 
										}

									}
							
									#if defined(DEBUG_sm_external_intersect)
									printf("%s 1.5: Done sm_AbsorberLayer(substrate to mirror), sm_transmit_through_layer.\n", supermirror_flat_s_prefix);
									#endif
									
									break;
								}
								
//////////////////////////////////1.4 sm_SubstrateSurfaceLayer(mirror to substrate), sm_Transmitted, return sm_Transmitted (stay in module).
								case sm_Transmitted: 
								{
									//ReflectSide, sm_SubstrateSurfaceLayer
									#if defined(DEBUG_sm_external_intersect)
									sm_print_refl("1.4: sm_SubstrateSurfaceLayer(mirror to substrate), sm_Transmitted, return sm_Transmitted (stay in module).", state, sm);
									printf("%s 1.4: sm_SubstrateSurfaceLayer(mirror to substrate) ",supermirror_flat_s_prefix);
									sm_print_state("sm_reflect_or_transmit_at_substrate_surface: sm_Transmitted, return sm_Transmitted (stay in module).", state, sm);
									printf("\n\n");							
									#endif
									
									//location: ReflectSide, sm_MirrorLayer(substrate to mirror)
									#if defined(NEUTRON_HISTORY_LIB)
									if ((sm->proc).is_tracking) { 

										set_event(state, sm, sm_Transmitted);
										neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
										
										#if defined(DEBUG_sm_external_intersect)
										printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
										#endif
									}
									#endif

									return sm_Transmitted;
									break;
								}
								
								default: 
								{
									sm_print_error(state, sm, "1.4 sm_SubstrateSurfaceLayer(mirror to substrate)", "sm_reflect_or_transmit_at_interface return out of range.", outcome);
									
									return sm_Error;
									break; 
								}
								
							}
							
							#if defined(DEBUG_sm_external_intersect)
							printf("%s 1.4: Done sm_SubstrateSurfaceLayer(mirror to substrate), sm_reflect_or_transmit_at_interface.\n", supermirror_flat_s_prefix);
							#endif
							
							break; 
						}
						
						default: 
						{
							sm_print_error(state, sm, "1.3 sm_AbsorberLayer(mirror to substrate)", "sm_transmit_through_layer return out of range.", outcome);
							
							return sm_Error;
							break; 
						}
						
					}
					
					#if defined(DEBUG_sm_external_intersect)
					printf("%s 1.3: Done sm_AbsorberLayer(mirror to substrate), sm_transmit_through_layer.\n", supermirror_flat_s_prefix);
					#endif

					break;
				}
				
				default: 
				{
					sm_print_error(state, sm, "1.2 sm_MirrorLayer(external to mirror)", "sm_reflect_or_transmit_at_interface return out of range.", outcome);
					return sm_Error;
					break; 
				}
				
			}
			
			#if defined(DEBUG_sm_external_intersect)
			printf("%s 1.2: Done sm_MirrorLayer(external to mirror), sm_reflect_or_transmit_at_interface.\n", 
					supermirror_flat_s_prefix);
			supermirror_flat_dec_prefix();
			#endif

			break;
		}
		
//////////1.1 sm_SubstrateLayer(external to substrate), transmitted into substrate, return sm_Transmitted (stay in module).
		case sm_SubstrateLayer: 
		{
			#if defined(DEBUG_sm_external_intersect)
			printf("%s 1.1: sm_Intersected, sm_SubstrateLayer.\n\n", supermirror_flat_s_prefix);
			#endif
			
			if ( (((sm->mat).sub).sub_type & sm_sub_type_front_edge_attn) == sm_sub_type_front_edge_attn) {

				#if defined(DEBUG_sm_external_intersect)
				printf("sm_external_intersect blocked at edge %d %d %d\n", (sm->mat).sub.sub_type, sm_sub_type_front_edge_attn, (((sm->mat).sub).sub_type) & sm_sub_type_front_edge_attn);
				#endif

				#if defined(NEUTRON_HISTORY_LIB)
				if ((sm->proc).is_tracking) {
					set_event(state, sm, sm_Absorbed);
					neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
					
					#if defined(DEBUG_sm_external_intersect)
					printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
					#endif
				}
				#endif
				
				return sm_Absorbed;
			}
			#if defined(DEBUG_sm_external_intersect)
			else {
				printf("sm_external_intersect enter from edge %d %d %d\n", (sm->mat).sub.sub_type, sm_sub_type_front_edge_attn, (sm->mat).sub.sub_type & sm_sub_type_front_edge_attn);
			}
			#endif
			
//////////////update internal reflection state variables
			state->n_surface_intersect = 1;
			state->n_mirror_intersect = 0;

			#if defined(DEBUG_sm_external_intersect)
			printf("%s 1.1: sm_SubstrateLayer(external to substrate) ", supermirror_flat_s_prefix);
			sm_print_state ("sm_Transmitted, return sm_Transmitted (stay in module).", state, sm);
			printf("\n\n");							
			#endif
			
			#if defined(NEUTRON_HISTORY_LIB)
			if ((sm->proc).is_tracking) {
				set_event(state, sm, sm_Transmitted);
				neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
				
				#if defined(DEBUG_sm_external_intersect)
				printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
				#endif
			}
			#endif
			
			#if defined(DEBUG_sm_external_intersect)
			supermirror_flat_dec_prefix();
			#endif
			
			return sm_Transmitted;

			break;
		}
		
		default: 
		{
			//sm_Error
			sm_print_error(state, sm, "1.1 switch (state->layer)", "state->layer is neither sm_MirrorLayer or sm_SubstrateLayer return out of range.", sm_Error);
			
			return sm_Error;
			break; 
		}
		
	}
	
	#if defined(DEBUG_sm_external_intersect)
	printf("%s 1: Done sm_external_intersect\n\n", supermirror_flat_s_prefix);
	supermirror_flat_dec_prefix();
	#endif

}

int sm_internal_intersect(SimState *state, Supermirror *sm) 
//neutron is inside the supermirror substrate, 
//calculate intersects 2nd (if 1st is mirror), possible 3rd (if 1st is edge, 2nd is mirror), and last intersect before absorbed or transmitted out 
{
//#define DEBUG_sm_internal_intersect
	#if defined(DEBUG_sm_internal_intersect)
	printf(	"%s int sm_internal_intersect(SimState *state, Supermirror *sm)\n"
			"%s state=%X, sm=%X\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, state, sm);
	supermirror_flat_inc_prefix();
	printf(	"%s ws, w,t,p,v:|v| = % 7.4f,%5e,% 7.4f,(% 7.4f,% 7.4f,% 7.4f),(% 7.4f,% 7.4f,% 7.4f):% 7.4f\n"
			"%s s3:|s|:s2 = (% 7.4f,% 7.4f,% 7.4f):% 7.4f:(% 7.4f,% 7.4f)\n", 
			supermirror_flat_s_prefix, (state->ws[0]+state->ws[1]), state->w, state->t, (state->p).x,(state->p).y,(state->p).z,(state->v).x,(state->v).y,(state->v).z, coords_len(state->v), 
			supermirror_flat_s_prefix, (state->s).x,(state->s).y,(state->s).z, coords_sp((sm->co).fa, state->s),(1+coords_sp((sm->co).fa, state->s))/2,(1-coords_sp((sm->co).fa, state->s))/2);
	#endif

	#if defined(DEBUG_sm_internal_intersect)
	printf("%s%d.0: ", supermirror_flat_s_prefix, state->n_surface_intersect);
	sm_print_state("incoming", state, sm);
	printf("\n");
	#endif
	
	#if defined(DEBUG_sm_internal_intersect)
	printf(	"mcget_run_num()=%d, n_surface_intersect=%d, n_mirror_intersect=%d\n",
			mcget_run_num(), state->n_surface_intersect, state->n_mirror_intersect);
	#endif	

	double v_len = state->v_len = coords_len(state->v); 
	double vn_len = state->vn_len = fabs(coords_sp(state->v, state->fn));
	
	int outcome;
	
//////n.1 from n-1 intersect, through substrate, to attenuate along the way
	//Start at n-1 intersect, sm_SubstrateLayer
	//n.1 sm_SubstrateLayer, sm_transmit_through_substrate, sm_Absorbed or sm_Transmitted-continue.

	#if defined(DEBUG_sm_internal_intersect)
	printf(	"before substrate\t"
			"z,w,t,p,v = % 7.4f, %5e,% 7.4f,(% 7.4f,% 7.4f,% 7.4f),(% 7.4f,% 7.4f,% 7.4f)\n", 
			(state->p).z, state->w, state->t, (state->p).x,(state->p).y,(state->p).z,(state->v).x,(state->v).y,(state->v).z);
	#endif

	state->layer = sm_SubstrateLayer;
	#if defined(DEBUG_sm_internal_intersect)
	printf(	"%s %d.1: sm_SubstrateLayer, call sm_transmit_through_substrate, sm_Absorbed, sm_Exited, or sm_Transmitted-continue.\n", 
			supermirror_flat_s_prefix, state->n_surface_intersect);
	#endif
	
	outcome = sm_transmit_through_substrate(state, sm);
	switch (outcome) {  
//////////n.1 sm_SubstrateLayer, sm_Absorbed, return sm_Absorbed (exit module)
		case sm_Absorbed: 
		{
			#if defined(DEBUG_sm_internal_intersect)
			printf("%s %d.1: sm_SubstrateLayer ", supermirror_flat_s_prefix, state->n_surface_intersect);
			sm_print_state("sm_transmit_through_substrate: sm_Absorbed, return sm_Absorbed (exit module).", state, sm);
			printf("\n\n");
			#endif
			
			//Location: Either side, sm_SubstrateLayer
			#if defined(NEUTRON_HISTORY_LIB)
			if ((sm->proc).is_tracking) {
				set_event(state, sm, sm_Absorbed);
				neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
				
				#if defined(DEBUG_sm_internal_intersect)
				printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
				#endif
			}
			#endif

			return sm_Absorbed;
			break; 
		}
		
//////////n.1 sm_SubstrateLayer, exit from edge, sm_Exited, return sm_Exited (exit module)
		case sm_Exited: 
		{
			#if defined(DEBUG_sm_internal_intersect)
			printf("%s %d.1: sm_SubstrateLayer ", supermirror_flat_s_prefix, state->n_surface_intersect);
			sm_print_state("sm_transmit_through_substrate: sm_Exited, return sm_Exited (exit module).", state, sm);
			printf("\n\n");
			#endif
			
			//Location: Either side, sm_SubstrateLayer
			#if defined(NEUTRON_HISTORY_LIB)
			if ((sm->proc).is_tracking) {
				set_event(state, sm, sm_Exited);
				neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
				
				#if defined(DEBUG_sm_internal_intersect)
				printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
				#endif
			}
			#endif

			return sm_Exited;
			break; 
		}
		
//////////n.1 sm_SubstrateLayer, transmitted to a mirror layer, sm_Transmitted, continue.
		case sm_Transmitted: //transmitted through substrate layer to the opposing mirror side, continue to next step
		{
			#if defined(DEBUG_sm_internal_intersect)
			printf("%s %d.1: sm_SubstrateLayer ", supermirror_flat_s_prefix, state->n_surface_intersect);
			sm_print_state("sm_transmit_through_substrate: sm_Transmitted-continue.", state, sm);
			printf("\n\n");
			#endif

			//Location: Eitehr side, sm_MirrorLayer(mirror to substrate)
			#if defined(NEUTRON_HISTORY_LIB)
			if ((sm->proc).is_tracking) {
				set_event(state, sm, sm_Transmitted);
				neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
				
				#if defined(DEBUG_sm_internal_intersect)
				printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
				#endif
			}
			#endif
			
//////////////n.2 sm_SubstrateSurfaceLayer(substract to mirror), sm_reflect_or_transmit_at_substrate_surface, sm_Reflected (stay in module) or sm_transmitted-continue
			state->layer = sm_SubstrateSurfaceLayer;
			
			if (state->n_mirror_intersect == 0) {
				//entered from edge, transmitted to the side of a mirror plane
				state->side = sm_TransmittedSide; 
				state->side_at_plane[state->plane] = sm_TransmittedSide;
				state->side_at_plane[1-state->plane] = sm_ReflectedSide;
			}

			++(state->n_surface_intersect);
			++(state->n_mirror_intersect);
			
			#if defined(DEBUG_sm_internal_intersect)
			printf(	"%s %d.2: sm_SubstrateLayer(substrate to mirror), call sm_calc_surface_parameters, sm_reflect_or_transmit_at_mirror, "
					"sm_Absorbed, sm_Reflected-sm_Exited, or sm_Transmitted-continue.\n",
					supermirror_flat_s_prefix, state->n_surface_intersect);
			#endif

			if (state->set_surface_parameters == 0) {
				sm_calc_surface_parameters(state, sm, going_outward);
			}
			
			outcome = sm_reflect_or_transmit_at_substrate_surface (state, sm, going_outward, keep_reflection); 
			switch (outcome) {
				
//////////////////n.2 sm_SubstrateSurfaceLayer(substrate to mirror), sm_Reflected, return sm_Reflected (stay in module).
				case sm_Reflected: 
				{	
					#if defined(DEBUG_sm_internal_intersect)
					printf("%s %d.2: ", supermirror_flat_s_prefix, state->n_surface_intersect);
					sm_print_state("sm_reflect_or_transmit_at_substrate_surface: sm_Reflected, return sm_Reflected (stay in module).", state, sm);
					printf("\n\n");
					#endif

					//Location: Either side, sm_SubstrateSurfaceLayer(substrate to mirror)
					#if defined(NEUTRON_HISTORY_LIB)
					if ((sm->proc).is_tracking) {
						set_event(state, sm, sm_Reflected);
						neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
						
						#if defined(DEBUG_sm_internal_intersect)
						printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
						#endif
					}
					#endif
					
					return sm_Reflected; //stay in module
					break;
				}
						
//////////////////n.2 sm_SubstrateSurfaceLayer(substrate to mirror), sm_Transmitted, continue.
				case sm_Transmitted: 
				{
					#if defined(DEBUG_sm_internal_intersect)
					printf("%s %d.2: ", supermirror_flat_s_prefix, state->n_surface_intersect);
					sm_print_state("sm_reflect_or_transmit_at_substrate_surface: sm_Transmitted, continue.", state, sm);
					printf("\n\n");
					#endif

					//Location: Either side, sm_SubstrateSurfaceLayer(substrate to mirror)
					#if defined(NEUTRON_HISTORY_LIB)
					if ((sm->proc).is_tracking) {
						set_event(state, sm, sm_Transmitted);
						neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
						
						#if defined(DEBUG_sm_internal_intersect)
						printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
						#endif
					}
					#endif
					
//////////////////////n.3 sm_AbsorberLayer(substrate to mirror), sm_transmit_through_absorber_at_plane, sm_Absorbed, sm_Exited or sm_Transmitted-continue.
					state->layer = sm_AbsorberLayer;
					#if defined(DEBUG_sm_internal_intersect)
					printf(	"%s %d.3: sm_AbsorberLayer(substrate to mirror), call sm_transmit_through_absorber_at_plane, "
							"sm_Absorbed or sm_Transmitted-continue.\n", 
							supermirror_flat_s_prefix, state->n_surface_intersect);
					#endif

					//sm_TransmittedSide or sm_ReflectedSide
					outcome = sm_transmit_through_absorber_at_plane (state, sm);
					switch (outcome) { 

//////////////////////////n.3 sm_AbsorberLayer(substrate to mirror), sm_Absorbed, return sm_Absorbed (exit module).
						case sm_Absorbed: 
						{
							#if defined(DEBUG_sm_internal_intersect)
							printf("%s %d.3: ", supermirror_flat_s_prefix, state->n_surface_intersect);
							sm_print_state("sm_transmit_through_absorber_at_plane: sm_Absorbed, return sm_Absorbed (exit module).", state, sm);
							printf("\n\n");
							#endif

							//Location: Either side, sm_AbsorberLayer(substrate to mirror)
							#if defined(NEUTRON_HISTORY_LIB)
							if ((sm->proc).is_tracking) {
								set_event(state, sm, sm_Absorbed);
								neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
								
								#if defined(DEBUG_sm_internal_intersect)
								printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
								#endif
							}
							#endif
							
							return sm_Absorbed;
							break; 
						}
						
//////////////////////////n.3 sm_AbsorberLayer(substrate to mirror), sm_Exited, return sm_Exited (exit module)
						case sm_Exited: 
						{
							#if defined(DEBUG_sm_internal_intersect)
							printf("%s %d.3: ", supermirror_flat_s_prefix, state->n_surface_intersect);
							sm_print_state("sm_transmit_through_absorber_at_plane: sm_Exited, return sm_Exited (exit module).", state, sm);
							printf("\n\n");
							#endif
							
							//Location: Eitehr side, sm_AbsorberLayer(substrate to mirror)
							#if defined(NEUTRON_HISTORY_LIB)
							if ((sm->proc).is_tracking) {
								set_event(state, sm, sm_Exited);
								neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
								
								#if defined(DEBUG_sm_internal_intersect)
								printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
								#endif
							}
							#endif
							
							return sm_Exited;
							break; 
						}
						
//////////////////////////n.3 sm_AbsorberLayer(substrate to mirror), sm_Transmitted, continue
						case sm_Transmitted: 
						{
							#if defined(DEBUG_sm_internal_intersect)
							printf("%s %d.3: ", supermirror_flat_s_prefix, state->n_surface_intersect);
							sm_print_state("sm_transmit_through_absorber_at_plane: sm_Transmitted, continue.", state, sm);
							printf("\n\n");
							#endif

							//Location: Either side, sm_AbsorberLayer(substrate to mirror)
							#if defined(NEUTRON_HISTORY_LIB)
							if ((sm->proc).is_tracking) {
								set_event(state, sm, sm_Transmitted);
								neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
								
								#if defined(DEBUG_sm_internal_intersect)
								printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
								#endif
							}
							#endif

//////////////////////////////n.4 sm_MirrorLayer(substrate to mirror), sm_reflect_or_transmit_at_mirror, sm_Absorbed, sm_Transmitted-sm_Exited or sm_Reflected-continue.
							state->layer = sm_MirrorLayer;
							#if defined(DEBUG_sm_internal_intersect)
							printf(	"%s %d.4: sm_MirrorLayer(substrate to mirror), call sm_reflect_or_transmit_at_mirror, "
									"sm_Transmitted-sm_Exited(exit module) or sm_Reflected-continue.\n", 
									supermirror_flat_s_prefix, state->n_surface_intersect);
							#endif

							outcome = sm_reflect_or_transmit_at_mirror(state, sm, going_outward, keep_reflection);
							switch (outcome) { 
						
//////////////////////////////////n.4 sm_MirrorLayer(substrate to mirror), sm_Absorbed.
								case sm_Absorbed: 
								{
									#if defined(DEBUG_sm_internal_intersect)
									printf("%s n.4: sm_MirrorLayer(substrate to mirror) ", supermirror_flat_s_prefix);
									sm_print_state("sm_reflect_or_transmit_at_mirror: sm_Absorbed, return sm_Absorbed (exit module).", state, sm);
									printf("\n\n");	
									#endif
									
									//location: Either side, sm_MirrorLayer(substrate to mirror)
									#if defined(NEUTRON_HISTORY_LIB)
									if ((sm->proc).is_tracking) {
										set_event(state, sm, sm_Absorbed);
										neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
										
										#if defined(DEBUG_sm_internal_intersect)
										printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
										#endif
									}
									#endif

									return sm_Absorbed;
									break; 
								}

//////////////////////////////////n.4 sm_MirrorLayer(substrate to mirror), sm_Transmitted-sm_Exited.
								case sm_Transmitted: 
								{
									#if defined(DEBUG_sm_internal_intersect)
									printf("%s %d.4: ", supermirror_flat_s_prefix, state->n_surface_intersect);
									sm_print_state("sm_reflect_or_transmit_at_mirror: sm_Transmitted, sm_Exited, return sm_Exited (exit module).", state, sm);
									printf("\n\n");
									#endif
									
									//Location: Either side, sm_MirrorLayer
									#if defined(NEUTRON_HISTORY_LIB)
									if ((sm->proc).is_tracking) {
										set_event(state, sm, sm_Transmitted);
										neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);

										#if defined(DEBUG_sm_internal_intersect)
										printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
										#endif

										set_event(state, sm, sm_Exited);
										neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
										
										#if defined(DEBUG_sm_internal_intersect)
										printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
										#endif
									}
									#endif

									return sm_Exited; //Exit
									break;
								}
										
//////////////////////////////////n.4 sm_MirrorLayer(substrate to mirror), sm_Reflected, continue
								case sm_Reflected: 
								{
									#if defined(DEBUG_sm_internal_intersect)
									printf("%s %d.4: ", supermirror_flat_s_prefix, state->n_surface_intersect);
									sm_print_state("sm_reflect_or_transmit_at_mirror: sm_Reflected, continue.", state, sm);
									printf("\n\n");
									#endif
									
									//Location: sm_TransmittedSide or sm_ReflectedSide, sm_MirrorLayer
									#if defined(NEUTRON_HISTORY_LIB)
									if ((sm->proc).is_tracking) {
										set_event(state, sm, sm_Reflected);
										neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);

										#if defined(DEBUG_sm_internal_intersect)
										printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
										#endif
									}
									#endif

									
//////////////////////////////////////n.5 sm_AbsorberLayer(mirror to substrate), sm_Absorbed or sm_Transmitted-continue.
									#if defined(DEBUG_sm_internal_intersect)
									printf(	"%s %d.5: sm_AbsorberLayer(mirror to substrate), call sm_transmit_through_absorber_at_plane, "
											"sm_Absorbed, sm_Exited, or sm_Transmitted-continue.\n", 
											supermirror_flat_s_prefix, state->n_surface_intersect);

									#endif
										
									outcome = sm_transmit_through_absorber_at_plane(state, sm);
									switch (outcome) { 
									
//////////////////////////////////////////n.5 sm_AbsorberLayer(mirror to substrate), sm_Absorbed, return sm_Absorbed (exit module).
										case sm_Absorbed: 
										{
											#if defined(DEBUG_sm_internal_intersect)
											printf("%s %d.5: sm_AbsorberLayer(mirror to substrate) ", supermirror_flat_s_prefix, state->n_surface_intersect);
											sm_print_state("sm_transmit_through_absorber_at_plane: sm_Absorbed, return sm_Absorbed (exit module).", state, sm);
											printf("\n\n");							
											#endif

											//Location: Either side, sm_AbsorberLayer
											#if defined(NEUTRON_HISTORY_LIB)
											if ((sm->proc).is_tracking) {
												set_event(state, sm, sm_Absorbed);
												neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);

												#if defined(DEBUG_sm_internal_intersect)
												printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
												#endif
											}
											#endif

											return sm_Absorbed;
											break; 
										}

//////////////////////////////////////////n.5 sm_AbsorberLayer(mirror to substrate), sm_Exited, return sm_Exited (exit module).
										case sm_Exited: 
										{
											#if defined(DEBUG_sm_internal_intersect)
											printf("%s %d.5: sm_AbsorberLayer(mirror to substrate) ", supermirror_flat_s_prefix, state->n_surface_intersect);
											sm_print_state("sm_transmit_through_absorber_at_plane: sm_Exited, return sm_Exited (exit module).", state, sm);
											printf("\n\n");	
											#endif

											//Location: Either side, sm_AbsorberLayer
											#if defined(NEUTRON_HISTORY_LIB)
											if ((sm->proc).is_tracking) {
												set_event(state, sm, sm_Exited);
												neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);

												#if defined(DEBUG_sm_internal_intersect)
												printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
												#endif
											}
											#endif

											return sm_Exited;
											break; 
										}

//////////////////////////////////////////n.5 sm_AbsorberLayer(mirror to substrate), sm_Transmitted, continue.
										case sm_Transmitted: 
										{
											#if defined(DEBUG_sm_internal_intersect)
											printf("%s %d.5: sm_AbsorberLayer(mirror to substrate) ", supermirror_flat_s_prefix, state->n_surface_intersect);
											sm_print_state("sm_transmit_through_absorber_at_plane: sm_Transmitted, continue.", state, sm);
											printf("\n\n");	
											#endif
											
											//Location: Either side, sm_AbsorberLayer
											#if defined(NEUTRON_HISTORY_LIB)
											if ((sm->proc).is_tracking) {
												set_event(state, sm, sm_Transmitted);
												neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);

												#if defined(DEBUG_sm_internal_intersect)
												printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
												#endif
											}
											#endif


//////////////////////////////////////////////n.6 sm_SubstrateSurfaceLayer, sm_Transmitted-continue
											state->layer = sm_SubstrateSurfaceLayer;
											#if defined(DEBUG_sm_internal_intersect)
											printf(	"%s%d.6: sm_SubstrateSurfaceLayer(mirror to substrate), call sm_reflect_or_transmit_at_substrate_surface, "
													"sm_Transmitted, continue.", 
													supermirror_flat_s_prefix, state->n_surface_intersect);
											#endif

											//sm_TransmittedSide or sm_ReflectedSide, sm_SubstrateSurfaceLayer
											outcome = sm_reflect_or_transmit_at_substrate_surface(state, sm, going_inward, ignore_reflection); 

											#if defined(DEBUG_sm_internal_intersect)
											printf("%s%d.6: sm_SubstrateSurfaceLayer(mirror to substrate) ", supermirror_flat_s_prefix, state->n_surface_intersect);
											sm_print_state("sm_reflect_or_transmit_at_substrate_surface: sm_Transmitted, return sm_Transmitted (stay in module).", state, sm);
											printf("\n\n");							
											#endif
	
											#if defined(NEUTRON_HISTORY_LIB)
											if ((sm->proc).is_tracking) { 
												set_event(state, sm, sm_Transmitted);
												neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
												
												#if defined(DEBUG_sm_internal_intersect)
												printf("%s neutron_history_add_record %s %s\n", supermirror_flat_s_prefix, state->location, state->event);
												#endif
											}
											#endif
											
											return sm_Transmitted; //stay in module
	
											break; 
										}

										default: 
										{
											sm_print_error(state, sm, "n.5: sm_AbsorberLayer(mirror to substrate)", "sm_transmit_through_absorber_at_plane return out of range", outcome);
											
											#if defined(DEBUG_sm_internal_intersect)	
											sprintf(track_msg, "%s%d.E ", track_msg, state->n_surface_intersect);
											#endif
											
											return sm_Error;
											break; 
										}
									}
								}
										
								default: 
								{
									sm_print_error(state, sm, "n.4: sm_MirrorLayer(substrate to mirror)", "sm_reflect_or_transmit_at_mirror return out of range", outcome);
									
									#if defined(DEBUG_sm_internal_intersect)	
									sprintf(track_msg, "%s%d.D ", track_msg, state->n_surface_intersect);
									#endif
									
									return sm_Error;
									break; 
								}
							}
							
							break; 
						}
						
						default: 
						{
							sm_print_error(state, sm, "n.3: sm_AbsorberLayer(substrate to mirror)", "sm_transmit_through_absorber_at_plane return out of range", outcome);

							#if defined(DEBUG_sm_internal_intersect)	
							sprintf(track_msg, "%s%d.D ", track_msg, state->n_surface_intersect);
							#endif
							
							return sm_Error;
							break; 
						}
					}
						
					break;
				}

				default: 
				{
					sm_print_error(state, sm, "n.2: sm_SubstrateSurfaceLayer(substract to mirror)", "sm_reflect_or_transmit_at_substrate_surface return out of range", outcome);

					#if defined(DEBUG_sm_internal_intersect)	
					sprintf(track_msg, "%s%d.D ", track_msg, state->n_surface_intersect);
					#endif
					
					return sm_Error;
					break; 
				}
				
			}
				
			break; 
		}
		
		default: 
		{
			sm_print_error(state, sm, "n.1: sm_SubstrateLayer", "sm_transmit_through_layer return out of range", outcome);

			#if defined(DEBUG_sm_internal_intersect)	
			sprintf(track_msg, "%s%d.D ", track_msg, state->n_surface_intersect);
			#endif
			
			return sm_Error;
			break; 
		}

	}
	
}

int sm_internal_reflections(SimState *state, Supermirror *sm) 
//calculate internal reflections and finally either absorbed or transmitted out of the supermirror
{
//#define DEBUG_sm_internal_reflections
	#if defined(DEBUG_sm_internal_reflections)
	printf(	"%s int sm_internal_reflections(SimState *state, Supermirror *sm)\n"
			"%s state=%X, sm=%X\n", 
			supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, state, sm);
	#endif
	#if defined(DEBUG_sm_internal_reflections)
	printf("%s incoming t,p,v:|v| = % 7.4f,(% 7.4f,% 7.4f,% 7.4f),(% 7.4f,% 7.4f,% 7.4f):% 7.4f\n", supermirror_flat_s_prefix, 
		state->t, state->p.x, state->p.y, state->p.z, state->v.x, state->v.y, state->v.z, coords_len(state->v));
	sm_print_state ("0: incident", state, sm);
	#endif
	
	#if defined(DEBUG_REF_LIB_TRACK)	
	sprintf(track_msg, "%sir.1 ", track_msg);
	#endif
	
//////ir.1 starting point is time to transit to supermirror edge exit and time to transit between mirrors 
	
	//ir.1 Calculate how long it takes to reach one of the edges of the supermirror using surface velocity
	//Find line-polyhedron intersects
	//itype: 1=x plane, 2=x edge, 3=x vertex, 4=on plane, 5=on edge

	#if defined(DEBUG_sm_internal_reflections)
	printf("%s ir.1: Call line_polyhedron_intersect to find intersect of Vs\n",supermirror_flat_s_prefix);
	#endif
	
	
	//polyhedron intersect parameters
	int n_skip_plane = 2; int skip_plane[n_skip_plane];
	skip_plane[0] = 0; skip_plane[1] = 1; 
	int num_intersect = 1; //only use values of the first intersect
	double idtime[2];
	Coords idpoint[2];
	double itime[2];
	Coords ipoint[2];
	int iplane[2];
	int itype[2]; ////type: 1=x plane, 2=x edge, 3=x vertex, 4=on plane, 5=on edge
	line_polyhedron_intersect(state->t, state->p, state->v, &(sm->geo), Maximum_On_Plane_Distance, n_skip_plane, skip_plane, 
								state->last_time, state->last_point, state->last_plane, 
								&num_intersect, idtime, idpoint, itime, ipoint, iplane, itype); 


	#if defined(DEBUG_sm_internal_reflections)
	sm_print_intersect("ir.1 vs:",num_intersect, idtime, idpoint, itime, ipoint, iplane, itype);
	#endif
	
	if (num_intersect == 0 || itype[0] > 3) { //something's not right

		printf("%s ir.1: Something's wrong. VS to reach end of mirror. Inside mirror but no intersect. Return 0 (exit module)\n",supermirror_flat_s_prefix);

		#if defined(DEBUG_REF_LIB_TRACK)	
		sprintf(track_msg, "%s ir.1 ", track_msg);
		#endif

//		#if defined(DEBUG_sm_internal_reflections) || defined(DEBUG_REF_LIB_CATCH_ANOMALY)
//		printf("calling line_polyhedron_intersect_debug\n");
//		line_polyhedron_intersect_debug(state->t, state->p, state->v, &(sm->geo), Maximum_On_Plane_Distance, n_skip_plane, skip_plane, 
//								state->last_time, state->last_point, state->last_plane, 
//								&num_intersect, idtime, idpoint, itime, ipoint, iplane, itype);
//		#endif

		return sm_Error; //somethings wrong, exit calculation
	}
	
	double idts, idtn;
	//idts=time it takes to reach the edge of sm
	idts = idtime[0];
	
	//idtn=time it takes between each internal reflection is state->t_prop_sub
	idtn = state->t_prop_sub;
	
	if (idts <= idtn) {
		//no more internal reflection, bring neutron to edge
		state->t += idts; 
		state->p = coords_add(state->p, coords_scale(state->v, idts));
		return sm_Exited;
	}
	
//////ir.2 Prepare parameters to calculate internal reflections 

	int plane, spin;
	
	//p =	starting p
	//		time from one layer to another * vs * ir_n + 
	//		time from one layer to another * vn if jumping from starting side to the other side (ir_r=1)
	//ir_p0 = starting p
	//ir_dps = time from one layer to another * vs
	//ir_dpn = time from one layer to another * vn
	plane = state->plane;
	Coords fn = state->fn;
	Coords ir_p0 = state->p;
	Coords ir_dps = coords_scale(coords_xp(coords_xp(fn, state->v), fn), idtn);
	Coords ir_dpn = coords_scale(fn, coords_sp(fn, state->v) * idtn); 
	
	double 	T_prop_sub, Rs_sub_to_vac_at_plane[2], T_prop_abs_at_plane[2], Rm_vac_to_mir_at_plane[2][2]; 
	T_prop_sub = state->T_prop_sub; 
	for (plane = 0; plane < SM_Num_Mirror_Planes; plane++) {
		Rs_sub_to_vac_at_plane[plane] = state->Rs_sub_to_vac_at_plane[plane];
		T_prop_abs_at_plane[plane] = state->T_prop_abs_at_plane[plane];
		for (spin = 0; spin < SM_Num_Spin_States; spin++) {
			Rm_vac_to_mir_at_plane[plane][spin] = state->Rm_vac_to_mir_at_plane[plane][spin];
		}
	}
		
	#if defined(DEBUG_sm_internal_reflections)
	printf("sm_internal_reflections: start plane = %d\n", plane); 
	printf("sm_internal_reflections: T_prop_sub = %lf\n", T_prop_sub); 
	for (plane = 0; plane < SM_Num_Mirror_Planes; plane++) {
		printf("sm_internal_reflections: Rs_sub_to_vac_at_plane[plane=%d] = %lf\n", plane, Rs_sub_to_vac_at_plane[plane]);
		printf("sm_internal_reflections: T_prop_abs_at_plane[plane=%d] = %lf\n", plane, T_prop_abs_at_plane[plane]);
		for (spin = 0; spin < SM_Num_Spin_States; spin++) {
			printf("sm_internal_reflections: Rm_vac_to_mir_at_plane[plane=%d][spin=%d] = %lf\n", plane, spin, Rm_vac_to_mir_at_plane[plane][spin]);
		}
	}
	#endif

	
//////ir.3 calculate how many internal reflections and the last step absorption or exit parameters 
	
	//ir_n_max = maximum zigzags
	//starting at ir_n=0, ir_r=0, 
	//loop ir_n until ir_n_max-1
	//ir_plane = 1 - ir_plane, ir_r = 1 - ir_r when neutron reaches the opposite substrate surface
	int outcome;
	
	int ir_n, ir_n_max, ir_r;
	ir_n_max = (int)floor(idts/idtn);
	
	int ir_side, ir_plane, ir_layer;
	ir_plane = state->plane;
	
	double ir_w = state->w, 
			ir_t0 = state->t, 
			dt_last = 0; 
	Coords ir_p, ir_v;
	double ir_ws[2];
	for (spin = 0; spin < SM_Num_Spin_States; spin++) {
		ir_ws[spin] = state->ws[spin];
	}
	
	double T_prop_sub_rand, ws_Rm_at_plane, ir_ws_sum; 
	
	#if defined(NEUTRON_HISTORY_LIB)
	if ((sm->proc).is_tracking) {
		
		//tracking

		ir_side = state->side_at_plane[ir_plane];
		
		double ir_t = state->t;
		ir_v = state->v_in_sub_inward_at_plane[ir_plane];
		Coords ir_s = state->s;
		
		ir_n = 0;
		ir_r = 0;
		while (ir_n < ir_n_max) {
			
			//transmitted or absorbed through substrate
			//rand01: transmitted (0, T_prop_sub), absorbed (T_prop_sub, 1)
			//transmitted T_prop_sub == 1, absorbed T_prop_sub == 0
			ir_layer = sm_SubstrateLayer;
			if (T_prop_sub < 1) {
				if (T_prop_sub < ZERO_THRESHOLD) {
					outcome = sm_Absorbed;
					break;
				}
				else {
					T_prop_sub_rand = rand01(); //probability of absorption, use for further processing
					if (T_prop_sub_rand >= T_prop_sub) {
						//Absorbed by substrate
						dt_last = -log(T_prop_sub_rand) * state->L_attn_sub / state->v_len;
						outcome = sm_Absorbed;
						break;
					}
				}
			}
			//transmitted through substrate
			//reach the other side of the substrate, update ir_r, ir_plane. 
			++ir_n;
			ir_r = 1 - ir_r;
			ir_plane = 1 - ir_plane;
			ir_side = state->side_at_plane[ir_plane];
			ir_t = ir_t0 + ir_n * idtn; 
			ir_p = coords_add(ir_p0, coords_scale(ir_dps, ir_n)); 
			if (ir_r == 1) ir_p = coords_add(ir_p, ir_dpn);

			#if defined(NEUTRON_HISTORY_LIB)
			neutron_history_add_record(
				((sm->proc).location)[ir_side][ir_plane][ir_layer], 
				((sm->proc).event)[sm_Transmitted], 
				ir_w, ir_t, ir_p, ir_v, ir_s);
			#endif
			
			//transmitted or reflected at Substrate interface 
			//neutron inside substrate, either there is mirror reflection or there is substrate reflection, or neither.
			//i.e. if there is mirror coating, Rs == 0,
			//rand01: reflected (0, Rs), transmitted (Rs, 1)
			//transmitted Rs == 0, reflected Rs == 1 
			ir_layer = sm_SubstrateSurfaceLayer;
			if (Rs_sub_to_vac_at_plane[ir_plane] > 0) {
				if (rand01() <= Rs_sub_to_vac_at_plane[ir_plane]) {
					//reflected by substrate interface back into substrate
					ir_v = state->v_in_sub_inward_at_plane[ir_plane];

					#if defined(NEUTRON_HISTORY_LIB)
					neutron_history_add_record(
						((sm->proc).location)[ir_side][ir_plane][ir_layer], 
						((sm->proc).event)[sm_Zigzag], 
						ir_w, ir_t, ir_p, ir_v, ir_s);
					#endif
					
					continue;
				}
			}
			//transmitted through substrate interface
			ir_v = state->v_in_sub_outward_at_plane[ir_plane];

			#if defined(NEUTRON_HISTORY_LIB)
			neutron_history_add_record(
				((sm->proc).location)[ir_side][ir_plane][ir_layer], 
				((sm->proc).event)[sm_Transmitted], 
				ir_w, ir_t, ir_p, ir_v, ir_s);
			#endif

			//transmitted or absorbed through absorber layer
			//rand01: transmitted (0, T_prop_abs_at_plane[ir_plane]), absorbed (T_prop_abs_at_plane[ir_plane], 1)
			//transmitted T_prop_abs_at_plane[ir_plane] == 1, absorbed T_prop_abs_at_plane[ir_plane] == 0
			ir_layer = sm_AbsorberLayer;
			if (T_prop_abs_at_plane[ir_plane] < 1) {
				if (rand01() >= T_prop_abs_at_plane[ir_plane]) {
					//Absorbed by absorber
					outcome = sm_Absorbed;
					break;
				}
			}
			//transmitted through absorber layer
			#if defined(NEUTRON_HISTORY_LIB)
			neutron_history_add_record(
				((sm->proc).location)[ir_side][ir_plane][ir_layer], 
				((sm->proc).event)[sm_Transmitted], 
				ir_w, ir_t, ir_p, ir_v, ir_s);
			#endif
			
			//transmitted or reflected at mirror 
			//neutron inside substrate, either there is mirror reflection or there is substrate reflection, or neither.
			//Rm = (ws+)*(Rm+)+(ws-)*(Rm-)
			//rand01: reflected (0, Rm), transmitted (Rm, 1)
			//transmitted Rm == 0, reflected Rm == 1 
			ir_layer = sm_MirrorLayer;
			ws_Rm_at_plane = ir_ws[0]*Rm_vac_to_mir_at_plane[ir_plane][0] + ir_ws[1]*Rm_vac_to_mir_at_plane[ir_plane][1];
			if (ws_Rm_at_plane < 1) {
				if (rand01() >= ws_Rm_at_plane) {
					//Transmitted out of mirror, calculate s+, s-
					ir_v = state->v_in_vac_outward_at_plane[ir_plane];

					ir_ws[0] *= 1 - Rm_vac_to_mir_at_plane[ir_plane][0];
					ir_ws[1] *= 1 - Rm_vac_to_mir_at_plane[ir_plane][1];
					ir_ws_sum = ir_ws[0] + ir_ws[1];
					ir_ws[0] /= ir_ws_sum;
					ir_ws[1] /= ir_ws_sum;
					
					outcome = sm_Exited;
					break;
				}
			}
			//Reflected by mirror, calculate v, s+, s-, s
			ir_v = state->v_in_vac_inward_at_plane[ir_plane];
			
			ir_ws[0] *= Rm_vac_to_mir_at_plane[ir_plane][0];
			ir_ws[1] *= Rm_vac_to_mir_at_plane[ir_plane][1];
			ir_ws_sum = ir_ws[0] + ir_ws[1];
			ir_ws[0] /= ir_ws_sum;
			ir_ws[1] /= ir_ws_sum;
			ir_s = coords_scale((sm->co).fa, ir_ws[0] - ir_ws[1]);
			
			#if defined(NEUTRON_HISTORY_LIB)
			neutron_history_add_record(
				((sm->proc).location)[ir_side][ir_plane][ir_layer], 
				((sm->proc).event)[sm_Zigzag], 
				ir_w, ir_t, ir_p, ir_v, ir_s);
			#endif
			
			//transmitted or absorbed through absorber layer
			//rand01: transmitted (0, T_prop_abs_at_plane[ir_plane]), absorbed (T_prop_abs_at_plane[ir_plane], 1)
			//transmitted T_prop_abs_at_plane[ir_plane] == 1, absorbed T_prop_abs_at_plane[ir_plane] == 0
			ir_layer = sm_AbsorberLayer;
			if (T_prop_abs_at_plane[ir_plane] < 1) {
				if (rand01() >= T_prop_abs_at_plane[ir_plane]) {
					//Absorbed by absorber
					outcome = sm_Absorbed;
					break;
				}
			}
			//transmitted through absorber layer
			neutron_history_add_record(
				((sm->proc).location)[ir_side][ir_plane][ir_layer], 
				((sm->proc).event)[sm_Transmitted], 
				ir_w, ir_t, ir_p, ir_v, ir_s);
			
			//there is mirror coating, no reflection at substrate interface
			//transmitted through substrate interface is a given
			ir_v = state->v_in_sub_inward_at_plane[ir_plane];
			ir_layer = sm_SubstrateSurfaceLayer;

			#if defined(NEUTRON_HISTORY_LIB)
			neutron_history_add_record(
				((sm->proc).location)[ir_side][ir_plane][ir_layer], 
				((sm->proc).event)[sm_Transmitted], 
				ir_w, ir_t, ir_p, ir_v, ir_s);
			#endif
			
			//continue to next substrate transmission -- internal reflection
		}
		
		if (ir_n == ir_n_max) {
			//neutron transmitted to the end of substrate & exit through the edge
			dt_last = idts - ir_n_max * idtn;
			
			ir_side = sm_EdgeSide;
			ir_layer = sm_SubstrateLayer;
			outcome = sm_Exited;
		}
	}
	else 
	#endif
	
	{

		//no tracking
		
		ir_n = 0;
		ir_r = 0;
		while (ir_n < ir_n_max) {

			//transmitted or absorbed through substrate
			//rand01: transmitted (0, T_prop_sub), absorbed (T_prop_sub, 1)
			//transmitted T_prop_sub == 1, absorbed T_prop_sub == 0
			if (T_prop_sub < 1) {
				if (T_prop_sub < ZERO_THRESHOLD) {
					ir_v = state->v_in_sub_inward_at_plane[ir_plane];

					ir_side = state->side_at_plane[ir_plane];
					ir_layer = sm_SubstrateLayer;
					outcome = sm_Absorbed;
					break;
				}
				else {
					T_prop_sub_rand = rand01(); //probability of absorption, use for further processing
					if (T_prop_sub_rand >= T_prop_sub) {
						//Absorbed by substrate
						dt_last = -log(T_prop_sub_rand) * state->L_attn_sub / state->v_len;
						ir_v = state->v_in_sub_inward_at_plane[ir_plane];

						ir_side = state->side_at_plane[ir_plane];
						ir_layer = sm_SubstrateLayer;
						outcome = sm_Absorbed;
						break;
					}
				}
			}
			//transmitted through substrate
			//reach the other side of the substrate, update ir_r, ir_plane. 
			++ir_n;
			ir_r = 1 - ir_r;
			ir_plane = 1 - ir_plane;
			
			//transmitted or reflected at Substrate interface 
			//neutron inside substrate, either there is mirror reflection or there is substrate reflection, or neither.
			//i.e. if there is mirror coating, Rs == 0,
			//rand01: reflected (0, Rs), transmitted (Rs, 1)
			//transmitted Rs == 0, reflected Rs == 1 
			if (Rs_sub_to_vac_at_plane[ir_plane] > 0) {
				if (rand01() <= Rs_sub_to_vac_at_plane[ir_plane]) {
					//reflected by substrate interface back into substrate
					continue;
				}
			}
			//transmitted through substrate interface
			
			//transmitted or absorbed through absorber layer
			//rand01: transmitted (0, T_prop_abs_at_plane[ir_plane]), absorbed (T_prop_abs_at_plane[ir_plane], 1)
			//transmitted T_prop_abs_at_plane[ir_plane] == 1, absorbed T_prop_abs_at_plane[ir_plane] == 0
			if (T_prop_abs_at_plane[ir_plane] < 1) {
				if (T_prop_abs_at_plane[ir_plane] < ZERO_THRESHOLD) {
					//Absorbed by absorber
					ir_v = state->v_in_sub_outward_at_plane[ir_plane];

					ir_side = state->side_at_plane[ir_plane];
					ir_layer = sm_AbsorberLayer;
					outcome = sm_Absorbed;
					break;
				}
				else {
					if (rand01() >= T_prop_abs_at_plane[ir_plane]) {
						//Absorbed by absorber
						ir_v = state->v_in_sub_outward_at_plane[ir_plane];

						ir_side = state->side_at_plane[ir_plane];
						ir_layer = sm_AbsorberLayer;
						outcome = sm_Absorbed;
						break;
					}
				}
			}
			//transmitted through absorber layer
			
			//transmitted or reflected at mirror 
			//neutron inside substrate, either there is mirror reflection or there is substrate reflection, or neither.
			//Rm = (ws+)*(Rm+)+(ws-)*(Rm-)
			//rand01: reflected (0, Rm), transmitted (Rm, 1)
			//transmitted Rm == 0, reflected Rm == 1 
			ws_Rm_at_plane = ir_ws[0]*Rm_vac_to_mir_at_plane[ir_plane][0] + ir_ws[1]*Rm_vac_to_mir_at_plane[ir_plane][1];
			if (ws_Rm_at_plane < 1) {
				if (rand01() >= ws_Rm_at_plane) {
					//Transmitted out of mirror
					ir_v = state->v_in_vac_outward_at_plane[ir_plane];

					ir_ws[0] *= 1 - Rm_vac_to_mir_at_plane[ir_plane][0];
					ir_ws[1] *= 1 - Rm_vac_to_mir_at_plane[ir_plane][1];
					ir_ws_sum = ir_ws[0] + ir_ws[1];
					ir_ws[0] /= ir_ws_sum;
					ir_ws[1] /= ir_ws_sum;

					#if defined(DEBUG_sm_internal_reflections)
					printf("sm_internal_reflections 1 ir_ws=%lg,%lg\n", ir_ws[0], ir_ws[1]);
					#endif
					
					ir_side = state->side_at_plane[ir_plane];
					ir_layer = sm_MirrorLayer;
					outcome = sm_Exited;
					break;
				}
			}
			//Reflected by mirror, recalculate s+, s-
			ir_ws[0] *= Rm_vac_to_mir_at_plane[ir_plane][0];
			ir_ws[1] *= Rm_vac_to_mir_at_plane[ir_plane][1];
			ir_ws_sum = ir_ws[0] + ir_ws[1];
			ir_ws[0] /= ir_ws_sum;
			ir_ws[1] /= ir_ws_sum;

			#if defined(DEBUG_sm_internal_reflections)
			printf("sm_internal_reflections 2 ir_ws=%lg,%lg\n", ir_ws[0], ir_ws[1]);
			#endif
			
			//transmitted or absorbed through absorber layer
			//rand01: transmitted (0, T_prop_abs_at_plane[ir_plane]), absorbed (T_prop_abs_at_plane[ir_plane], 1)
			//transmitted T_prop_abs_at_plane[ir_plane] == 1, absorbed T_prop_abs_at_plane[ir_plane] == 0
			if (T_prop_abs_at_plane[ir_plane] < 1) {
				if (rand01() >= T_prop_abs_at_plane[ir_plane]) {
					//Absorbed by absorber
					ir_v = state->v_in_vac_inward_at_plane[ir_plane];
					
					ir_side = state->side_at_plane[ir_plane];
					ir_layer = sm_AbsorberLayer;
					outcome = sm_Absorbed;
					break;
				}
			}
			//transmitted through absorber layer
			
			//there is mirror coating, transmitted through substrate interface is a given
			
			//continue to next substrate transmission -- internal reflection
		}
		
		if (ir_n == ir_n_max) {
			//neutron transmitted to the end of substrate & exit through the edge
			dt_last = idts - ir_n_max * idtn;
			ir_v = state->v_in_sub_inward_at_plane[ir_plane];
			
			ir_side = sm_EdgeSide;
			ir_layer = sm_SubstrateLayer;
			outcome = sm_Exited;
		}
	}
	
	#if defined(DEBUG_sm_internal_reflections)
	if (ir_n > 0)
		printf(	"mcget_run_num()=%d, n_surface_intersect=%d, n_mirror_intersect=%d, ir_n=%d, ir_r=%d, dt_last=%lf\n",
				mcget_run_num(), state->n_surface_intersect, state->n_mirror_intersect, ir_n, ir_r, dt_last);
	#endif	
	
	#if defined(DEBUG_REF_LIB_TRACK)	
	sprintf(track_msg, "%sir.9 ", track_msg);
	#endif

	state->side = ir_side;
	state->plane = ir_plane;
	state->layer = ir_layer; 
	
	state->fn = (sm->geo).fn[ir_plane];
	
	state->t = ir_t0 + ir_n * idtn + dt_last;
	
	ir_p = coords_add(ir_p0, coords_scale(ir_dps, ir_n));
	if (ir_r == 1) ir_p = coords_add(ir_p, ir_dpn);
	if (dt_last > 0) ir_p = coords_add(ir_p, coords_scale(ir_v, dt_last));
	state->p = ir_p;
	
	state->v = ir_v; 
	
	state->ws[0] = ir_ws[0];
	state->ws[1] = ir_ws[1];
	state->s = coords_scale( (sm->co).fa, ir_ws[0]-ir_ws[1]);

	#if defined(DEBUG_sm_internal_reflections)
	printf("sm_internal_reflections 1 ws=%lg,%lg\n", state->ws[0], state->ws[1]);
	#endif
	
	state->last_time = state->t;
	state->last_point = state->p;
	state->last_plane = state->plane;

	#if defined(NEUTRON_HISTORY_LIB)
	if ((sm->proc).is_tracking) {
		neutron_history_add_record(state->location, state->event, state->w, state->t, state->p, state->v, state->s);
	}
	#endif

	#if defined(DEBUG_sm_internal_reflections)
	if (ir_n == ir_n_max) {
		sm_print_state ("ir.2: After internal reflection just before the end of sm", state, sm);
		printf("%s 3: Reach just before end of sm. n-reflection = %d max=%d. Return sm_InternalReflection (stay in module)\n\n", 
				supermirror_flat_s_prefix,ir_n,ir_n_max);
	} 
	else {
		sm_print_state ("ir.2: After internal reflection just before absorbed or transmitted through mirror plane", state, sm);
		printf("%s ir.2: Just before absorbed or transmitted through mirror plane. Internal reflection = %d max=%d. Return sm_InternalReflection (stay in module)\n\n", supermirror_flat_s_prefix,ir_n,ir_n_max);
	}
	#endif
		
	return outcome; //stay in module, continue to calculate the exit

}


/*******************************/
/* Functions called by modules */
/*******************************/

int InitialiseStdSupermirrorFlat( 
		
		char *name, //Supermirror name
		
		////////////////////////////////////////////////////////////////////////////////
		//STEP 1: Specify the supermirror shape, mirror coatings and substrate material
		//In this step, the supermirror is lying horizontally on the xz plane with the long side along +z.
		double length, //m, use SI unit unless specified
		double thickness_in_mm, //mm - note the unit
		Coords side_edge_normal, Coords side_edge_point, //edges in +x and -x sides, symmetric about yz plane. 
		
		char*mirror_coated_side, //Sequential combination of keywords of
								 //position: "Both", "Top", "Bottom";
								 //surface property: "Coated", "Substrate", "NoReflection"; 
								 //e.g. "BothCoated", "BottomCoatedTopSubstrate",
								 //case-insensitive.
		char*mirror_spin_plus_material_name, //defined in "Supermirror_reflective_coating_materials.txt", non-polarising: use same for spin minus, case-insensitive
		double mirror_spin_plus_m, 
		char*mirror_spin_minus_material_name, //defined in "Supermirror_reflective_coating_materials.txt", non-polarising: use same for spin plus, case-insensitive
		double mirror_spin_minus_m, 
		
		char*absorber_coated_side, //"BothNotCoated", "BothCoated", "TopCoated", "BottomCoated" 
		char*absorber_material_name, //defined in "Supermirror_absorber_coating_materials.txt" or "Empty", case-insensitive
		double absorber_thickness_in_micron, //micrometer
		
		char*substrate_material_name, //defined in "Supermirror_substrate_materials.txt" or "Empty", case-insensitive.
		char*substrate_edge_block, //"yes" = block neutron entry through substrate, "no" = allow neutron entry through substrate edge
		
		////////////////////////////////////////////////////////////////////////////////
		//STEP 2: Orient and position the supermirror 
		char*initial_placement_at_origin,	 //"TopFrontEdgeCentre","FrontSubstrateCentre","BottomFrontEdgeCentre"
											 //(insensitive to case and reginal English spelling)
		char*tilt_y_axis_location, 			 //"TopFrontEdge","TopMirrorCentre","TopBackEdge"
											 //"FrontSubstrateCentre","SubstrateCentre","BackSubstrateCentre", 
											 //"BottomFrontEdge","BottomMirrorCentre","BottomBackEdge"
											 //(insensitive to case and reginal English spelling)
		double tilt_about_y_first_in_degree, //degree, first, tile about y-axis at selected location 
		Coords translation_second,			 //second, translate reference point 
		double rot_about_z_third_in_degree,	 //third, rotate about global z-axis 

		////////////////////////////////////////////////////////////////////////////////
		//STEP 3: simulation process control parameters
		int is_tracking,
		
		////////////////////////////////////////////////////////////////////////////////
		//OUTPUT: Supermirror struct with all parameter values entered and initialised
		//User declares "Supermirror supermirror;" or its equivalence, 
		//then passes pointer "&supermirror" to function.
		Supermirror*sm
		) 
{ //Wrapper function to call InitialiseStdSupermirrorFlat_detail
//#define DEBUG_InitialiseStdSupermirrorFlat
	#if defined(DEBUG_InitialiseStdSupermirrorFlat)
	MPI_MASTER (
		printf("InitialiseStdSupermirrorFlat(\n");
		printf("name=\"%s\"\n",name);
		printf("length = %g m, thickness_in_mm = %g mm\n",length,thickness_in_mm);
		printf("side_edge normal,point = (%g,%g,%g), (%g,%g,%g) m\n",
			side_edge_normal.x, side_edge_normal.y, side_edge_normal.z,
			side_edge_point.x, side_edge_point.y, side_edge_point.z
			);
		printf("mirror_coated_side = %s\n",mirror_coated_side);
		printf("mirror_spin_plus_material  name,m = %s, %g\n",mirror_spin_plus_material_name, mirror_spin_plus_m);
		if (mirror_spin_minus_m != -1)
			printf("mirror_spin_minus_material name,m = %s, %g\n",mirror_spin_minus_material_name, mirror_spin_minus_m);
		else 
			printf("mirror_spin_minus_material name,m = %s, m from file\n",mirror_spin_minus_material_name);
		printf("substrate_material name = %s, substrate_edge_block=%s\n",substrate_material_name, substrate_edge_block);
		printf("absorber_coated_side = %s\n",absorber_coated_side);
		printf("absorber_material_name, thickness = %s, %g [micrometer]\n",absorber_material_name, absorber_thickness_in_micron);
		printf("initial_placement_at_origin = %s\n",initial_placement_at_origin);
		printf("tilt_y_axis_location = %s\n",tilt_y_axis_location);
		printf("tilt_about_y_first_in_degree, translation_second, rot_about_z_third_in_degree = %g deg, (%g,%g,%g) m, %g deg\n",
			tilt_about_y_first_in_degree, 
			translation_second.x, translation_second.y, translation_second.z, 
			rot_about_z_third_in_degree
			);
		printf("is_tracking = %d\n",is_tracking);
		printf(")\n");
	)
	#endif

    if (sm == NULL) {
        MPI_MASTER(printf("Error: sm pointer is NULL\n"));
        return 0;
    }


	char top_mirror_spin_plus_material[CHAR_BUF_LENGTH], top_mirror_spin_minus_material[CHAR_BUF_LENGTH], 
		 bottom_mirror_spin_plus_material[CHAR_BUF_LENGTH], bottom_mirror_spin_minus_material[CHAR_BUF_LENGTH]; 
	double top_mirror_spin_plus_m, top_mirror_spin_minus_m, bottom_mirror_spin_plus_m, bottom_mirror_spin_minus_m; 
	
	char *lc = 0;

	
	if (mirror_coated_side != 0) {
		if (strlen(mirror_coated_side) != 0) {
			to_lower_case(mirror_coated_side, &lc);
		}
	}
	if (lc == 0) {
		store_text("bothsubstrate",&lc);
	}
	
	replace_keyword(lc,"side", 0, &lc);
	replace_keyword(lc,"notcoated","substrate", &lc);
	replace_keyword(lc,"nocoating","substrate", &lc);
	replace_keyword(lc,"substratesurface","substrate", &lc);
	replace_keyword(lc,"empty","nosurfaceboundary", &lc);
	replace_keyword(lc,"noreflection","nosurfaceboundary", &lc);
	replace_keyword(lc,"coated","mirror", &lc);
	
	#if defined(DEBUG_InitialiseStdSupermirrorFlat)
	MPI_MASTER (
	printf("mirror_coated_side=%s, lc=%s\n", mirror_coated_side, lc);
	)
	#endif
	
	if (strcmp(lc,"bothmirror") == 0) {
		strcpy(top_mirror_spin_plus_material, mirror_spin_plus_material_name); top_mirror_spin_plus_m = mirror_spin_plus_m;
		strcpy(top_mirror_spin_minus_material, mirror_spin_minus_material_name); top_mirror_spin_minus_m = mirror_spin_minus_m;
		strcpy(bottom_mirror_spin_plus_material, mirror_spin_plus_material_name); bottom_mirror_spin_plus_m = mirror_spin_plus_m;
		strcpy(bottom_mirror_spin_minus_material, mirror_spin_minus_material_name); bottom_mirror_spin_minus_m = mirror_spin_minus_m;
	}
	else if (strcmp(lc,"bothsubstrate") == 0 || strcmp(lc,"substrate") == 0) {
		strcpy(top_mirror_spin_plus_material, "SubstrateSurface"); top_mirror_spin_plus_m = 0;
		strcpy(top_mirror_spin_minus_material, "SubstrateSurface"); top_mirror_spin_minus_m = 0;
		strcpy(bottom_mirror_spin_plus_material, "SubstrateSurface"); bottom_mirror_spin_plus_m = 0;
		strcpy(bottom_mirror_spin_minus_material, "SubstrateSurface"); bottom_mirror_spin_minus_m = 0;
	}
	else if (strcmp(lc,"bothnosurfaceboundary") == 0) {
		strcpy(top_mirror_spin_plus_material, "NoSurfaceBoundary"); top_mirror_spin_plus_m = 0;
		strcpy(top_mirror_spin_minus_material, "NoSurfaceBoundary"); top_mirror_spin_minus_m = 0;
		strcpy(bottom_mirror_spin_plus_material, "NoSurfaceBoundary"); bottom_mirror_spin_plus_m = 0;
		strcpy(bottom_mirror_spin_minus_material, "NoSurfaceBoundary"); bottom_mirror_spin_minus_m = 0;
	}
	else if (strcmp(lc,"topmirrorbottomsubstrate") == 0 || strcmp(lc,"bottomsubstratetopmirror") == 0) { 
		strcpy(top_mirror_spin_plus_material, mirror_spin_plus_material_name); top_mirror_spin_plus_m = mirror_spin_plus_m;
		strcpy(top_mirror_spin_minus_material, mirror_spin_minus_material_name); top_mirror_spin_minus_m = mirror_spin_minus_m;
		strcpy(bottom_mirror_spin_plus_material, "SubstrateSurface"); bottom_mirror_spin_plus_m =0;
		strcpy(bottom_mirror_spin_minus_material, "SubstrateSurface"); bottom_mirror_spin_minus_m = 0;
	}
	else if (strcmp(lc,"topsubstratebottommirror") == 0 || strcmp(lc,"bottommirrortopsubstrate") == 0) {
		strcpy(top_mirror_spin_plus_material, "SubstrateSurface"); top_mirror_spin_plus_m = 0;
		strcpy(top_mirror_spin_minus_material, "SubstrateSurface"); top_mirror_spin_minus_m = 0;
		strcpy(bottom_mirror_spin_plus_material, mirror_spin_plus_material_name); bottom_mirror_spin_plus_m = mirror_spin_plus_m;
		strcpy(bottom_mirror_spin_minus_material, mirror_spin_minus_material_name); bottom_mirror_spin_minus_m = mirror_spin_minus_m;
	}
	else if (strcmp(lc,"topmirrorbottomnosurfaceboundary") == 0 || strcmp(lc,"bottomnosurfaceboundarytopmirror") == 0) { 
		strcpy(top_mirror_spin_plus_material, mirror_spin_plus_material_name); top_mirror_spin_plus_m = mirror_spin_plus_m;
		strcpy(top_mirror_spin_minus_material, mirror_spin_minus_material_name); top_mirror_spin_minus_m = mirror_spin_minus_m;
		strcpy(bottom_mirror_spin_plus_material, "NoSurfaceBoundary"); bottom_mirror_spin_plus_m = 0;
		strcpy(bottom_mirror_spin_minus_material, "NoSurfaceBoundary"); bottom_mirror_spin_minus_m = 0;
	}
	else if (strcmp(lc,"topnosurfaceboundarybottommirror") == 0 || strcmp(lc,"bottommirrortopnosurfaceboundary") == 0) {
		strcpy(top_mirror_spin_plus_material, "NoSurfaceBoundary"); top_mirror_spin_plus_m = 0;
		strcpy(top_mirror_spin_minus_material, "NoSurfaceBoundary"); top_mirror_spin_minus_m = 0;
		strcpy(bottom_mirror_spin_plus_material, mirror_spin_plus_material_name); bottom_mirror_spin_plus_m = mirror_spin_plus_m;
		strcpy(bottom_mirror_spin_minus_material, mirror_spin_minus_material_name); bottom_mirror_spin_minus_m = mirror_spin_minus_m;
	}
	else if (strcmp(lc,"topsubstratebottomnosurfaceboundary") == 0 || strcmp(lc,"bottomnosurfaceboundarytopsubstrate") == 0) { 
		strcpy(top_mirror_spin_plus_material, "SubstrateSurface"); top_mirror_spin_plus_m = mirror_spin_plus_m;
		strcpy(top_mirror_spin_minus_material, "SubstrateSurface"); top_mirror_spin_minus_m = mirror_spin_minus_m;
		strcpy(bottom_mirror_spin_plus_material, "NoSurfaceBoundary"); bottom_mirror_spin_plus_m = 0;
		strcpy(bottom_mirror_spin_minus_material, "NoSurfaceBoundary"); bottom_mirror_spin_minus_m = 0;
	}
	else if (strcmp(lc,"topnosurfaceboundarybottomsubstrate") == 0 || strcmp(lc,"bottomsubstratetopnosurfaceboundary") == 0) {
		strcpy(top_mirror_spin_plus_material, "NoSurfaceBoundary"); top_mirror_spin_plus_m = 0;
		strcpy(top_mirror_spin_minus_material, "NoSurfaceBoundary"); top_mirror_spin_minus_m = 0;
		strcpy(bottom_mirror_spin_plus_material, "SubstrateSurface"); bottom_mirror_spin_plus_m = mirror_spin_plus_m;
		strcpy(bottom_mirror_spin_minus_material, "SubstrateSurface"); bottom_mirror_spin_minus_m = mirror_spin_minus_m;
	}
	else {
		MPI_MASTER(printf("InitialiseStdSupermirrorFlat: sm_Error: found \"%s\"=>\"%s\" mirror_coated_side must be sequential combination of keywords of\n"
							"position: \"Both\", \"Top\", \"Bottom\"; \n"
							"surface property: \"Coated\" = \"Mirror\", \"Substrate\" = \"SubstrateSurface\", \"NoReflection\"; \n"
							"e.g. \"BothMirror\", \"TopCoatedBottomSubstrate\", \n"
							"not case sensitive. \n"
							"Return 0.\n", mirror_coated_side, lc);)
		if (lc != 0) {
			free(lc);
			lc = 0;
		}
		return 0; 
	}
	if (lc != 0) {
		free(lc);
		lc = 0;
	}

	char abs_side[CHAR_BUF_LENGTH], abs_name[CHAR_BUF_LENGTH], top_absorber_material[CHAR_BUF_LENGTH], bottom_absorber_material[CHAR_BUF_LENGTH]; 
	double absorber_top_thickness_in_micron, absorber_bottom_thickness_in_micron; 
	strcpy(abs_side, "bothempty");
	if (absorber_coated_side != 0) {
		if (strlen(absorber_coated_side) !=0) {
			strcpy(abs_side, absorber_coated_side);
		}
	}
	strcpy(abs_name, "empty");
	if (absorber_material_name != 0) {
		if (strlen(absorber_material_name) !=0) {
			strcpy(abs_name, absorber_material_name);
		}
	}
	
	to_lower_case(abs_side, &lc);
	replace_keyword(lc,"side", 0, &lc);
	replace_keyword(lc,"notcoated", "empty", &lc);
	replace_keyword(lc,"nocoating", "empty", &lc);
	
	if (strcmp(lc,"bothcoated") == 0) {
		strcpy(top_absorber_material, abs_name); absorber_top_thickness_in_micron = absorber_thickness_in_micron;
		strcpy(bottom_absorber_material, abs_name); absorber_bottom_thickness_in_micron = absorber_thickness_in_micron;
	}
	else if (strcmp(lc,"bothempty") == 0) { 
		strcpy(top_absorber_material, "empty"); absorber_top_thickness_in_micron = 0;
		strcpy(bottom_absorber_material, "empty"); absorber_bottom_thickness_in_micron = 0;
	}
	else if (strcmp(lc,"topcoated") == 0 || strcmp(lc,"topcoatedbottomempty") == 0 || strcmp(lc,"bottomemptytopcoated") == 0) { 
		strcpy(top_absorber_material, abs_name); absorber_top_thickness_in_micron = absorber_thickness_in_micron;
		strcpy(bottom_absorber_material, "Empty"); absorber_bottom_thickness_in_micron = 0;
	}
	else if (strcmp(lc,"bottomcoated") == 0 || strcmp(lc,"bottomcoatedtopempty") == 0 || strcmp(lc,"topemptybottomcoated") == 0) {
		strcpy(top_absorber_material, "Empty"); absorber_top_thickness_in_micron = 0;
		strcpy(bottom_absorber_material, abs_name); absorber_bottom_thickness_in_micron = absorber_thickness_in_micron;
	}
	else {
		MPI_MASTER(
			printf(	"InitialiseStdSupermirrorFlat: sm_Error: absorber_coated_side must be "
					"\"BothCoated\", "
					"\"TopCoated\" = \"TopCoatedBottomNotCoated\", "
					"\"BottomCoated\" = \"BottomCoatedTopNotCoated\", or "
					"\"BothNotCoated\". Return 0\n");)
		if (lc != 0) {
			free(lc);
			lc = 0;
		}
		return 0; 
	}
	if (lc != 0) {
		free(lc);
		lc = 0;
	}
	
	char substrate_material[CHAR_BUF_LENGTH];
	strcpy(substrate_material, "empty");
	if (substrate_material_name != 0) {
		if (strlen(substrate_material_name) !=0) {
			strcpy(substrate_material, substrate_material_name);
		}
	}
		
	Coords n = coords_set(0, 1, 0); //reflecting +y edge to -y edge, vice versa
		
	return InitialiseStdSupermirrorFlat_detail (
		name,
		length,
		thickness_in_mm,
		side_edge_normal, side_edge_point, 
		coords_mirror(side_edge_normal, n), coords_mirror(side_edge_point, n),
		
		top_mirror_spin_plus_material, 0, top_mirror_spin_plus_m, 
		top_mirror_spin_minus_material, 0, top_mirror_spin_minus_m, 
		bottom_mirror_spin_plus_material, 0, bottom_mirror_spin_plus_m, 
		bottom_mirror_spin_minus_material, 0, bottom_mirror_spin_minus_m, 

		top_absorber_material, -1, -1, absorber_top_thickness_in_micron, 
		bottom_absorber_material, -1, -1, absorber_bottom_thickness_in_micron, 

		substrate_material, -1, -1, 0, 0, 0, -1, -1, 0, 0, substrate_edge_block, 
		
		initial_placement_at_origin,
		tilt_y_axis_location,
		tilt_about_y_first_in_degree,
		translation_second,
		rot_about_z_third_in_degree,
		
		is_tracking,
		sm);

}

int InitialiseStdSupermirrorFlat_detail ( 
		char *name, //Supermirror name
		
		////////////////////////////////////////////////////////////////////////////////
		//STEP 1: Specify the supermirror shape, mirror coatings and substrate material
		//In this step, the supermirror is lying horizontally on the xz plane with the long side along +z.
		double length, //m, use SI unit unless specified
		double thickness_in_mm, //in mm - note the unit
		Coords side_edge_1_normal, Coords side_edge_1_point, //edge in +x or -x side 
		Coords side_edge_2_normal, Coords side_edge_2_point, //edge in +x or -x side 
		
		//If materials name is specified and matching those defined in "Supermirror_reflective_coating_materials.txt" 
		//material name overrides material spec, otherwise 6-parameter material spec is used.  
		//Use the same for spin plus and spin minus if the mirror is non-polarising
		char*mirror_top_spin_plus_material_name, double*mirror_top_spin_plus_material_spec, double mirror_top_spin_plus_m, 
		char*mirror_top_spin_minus_material_name, double*mirror_top_spin_minus_material_spec, double mirror_top_spin_minus_m, 
		char*mirror_bottom_spin_plus_material_name, double*mirror_bottom_spin_plus_material_spec, double mirror_bottom_spin_plus_m, 
		char*mirror_bottom_spin_minus_material_name, double*mirror_bottom_spin_minus_material_spec, double mirror_bottom_spin_minus_m, 

		//INPUT: Absorber parameters are absorption paramter and thickness in microns: 
		//If materials name is specified and matching those defined in "Supermirror_absorber_coating_materials.txt"  
		//material name overrides material spec, otherwise 1-parameter material spec is used.  
		char*absorber_top_material_name, double absorber_top_L_abs, double absorber_top_L_inc, double absorber_top_thickness_in_micron,
		char*absorber_bottom_material_name, double absorber_bottom_L_abs, double absorber_bottom_L_inc, double absorber_bottom_thickness_in_micron,

		//INPUT: Substrate parameters are substrate attenuation paramters and SLD: 
		//If materials name is specified and matching those defined in "Supermirror_substrate_materials.txt" or is "Empty",  
		//material name overrides material spec, otherwise the 3 material parameters are used. 
		//Name is case-insensitive. 0 if not specified. 
		char*substrate_material_name, double substrate_L_abs, double substrate_L_inc, double substrate_SLD, 
		double substrate_S_coh, double substrate_A, double substrate_T_D, double substrate_T, double substrate_n, double substrate_C2,  
		char*substrate_edge_block, //"yes" = block neutron entry through substrate, "no" = allow neutron entry through substrate edge

		////////////////////////////////////////////////////////////////////////////////
		//STEP 2: Orient and position the supermirror 
		char*initial_placement_at_origin,	 //"TopFrontEdgeCentre","FrontSubstrateCentre","BottomFrontEdgeCentre"
											 //(insensitive to case and reginal English spelling)
		char*tilt_y_axis_location, 			 //"TopFrontEdge","TopMirrorCentre","TopBackEdge"
											 //"FrontSubstrateCentre","SubstrateCentre","BackSubstrateCentre", 
											 //"BottomFrontEdge","BottomMirrorCentre","BottomBackEdge"
											 //(insensitive to case and reginal English spelling)
		double tilt_about_y_first_in_degree, //degree, first, tile about y-axis at selected location 
		Coords translation_second,			 //second, translate reference point 
		double rot_about_z_third_in_degree,	 //third, rotate about global z-axis 

		////////////////////////////////////////////////////////////////////////////////
		//STEP 3: simulation process control parameters
		int is_tracking, //
		
		////////////////////////////////////////////////////////////////////////////////
		//OUTPUT: Supermirror struct with all parameter values entered and initialised
		//User declares "Supermirror supermirror;" or its equivalence, 
		//then passes pointer "&supermirror" to function.
		Supermirror*sm
		) 
{ //Initialisation function
//#define DEBUG_InitialiseStdSupermirrorFlat_detail

    if (sm == NULL) {
        MPI_MASTER(printf("Error: sm pointer is NULL\n"));
        return 0;
    }

	int i,j,k;
	if (sm->proc.initialised != 0) { 
		EmptySupermirrorFlatData(sm); 
		
		#if defined(DEBUG_InitialiseStdSupermirrorFlat_detail)
			MPI_MASTER (printf("InitialiseStdSupermirrorFlat_detail: empty existing data for initialisation\n");)
		#endif
	}
	
	#if defined(DEBUG_InitialiseStdSupermirrorFlat_detail)
		MPI_MASTER (
			printf("InitialiseStdSupermirrorFlat_detail()\n");
			printf("name = %s\n",name);
			printf("length = %g m, thickness_in_mm = %g mm\n",length,thickness_in_mm);
			printf("side_edge_1 normal,point = (%g,%g,%g), (%g,%g,%g) m\n",
				side_edge_1_normal.x, side_edge_1_normal.y, side_edge_1_normal.z,
				side_edge_1_point.x, side_edge_1_point.y, side_edge_1_point.z
				);
			printf("side_edge_2 normal,point = (%g,%g,%g), (%g,%g,%g) m\n",
				side_edge_2_normal.x, side_edge_2_normal.y, side_edge_2_normal.z,
				side_edge_2_point.x, side_edge_2_point.y, side_edge_2_point.z
				);
			printf("origin = %s\n",initial_placement_at_origin);
			printf("tilt_y_axis_location = %s\n",tilt_y_axis_location);
			printf("tilt_about_x_first, translation_second, rot_about_z_third_in_degree = %g deg, (%g,%g,%g) m, %g deg\n",
				tilt_about_y_first_in_degree, 
				translation_second.x, translation_second.y, translation_second.z, 
				rot_about_z_third_in_degree
				);
				
			printf("mirror_top_spin_plus_material name,spec,m = ");
			if (mirror_top_spin_plus_material_name != 0) printf("%s , {",mirror_top_spin_plus_material_name);
			else printf("use spec, {");
			if (mirror_top_spin_plus_material_spec != 0) 
				for (i = 0; i < 6; i++) {
					printf("%g",mirror_top_spin_plus_material_spec[i]);
					if (i < 5) printf(",");
				}
			else 
				printf("spec from file");
			printf("}, %g\n",mirror_top_spin_plus_m);
			
			printf("mirror_top_spin_minus_material name,spec,m = ");
			if (mirror_top_spin_minus_material_name != 0) printf("%s , {",mirror_top_spin_minus_material_name);
			else printf("use spec, {");
			if (mirror_top_spin_minus_material_spec != 0) 
				for (i = 0; i < 6; i++) {
					printf("%g",mirror_top_spin_minus_material_spec[i]);
					if (i < 5) printf(",");
				}
			else 
				printf("spec from file");
			if (mirror_top_spin_minus_m != -1)
				printf("}, %g\n",mirror_top_spin_minus_m);
			else
				printf("}, %g\n",mirror_top_spin_minus_m);

			printf("mirror_bottom_spin_plus_material name,spec,m = ");
			if (mirror_bottom_spin_plus_material_name != 0) printf("%s , {",mirror_bottom_spin_plus_material_name);
			else printf("use spec, {");
			if (mirror_bottom_spin_plus_material_spec != 0) 
				for (i = 0; i < 6; i++) {
					printf("%g",mirror_bottom_spin_plus_material_spec[i]);
					if (i < 5) printf(",");
				}
			else 
				printf("spec from file");
			printf("}, %g\n",mirror_bottom_spin_plus_m);
			
			printf("mirror_bottom_spin_minus_material name,spec,m = ");
			if (mirror_bottom_spin_minus_material_name != 0) printf("%s , {",mirror_bottom_spin_minus_material_name);
			else printf("use spec, {");
			if (mirror_bottom_spin_minus_material_spec != 0) 
				for (i = 0; i < 6; i++) {
					printf("%g",mirror_bottom_spin_minus_material_spec[i]);
					if (i < 5) printf(",");
				}
			else 
				printf("spec from file");
			if (mirror_bottom_spin_minus_m != -1)
				printf("}, %g\n",mirror_bottom_spin_minus_m);
			else
				printf("}, m from file\n",mirror_bottom_spin_minus_m);

			printf("absorber_top_material_name, L_abs, L_inc, thickness = ");
			if (absorber_top_material_name != 0) printf("%s , get from file, get from file, ",absorber_top_material_name);
			else 
				printf("use spec, %g, %g, ",absorber_top_L_abs, absorber_top_L_inc);
			printf("%g\n", absorber_top_thickness_in_micron);

			printf("absorber_bottom_material_name, L_abs, L_inc, thickness = ");
			if (absorber_bottom_material_name != 0) printf("%s , get from file, get from file, ",absorber_bottom_material_name);
			else 
				printf("use spec, %g, %g, ",absorber_bottom_L_abs, absorber_bottom_L_inc);
			printf("%g\n", absorber_bottom_thickness_in_micron);

			printf("substrate_material name,L_abs,L_inc,SLD = ");
			if (substrate_material_name != 0) printf("%s , {spec in file}\n",substrate_material_name);
			else printf("---, {%lg, %lg, %lg}\n", substrate_L_abs, substrate_L_inc, substrate_SLD); 

			printf("is_tracking=%d\n",is_tracking);
			printf("\n");
			printf("InitializeStdSupermirrorFlatFunc: begin\n");
		)
	#endif

	if (name != 0) strcpy(sm->name,name);
	
//	sm->geo = (void*)calloc(1, sizeof(Polyhedron));
	if (set_supermirror_flat_geometry(
			length, thickness_in_mm, //mm
			side_edge_1_normal, side_edge_1_point, 
			side_edge_2_normal, side_edge_2_point, 
			initial_placement_at_origin, 
			tilt_y_axis_location, tilt_about_y_first_in_degree, 
			translation_second, 
			rot_about_z_third_in_degree, 
			&(sm->geo), &(sm->co)) == 0) {
			MPI_MASTER(printf("InitializeStdSupermirrorFlatFunc - error loading geometry\n");)
			return 0; //initialisation failed
	}

	//substrate parameters to be set first. sub->sub_type may be overrided when setting mirror and absorber parameters
	if (set_substrate_material_parameters(
			substrate_material_name, substrate_L_abs, substrate_L_inc, substrate_SLD, 
			substrate_S_coh, substrate_A, substrate_T_D, substrate_T, substrate_n, substrate_C2,  
			thickness_in_mm, substrate_edge_block, 
			&((sm->mat).sub), (sm->mat).subsurface) == 0) {
			MPI_MASTER(printf("InitializeStdSupermirrorFlatFunc - error loading substrate parameters\n");)
			return 0; //initialisation failed
	}
	#if defined(DEBUG_InitialiseStdSupermirrorFlat_detail)
	MPI_MASTER (
		SubstrateParameters*sub = &((sm->mat).sub);
		RefractionParameters*subsurface = (sm->mat).subsurface;
		printf("set_substrate_material_parameters: sub = (name, L_abs, L_inc, SLD, thickness_in_mm, sub_type)\n");
		printf(" L_abs = absorption 1/e length [m], L_inc = incoherent 1/e attenuation length [m], SLD = coherent SLD [AA-2], thickness_in_mm=%lf\n", thickness_in_mm);
		printf(" sub = (%s, % 7.4f, % 7.4f, %6e, %X)\n", sub->name, sub->L_abs, sub->L_inc, sub->SLD, sub->sub_type);
		printf(" subsurface critical Qc_sub [1/A] = %6e, %6e\n", subsurface[0].Qc_sub, subsurface[1].Qc_sub);
		printf(" subsurface 1-n^2 @ 1 AA, air to substrate [0],[1] = %6e, %6e\n", subsurface[0].delta_n_2, subsurface[1].delta_n_2);
		printf(" subsurface[top],[bottom]: subsurface[0],[1]->subsurface_type = %X, %X\n", subsurface[0].subsurface_type, subsurface[1].subsurface_type);
	)
	#endif
	
	
	//mirror parameters to be set first. 
	if (set_mirror_material_parameters(
			mirror_top_spin_plus_material_name, mirror_top_spin_plus_material_spec, mirror_top_spin_plus_m, 
			&((sm->mat).mir[0][0]), 
			&((sm->mat).subsurface[0])) == 0) {
			MPI_MASTER(printf("InitializeStdSupermirrorFlatFunc - error loading top mirror spin+ parameters\n");)
			return 0; //initialisation failed
	}
	if (set_mirror_material_parameters(
			mirror_top_spin_minus_material_name, mirror_top_spin_minus_material_spec, mirror_top_spin_minus_m, 
			&((sm->mat).mir[0][1]), 
			&((sm->mat).subsurface[0])) == 0) {
			MPI_MASTER(printf("InitializeStdSupermirrorFlatFunc - error loading top mirror spin- parameters\n");)
			return 0; //initialisation failed
	}
	if (set_mirror_material_parameters(
			mirror_bottom_spin_plus_material_name, mirror_bottom_spin_plus_material_spec, mirror_bottom_spin_plus_m, 
			&((sm->mat).mir[1][0]), 
			&((sm->mat).subsurface[1])) == 0) {
			MPI_MASTER(printf("InitializeStdSupermirrorFlatFunc - error loading bottom mirror spin+ parameters\n");)
			return 0; //initialisation failed
	}
	if (set_mirror_material_parameters(
			mirror_bottom_spin_minus_material_name, mirror_bottom_spin_minus_material_spec, mirror_bottom_spin_minus_m, 
			&((sm->mat).mir[1][1]), 
			&((sm->mat).subsurface[1])) == 0) {
			MPI_MASTER(printf("InitializeStdSupermirrorFlatFunc - error loading bottom mirror spin- parameters\n");)
			return 0; //initialisation failed
	}
	#if defined(DEBUG_InitialiseStdSupermirrorFlat_detail)
	MPI_MASTER (
		printf("set_mirror_material_parameters: mir[top/bottom][+/-] = (name,R0,Qc,alpha,m,W,beta,type)\n"); 
		ReflectionParameters*mir;
		for (i=0; i<SM_Num_Mirror_Planes; i++) {
			for (j=0; j<SM_Num_Spin_States; j++) {
				mir = &((sm->mat).mir[i][j]);
				printf(" mir[%d][%d] = (%s, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, %x)\n", 
					i,j, mir->name, mir->R0, mir->Qc, mir->alpha, mir->m, mir->W, mir->beta, mir->refl_type);
			}
		}
		printf(" subsurface_type[top],[bottom]: subsurface[0],[1]->subsurface_type = %X, %X (updated)\n", (((sm->mat).subsurface)[0]).subsurface_type, (((sm->mat).subsurface)[1]).subsurface_type);
	)
	#endif
			
	//absorber parameters to be set last. may override mir->refl_type (if bare substrate) and sub->sub_type (no reflection or refraction)
	if (set_absorber_material_parameters(
			absorber_top_material_name, absorber_top_L_abs, absorber_top_L_inc, absorber_top_thickness_in_micron, 
			&((sm->mat).abs[0])) == 0) {
			MPI_MASTER(printf("InitializeStdSupermirrorFlatFunc - error loading top abs parameters\n");)
			return 0; //initialisation failed
	}
	if (set_absorber_material_parameters(
			absorber_bottom_material_name, absorber_bottom_L_abs, absorber_bottom_L_inc, absorber_bottom_thickness_in_micron, 
			&((sm->mat).abs[1])) == 0) {
			MPI_MASTER(printf("InitializeStdSupermirrorFlatFunc - error loading bottom abs parameters\n");)
			return 0; //initialisation failed
	}
	#if defined(DEBUG_InitialiseStdSupermirrorFlat_detail)
	MPI_MASTER (
		AbsorptionParameters*abs;
		printf("set_absorber_material_parameters: abs[top/bottom] = (name, L_abs, L_inc, thickness_in_micron, abs_type)\n");
		printf(" L_abs = absorption 1/e length [m], L_inc = incoherent 1/e attenuation length [m], thickness_in_micron converted to [m]\n");
		for (i=0; i<SM_Num_Mirror_Planes; i++) {
			abs = &((sm->mat).abs[i]);
			printf(" abs[%d] = (%s, % 7.4f, % 7.4f, % 7.4f, %d)\n", i, abs->name, abs->L_abs, abs->L_inc, abs->thickness_in_micron, abs->abs_type);
		}
	)
	#endif
		
	set_process_parameters(is_tracking, sm, &(sm->proc));
			
	sm->proc.initialised = 1;
	
	#if USE_MPI
		MPI_Barrier(MPI_COMM_WORLD);
	#endif

	#if defined(DEBUG_InitialiseStdSupermirrorFlat_detail)
	printf("InitialiseStdSupermirrorFlat_detail: node = %d completed\n\n\n",mpi_node_rank);
	#endif
	
	FILE*fpp;

	// Ensure only one thread/process writes the file
	#ifdef _OPENMP
	if (omp_get_thread_num() == 0)
	{
	#endif
			
	#ifdef USE_MPI
	// MPI: Only master process writes
	if (mpi_node_rank == mpi_node_root) {
	#endif

		char refl_check_file_path[CHAR_BUF_LENGTH]; 
		sprintf(refl_check_file_path, "%s/refl_check.csv", dirname); 
		fpp=fopen(refl_check_file_path,"a");
		if (fpp) { 
			fclose(fpp);

			ReflectionParameters*mir[2][2]; 
			for (i = 0; i < SM_Num_Mirror_Planes; i++)
			for (j = 0; j < SM_Num_Spin_States; j++) {
				mir[i][j] = &((sm->mat).mir[i][j]);
			}
			int save_refl = 1; 
//			int save_refl = 0; 
//			for (i = 0; i < SM_Num_Mirror_Planes; i++) {
//				if (mir[i][0]->m != mir[i][1]->m) {
//					save_refl = 1;
//				}
//			}
			
			if (save_refl == 1) {
 				fpp = fopen(refl_check_file_path,"a");
				if (fpp != 0) {
					fprintf(fpp,"name,R0,Qc,alpha,m,W,beta,SLD,Qc_sub m_plot_scale\n");
					
					double m_plot_scale = 0;
					double qc = 0.0217;
					
					for (i = 0; i < SM_Num_Mirror_Planes; i++)
					for (j = 0; j < SM_Num_Spin_States; j++) {
						m_plot_scale = MAX(m_plot_scale, mir[i][j]->m * 1.2);
						fprintf(fpp,"%s, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f, % 10.4f\n",
								mir[i][j]->name, mir[i][j]->R0, mir[i][j]->Qc, mir[i][j]->alpha, mir[i][j]->m, mir[i][j]->W, mir[i][j]->beta, 
								((sm->mat).sub).SLD, (((sm->mat).subsurface)[i]).Qc_sub, m_plot_scale);
						if (qc < mir[i][j]->Qc) qc = mir[i][j]->Qc;
					}
					
					m_plot_scale /= 100;
					fprintf(fpp,"Q,Rm_vac_to_mir_at_plane[0][+],Rm_vac_to_mir_at_plane[0][-],Rm_vac_to_mir_at_plane[1][+],Rm_vac_to_mir_at_plane[1][-]\n");
					double q; 
					for (k = 0; k < 100; k++) {
						q = qc * k * m_plot_scale; 
						fprintf(fpp, "%le",q);
						for (i = 0; i < SM_Num_Mirror_Planes; i++)
						for (j = 0; j < SM_Num_Spin_States; j++) {
							fprintf(fpp, ",%12.9e",sm_calc_Rm(q, mir[i][j]->Qc, mir[i][j]->R0, mir[i][j]->alpha, mir[i][j]->m, mir[i][j]->W, mir[i][j]->beta));
						}
						fprintf(fpp, "\n");
					}
					fclose(fpp);
				}
			}
		}
		
	#ifdef USE_MPI
	} // end if master process
	#endif
	
	#ifdef _OPENMP
	} // end #pragma omp single
	#endif
	
	#if defined(DEBUG_REF_LIB_SAVE)
	MPI_MASTER (
		fpp = fopen("trace.csv","a+");
		if (fpp != 0) {
			fprintf(fpp,
					"event, w,, t,, px,py,pz,, vx,vy,vz,|v|,|vn|,, ws+,ws-,ws,,"
					"sx,sy,sz,|s|,, fa.x,fa.y,fa.z,, fa.s,s+,s-,,"
					"surface intersect,mirror intersect,,location,event,,side,,,plane,,,layer,,,fn.x,fn.y,fn.z,,"
					"at plane, "
					"v_exit0.x,v_exit0.y,v_exit0.z,,v_exit1.x,v_exit1.y,v_exit1.z,,"
					"v_ir0.x,v_ir0.y,v_ir0.z,,v_ir1.x,v_ir1.y,v_ir1.z,,"
					"Rm0+,Rm0-,,Rm1+,Rm1-,,"
					"L_attn_abs0,L_attn_abs1,t_prop_abs0,t_prop_abs1,T_prop_abs0,T_prop_abs1,,"
					"Rs0,Rs1,L_attn_sub,t_prop_sub,T_prop_sub,,"
					"\n");
			fclose(fpp);
		}
	)
	#endif

	return 1; //initialisation succeed
}

int IntersectStdSupermirrorFlat(
		//Calculate the supermirror intersect time and position of a neutron from outside the supermirror 
		//return values: sm_Intersected, sm_Missed, sm_Error in "typedef enum SupermirrorEventCode" in header file
		//note: sm_Missed = neutron either skips supermirror, or intersect only once (i.e. one edge or one vertex), or flies on plane or vertex
		//INPUT
		double t_in, Coords p_in, Coords v_in, 
		double last_time, Coords last_point, int last_plane, 
		Supermirror *sm, 
		//OUTPUT 
		//User declare one or more parameters, e.g. "int num_intersect; double first_intersect_time; Coords first_intersect_point; int first_intersect_plane;", 
		//then passes pointers "&num_intersect, &first_intersect_time, &first_intersect_point, &first_intersect_plane" to function.
		//Pass 0 if not needed.
		int *num_intersect, 
		double*first_intersect_dtime, Coords*first_intersect_dpoint, double*first_intersect_time, Coords*first_intersect_point, int*first_intersect_plane) 
{
//#define DEBUG_IntersectStdSupermirrorFlat
	#if defined(DEBUG_IntersectStdSupermirrorFlat)
	printf(	"%s void IntersectStdSupermirrorFlat(\n"
			"%s \t double t_in, Coords p_in, Coords v_in,\n"
			"%s \t double last_time, Coords last_point, int last_plane,\n"
			"%s \t Supermirror *sm, int *num_intersect,\n"
			"%s \t double*first_intersect_dtime, Coords*first_intersect_dpoint, double*first_intersect_time, Coords*first_intersect_point, int*first_intersect_plane)\n\n"
			"%s t_in=% 7.4f, p_in=(% 7.4f,% 7.4f,% 7.4f), v_in=(% 7.4f,% 7.4f,% 7.4f),\n",
			supermirror_flat_s_prefix, supermirror_flat_s_prefix, supermirror_flat_s_prefix, supermirror_flat_s_prefix, supermirror_flat_s_prefix, 
			supermirror_flat_s_prefix, t_in, p_in.x,p_in.y,p_in.z, v_in.x,v_in.y,v_in.z
			);
	if (last_time == F_INDETERMINED || last_time == D_INDETERMINED)
		printf(	"%s last_time=indetermined, last_point=indetermined, last_plane=indetermined,\n", supermirror_flat_s_prefix);
	else
		printf(	"%s last_time=% 7.4f, last_point=(% 7.4f,% 7.4f,% 7.4f), last_plane=%d,\n",
				supermirror_flat_s_prefix, last_time, last_point.x,last_point.y,last_point.z, last_plane);
	printf(	"%s sm=%X, num_intersect=%X,\n"
			"%s first_intersect_dtime=%X, first_intersect_dpoint=%X, first_intersect_time=%X, first_intersect_point=%X, first_intersect_plane=%X)\n\n",
			supermirror_flat_s_prefix, sm, num_intersect, 
			supermirror_flat_s_prefix, first_intersect_dtime, first_intersect_dpoint, first_intersect_time, first_intersect_point , first_intersect_plane 
			);
	#endif
	
	#if defined(DEBUG_IntersectStdSupermirrorFlat)
	printf("%s incoming t,p,v:|v| = % 7.4f,(% 7.4f,% 7.4f,% 7.4f),(% 7.4f,% 7.4f,% 7.4f):% 7.4f ", supermirror_flat_s_prefix, 
		t_in, p_in.x, p_in.y, p_in.z, v_in.x, v_in.y, v_in.z, coords_len(v_in));
	if (last_plane == I_INDETERMINED) {
		printf("last t,p,plane = indetermined\n");
	}
	else { 
		printf("last t,p,plane = % 7.4f,(% 7.4f,% 7.4f,% 7.4f),%d\n", last_time, last_point.x, last_point.y, last_point.z, last_plane);
	}
	#endif
	
	if (num_intersect) *num_intersect = 0;
	if (first_intersect_dtime) *first_intersect_dtime = F_INDETERMINED;
	if (first_intersect_dpoint) *first_intersect_dpoint = coords_set(F_INDETERMINED,F_INDETERMINED,F_INDETERMINED);
	if (first_intersect_time) *first_intersect_time = F_INDETERMINED;
	if (first_intersect_point) *first_intersect_point = coords_set(F_INDETERMINED,F_INDETERMINED,F_INDETERMINED);
	if (first_intersect_plane) *first_intersect_plane = I_INDETERMINED;
	
	//Find line-polyhedron intersects
	//itype: 1=x plane, 2=x edge, 3=x vertex, 4=on plane, 5=on edge
	#if defined(DEBUG_IntersectStdSupermirrorFlat)
	printf("%s Call line_polyhedron_intersect to find intersect\n", supermirror_flat_s_prefix);
	supermirror_flat_inc_prefix();
	#endif

	SimState state;
	sm_initialise_state(&state);
			
	//polyhedron intersect parameters
	int n = 1; //only use values of the first intersect
	double idtime[2];
	Coords idpoint[2];
	double itime[2];
	Coords ipoint[2];
	int iplane[2];
	int itype[2]; ////type: 1=x plane, 2=x edge, 3=x vertex, 4=on plane, 5=on edge
	line_polyhedron_intersect(t_in, p_in, v_in, &(sm->geo), Maximum_On_Plane_Distance, 0, 0, 
								last_time, last_point, last_plane,  
								&n, idtime, idpoint, itime, ipoint, iplane, itype); 

	#if defined(DEBUG_IntersectStdSupermirrorFlat)
	supermirror_flat_dec_prefix();
	#endif
								
	if (n < 2 || itype[0] > 3) {
		//Neutron either does not intersect, intersect edge or vertex, or flies on plane or vertex, skip
		#if defined(DEBUG_IntersectStdSupermirrorFlat)
		printf("%s Neutron either does not intersect, intersect edge or vertex, or flies on plane or vertex, skip\n", supermirror_flat_s_prefix);
		#endif
		return sm_Missed; //missed, exit calculation
	}
	
	if (num_intersect) *num_intersect = n;
	if (first_intersect_dtime) *first_intersect_dtime = idtime[0];
	if (first_intersect_dpoint) *first_intersect_dpoint = idpoint[0];
	if (first_intersect_time) *first_intersect_time = itime[0];
	if (first_intersect_point) *first_intersect_point = ipoint[0];
	if (first_intersect_plane) *first_intersect_plane = iplane[0];
	
	#if defined(DEBUG_IntersectStdSupermirrorFlat)
	supermirror_flat_inc_prefix();
	sm_print_intersect( "IntersectStdSupermirrorFlat", 1, idtime, idpoint, itime, ipoint, iplane, itype);
	supermirror_flat_dec_prefix();
	#endif

	#if defined(DEBUG_IntersectStdSupermirrorFlat)
	printf("%s IntersectStdSupermirrorFlat done. Return 1.\n", supermirror_flat_s_prefix);
	#endif

	return sm_Intersected; //intersected, exit calculation
}

int StdSupermirrorFlat(
		//Calculates how incoming neutron propagates through the supermirror
		//return values: sm_Exited, sm_Absorbed, sm_Error in "typedef enum SupermirrorEventCode" in header file 
		//INPUT
		double *w_sm, double *t_sm, Coords *p_sm, Coords *v_sm, Coords *s_sm, 
		double*last_time, Coords*last_point, int*last_plane, 
		Supermirror *sm) 
{
//#define DEBUG_StdSupermirrorFlat
	#if defined(DEBUG_StdSupermirrorFlat) 
	printf("StdSupermirrorFlat: incoming =============\n"
			"w,t,p,v:|v|,s3:|s|:s2 = %5e,% 7.4f,(% 7.4f,% 7.4f,% 7.4f),(% 7.4f,% 7.4f,% 7.4f):% 7.4f,(% 7.4f,% 7.4f,% 7.4f):% 7.4f:(% 7.4f,% 7.4f)\n", 
			*w_sm, *t_sm, (*p_sm).x, (*p_sm).y, (*p_sm).z, (*v_sm).x, (*v_sm).y, (*v_sm).z, coords_len(*v_sm), 
			(*s_sm).x, (*s_sm).y, (*s_sm).z, coords_sp((sm->co).fa, *s_sm),(1+coords_sp((sm->co).fa, *s_sm))/2,(1-coords_sp((sm->co).fa, *s_sm))/2);
	#endif
	
	#if defined(DEBUG_REF_LIB_SAVE)
	FILE *fpp = fopen("trace.csv","a+");
	if (fpp != 0) {
		fprintf(fpp,"\n");
		fclose(fpp);
	}
	#endif
	
	SimState state;
	sm_initialise_state(&state);
	
	state.ray_count = mcget_run_num();
	
	state.w = *w_sm; 
	state.t = *t_sm; 
	state.p = *p_sm; 
	state.v = *v_sm; 
	
	state.s = *s_sm;
	double s_len = coords_sp((sm->co).fa, *s_sm); //incident polarisation is projected w.r.t. field-axis to determine polarisation
	state.ws[0] = (1+s_len)/2; state.ws[1] = (1-s_len)/2;

	#if defined(DEBUG_StdSupermirrorFlat) 
	printf("StdSupermirrorFlat 1 ws=%lg,%lg\n", state.ws[0], state.ws[1]);
	#endif
	
	state.last_time = *last_time; 
	state.last_point = *last_point; 
	state.last_plane = *last_plane;
		
	#if defined(DEBUG_REF_LIB_TRACK)
	sprintf(track_msg,"%s w,t,p,v:|v| = %5e,% 7.4f,(% 7.4f,% 7.4f,% 7.4f),(% 7.4f,% 7.4f,% 7.4f):% 7.4f s3:|s|:s2 = (% 7.4f,% 7.4f,% 7.4f):% 7.4f:(% 7.4f,% 7.4f)\n", 
				track_msg, state.w, state.t, (state.p).x,(state.p).y,(state.p).z,(state.v).x,(state.v).y,(state.v).z, coords_len(state.v), 
				(state.s).x,(state.s).y,(state.s).z, coords_sp((sm->co).fa, state.s),(1+coords_sp((sm->co).fa, state.s))/2,(1-coords_sp((sm->co).fa, state.s))/2);
	#endif

	int outcome; 
	int nth=0;

	#if defined(DEBUG_REF_LIB_TRACK)	
	for (int i=0; i<65536; i++) track_msg[i]=0;
	
	#endif

//////1st intersect
#ifndef Intersect_1st
#define Intersect_1st
	
	++nth;
	
	#if defined(DEBUG_StdSupermirrorFlat)
	printf("StdSupermirrorFlat step %d: EXTERNAL INTERSECT ==============================\n", nth);
	set_supermirror_flat_prefix(0);
	#endif
	#if defined(DEBUG_REF_LIB_TRACK)	
	sprintf(track_msg, "%s%d\n", track_msg, nth);
	#endif

	outcome = sm_external_intersect(&state, sm);
	
	#if defined(DEBUG_StdSupermirrorFlat)
	printf("StdSupermirrorFlat: sm_external_intersect nth=%d outcome = %s(%d)\n", 
			nth, ((sm->proc).event)[outcome], outcome);
	supermirror_flat_dec_prefix();
	#endif
	#if defined(DEBUG_REF_LIB_TRACK)	
	sprintf(track_msg, "%s\nnth=%d outcome=%d ", track_msg, nth, outcome);
	#endif

	switch (outcome) {
		
		case sm_Transmitted: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			sprintf(track_msg, "%s 1st sm_Transmitted\n",track_msg);
			#endif
			
			#if defined(DEBUG_StdSupermirrorFlat)
			sm_print_state("sm_external_intersect 1: sm_Transmitted", &state, sm);
			printf("StdSupermirrorFlat: sm_external_intersect outcome = %s(%d), neutron enters supermirror substrate, continue to next step.\n", 
				((sm->proc).event)[outcome], outcome);
			#endif

			break; //transmitted inward, continue to next step
			
		case sm_Missed: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			track_msg[0]=0;
			#endif

			sm_print_state("sm_external_intersect 1: sm_Missed", &state, sm);
			printf("StdSupermirrorFlat: sm_external_intersect outcome = %s(%d), should've been caught in IntersectStdSupermirrorFlat(...), return sm_Error.\n\n",
				((sm->proc).event)[outcome], outcome); 

			return sm_Error; break; //neutron skips module, should have been caught in function IntersectStdSupermirrorFlat(...)
			
		case sm_Exited: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			track_msg[0]=0;
			#endif

			*w_sm = state.w; 
			*t_sm = state.t; 
			*p_sm = state.p; 
			*v_sm = state.v; 
			*s_sm = state.s;
			
			*last_time = state.t;
			*last_point = state.p;
			*last_plane = state.plane;

			#if defined(DEBUG_StdSupermirrorFlat)
			sm_print_state("sm_external_intersect 1: sm_Exited", &state, sm);
			printf("StdSupermirrorFlat: sm_external_intersect outcome = %s(%d), return sm_Exited.\n\n", 
					((sm->proc).event)[outcome], outcome);
			#endif

			return sm_Exited; break; //scattered
			
		case sm_Absorbed:

			#if defined(DEBUG_REF_LIB_TRACK)	
			track_msg[0]=0;
			#endif

			*w_sm = state.w; 
			*t_sm = state.t; 
			*p_sm = state.p; 
			*v_sm = state.v; 
			*s_sm = state.s;

			#if defined(DEBUG_StdSupermirrorFlat)
			sm_print_state("sm_external_intersect 1: sm_Absorbed", &state, sm);
			printf("StdSupermirrorFlat: sm_external_intersect outcome = %s(%d), return sm_Absorbed.\n\n", 
					((sm->proc).event)[outcome], outcome);
			#endif

			return sm_Absorbed; break; //absorbed
			
		case sm_Error: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			#if defined(NEUTRON_HISTORY_LIB)
			save_neutron_history("track",0,track_msg);
			#endif
			printf("%s 1st sm_Error\n",track_msg);
			track_msg[0]=0;
			#endif

			sm_print_state("sm_external_intersect 1: sm_Error", &state, sm);
			printf("StdSupermirrorFlat: sm_external_intersect outcome = %s(%d), something's wrong, return sm_Error.\n\n", 
				((sm->proc).event)[outcome], outcome);

			return sm_Error; break; //something's wrong
			
		default: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			#if defined(NEUTRON_HISTORY_LIB)
			save_neutron_history("track",0,track_msg);
			#endif
			printf("%s 1st default\n",track_msg);
			track_msg[0]=0;
			#endif

			sm_print_state("sm_external_intersect 1: sm_Error", &state, sm);
			printf("StdSupermirrorFlat: sm_external_intersect outcome = %d, something's wrong, return sm_Error.\n\n", outcome); 

			return sm_Error; break; //something's wrong
			
	}

#endif

//////2nd intersect
#ifndef Intersect_2nd
#define Intersect_2nd
	
	++nth;
	
	#if defined(DEBUG_StdSupermirrorFlat)
	printf("StdSupermirrorFlat step %d: INTERNAL INTERSECT ==============================\n", nth);
	set_supermirror_flat_prefix(0);
	#endif
	#if defined(DEBUG_REF_LIB_TRACK)	
	sprintf(track_msg, "%s%d\n", track_msg, nth);
	#endif

	outcome = sm_internal_intersect(&state, sm);
		
	*last_time = state.last_time;
	last_point->x = (state.last_point).x;
	last_point->y = (state.last_point).y;
	last_point->z = (state.last_point).z;
	*last_plane = state.last_plane;

	#if defined(DEBUG_StdSupermirrorFlat)
	printf("StdSupermirrorFlat: sm_internal_intersect nth=%d outcome = %s(%d)\n", 
			nth, ((sm->proc).event)[outcome], outcome);
	supermirror_flat_dec_prefix();
	#endif
	#if defined(DEBUG_REF_LIB_TRACK)	
	sprintf(track_msg, "%s\nnth=%d outcome=%d ", track_msg, nth, outcome);
	#endif

	switch (outcome) {
		
		case  sm_Reflected: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			sprintf(track_msg,"%s 2nd sm_Reflected\n",track_msg);
			#endif

			#if defined(DEBUG_StdSupermirrorFlat)
			sm_print_state("sm_internal_intersect 2: sm_Reflected", &state, sm);
			printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d outcome = %s(%d), neutron transmitted, continue to next step.\n", 
				state.n_surface_intersect, state.n_mirror_intersect, ((sm->proc).event)[outcome], outcome);
			#endif

			break; //transmitted, continue to next step
			
		case  sm_Transmitted: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			sprintf(track_msg,"%s 2nd sm_Transmitted\n",track_msg);
			#endif
			
			#if defined(DEBUG_StdSupermirrorFlat)
			sm_print_state("sm_internal_intersect 2: sm_Transmitted", &state, sm);
			printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d outcome = %s(%d), neutron transmitted, continue to next step.\n", 
				state.n_surface_intersect, state.n_mirror_intersect, ((sm->proc).event)[outcome], outcome);
			#endif

			break; //transmitted, continue to next step

		case  sm_Exited: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			track_msg[0]=0;
			#endif

			*w_sm = state.w; 
			*t_sm = state.t; 
			*p_sm = state.p; 
			*v_sm = state.v; 
			*s_sm = state.s;
			
			*last_time = state.t;
			*last_point = state.p;
			*last_plane = state.plane;

			#if defined(DEBUG_StdSupermirrorFlat)
			sm_print_state("sm_internal_intersect 2: sm_Exited", &state, sm);
			printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d sm_internal_intersect outcome = %s(%d), return sm_Exited.\n\n", 
					state.n_surface_intersect, state.n_mirror_intersect, ((sm->proc).event)[outcome], outcome);
			#endif

			#if defined(DEBUG_StdSupermirrorFlat)
			if (state.plane == 3) {
				//exit from back edge, absorbed
				printf(	"2nd,  mcget_run_num()=%d, exit from back edge: n_surface_intersect=%d, n_mirror_intersect=%d\n",
						mcget_run_num(), state.n_surface_intersect, state.n_mirror_intersect);
				return sm_Absorbed; break;
			}
			#endif
			
			return sm_Exited; break; //scattered
			
		case  sm_Absorbed:

			#if defined(DEBUG_REF_LIB_TRACK)	
			track_msg[0]=0;
			#endif

			*w_sm = state.w; 
			*t_sm = state.t; 
			*p_sm = state.p; 
			*v_sm = state.v; 
			*s_sm = state.s;

			#if defined(DEBUG_StdSupermirrorFlat)
			sm_print_state("sm_internal_intersect 2: sm_Absorbed", &state, sm);
			printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d sm_internal_intersect outcome = %s(%d), return sm_Absorbed.\n\n", 
					state.n_surface_intersect, state.n_mirror_intersect, ((sm->proc).event)[outcome], outcome);
			#endif

			return sm_Absorbed; break; //absorbed
			
		case  sm_Error: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			#if defined(NEUTRON_HISTORY_LIB)
			save_neutron_history("track",0,track_msg);
			#endif
			printf("%s 2nd sm_Error\n",track_msg);
			track_msg[0]=0;
			#endif

			sm_print_state("sm_internal_intersect 2: sm_Error", &state, sm);
			printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d sm_internal_intersect outcome = %s(%d), something's wrong, return sm_Error.\n\n", 
					state.n_surface_intersect, state.n_mirror_intersect, ((sm->proc).event)[outcome], outcome);
			
			return sm_Error; break; //something's wrong
			
		default: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			#if defined(NEUTRON_HISTORY_LIB)
			save_neutron_history("track",0,track_msg);
			#endif
			printf("%s 2nd default\n",track_msg);
			track_msg[0]=0;
			#endif

			sm_print_state("sm_internal_intersect 2: sm_Error", &state, sm);
			printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d sm_internal_intersect outcome = %d, something's wrong, return sm_Error.\n\n", 
					state.n_surface_intersect, state.n_mirror_intersect, outcome); 

			return sm_Error; break; //something's wrong
	}
	
#endif

//////3rd intersect
#ifndef Intersect_3rd
#define Intersect_3rd

	if (state.n_mirror_intersect < SM_Num_Mirror_Planes) {
		
		++nth;
		
		#if defined(DEBUG_StdSupermirrorFlat)
		printf("StdSupermirrorFlat step %d: INTERNAL INTERSECT ==============================\n", nth);
		set_supermirror_flat_prefix(0);
		#endif
		#if defined(DEBUG_REF_LIB_TRACK)	
		sprintf(track_msg, "%s%d\n", track_msg, nth);
		#endif

		outcome = sm_internal_intersect(&state, sm);
		
		#if defined(DEBUG_StdSupermirrorFlat)
		printf("StdSupermirrorFlat: sm_internal_intersect nth=%d outcome = %s(%d)\n", 
				nth, ((sm->proc).event)[outcome], outcome);
		supermirror_flat_dec_prefix();
		#endif
		#if defined(DEBUG_REF_LIB_TRACK)	
		sprintf(track_msg, "%s\nnth=%d outcome=%d ", track_msg, nth, outcome);
		#endif

		switch (outcome) {
			
			case  sm_Reflected: 

				#if defined(DEBUG_REF_LIB_TRACK)	
				sprintf(track_msg,"%s 3rd sm_Reflected\n",track_msg);
				#endif
				
				#if defined(DEBUG_StdSupermirrorFlat)
				sm_print_state("sm_internal_intersect 3: sm_Reflected", &state, sm);
				printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d outcome = %s(%d), neutron transmitted, continue to next step.\n", 
					state.n_surface_intersect, state.n_mirror_intersect, ((sm->proc).event)[outcome], outcome);
				#endif

				break; //transmitted, continue to next step
				
			case  sm_Transmitted: 

				#if defined(DEBUG_REF_LIB_TRACK)	
				sprintf(track_msg,"%s 3rd sm_Transmitted\n",track_msg);
				#endif
				
				#if defined(DEBUG_StdSupermirrorFlat)
				sm_print_state("sm_internal_intersect 3: sm_Transmitted", &state, sm);
				printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d sm_internal_intersect outcome = %s(%d), neutron transmitted, continue to next step.\n", 
					state.n_surface_intersect, state.n_mirror_intersect, ((sm->proc).event)[outcome], outcome);
				#endif

				break; //transmitted, continue to next step
				
			case  sm_Exited: 

				#if defined(DEBUG_REF_LIB_TRACK)	
				track_msg[0]=0;
				#endif

				*w_sm = state.w; 
				*t_sm = state.t; 
				*p_sm = state.p; 
				*v_sm = state.v; 
				*s_sm = state.s;
			
				*last_time = state.t;
				*last_point = state.p;
				*last_plane = state.plane;
					
				#if defined(DEBUG_StdSupermirrorFlat)
				sm_print_state("sm_internal_intersect 3: sm_Exited", &state, sm);
				printf("StdSupermirrorFlat: %d sm_internal_intersect outcome = %s(%d), return sm_Exited.\n\n", state.n_surface_intersect, ((sm->proc).event)[outcome], outcome);
				#endif

				#if defined(DEBUG_StdSupermirrorFlat)
				if (state.plane == 3) {
					//exit from back edge, absorbed
					printf(	"3rd,  mcget_run_num()=%d, exit from back edge: n_surface_intersect=%d, n_mirror_intersect=%d\n",
							mcget_run_num(), state.n_surface_intersect, state.n_mirror_intersect);
					return sm_Absorbed; break;
				}
				#endif

				return sm_Exited; break; //scattered
				
			case  sm_Absorbed:

				#if defined(DEBUG_REF_LIB_TRACK)	
				track_msg[0]=0;
				#endif

				*w_sm = state.w; 
				*t_sm = state.t; 
				*p_sm = state.p; 
				*v_sm = state.v; 
				*s_sm = state.s;

				#if defined(DEBUG_StdSupermirrorFlat)
				sm_print_state("sm_internal_intersect 3: sm_Absorbed", &state, sm);
				printf("StdSupermirrorFlat: %d sm_internal_intersect outcome = %s(%d), return sm_Absorbed.\n\n", state.n_surface_intersect, ((sm->proc).event)[outcome], outcome);
				#endif

				return sm_Absorbed; break; //absorbed
				
			case  sm_Error: 

				#if defined(DEBUG_REF_LIB_TRACK)	
				#if defined(NEUTRON_HISTORY_LIB)
				save_neutron_history("track",0,track_msg);
				#endif
				printf("%s 3rd sm_Error\n",track_msg);
				track_msg[0]=0;
				#endif

				sm_print_state("sm_internal_intersect 3: sm_Error", &state, sm);
				printf("StdSupermirrorFlat: %d sm_internal_intersect outcome = %s(%d), something's wrong, return sm_Error.\n\n", 
						state.n_surface_intersect, ((sm->proc).event)[outcome], outcome);

				return sm_Error; break; //something's wrong
				
			default: 
				
				#if defined(DEBUG_REF_LIB_TRACK)	
				#if defined(NEUTRON_HISTORY_LIB)
				save_neutron_history("track",0,track_msg);
				#endif
				printf("%s 3rd default\n",track_msg);
				track_msg[0]=0;
				#endif

				sm_print_state("sm_internal_intersect 3: sm_Error", &state, sm);
				printf("StdSupermirrorFlat: %d sm_internal_intersect outcome = %d, something's wrong, return sm_Error.\n\n", 
						state.n_surface_intersect, outcome); 

				return sm_Error; break; //something's wrong
		}
	}
	
#endif

//////Internal reflections
#ifndef Internal_reflections
#define Internal_reflections
		
	++nth;
	
	#if defined(DEBUG_StdSupermirrorFlat)
	printf("StdSupermirrorFlat step %d: INTERNAL REFLECTION ==============================\n", nth);
	printf("state.n_mirror_intersect = %d", state.n_mirror_intersect);
	set_supermirror_flat_prefix(0);
	#endif
	#if defined(DEBUG_REF_LIB_TRACK)	
	sprintf(track_msg, "%s%d\n", track_msg, nth);
	#endif
	
	outcome = sm_internal_reflections(&state, sm);
		
	#if defined(DEBUG_StdSupermirrorFlat)
	printf("StdSupermirrorFlat: sm_internal_reflections nth=%d outcome = %s(%d)\n", 
			nth, ((sm->proc).event)[outcome], outcome);
	supermirror_flat_dec_prefix();
	#endif
	#if defined(DEBUG_REF_LIB_TRACK)	
	sprintf(track_msg, "%s\nnth=%d outcome=%d ", track_msg, nth, outcome);
	#endif
	
	switch (outcome) {

		case sm_Exited:

			#if defined(DEBUG_REF_LIB_TRACK)	
			track_msg[0]=0;
			#endif

			*w_sm = state.w; 
			*t_sm = state.t; 
			*p_sm = state.p; 
			*v_sm = state.v; 
			*s_sm = state.s;
			
			*last_time = state.t;
			*last_point = state.p;
			*last_plane = state.plane;
			
			#if defined(DEBUG_StdSupermirrorFlat)
			sm_print_state("sm_internal_reflections: sm_Exited", &state, sm);
			printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d sm_internal_reflections outcome = %s(%d), return sm_Exited.\n\n", 
					state.n_surface_intersect, state.n_mirror_intersect, ((sm->proc).event)[outcome], outcome);
			#endif

			#if defined(DEBUG_StdSupermirrorFlat)
			if (state.plane == 3) {
				//exit from back edge, absorbed
				printf(	"last, mcget_run_num()=%d, exit from back edge: n_surface_intersect=%d, n_mirror_intersect=%d\n",
						mcget_run_num(), state.n_surface_intersect, state.n_mirror_intersect);
			}
			#endif

			return sm_Exited; 
			break; //scattered
			
		case sm_Absorbed:

			#if defined(DEBUG_REF_LIB_TRACK)	
			track_msg[0]=0;
			#endif

			*w_sm = state.w; 
			*t_sm = state.t; 
			*p_sm = state.p; 
			*v_sm = state.v; 
			*s_sm = state.s;

			#if defined(DEBUG_StdSupermirrorFlat)
			sm_print_state("sm_internal_reflections: sm_Absorbed", &state, sm);
			printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d sm_internal_reflections outcome = %s(%d), return sm_Absorbed.\n\n", 
					state.n_surface_intersect, state.n_mirror_intersect, ((sm->proc).event)[outcome], outcome);
			#endif

			return sm_Absorbed; 
			break; //absorbed
						
		case sm_Error: 
		
			#if defined(DEBUG_REF_LIB_TRACK)	
			#if defined(NEUTRON_HISTORY_LIB)
			save_neutron_history("track",0,track_msg);
			#endif
			printf("%s last sm_Error\n",track_msg);
			track_msg[0]=0;
			#endif

			sm_print_state("sm_internal_reflections: sm_Error", &state, sm);
			printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d sm_internal_reflections outcome = %s(%d), something's wrong, return sm_Error.\n\n", 
					state.n_surface_intersect, state.n_mirror_intersect, ((sm->proc).event)[outcome], outcome);

			return sm_Error; 
			break; //something's wrong
			
		default: 

			#if defined(DEBUG_REF_LIB_TRACK)	
			#if defined(NEUTRON_HISTORY_LIB)
			save_neutron_history("track",0,track_msg);
			#endif
			printf("%s last default\n",track_msg);
			track_msg[0]=0;
			#endif

			sm_print_state("sm_internal_reflections: sm_Error", &state, sm);
			printf("StdSupermirrorFlat: n_surface_intersect=%d n_mirror_intersect=%d sm_internal_reflections outcome = %d, something's wrong, return sm_Error.\n\n", 
					state.n_surface_intersect, state.n_mirror_intersect, outcome); 

			return sm_Error; 
			break; //something's wrong
			
	}
	
#endif


//////Something's wrong if it gets here	
	#if defined(DEBUG_REF_LIB_TRACK)	
	#if defined(NEUTRON_HISTORY_LIB)
	save_neutron_history("track",0,track_msg);
	#endif
	printf("%s should not be here\n",track_msg);
	track_msg[0]=0;
	#endif

	printf("StdSupermirrorFlat: SOMETHING'S WRONG, PASSED LAST INTERSECT. Return sm_Error.\n\n");

	return sm_Error;
}

void EmptySupermirrorFlatData(Supermirror*sm) 
{//Clean up when finished all MC calculations
//#define DEBUG_EmptySupermirrorFlatData

	#if defined(DEBUG_EmptySupermirrorFlatData) 
	printf("EmptySupermirrorFlatData(sm) Start\n");
	#endif

	if (sm->proc.initialised != 0) {
		empty_polyhedron(&(sm->geo));
		
		#if defined(DEBUG_EmptySupermirrorFlatData) 
		printf("EmptySupermirrorFlatData: called empty_polyhedron\n");
		#endif
	}	
	sm->proc.initialised = 0;
	
	#if defined(DEBUG_EmptySupermirrorFlatData) 
	printf("EmptySupermirrorFlatData(sm) End\n");
	#endif

}


#endif

/* end of SUPERMIRROR_LIB_C */

