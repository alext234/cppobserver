#include "gmock/gmock.h"
#include "cpp_observer.h"

using namespace std;

class TestEvent {
	string msg;
};

struct Callback {
	void operator() (const TestEvent& event) const {
	}
};
TEST(CPP_OBSERVER, registerAndNotify ) {
	// TODO: registered observer should receive notification
	Observers<TestEvent> eventObservers;


	eventObservers.registerObserver (Callback());

}

TEST(CPP_OBSERVER, multipleRegisterAndNotify ) {
	// TODO: multiple registered observer should receive notification

	// TODO: at least 1 normal function and 1 lambda
}

TEST(CPP_OBSERVER, registerAndDeregister ) {
	// TODO: register and then deregister -> should not receive any notify
}

TEST(CPP_OBSERVER, registeredObserverIsFreedWithoutDeregister ) {
	// TODO: a registered observed is freed and not deregistered
}

int main(int argc, char *argv[])
{
	testing::InitGoogleMock (&argc, argv);
	return RUN_ALL_TESTS();
}
