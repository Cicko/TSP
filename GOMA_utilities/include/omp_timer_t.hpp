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

namespace GOMA {

	class omp_timer_t {
	protected:

		double acumulated_;
		double start_;

	public:
		omp_timer_t(void);
		virtual ~omp_timer_t(void);

		void start(void);
		void stop(void);
		void reset(void);
		
		double current_time(void);

		double seconds(void);
	};
	
}