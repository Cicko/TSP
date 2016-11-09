#include "sparse_matrix_t.hpp"

namespace GOMA {

	sparse_matrix_t::sparse_matrix_t(void):
	n_row_(0),
	n_col_(0),
	nz_(0),
	matbeg_(NULL),
	matind_(NULL),
	matval_(NULL)
	{}
	
	sparse_matrix_t::~sparse_matrix_t(void)
	{
		clean();
	}

	void sparse_matrix_t::build(int n_col, int maxsz)
	{
		matval_ = new double [maxsz];
		matind_ = new int    [maxsz];	
		matbeg_ = new int    [n_col + 1];
	}

	void sparse_matrix_t::clean(void)
	{
		if (matval_){
			delete [] matval_;
			matval_ = NULL;
		}
		
		if (matind_){
			delete [] matind_;
			matind_ = NULL;
		}
		
		if (matbeg_){
			delete [] matbeg_;
			matbeg_ = NULL;
		}		
	}


}

