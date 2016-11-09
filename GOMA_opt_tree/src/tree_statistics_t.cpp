#include "tree_statistics_t.hpp"

#include <cstdio>
#include <cstring>

namespace GOMA {

	tree_statistics_t::tree_statistics_t(int n_objectives):
	global_time_(),
	root_time_(),
	branching_time_(),
	processed_nodes_(),
	created_nodes_(),
	root_lb_(),
	root_ub_(1E100),
	lb_(),
	ub_(1E100),	
	gap_(),
	feasible_(false)
	{
    }
	
	tree_statistics_t::~tree_statistics_t(void)
	{}
	
	void tree_statistics_t::reset(double inf_bound)
	{
			global_time_.reset();
			root_time_.reset();
			branching_time_.reset();
			processed_nodes_ = 0;
			created_nodes_ =  0;
			
            
			root_lb_ = -inf_bound;
			//root_ub_ = inf_bound;
			lb_      = -inf_bound;
			//ub_      = inf_bound;			
            
			gap_ = inf_bound;
			feasible_ = false;
	}
	
	void tree_statistics_t::write(ostream& s_os)
	{
		char aux[256];
		

        if (lb_ > ub_)
            lb_ = ub_;
         
        /*
        if ((root_lb_ < -1E10) && (root_ub_ >-1E10))
            root_lb_ = root_ub_;            
        */ 

        if (lb_ < -1E10)
            sprintf(aux, "%15.7lf \t", -lb_);
        else   if (lb_ < 1E10){
            sprintf(aux, "%15.7lf \t", lb_);
        }  else 
                sprintf(aux, "      Inf       \t");
        
		s_os << aux;

        if (ub_ < -1E10)
            sprintf(aux, "%15.0lf \t", -ub_);
        else
            if (ub_ < 1E10){
                sprintf(aux, "%15.0lf \t", ub_);
            } else 
                sprintf(aux, "      Inf       \t");
                
		s_os << aux; 

		if (root_lb_ < -1E10)
            sprintf(aux, "%15.7lf \t", -root_lb_);
        else  if (root_lb_ < 1E10){
            sprintf(aux, "%15.7lf \t", root_lb_);
        } else 
                sprintf(aux, "      Inf       \t");
        
		s_os << aux;

        if (root_ub_ < -1E10)
            sprintf(aux, "%15.0lf \t", -root_ub_);
        else
            if (root_ub_ < 1E10){
                sprintf(aux, "%15.0lf \t", root_ub_);
            } else 
                sprintf(aux, "      Inf       \t");
            
		s_os << aux;

        const double gap  = (ub_ - lb_)/ub_;
        const double rgap = (ub_ - root_lb_)/ub_;

		if (gap < 1000)
			sprintf(aux, "%7.2lf \t", gap);			
		 else
			sprintf(aux, "    inf \t");
		s_os <<  aux;
        
		if (rgap < 1000)
			sprintf(aux, "%7.2lf \t", rgap);			
		 else
			sprintf(aux, "    inf \t");
		s_os <<  aux;        
		
		sprintf(aux, "%12.1lf \t", global_time_.seconds());
		s_os << aux;
		
		sprintf(aux, "%12.1lf \t", root_time_.seconds());
		s_os << aux;
		
		sprintf(aux, "%12.1lf \t", branching_time_.seconds());
		s_os << aux; 
		
		sprintf(aux, "%7d \t", processed_nodes_);
		s_os << aux;
		
		sprintf(aux, "%7d \t", created_nodes_);
		s_os << aux; 
		
		sprintf(aux,"%3d \t", feasible_);
		s_os << aux;
	}
	
}