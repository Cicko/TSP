#pragma once

#ifndef DEFAULT_BUFF_VECTOR_SZ
	#define DEFAULT_BUFF_VECTOR_SZ 50
#endif

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	#include <iomanip>
	#include <cstring>
	
	using namespace std;
	
    #define IT_PER_LINE 8	
	#define WIDE_OUTPUT 9
#endif 

#include <cstdio>
#include <cstring>
#include <algorithm>

namespace GOMA {

	template <class T>
	class vector_t
	{
	public:	
		
		T* v_;              /** Base address            */
		
		int sz_;            /** Current number of items */
		int msz_;           /** Maximum size            */
		
		int buff_sz_; 		/** BUffer size             */
		
	public:

		vector_t(void):
		v_(NULL),
		sz_(0),
		msz_(0),
		buff_sz_(DEFAULT_BUFF_VECTOR_SZ)
		{}

		vector_t(const vector_t& C):
		v_(NULL),
		sz_(C.sz_),
		msz_(C.msz_),
		buff_sz_(C.buff_sz_)
		{
			v_ = new T [msz_];
            
            for(int i = 0; i < sz_; i ++)
                v_[i] = C.v_[i];
			
			//memcpy(v_, C.v_, sz_ * sizeof(T));				
		}

		vector_t(int sz):
		v_(NULL),
		sz_(sz),
		msz_(0),
		buff_sz_(DEFAULT_BUFF_VECTOR_SZ)
		{
			msz_ = sz_ + buff_sz_;

			v_ = new T [msz_];
		}

		vector_t(int sz, int buff_sz):
		v_(NULL),
		sz_(sz),
		msz_(sz + buff_sz),
		buff_sz_(buff_sz)
		{
			msz_ = sz_ + buff_sz_;

			v_ = new T [msz_];
		}

		virtual ~vector_t(void)
		{
			if (v_){
				delete [] v_;
				v_ = NULL;
			}
		}	
		
		void clean(void){

			if (v_){
				delete [] v_;
				v_ = NULL;
			}

			sz_ = 0;
			msz_ = 0;
			buff_sz_ = 0;
		}
		
		void init(T val)
		{
			T* v = v_;
			
			for(int i = 0; i < sz_; i++){

				(*v) = val;
				v++;
			}
		}	
		
        bool empty(void) const{
            return sz_ == 0;
        }
        
		virtual void clear(void)
		{
			sz_ = 0;
		}
		
		virtual void clear(T val)
		{
			sz_ = 0;
			
			//DEBUG
			for(int i = 0; i < msz_; i++)
				v_[i] = val;
		}		
		
		void resize(int new_sz, T val)
		{
			if (new_sz <= msz_){
				
				for(int i = sz_; i < new_sz; i++)
					v_[i] = val;
				
				sz_ = new_sz;				
			}
			else{
				
				T* aux = new T [new_sz + buff_sz_];
				
				memcpy(aux, v_, sz_ * sizeof(T));
				
				for(int i = sz_; i < new_sz; i++)
					aux[i] = val;
				
				
				sz_ = new_sz;
				msz_ = sz_ + buff_sz_;
				
				delete [] v_;
				v_ = aux;
			}
		}
		
		virtual void resize(int new_sz)
		{
			if (new_sz < msz_)
				sz_ = new_sz;
			else{
				
				T* aux = new T [new_sz + buff_sz_];
				
                for(int i = 0; i < sz_; i++)
                    aux[i] = v_[i];
				//memcpy(aux, v_, sz_ * sizeof(T));
				
				sz_ = new_sz;
				msz_ = sz_ + buff_sz_;
                
                if (v_)				
                    delete [] v_;
				v_ = aux;
			}
		}		
		
		void push_back(T it)
		{
			resize(sz_ + 1);
			
			v_[sz_ - 1] = it;
		}
		
		virtual T pop_back(void)
		{
			resize(sz_ - 1);
			
			return v_[sz_];
		}	
		
		void sort(void)
		{
			std::sort(v_, v_ + sz_);
		}	
		
		void set(int pos, T it)
		{
	#ifdef _DEBUG
			assert((pos >= 0) && (pos < sz_));
	#endif

			v_[pos] = it;
		}
		
		 T& get(int pos)
		{
	#ifdef _DEBUG
			assert((pos >= 0) && (pos < sz_));
	#endif

			return v_[pos];
		}		
		
		 T get(int pos) const
		{
	#ifdef _DEBUG
			assert((pos >= 0) && (pos < sz_));
	#endif

			return v_[pos];
		}	
		
		T operator[](int pos) const
		{
	#ifdef _DEBUG
			assert((pos >= 0) && (pos < sz_));
	#endif

			return v_[pos];		
		}
		
		T& operator[](int pos)
		{
	#ifdef _DEBUG
			assert(pos < sz_);
	#endif

			return v_[pos];		
		}	
		
		
		int get_sz(void) const
		{
			return sz_;
		}		
		
		T* get_v(void) const
		{
			return v_;
		}	
		
		vector_t& operator=(const vector_t& C)
		{
			sz_ = C.sz_;
			msz_ = C.msz_;
			buff_sz_ = C.buff_sz_;
			
			if (v_){
				delete [] v_;
				v_ = NULL;
			}
			
			v_ = new T [msz_];
			
			memcpy(v_, C.v_, sz_ * sizeof(T));

			return *this;
		}
		
		void copy(const vector_t& C)
		{
			clear();
			resize(C.sz_);
			memcpy(v_, C.v_, sz_ * sizeof(T));
		}		

		void move(vector_t& C)
		{
			clear();
			resize(C.sz_);
			memcpy(v_, C.v_, sz_ * sizeof(T));
			C.clear();
		}
		
	#ifdef _DEBUG
		virtual void write(ostream& os) const
		{
			for(int i = 0; i < sz_; i ++){
				if (!(i % IT_PER_LINE))  os << endl;
				//os << v_[i] << " ";
			}
			
			os.flush();
		}
		
		ostream& operator<<(ostream& os)
		{
			write(os);
			return os;		
		}
	#endif 	
	};

}
