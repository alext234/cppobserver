#ifndef __CPP_OBSERVER__
#define __CPP_OBSERVER__
#include <memory>
#include <vector>

template <typename Event>
class AbstractObserver {
public:
	virtual void onNotified (const Event& event) = 0;
	virtual ~AbstractObserver() {}
};


template <typename Event>
class Observable{
using CallableFunc = std::function<void(const Event&)>;
public:
	
	void registerObserver (std::shared_ptr<AbstractObserver<Event>> ob){
		_observers.push_back (ob);
	}
	void registerObserver (CallableFunc callable){
		struct CallableWrapper: public AbstractObserver<Event> {
			CallableWrapper(CallableFunc func):_callable{func} {}
			void onNotified (const Event& event) override {
				_callable(event);	
			}
			CallableFunc _callable;
		};

		auto observer = std::make_shared<CallableWrapper>(callable);
		_observersFromLambda.push_back(observer);

		registerObserver(observer);
	}

	void deregisterObserver (std::shared_ptr<AbstractObserver<Event>> ob){
		for (auto it = _observers.begin(); it !=_observers.end (); ) {
			
			auto obs = (*it).lock();
			if (obs) {
				if (obs.get()==ob.get()) {
					_observers.erase (it);
				} else ++it;
			} else ++it;
		}
	}
	void notifyObservers(const Event& event){
		for (auto it = _observers.begin(); it !=_observers.end (); ++it) {
			auto obs = (*it).lock();
			if (obs) {
				obs->onNotified (event);
			}
			
		}

	}

protected:
	std::vector<std::weak_ptr<AbstractObserver<Event>> >  _observers;
	std::vector<std::shared_ptr<AbstractObserver<Event>> >  _observersFromLambda; // as a place holder to keep these objects alive (i.e. from killing away by smartpointer)
};

#endif //__CPP_OBSERVER__
