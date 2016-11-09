#pragma once

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	using namespace std;
#endif

#include <cstdio>
#include <algorithm>

#ifndef INF_BOUND
	#define INF_BOUND 1E100
#endif

#define EPS_THRL 1E-2


namespace GOMA {

	enum NODE_STATUS {WAITING, DONE, RUNNING};	
	
	class node_t
	{
	public:
	
		int                 id_;
		
		double              lb_;                        /** Lower bound                             */
		
		node_t*				father_;					/** Reference to father                     */
		node_t*				L_child_;					/** Reference to the lower child            */
		node_t*				U_child_;					/** Reference to the upper child 		    */
		
		int                 status_;
		
	public:
		
		node_t(node_t* father, int id = 1):
		id_(id),
		lb_(father?father->lb_:-INF_BOUND),
		father_(father),
		L_child_(NULL),
		U_child_(NULL),
		status_(WAITING)
		{}
		
		virtual ~node_t(void)
		{}
		
		double get_lb(void) {return lb_;}
	
		void branch (node_t*& L_child, node_t*& U_child)
		{
			L_child = copy();
			U_child = copy();
		}  
	
		virtual node_t* copy(void) = 0;
		virtual void release(void) = 0;                                /** Release the unnecessary information              */
		
		void update_lb(void)
		{
			if ((L_child_ != NULL) && (U_child_ != NULL)) 

				//if((L_child_->status_ == DONE) && (U_child_->status_ == DONE))
				{

					const double new_lb = std::min(L_child_->lb_, U_child_->lb_);
#ifdef _DEBUG					
					if (lb_ > new_lb  + EPS_THRL)
						cout << lb_ << " - "<< new_lb << endl;
					//assert(lb_ < new_lb + EPS_THRL);
#endif					
					lb_ = new_lb;
					
					if(father_)
						father_->update_lb();
								
				}
		}
		
#ifdef _DEBUG
		virtual void write(void) = 0;                                  /** Write node details                               */
#endif		
	};	
	
}