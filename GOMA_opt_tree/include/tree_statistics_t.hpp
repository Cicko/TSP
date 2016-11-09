#pragma once

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	using namespace std;
#endif

#include <iostream>
using namespace std;

/*#ifdef _OPENMP
	#include "omp_timer_t.hpp"
#else
 */ 
	#include "timer_t.hpp"
/* #endif */ 

namespace GOMA {

	class tree_statistics_t {
	public:

/*		
#ifdef _OPENMP
		omp_timer_t global_time_;
		omp_timer_t root_time_;
		omp_timer_t branching_time_;
#else
*/ 
		timer_t global_time_;
		timer_t root_time_;
		timer_t branching_time_;
/* #endif */

		int processed_nodes_; // Nodos procesados
		int created_nodes_; // Nodos creados

		// Cotas
		double root_lb_;
		double root_ub_;

		double lb_;
		double ub_;

		double vm_;         // Virtual memory
		double rs_;         // Memory
		
		double gap_;
		
		bool feasible_;

	public:

		tree_statistics_t(int n_objectives = 2);
		virtual ~tree_statistics_t(void);
		
		void reset(double inf_bound);
		void write(ostream& os);
	};
	
}
