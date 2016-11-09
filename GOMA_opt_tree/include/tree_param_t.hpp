#pragma once

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	using namespace std;
#endif

namespace GOMA {

	class tree_param_t {
	public:
	
		int   verbose_;                             /** Verbose level                       */
	
		double inf_bound_;                          /** Infinitum                           */
		double int_tolerance_;                      /** Tolerance of the integer gap        */
		double zero_tolerance_;                     /** Zero                                */
		
		double      time_limit_;                    /** Wall time limit                     */
		double      mem_limit_;		  			    /** Memory limit                        */		
		long int    node_limit_;					/** Maximum number of branching nodes   */	

	public:
		tree_param_t(void);
		virtual ~tree_param_t(void);
		
		void set_default(void);
	};
	
}