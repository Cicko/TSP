#include "sparse_vector_t.hpp"

#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>

namespace GOMA {

	sparse_vector_t::sparse_vector_t(int sz, double* v, double eps):
	nz_(0),
	max_sz_(0),
	val_(NULL),	
	inx_(NULL) 
	{
		for(int i = 0; i < sz; i ++)
			if (fabs(v[i]) > eps)
				nz_ ++;
				
		max_sz_ = nz_ + DEFAULT_BUFF_SPARSE_VECTOR_SZ;

		val_ = new double [max_sz_];
		inx_ = new int    [max_sz_];


		nz_ = 0;
		for(int i = 0; i < sz; i ++)
			if (fabs(v[i]) > eps){
				inx_[nz_] = i;
				val_[nz_] = v[i];
				nz_ ++;				
			}
	}

	sparse_vector_t::sparse_vector_t(int nz, int* inx, double* val):
	nz_(nz),
	max_sz_(nz + DEFAULT_BUFF_SPARSE_VECTOR_SZ),
	val_(NULL),	
	inx_(NULL) 
	{
            val_ = new double [max_sz_];
            inx_ = new int    [max_sz_];
            
            memcpy(val_, val, nz_ * sizeof(double));
            memcpy(inx_, inx, nz_ * sizeof(int));
	}
    
	sparse_vector_t::sparse_vector_t(int nz, int* inx, double* val, bool):
	nz_(nz),
	max_sz_(nz + DEFAULT_BUFF_SPARSE_VECTOR_SZ),
	val_(NULL),	
	inx_(NULL) 
	{
        if (nz != 0){
            val_ = new double [max_sz_];
            inx_ = new int    [max_sz_];
            
            memcpy(val_, val, nz_ * sizeof(double));
            memcpy(inx_, inx, nz_ * sizeof(int));
        } else {
            max_sz_ = 0;
        }
        
	}

	sparse_vector_t::sparse_vector_t(void):
	nz_(0),
	max_sz_(0),
	val_(NULL),	
	inx_(NULL) 
	{}

	sparse_vector_t::sparse_vector_t(const sparse_vector_t& sm):
	nz_(sm.nz_),	
	max_sz_(sm.max_sz_),
	val_(NULL),
	inx_(NULL)	
	{
		val_ = new double [max_sz_];
		inx_ = new int    [max_sz_];
		
		memcpy(val_, sm.val_, nz_ * sizeof(double));
		memcpy(inx_, sm.inx_, nz_ * sizeof(int));
		
	}

    const sparse_vector_t& sparse_vector_t::operator=(const sparse_vector_t& sm)
    {
        nz_     = sm.nz_;
        max_sz_ = sm.max_sz_;
        val_    = NULL;
        inx_    = NULL;
	
		val_ = new double [max_sz_];
		inx_ = new int    [max_sz_];
		
		memcpy(val_, sm.val_, nz_ * sizeof(double));
		memcpy(inx_, sm.inx_, nz_ * sizeof(int));        
        
        return *this;
    }

	sparse_vector_t::sparse_vector_t(sparse_vector_t* sm):
	nz_(sm->nz_),	
	max_sz_(sm->max_sz_),
	val_(NULL),
	inx_(NULL)	
	{
		val_ = new double [max_sz_];
		inx_ = new int    [max_sz_];
		
		memcpy(val_, sm->val_, nz_ * sizeof(double));
		memcpy(inx_, sm->inx_, nz_ * sizeof(int));
		
	}

	sparse_vector_t::~sparse_vector_t(void) 
	{
		clean();
	}

	void sparse_vector_t::set(int nz, int* inx, double* val)
	{
		clean();
		
		nz_ = nz;
		max_sz_ = nz_ + DEFAULT_BUFF_SPARSE_VECTOR_SZ;
		
		inx_ = new int    [max_sz_];
		val_ = new double [max_sz_];
		
		memcpy(val_, val, nz_ * sizeof(double));
		memcpy(inx_, inx, nz_ * sizeof(int));
	}


	void sparse_vector_t::clean(void)
	{
		if (val_){
			
			delete [] val_;
			val_ = NULL;
		}
		
		if (inx_){
			
			delete [] inx_;
			inx_ = NULL;
		}	
		
		nz_ = 0;
		max_sz_ = 0;	
	}


	void sparse_vector_t::build(int nz)
	{
		nz_ = nz;
		max_sz_ = nz_ + DEFAULT_BUFF_SPARSE_VECTOR_SZ;
		
		inx_ = new int    [max_sz_];
		val_ = new double [max_sz_];
		
	}

	#ifdef _DEBUG
	void sparse_vector_t::write(ostream& os) 
	{
		for (int i = 0; i < nz_; i++)
			os << "[ " << inx_[i] << " " << val_[i] << " ] ";
	}
	#endif

	void sparse_vector_t::sort(void) {
		
		std::vector<std::pair<int, double> > aux(nz_);

		for (int i = 0; i < nz_; i++)
			aux[i] = std::pair<int, double> (inx_[i], val_[i]);

		std::sort(aux.begin(), aux.end());

		for (int i = 0; i < nz_; i++) {
			
			inx_[i] = aux[i].first;
			val_[i] = aux[i].second;
		}

	}

	double sparse_vector_t::scal_prod(sparse_vector_t& si) {

		if ((nz_ == 0) || (si.nz_ == 0))
			return 0.0;
		
		int* a_i_ptr = inx_;
		double * a_v_ptr = val_;
		const int* e_a_i_ptr = inx_ + nz_ - 1;

		int* b_i_ptr = si.inx_;
		double * b_v_ptr = si.val_;
		const int* e_b_i_ptr = si.inx_ + si.nz_ - 1;

		double scalprod = 0;
		bool fin = false;

		do {
			
			if ((*a_i_ptr) == (*b_i_ptr)) {

				scalprod += (*a_v_ptr)*(*b_v_ptr);

				if ((a_i_ptr != e_a_i_ptr) && (b_i_ptr != e_b_i_ptr)) {
					a_i_ptr++;
					a_v_ptr++;
					b_i_ptr++;
					b_v_ptr++;
				} else fin = true;

			} else if ((*a_i_ptr) < (*b_i_ptr)) {

				if (a_i_ptr != e_a_i_ptr) {
					a_i_ptr++;
					a_v_ptr++;
				} else fin = true;

			} else {

				if (b_i_ptr != e_b_i_ptr) {
					b_i_ptr++;
					b_v_ptr++;
				} else fin = true;
			}

		} while (!fin);

		return scalprod;

	}    
		
	double sparse_vector_t::scal_prod(sparse_vector_t* si) {

		if ((nz_ == 0) || (si->nz_ == 0))
			return 0.0;
		
		int* a_i_ptr = inx_;
		double * a_v_ptr = val_;
		const int* e_a_i_ptr = a_i_ptr + nz_;

		int* b_i_ptr = si->inx_;
		double * b_v_ptr = si->val_;
		const int* e_b_i_ptr = b_i_ptr + si->nz_;

		double scalprod = 0;
		bool fin = false;
		
		//cout << "ENTRANDO" << endl;

		do {
			
			//cout << "UNO: "<< (*a_i_ptr) << endl;
			//cout << "DOS: " <<  (*b_i_ptr) << endl;
			
			if ((*a_i_ptr) == (*b_i_ptr)) {

				scalprod += (*a_v_ptr)*(*b_v_ptr);

				a_i_ptr++;
				a_v_ptr++;
				b_i_ptr++;
				b_v_ptr++;

				if ((a_i_ptr == e_a_i_ptr) || (b_i_ptr == e_b_i_ptr)) 
					fin = true;

			} else if ((*a_i_ptr) < (*b_i_ptr)) {

				a_i_ptr++;
				a_v_ptr++;				
				
				if (a_i_ptr == e_a_i_ptr) 
					fin = true;

			} else {

				b_i_ptr++;
				b_v_ptr++;
				
				if (b_i_ptr == e_b_i_ptr) 
					fin = true;
			}

		} while (!fin);

		return scalprod;

	}  		
		
	double sparse_vector_t::scal_prod(double* v) {

		if (nz_ == 0)
			return 0.0;
		
		int*    a_i_ptr = inx_;
		double* a_v_ptr = val_;

		double scalprod = 0;
		int i = 0;

		while (i < nz_) {
			
            //cout << *a_i_ptr << endl;
            
			scalprod += (*a_v_ptr)*(v[*a_i_ptr]);

			a_i_ptr++;
			a_v_ptr++;
				
			i++;
		}

		return scalprod;
	}    	
		
	double sparse_vector_t::scal_prod(double* v, int sz) {

		if (nz_ == 0)
			return 0.0;
		
		int*    a_i_ptr = inx_;
		double* a_v_ptr = val_;

		double scalprod = 0;
		int i = 0;

		while (i < nz_) {
			
			const int inx = *a_i_ptr;
			
			if (inx < sz)
				scalprod += (*a_v_ptr)*(v[inx]);

			a_i_ptr++;
			a_v_ptr++;
				
			i++;
		}

		return scalprod;
	} 		
		
	void sparse_vector_t::set(int pos, double val)
	{
		// Find position by binary search
		
		inx_[nz_] = pos;
		val_[nz_] = val;
		
		nz_ ++;
	#ifdef _DEBUG
		assert(nz_ < max_sz_);
	#endif	
	}


}