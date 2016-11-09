#include "tree_node_t.hpp"

namespace GOMA {

    tree_node_t::tree_node_t(node_t* node) :
    sll_item_t(),
    node_(node) {
    }

    tree_node_t::~tree_node_t(void) {
		if (node_){
			
			delete node_;
			node_ = NULL;			
		}
    }

#ifdef _DEBUG
    void tree_node_t::write(ostream& os) {
        os << node_->get_lb();
    }
#endif

    void tree_node_t::clean(void) {
		
        if (node_){
            delete node_;
			node_ = NULL;
		}
    }

    sll_item_t* tree_node_t::copy(void) {
        return new tree_node_t(node_);
    }

    double tree_node_t::get_lb(void) {
		return node_->get_lb();
    }
	
	node_t* tree_node_t::get_node(void) {				
		return node_;
    }
			
	
}