#pragma once

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	using namespace std;
#endif

#include "sll_t.hpp"
#include "node_t.hpp"

namespace GOMA {
	
    class tree_node_t : public sll_item_t {
    public:
       node_t* node_;

    public:

        tree_node_t(node_t* node);
        virtual ~tree_node_t(void);

#ifdef _DEBUG
        virtual void write(std::ostream& os);
#endif		
		
        virtual void clean(void);
        virtual sll_item_t* copy(void);

		double get_lb(void);
		void get_lb(double*);
		
		node_t* get_node(void);
    };
	
}