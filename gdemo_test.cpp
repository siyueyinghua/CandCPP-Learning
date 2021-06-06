#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "gdemo_func.h"
#include "foo_interface.h"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

struct Base
{
  Base() { std::cout << "  Base::Base()\n"; }
  // Note: non-virtual destructor is OK here
  ~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived : public Base
{
  Derived() { std::cout << "  Derived::Derived()\n"; }
  ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};

void thr(std::shared_ptr<Base> p)
{
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::shared_ptr<Base> lp = p; // thread-safe, even though the
                                // shared use_count is incremented
  {
    static std::mutex io_mutex;
    std::lock_guard<std::mutex> lk(io_mutex);
    std::cout << "local pointer in a thread:\n";
  }
}

bool CDummy::isitme(const CDummy &param)
{
  if (&param == this)
    return true;
  else
    return false;
}

int CDummy::get_member1()
{
  return member1;
}

int CDummy::get_member2()
{
  return member2;
}

//----------------------------------------//

bool DDummy::isitme(const DDummy &param)
{
  if (&param == this)
    return true;
  else
    return false;
}

int DDummy::get_member1()
{
  return member1;
}

int DDummy::get_member2()
{
  return member2;
}

//========================================//

TEST(ClassConstruct, WithOutUserDeclare1)
{
  CDummy ca; // CDumy has no user-declared constructor, Compiler-provided default constructor is used
             // The compiler-provided constructor will do nothing, meaning that it will not initialize CDumy::members
             // Hence, here `ca.members` contains garbage, in other word arbitrary value
  CDummy &cb = ca;
  if (cb.isitme(ca))
    std::cout << "yes, ca is ab" << std::endl;
  std::cout << "ca.member1 = " << ca.get_member1() << std::endl;
  std::cout << "ca.member2 = " << ca.get_member2() << std::endl;

  CDummy cc = CDummy(); // Does not use default constructor for `CDumy()`
                        // Uses value-initialization feature instead
  std::cout << "cc.member1 = " << cc.get_member1() << std::endl;
  std::cout << "cc.member2 = " << cc.get_member2() << std::endl;
  GTEST_ASSERT_EQ(cc.get_member1(), 0);
  GTEST_ASSERT_EQ(cc.get_member2(), 0);
}

TEST(ClassConstruct, WithOutUserDeclare2)
{
  // Another example of initialization that is performed without involving constructor is, of course, aggregate initialization

  CDummy cd{}; // Does not use any `C` constructors at all. Same as C c{}; in C++11.
  std::cout << "cd.member1 = " << cd.get_member1() << std::endl;
  std::cout << "cd.member2 = " << cd.get_member2() << std::endl;
  GTEST_ASSERT_EQ(cd.get_member1(), 0);
  GTEST_ASSERT_EQ(cd.get_member2(), 0);

  CDummy ce = {}; // Does not use any `C` constructors at all. Same as C c{}; in C++11.
  std::cout << "ce.member1 = " << ce.get_member1() << std::endl;
  std::cout << "ce.member2 = " << ce.get_member2() << std::endl;
  GTEST_ASSERT_EQ(ce.get_member1(), 0);
  GTEST_ASSERT_EQ(ce.get_member2(), 0);
}

TEST(ClassConstruct, WithUserDeclare1)
{
  // With user defined constructor,
  // compiler will run the construtcor every time instancing an object of the class
  // The parameter list decides which constructor to be runned
  DDummy da; // Note: please don't write "DDummy da() — declare a function of which the return type is DDumy, not an object
  DDummy db = DDummy();

  std::cout << "ca.member1 = " << da.get_member1() << std::endl;
  std::cout << "ca.member2 = " << da.get_member2() << std::endl;
  GTEST_ASSERT_EQ(da.get_member1(), 11);
  GTEST_ASSERT_EQ(da.get_member2(), 22);

  std::cout << "ca.member1 = " << db.get_member1() << std::endl;
  std::cout << "ca.member2 = " << db.get_member2() << std::endl;
  GTEST_ASSERT_EQ(db.get_member1(), 11);
  GTEST_ASSERT_EQ(db.get_member2(), 22);
}

TEST(ClassConstruct, WithUserDeclare2)
{
  DDummy *dc = new DDummy();
  auto dd = new DDummy();
  auto de = new DDummy;
  DDummy &df = *dd;

  std::cout << "dc.member1 = " << dc->get_member1() << std::endl;
  std::cout << "dc.member2 = " << dc->get_member2() << std::endl;
  GTEST_ASSERT_EQ(dc->get_member1(), 11);
  GTEST_ASSERT_EQ(dc->get_member2(), 22);

  std::cout << "dd.member1 = " << dd->get_member1() << std::endl;
  std::cout << "dd.member2 = " << dd->get_member2() << std::endl;
  GTEST_ASSERT_EQ(dd->get_member1(), 11);
  GTEST_ASSERT_EQ(dd->get_member2(), 22);

  std::cout << "de.member1 = " << de->get_member1() << std::endl;
  std::cout << "de.member2 = " << de->get_member2() << std::endl;
  GTEST_ASSERT_EQ(de->get_member1(), 11);
  GTEST_ASSERT_EQ(de->get_member2(), 22);

  std::cout << "df.member1 = " << df.get_member1() << std::endl;
  std::cout << "df.member2 = " << df.get_member2() << std::endl;
  GTEST_ASSERT_EQ(df.get_member1(), 11);
  GTEST_ASSERT_EQ(df.get_member2(), 22);
}

TEST(ClassConstruct, WithUserDeclare3)
{
  DDummy dg(111, 212);
  auto dh = DDummy(121, 222);
  auto di = new DDummy(131, 232);

  std::cout << "dg.member1 = " << dg.get_member1() << std::endl;
  std::cout << "dg.member2 = " << dg.get_member2() << std::endl;
  GTEST_ASSERT_EQ(dg.get_member1(), 111);
  GTEST_ASSERT_EQ(dg.get_member2(), 212);

  std::cout << "dh.member1 = " << dh.get_member1() << std::endl;
  std::cout << "dh.member2 = " << dh.get_member2() << std::endl;
  GTEST_ASSERT_EQ(dh.get_member1(), 121);
  GTEST_ASSERT_EQ(dh.get_member2(), 222);

  std::cout << "di.member1 = " << di->get_member1() << std::endl;
  std::cout << "di.member2 = " << di->get_member2() << std::endl;
  GTEST_ASSERT_EQ(di->get_member1(), 131);
  GTEST_ASSERT_EQ(di->get_member2(), 232);
}

TEST(ThreadShareptr, Baseusage)
{
  std::shared_ptr<Base> p = std::make_shared<Derived>();

  std::cout << "Created a shared Derived (as a pointer to Base)\n"
            << "  p.get() = " << p.get()
            << ", p.use_count() = " << p.use_count() << '\n';
  std::thread t1(thr, p), t2(thr, p), t3(thr, p);
  p.reset(); // release ownership from main
  std::cout << "Shared ownership between 3 threads and released\n"
            << "ownership from main:\n"
            << "  p.get() = " << p.get()
            << ", p.use_count() = " << p.use_count() << '\n';
  t1.join();
  t2.join();
  t3.join();
  std::cout << "All threads completed, the last one deleted Derived\n";
}

//========================================//
using ::testing::Return;

int main(int argc, char *argv[])
{

  ::testing::InitGoogleTest(&argc, argv);

  // ::testing::InitGoogleMock(&argc, argv);

  int a = 4, b = 8;
  std::cout << "add two num: " << a << b << add(a, b) << std::endl;

  std::vector<std::string> msg{"Hello", "C++", "World", "from", "VS Code", "GoogleTest!"};

  for (const std::string &word : msg)
  {
    std::cout << word << " ";
  }
  std::cout << std::endl;

  int n = 100;
  std::string value = "Hello World!";
  MockFoo mockFoo;
  EXPECT_CALL(mockFoo, getArbitraryString())
      .Times(10)
      .WillOnce(Return(value))
      .WillOnce(Return("Hello gmock"));
  std::string returnValue = mockFoo.getArbitraryString();
  std::cout << "Returned Value: " << returnValue << std::endl;

  returnValue = mockFoo.getArbitraryString();
  std::cout << "Returned Value: " << returnValue << std::endl;
  //在这里Times(2)意思是调用两次，但是下边只调用了一次，所以会报出异常
  EXPECT_CALL(mockFoo, getPosition())
      .Times(2)
      .WillRepeatedly(Return(n++));
  int val = mockFoo.getPosition(); //100
  std::cout << "Returned Value: " << val << std::endl;

  val = mockFoo.getPosition(); //100
  std::cout << "Returned Value: " << val << std::endl;

  //getPosition指定了调用两次，这里只调用了一次，所以运行结果显示出错

  return RUN_ALL_TESTS();
}