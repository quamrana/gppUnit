#pragma once

#include "CompositeNotification.h"

namespace gppUnit {
	class MethodTimer;

	struct ProjectContext {
		explicit ProjectContext(MethodTimer* timer_):timer(timer_){}
		CompositeNotification notify;
		MethodTimer* timer;
		//TODO: Add command line options here
	};
}
