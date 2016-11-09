
#include "sorted_vector_t.hpp"

#include <assert.h>
#include <cstdio>

namespace GOMA {


    sorted_vector_t::sorted_vector_t(void):
    v_(NULL),
    sz_(0),
    msz_(0)
    {}

    sorted_vector_t::sorted_vector_t(const sorted_vector_t& C):
    v_(NULL),
    sz_(C.sz_),
    msz_(C.msz_)
    {
        v_ = new int [msz_];
        
        memcpy(v_, C.v_, sz_ * sizeof(int));				
    }

    sorted_vector_t::sorted_vector_t(int sz):
    v_(NULL),
    sz_(0),
    msz_(sz)
    {
        v_ = new int [msz_];
    }

    sorted_vector_t::~sorted_vector_t(void)
    {
        if (v_){
            delete [] v_;
            v_ = NULL;
        }
    }	
    
    void sorted_vector_t::clear(void)
    {
        sz_ = 0;
    }
        
    void sorted_vector_t::resize(int new_sz)
    {
        if (v_){
            delete [] v_;
            v_ = NULL;
        }
        
        v_ = new int [new_sz];

        msz_ = new_sz;
        sz_ = 0;
    }		
    

    
    int sorted_vector_t::operator[](int pos) const
    {
#ifdef _DEBUG
        assert(pos < sz_);
#endif

        return v_[pos];		
    }
    
    int& sorted_vector_t::operator[](int pos)
    {
#ifdef _DEBUG
        assert(pos < sz_);
#endif

        return v_[pos];		
    }	
    
    
    int sorted_vector_t::get_sz(void) const
    {
        return sz_;
    }		
    
    int* sorted_vector_t::get_v(void) const
    {
        return v_;
    }	
    
    sorted_vector_t& sorted_vector_t::operator=(const sorted_vector_t& C)
    {
        sz_ = C.sz_;
        msz_ = C.msz_;
        
        if (v_){
            delete [] v_;
            v_ = NULL;
        }
        
        v_ = new int [msz_];
        
        memcpy(v_, C.v_, sz_ * sizeof(int));

        return *this;
    }
    
    int sorted_vector_t::get_pos_debug(int key){
    
        for(int i = 0; i < sz_; i++)
            if (v_[i] == key)
                return i;
            
        return -1;
    }   
    
    int sorted_vector_t::get_pos(int key){
        
        int izda = 0;
        int dcha = sz_ - 1;
        int mid;
        
        do {
            mid = (izda + dcha);
            mid >>= 1;

            if (v_[mid] < key) 
                izda = mid + 1;
            else 
                dcha = mid - 1;
        
        } while(izda <= dcha);
        
        return izda;
    }
    
    void sorted_vector_t::insert(int key)
    {
        assert(msz_ > sz_);
     
        if (sz_ == 0)
        {
            v_[0] = key;
            sz_ ++;
        } 
        else {

            const int pos = get_pos(key);

            int* pos_ptr = v_ + pos;
            memmove(pos_ptr + 1, pos_ptr, sizeof(int) * (sz_ - pos));

            *pos_ptr = key;
            
            sz_ ++;
        
        }
    }
        
}