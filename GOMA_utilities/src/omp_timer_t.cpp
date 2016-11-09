#include "omp_timer_t.hpp"

#include <omp.h>

namespace GOMA {

	omp_timer_t::omp_timer_t(void) :
	acumulated_(0.0),
	start_(0.0) {
	}

	omp_timer_t::~omp_timer_t(void) {
	}

	void omp_timer_t::start(void) {
		start_ = omp_get_wtime();
	}
	
	void omp_timer_t::reset(void) {
		acumulated_ = 0;
	}	

	void omp_timer_t::stop(void) {

		const double stop = omp_get_wtime();
		acumulated_ += stop - start_;
	}

	double omp_timer_t::seconds(void) {
		return acumulated_;
	}
	
	double omp_timer_t::current_time(void){
		
		const double stop = omp_get_wtime();

		double acumulated = 0.0;

		acumulated = acumulated_ + stop - start_;

		return acumulated;		
	}
	
}