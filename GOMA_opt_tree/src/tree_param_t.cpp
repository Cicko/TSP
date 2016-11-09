#include "tree_param_t.hpp"

namespace GOMA {
	
	tree_param_t::tree_param_t(void):
	verbose_(),
	inf_bound_(),
	int_tolerance_(),
	zero_tolerance_(),
	time_limit_(),
	mem_limit_(),
	node_limit_()
	{
		set_default();
	}
	
	tree_param_t::~tree_param_t(void)
	{}
		
	void tree_param_t::set_default(void)
	{
		verbose_       = 3;
		inf_bound_     = 1E100;
		int_tolerance_ = 0.9999;
		zero_tolerance_ = 1E-3;
		time_limit_    = 3600;
		mem_limit_     = 0x00fffffffffffff;
		node_limit_    = 999999;
	}	
}