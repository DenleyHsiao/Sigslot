#include "CppUnitLite/CppUnitLite.h"
#include "sigslot.h"
#include "mock_subscriber.h"

namespace {
    MockSubscriber* subscriber = nullptr;
    void SetUp() {
        subscriber = new MockSubscriber();
    }
    
    void TearDown() {
        delete subscriber;
        subscriber = nullptr;
    }
}

TEST(SigSlotArg, Empty)
{
    sigslot::signal_d<> publisher;
    publisher.connect(subscriber, &MockSubscriber::update);
    publisher();
    CHECK_EQUAL(SimpleString(""), subscriber->result());
}

TEST(SigSlotArg, One)
{
    sigslot::signal_d<int> publisher;
    publisher.connect(subscriber, &MockSubscriber::update<int>);
    publisher(1);
    CHECK_EQUAL(SimpleString("1"), subscriber->result());
}

TEST(SigSlotArg, Two)
{
    sigslot::signal_d<int, int> publisher;
    publisher.connect(subscriber, &MockSubscriber::update<int, int>);
    publisher(1, 2);
    CHECK_EQUAL(SimpleString("12"), subscriber->result());
}

TEST(SigSlotArg, Three)
{
    sigslot::signal_d<int, int, int> publisher;
    publisher.connect(subscriber, &MockSubscriber::update<int, int, int>);
    publisher(1, 2, 3);
    CHECK_EQUAL(SimpleString("123"), subscriber->result());
}

TEST(SigSlotArg, Five)
{
    sigslot::signal_d<int, int, int, int, int> publisher;
    publisher.connect(subscriber, &MockSubscriber::update<int, int, int, int, int>);
    publisher(1, 2, 3, 4, 5);
    CHECK_EQUAL(SimpleString("12345"), subscriber->result());
}

TEST(SigSlotArg, Ten)
{
    sigslot::signal_d<int, int, int, int, int, int, int, int, int, int> publisher;
    publisher.connect(subscriber, &MockSubscriber::update<int, int, int, int, int, int, int, int, int, int>);
    publisher(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    CHECK_EQUAL(SimpleString("12345678910"), subscriber->result());
}

TEST(SigSlotArg, ThreeWithDiffType)
{
    sigslot::signal_d<int, double, std::string> publisher;
    publisher.connect(subscriber, &MockSubscriber::update<int, double, std::string>);
    publisher(1, 3.14159, "abcd");
    CHECK_EQUAL(SimpleString("13.14159abcd"), subscriber->result());
}