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
	Observer observer;
	subject.registerObserver (&observer);
	std::srand(std::time(0));
	const int TEST_EVENT_ID = std::rand();
	TestEvent event{TEST_EVENT_ID};
	subject.notify(event);
	EXPECT_THAT (observer._receivedEventId, Eq(TEST_EVENT_ID));
	
	
}

TEST(CPP_OBSERVER, registerAndDeregister ) {
	Subject subject;
	Observer observer;
	subject.registerObserver (&observer);
	std::srand(std::time(0));
	const int TEST_EVENT_ID = std::rand();
	subject.notify(TestEvent{TEST_EVENT_ID});
	EXPECT_THAT (observer._receivedEventId, Eq(TEST_EVENT_ID));

	subject.deregisterObserver (&observer);
	observer._receivedEventId=0;	
	subject.notify(TestEvent{TEST_EVENT_ID});
	EXPECT_THAT (observer._receivedEventId, Ne(TEST_EVENT_ID));

	
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
	ObserverMulti observer;
	subject1.registerObserver (&observer);
	subject2.registerObserver (&observer);

	std::srand(std::time(0));
	const int TEST_EVENT_ID1 = std::rand();
	const int TEST_EVENT_ID2 = std::rand();

	TestEvent1 event1{TEST_EVENT_ID1};
	TestEvent2 event2{TEST_EVENT_ID2};

	subject1.notify(event1);
	subject2.notify(event2);
	EXPECT_THAT (observer._receivedEventId1, Eq(TEST_EVENT_ID1));
	EXPECT_THAT (observer._receivedEventId2, Eq(TEST_EVENT_ID2));

	
}


TEST(CPP_OBSERVER, subjectSupportsMultipleEvents ) {

	// TODO: 
}


TEST(CPP_OBSERVER, registeredObserverIsFreedWithoutDeregister ) {
	// TODO: a registered observed is freed and not deregistered
}

int main(int argc, char *argv[])
{
	testing::InitGoogleMock (&argc, argv);
	return RUN_ALL_TESTS();
}
