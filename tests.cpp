#include "gmock/gmock.h"
#include "cpp_observer.h"

int main(int argc, char *argv[])
{
	testing::InitGoogleMock (&argc, argv);
	return RUN_ALL_TESTS();
}
