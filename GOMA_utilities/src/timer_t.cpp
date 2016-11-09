#include "timer_t.hpp"

namespace GOMA {

	timer_t::timer_t(void) :
	acumulated_(0.0),
	start_() {
	}

	timer_t::~timer_t(void) {
	}

	void timer_t::start(void) {
		getrusage(RUSAGE_SELF, &start_);
	}

	void timer_t::reset(void) {
		acumulated_ = 0;
	}

	void timer_t::stop(void) {

		rusage stop;
		getrusage(RUSAGE_SELF, &stop);

		acumulated_ += (double) (stop.ru_utime.tv_sec) - (double) (start_.ru_utime.tv_sec);
		acumulated_ += ((double) (stop.ru_utime.tv_usec) - (double) (start_.ru_utime.tv_usec)) / 1000000.0;
	}

	double timer_t::seconds(void) {
		return acumulated_;
	}
	
	double timer_t::current_time() {
		
		rusage stop;
		getrusage(RUSAGE_SELF, &stop);

		double acumulated = 0.0;

		acumulated  = acumulated_ + (double) (stop.ru_utime.tv_sec) - (double) (start_.ru_utime.tv_sec);
		acumulated += acumulated_ + ((double) (stop.ru_utime.tv_usec) - (double) (start_.ru_utime.tv_usec)) / 1000000.0;

		return acumulated;
	}	
}