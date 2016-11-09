#pragma once

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	#include <iomanip>
	#include <cstring>	
	
	using namespace std;
	
    #define IT_PER_LINE 8	
	#define WIDE_OUTPUT 9
#endif 

//#include <cstdint>


extern "C" void set_bit_64  (void*, int i);
extern "C" void reset_bit_64(void*, int i);
extern "C" int test_bit_64 (void*, int i);
extern "C" bool find_bit_64 (void*, int* pos);


#define BITSET_BLOCK_SIZE 64
#define ONE_MASK 0x01

typedef unsigned long int block_t;

namespace GOMA {

	class bitset_64_t {
	public:
		block_t* block_;
		int sz_;

	public:
		bitset_64_t(void);
		bitset_64_t(int max);
		bitset_64_t(const bitset_64_t& bs);

		~bitset_64_t(void);

		void init(int max);

		void insert(int i);
		void insert(const bitset_64_t& bs);
		
		void remove(int i);
		void remove(const bitset_64_t& bs);
		
		bool contains(int i);
		bool contains(const bitset_64_t& a);
		
		void clear(void);
		
		void op_intersec(const bitset_64_t& bsj, bitset_64_t& result);
		void op_union   (const bitset_64_t& bsj, bitset_64_t& result);
		void op_minus   (const bitset_64_t& bsj, bitset_64_t& result);
		
		int cardinality(void);
		
	#ifdef _DEBUG	
		void write(std::ostream&);
	#endif	
		
		bool operator==(bitset_64_t& bs);	
		const bitset_64_t& operator=(const bitset_64_t& bs);	

	private:
		void build(void);
		void clean(void);
	};
	 
	class bitset_128_t {
	public:
		block_t* block_;

	public:
		bitset_128_t(void);
		bitset_128_t(const bitset_128_t& bs);

		~bitset_128_t(void);

		void init(int max);

		void insert(int i);
		void insert(const bitset_128_t& bs);
		
		void remove(int i);
		void remove(const bitset_128_t& bs);
		
		bool contains(int i);
		bool contains(const bitset_128_t& a);
		
		void clear(void);
		
        bool empty_intersec(const bitset_128_t& bsj);
        
		void op_intersec(const bitset_128_t& bsj, bitset_128_t& result);
		void op_union   (const bitset_128_t& bsj, bitset_128_t& result);
		void op_minus   (const bitset_128_t& bsj, bitset_128_t& result);
		
		int cardinality(void);
		
	#ifdef _DEBUG	
		std::ostream& write(std::ostream&);
	#endif	
		
		bool operator==(bitset_128_t& bs);	
        bool operator==(const bitset_128_t& bs);	
		void set(const bitset_128_t& bs);

        bitset_128_t& operator= (const bitset_128_t& bs);

	};     
     
	#define END_BITSET_ITERATOR -1
	  
	class bitset_64_iterator_t {
	public:
		
		block_t*    block_;      // Bitset
		
		block_t 	cb_;         // Current block
		int         cb_inx_;     // Current block inx
		int         offset_;
		
	public:
		bitset_64_iterator_t(const bitset_64_t& bs);
		virtual ~bitset_64_iterator_t(void);

		int get(void);
	}; 

}