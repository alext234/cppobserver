#ifndef __CPP_OBSERVER__
#define __CPP_OBSERVER__
#include <memory>

template <typename Event>
class AbstractObserver {
public:
	virtual void onNotified (const Event& event) = 0;
	virtual ~AbstractObserver() {}
};


template <typename Event>
class ObservedSubject{
using ObsEventPtr = std::weak_ptr<AbstractObserver<Event>>;
public:
	void registerObserver (ObsEventPtr ob){
		_observers.push_back (ob);
	}
	void deregisterObserver (ObsEventPtr ob){
		for (auto it = _observers.begin(); it !=_observers.end (); ) {
			
			auto obs = (*it).lock();
			if (obs) {
				if (obs.get()==ob.lock().get()) {
					_observers.erase (it);
				} else ++it;
			} else ++it;
		}
	}
protected: 
	void notifyObservers(const Event& event){
		for (auto it = _observers.begin(); it !=_observers.end (); ++it) {
			auto obs = (*it).lock();
			if (obs) {
				obs->onNotified (event);
			}
			
		}

	}

private:
	std::vector<ObsEventPtr>  _observers;
};

#endif //__CPP_OBSERVER__
