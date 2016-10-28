#ifndef __CPP_OBSERVER__
#define __CPP_OBSERVER__
#include <map>

template <typename Event>
class Observers {
using ObsFunc = std::function<void(const Event&)>;
public:
	void registerObserver (ObsFunc func){
		_observers.push_back (func);
	}
private:
	std::vector<ObsFunc> _observers;

};

#endif //__CPP_OBSERVER__
