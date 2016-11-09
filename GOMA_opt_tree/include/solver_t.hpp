#pragma once

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	using namespace std;
#endif

#include <iostream>
#include "tree_node_t.hpp"
#include "node_t.hpp"

using namespace std;

namespace GOMA {
	
	class solver_t
	{
		
	public:
		
		solver_t(void);	
		virtual ~solver_t(void);
		
		void                init        (tree_node_t*);
		virtual void        init        (node_t*) = 0;	        
		virtual void        optimize    (double ub) = 0;             
		virtual bool        feasible    (void) = 0;
		virtual void        update_output(int verbose, ostream& os) {} 

		virtual double get_lb(void) = 0;
		void update_lb(tree_node_t*);
	};	
	
}

