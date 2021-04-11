#ifndef _GDEMO_FUNC_H_
#define _GDEMO_FUNC_H_

int add(int a, int b)
{
    return a + b;
}

class CDummy {
public:
    bool isitme (const CDummy& param);     //why not (CDummy* param);
    int get_member1();
    int get_member2();
private:
    int member1;
    int member2;
};

class DDummy {
public:
    DDummy(): member1(11), member2(22)
    {
        std::cout << "user difined construtor1" << std::endl;
    }
    DDummy(const int& initial_member1, const int& initial_member2): member1(initial_member1), member2(initial_member2)
    {
        std::cout << "user difined construtor" << std::endl;
    }
    bool isitme (const DDummy& param);     //why not (CDummy* param);
    int get_member1();
    int get_member2();
private:
    int member1;
    int member2;
};



#endif