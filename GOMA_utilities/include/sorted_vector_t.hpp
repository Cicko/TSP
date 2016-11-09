#pragma once

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	#include <iomanip>
	#include <cstring>
	
	using namespace std;

#endif 

#include <cstdio>
#include <cstring>
#include <algorithm>

namespace GOMA {

	class sorted_vector_t
	{
	public:	
		
		int* v_;              /** Base address            */
		
		int sz_;            /** Current number of items */
		int msz_;           /** Maximum size            */
		
	public:

		sorted_vector_t(void);
		sorted_vector_t(const sorted_vector_t& C);
		sorted_vector_t(int sz);
		virtual ~sorted_vector_t(void);	
		
		virtual void clear(void);
        void resize(int new_sz);
		int operator[](int pos) const;
		int& operator[](int pos);
		int get_sz(void) const;	
		int* get_v(void) const;
		sorted_vector_t& operator=(const sorted_vector_t& C);
        int get_pos(int key);
        int get_pos_debug(int key);
        void insert(int key);
   };     

}