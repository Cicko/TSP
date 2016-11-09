#pragma once

#ifndef DEFAULT_BUFF_SPARSE_VECTOR_SZ
	#define DEFAULT_BUFF_SPARSE_VECTOR_SZ 10
#endif

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	#include <iomanip>
	#include <cstring>
	
	using namespace std;
	
    #define IT_PER_LINE 8	
	#define WIDE_OUTPUT 9
#endif 

#include <cstdio>


namespace GOMA {

	class sparse_matrix_t {
		
	public:
			int                     n_row_;
			int               		n_col_;
			
			int 			    	nz_;		

			int*			  		matbeg_;
			int*              		matind_;		
			double*                 matval_;

	public:
		sparse_matrix_t(void);
		virtual ~sparse_matrix_t(void);

	public:
		void clean(void);
		void build(int n_col, int maxsz);
		
	#ifdef _DEBUG
	public:
			void write(ostream& os);
			ostream& operator<<(ostream& os);
	#endif	
	};

}