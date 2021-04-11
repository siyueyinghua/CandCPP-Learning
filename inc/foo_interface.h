#include <string>
#include <gmock/gmock.h>

//定义需要模拟的接口类
class FooInterface
{
public:
    virtual ~FooInterface() {}
    virtual std::string getArbitraryString() = 0;

    virtual int getPosition() = 0;
};

class MockFoo : public FooInterface
{
public:
    MOCK_METHOD0(getArbitraryString, std::string());
    MOCK_METHOD0(getPosition, int());
};