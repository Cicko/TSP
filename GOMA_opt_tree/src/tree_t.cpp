#include "tree_t.hpp"

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_num_threads() 1
    #define omp_get_thread_num() 0
#endif
namespace GOMA {
		
	tree_t::tree_t(void):
	param_(),
	statistics_(),
	pending_nodes_(),
	processed_nodes_(),
	root_(NULL)
	{}
	
	tree_t::~tree_t(void)
	{
		clean();
	}

	void tree_t::init(void)
	{
		statistics_.reset(param_.inf_bound_);
        
		clean();
        
		tree_node_t* t_node = new tree_node_t(root_node());
		
		root_ = t_node->get_node();
        
		pending_nodes_.push_back(t_node);
        
	}
	
	void tree_t::clean(void)
	{
		pending_nodes_.clean();
		processed_nodes_.clean();
	}
	
	void tree_t::check_if_done(bool& is_done)
	{
		if (is_done)  return;
		else{
			
			is_done = (pending_nodes_.empty() || 
				(statistics_.global_time_.current_time() > param_.time_limit_) || 
				(statistics_.processed_nodes_ > param_.node_limit_));
		}

	} 
	
	void tree_t::update_statistics(solver_t* solver)
	{
		
	}	
	
	void tree_t::update_statistics(tree_node_t* node)
	{		
		if (node->get_node()->id_ == 0){
			
			statistics_.root_time_.stop();
			statistics_.root_lb_ = node->get_lb();
			statistics_.root_ub_ = statistics_.ub_;
		}
			
	   statistics_.processed_nodes_ ++;
	}
	
	tree_node_t* tree_t::get_node()
	{
		if (pending_nodes_.inicio_ == NULL)
			return NULL;
		
		//const double inf_bound = param_.inf_bound_;
		
		tree_node_t* si = (tree_node_t*)(pending_nodes_.inicio_);		
		node_t* nodo = si->get_node();	
		
		double best_lb = nodo->lb_;
		tree_node_t* best_si = (tree_node_t*)(si);
		si = (tree_node_t*)(si->next_);
		
		while(si != NULL){
		
			nodo = si->get_node();
			
			//const double c_lb = nodo->father_?nodo->father_->get_lb():inf_bound;
            const double c_lb = nodo->get_lb();
			
			if (c_lb < best_lb){
			
				best_lb = c_lb;
				best_si = (tree_node_t*)(si);
			} 
			
			si = (tree_node_t*)(si->next_);
		}
		 
		pending_nodes_.remove(best_si);
		best_si->prev_ = NULL;
		best_si->next_ = NULL;
		best_si->get_node()->status_ = RUNNING;		
		
        return best_si;		
	}
    
    
	void tree_t::clean_tree(void)
	{
		if (pending_nodes_.inicio_ == NULL)
			return;
		
		tree_node_t* aux = NULL;
		tree_node_t* si = (tree_node_t*)(pending_nodes_.inicio_);		
		node_t* nodo = NULL;	
		
		while(si != NULL){
		
			nodo = si->get_node();
			
			const double c_lb = nodo->get_lb();
			
			if (c_lb + param_.int_tolerance_ > statistics_.ub_){
				aux = (tree_node_t*)(si);
                si = (tree_node_t*)(si->next_);
                
                pending_nodes_.remove(aux);
                
                release_node(aux, true);
			} else
            {
                 si = (tree_node_t*)(si->next_);
            }
			
			
		}
	}    
	
	bool tree_t::valid(tree_node_t* node){
		
		node_t* n = node->get_node();
		
		if (!n->father_)
			return true;
		else {
            
            if (n->get_lb() + param_.int_tolerance_ > statistics_.ub_){
                return false;                          
            }
            else
                return true;  
        }            
		
		
	}
	
	void tree_t::init_solver(int nthreads, solver_t**& solver)
	{
		solver = new solver_t* [nthreads];
		
		for(int i = 0; i < nthreads; i++)
			solver[i] = new_solver();
				
	}
	
	void tree_t::release_solver(int nthreads, solver_t**& solver)
	{		
		if (solver){
		
			 for(int i = 0; i < nthreads; i++)
				if (solver[i]){
					delete solver[i];
					solver[i] = NULL;
				}
			 
			 delete [] solver;
			 solver = NULL;
		}		
	}
	
	void tree_t::process(ostream& r_os, ostream& s_os)
	{
		 //header(r_os);
		 
		 bool is_done = false;
		 
		 statistics_.global_time_.start();
		 statistics_.root_time_.start();
         
		 init();
         
		 tree_node_t* node;
		 int thread_id;
		 solver_t** solver;

		 //#pragma omp parallel private(node, thread_id)
		 {	
			  int nthreads = omp_get_num_threads();
			  thread_id = omp_get_thread_num();
			  
			  if (thread_id == 0)
				init_solver(nthreads, solver); 
			  
			 //#pragma omp barrier 
			 while (!is_done)
			 {
                 
				 node   = NULL;
				 //#pragma omp critical
					node = get_node();                   // Bloquea el nodo en la lista de nodos pendientes
			
				 if (node){

					 const bool valid_node = valid(node);
					 
					 if (valid_node){
						 
						solver[thread_id]->init(node);     			 // Inicializa el resolutor con el nodo
                        
                        //const double prev_lb = node->get_lb();
                        
						solver[thread_id]->optimize(statistics_.ub_);                 // Optimiza el nodo
						
						solver[thread_id]->update_lb(node);                  // Actualiza la cota inferior global
	 
                        //const double new_lb = node->get_lb();
#ifdef _DEBUG                        
                        //if (new_lb < prev_lb - 1E-2)
                        //    cout << new_lb << " -> " << prev_lb << endl;
#endif                            
     
						//#pragma omp critical
						{	
							update_ub(solver[thread_id], node);                  // Actualiza la cota superior y mejor solución factible

							branch(node, solver[thread_id]);               // Ramifica si fuese necesario
							update_tree_lb(node, valid_node);

#ifndef NDEBUG							
							update_output(node, solver[thread_id], r_os);  // Muestra salida	
#endif							
							update_statistics(node);
							update_statistics(solver[thread_id]); 						
							 
							release(solver[thread_id]);
						}											
						//if (node->get_node()->id_ == 17)
							//cout << "HOLA" << endl;
					}
					//#pragma omp critical
					{	
					 release_node(node, valid_node);  // Libera el nodo y lo incluye en la lista de nodos procesados
					 check_if_done(is_done);          // Comprueba si se ha producido la condición de salida
					}					

				 }
			 }
			  if (thread_id == 0)
				release_solver(nthreads, solver);
		 }		
 
		 clean();
		 
		 statistics_.feasible_ = statistics_.ub_ > 1E20? false : true;
		 statistics_.global_time_.stop();
		 
		 foot(r_os);
	}
	
	solver_t* tree_t::new_solver(void) 
	{ 
		return NULL;
	}
	
	void tree_t::update_lb(tree_node_t* n, solver_t* s) 
	{
		s->update_lb(n); 
	}	
	
	void tree_t::update_tree_lb(tree_node_t* node, bool valid_node)
	{		

		const double inf_bound = param_.inf_bound_;

		if (pending_nodes_.inicio_ == NULL){
			statistics_.lb_ = node->get_node()->lb_;
			root_->lb_ = node->get_node()->lb_;		
			return;
		}
		
        
		tree_node_t* si = (tree_node_t*)(pending_nodes_.inicio_);		
		node_t* nodo = si->get_node();	
		
		double best_lb = inf_bound;
		
		while(si != NULL){
		
			nodo = si->get_node();
			
			const double c_lb = nodo->get_lb();
			
			if (c_lb < best_lb){
			
				best_lb = c_lb;
			} 
			
			if (nodo->father_)
				if (nodo->father_->lb_ > nodo->lb_)
				{
					cout << nodo->father_->id_ << " : "<< nodo->father_->lb_ << " > " << nodo->id_ << " : " << nodo->lb_ << endl;
					exit(0);
				}
			
			si = (tree_node_t*)(si->next_);
		}
		 	
		statistics_.lb_ = best_lb;
		//root_->lb_ = best_lb;

	}	
	
	
	void tree_t::release_node(tree_node_t* node, bool valid_node)
	{		
		processed_nodes_.push_back(node);		
		
		node->get_node()->status_ = DONE;	
		release(node);
	}	
	
	void tree_t::write_statistics(ostream& s_os)
	{
		statistics_.write(s_os);
	}
}