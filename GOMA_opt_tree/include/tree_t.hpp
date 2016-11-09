#pragma once

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	using namespace std;
#endif

#include <iostream>
using namespace std;

#include "solver_t.hpp"
#include "node_t.hpp"
#include "sll_t.hpp"

#include "tree_param_t.hpp"
#include "tree_statistics_t.hpp"
#include "tree_node_t.hpp"

namespace GOMA {
			
	class tree_t
	{
	public:
	
		tree_param_t param_;
		tree_statistics_t statistics_;		

        sll_t pending_nodes_;
        sll_t processed_nodes_;	

		node_t* root_;
		
	public:
		
		tree_t(void);
		virtual ~tree_t(void);

        void process(ostream& r_os, ostream& s_os);	

	protected:
	
		void init(void);
		virtual tree_node_t* get_node();
		void release_node(tree_node_t*, bool valid_node);
		virtual void release(tree_node_t*) = 0;
		virtual void release(solver_t* solver) = 0;
		
		virtual solver_t* new_solver(void);
		
		void update_lb(tree_node_t* n, solver_t* s);
		virtual void update_ub(solver_t*, tree_node_t* n) = 0;
		virtual void branch(tree_node_t* ,solver_t*) = 0;
		
		virtual void update_tree_lb(tree_node_t*, bool valid_node);
	
        virtual void header(ostream& os) {}
        virtual void foot  (ostream& os) {}
        virtual void update_output(tree_node_t* node, solver_t* solver, ostream& os) {}	
		virtual node_t* root_node(void) = 0;
        
        void clean_tree(void);
		
		bool valid(tree_node_t*);
		
		virtual void write_statistics(ostream& os);
		
	protected:
	
		void clean(void);
		virtual void update_statistics(tree_node_t* node);
		virtual void update_statistics(solver_t* solver);
		void check_if_done(bool& is_done);
		void init_solver(int nthreads, solver_t**&);
		void release_solver(int nthreads, solver_t**&);
	
	};	
	
}