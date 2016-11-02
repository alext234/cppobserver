#include "gmock/gmock.h"
#include "cpp_observer.h"
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace testing;

struct TestEvent {
	TestEvent (int eventId) : _eventId{eventId} {}
	int _eventId;
};

class Subject: public ObservedSubject<TestEvent> {
public:
	void notify (const TestEvent & event) { 
		notifyObservers(event);
	}
};

class Observer: public AbstractObserver<TestEvent>{
public: 
	Observer() : _receivedEventId{0} {}
	void onNotified(const TestEvent& event) override {
		_receivedEventId = event._eventId;
	}
	int _receivedEventId;
};

TEST(CPP_OBSERVER, registerAndNotify ) {
	Subject subject;
	auto observer=make_shared<Observer> ();

	subject.registerObserver (observer);
	std::srand(std::time(0));
	const int TEST_EVENT_ID = std::rand();
	TestEvent event{TEST_EVENT_ID};
	subject.notify(event);
	EXPECT_THAT (observer->_receivedEventId, Eq(TEST_EVENT_ID));
	
	
}

TEST(CPP_OBSERVER, registerAndDeregister ) {
	Subject subject;
	auto observer = make_shared<Observer> ();
	subject.registerObserver (observer);
	std::srand(std::time(0));
	const int TEST_EVENT_ID = std::rand();
	subject.notify(TestEvent{TEST_EVENT_ID});
	EXPECT_THAT (observer->_receivedEventId, Eq(TEST_EVENT_ID));

	subject.deregisterObserver (observer);
	observer->_receivedEventId=0;	
	subject.notify(TestEvent{TEST_EVENT_ID});
	EXPECT_THAT (observer->_receivedEventId, Ne(TEST_EVENT_ID));

	
}

struct TestEvent1 {
	TestEvent1(int eventId) : _eventId{eventId} {}
	int _eventId;
};
struct TestEvent2 {
	TestEvent2 (int eventId) : _eventId{eventId} {}
	int _eventId;
};

class Subject1: public ObservedSubject<TestEvent1> {
public:
	void notify (const TestEvent1 & event) { 
		notifyObservers(event);
	}
};

class Subject2: public ObservedSubject<TestEvent2> {
public:
	void notify (const TestEvent2 & event) { 
		notifyObservers(event);
	}

};

class ObserverMulti: public AbstractObserver<TestEvent1>, public AbstractObserver<TestEvent2> {
public:
	ObserverMulti() : _receivedEventId1{0}, _receivedEventId2{0} {}
	void onNotified(const TestEvent1& event) override {
		_receivedEventId1	 = event._eventId;
	}
	void onNotified(const TestEvent2& event) override {
		_receivedEventId2=event._eventId;
	}
	int _receivedEventId1, _receivedEventId2;
};

TEST(CPP_OBSERVER, registerAndNotifyMultipleEvent ) {
	Subject1 subject1;
	Subject2 subject2;
	auto observer = make_shared<ObserverMulti> ();
	subject1.registerObserver (observer);
	subject2.registerObserver (observer);

	std::srand(std::time(0));
	const int TEST_EVENT_ID1 = std::rand();
	const int TEST_EVENT_ID2 = std::rand();

	TestEvent1 event1{TEST_EVENT_ID1};
	TestEvent2 event2{TEST_EVENT_ID2};

	subject1.notify(event1);
	subject2.notify(event2);
	EXPECT_THAT (observer->_receivedEventId1, Eq(TEST_EVENT_ID1));
	EXPECT_THAT (observer->_receivedEventId2, Eq(TEST_EVENT_ID2));

	
}
//
//
class SubjectMulti:  public ObservedSubject<TestEvent1>, public ObservedSubject<TestEvent2>{
public:
	void notifyEvent1 (const TestEvent1 & event) { 
		::ObservedSubject<TestEvent1>::notifyObservers(event);
	}
	void notifyEvent2 (const TestEvent2 & event) { 
		::ObservedSubject<TestEvent2>::notifyObservers(event);
	}
};
class Observer1: public AbstractObserver<TestEvent1> {
public: 
	Observer1() : _receivedEventId{0} {}
	void onNotified(const TestEvent1& event) override {
		_receivedEventId = event._eventId;
	}
	int _receivedEventId;
};
class Observer2: public AbstractObserver<TestEvent2> {
public: 
	Observer2() : _receivedEventId{0} {}
	void onNotified(const TestEvent2& event) override {
		_receivedEventId = event._eventId;
	}
	int _receivedEventId;
};


TEST(CPP_OBSERVER, subjectSupportsMultipleEvents ) {

	SubjectMulti subject;
	auto observer1=make_shared<Observer1>();
	auto observer2= make_shared<Observer2>();

	subject.ObservedSubject<TestEvent1>::registerObserver (observer1);
	subject.ObservedSubject<TestEvent2>::registerObserver (observer2);


	std::srand(std::time(0));
	const int TEST_EVENT_ID1 = std::rand();
	const int TEST_EVENT_ID2 = std::rand();

	TestEvent1 event1{TEST_EVENT_ID1};
	TestEvent2 event2{TEST_EVENT_ID2};

	subject.notifyEvent1(event1);
	subject.notifyEvent2(event2);
	ASSERT_THAT (observer1->_receivedEventId, Eq(TEST_EVENT_ID1));
	ASSERT_THAT (observer2->_receivedEventId, Eq(TEST_EVENT_ID2));


	

}


TEST(CPP_OBSERVER, registeredObserverIsFreedWithoutDeregister ) {

	Subject subject;
	shared_ptr<Observer> observer (new Observer());
	subject.registerObserver (observer);
	std::srand(std::time(0));
	const int TEST_EVENT_ID = std::rand();
	observer.reset();

	subject.notify(TestEvent{TEST_EVENT_ID});
	// should not have any seg fault!

}

int main(int argc, char *argv[])
{
	testing::InitGoogleMock (&argc, argv);
	return RUN_ALL_TESTS();
}
