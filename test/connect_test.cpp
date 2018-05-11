#include "CppUnitLite/CppUnitLite.h"
#include "CppUnitLite/TestDefaultConfig.h"
#include "sigslot_f.h"

namespace {
	long result = 0L;
	void add(long a, long b) {
		result = a + b;
	}
	class MockClass {
	public:
		static void add(long a, long b) {
			::add(a, b);
		}
	};
}

TEST(SigSlotConnect, global_function)
{
  sigslot::signal_fd<long,long> publisher;
  publisher.connect(add);
  publisher(2, 3);
  CHECK_EQUAL(5L, result)
}

TEST(SigSlotConnect, class_function)
{
  sigslot::signal_fd<long,long> publisher;
  publisher.connect(MockClass::add);
  publisher(3, 9);
  CHECK_EQUAL(12L, result)
}