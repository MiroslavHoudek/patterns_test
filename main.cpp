#include <iostream>
#include <functional>
#include <vector>

#include "observable.h"

class Callback : public Observable<
                            void(void),
                            void(int,std::string),
                            void(int,int)
                            >
{
public:

private:
    int a;
    std::string s;
};

class ReceiverA
{
public:
    void EventZeroHappened()
    {
        std::cout << "A has observed event zero\n";
    }

    void EventOneHappened(int a, std::string s)
    {
        std::cout << "A has observed event one with params: " << a << " and " << "\"" << s << "\"" <<'\n';
    }

    void EventTwoHappened(int a, int b)
    {
        std::cout << "A has observed event two with params: " << a << " and " << b <<'\n';
    }
};

class ReceiverB
{
public:
    void EventZeroHappened()
    {
        std::cout << "B has observed event zero\n";
    }
};

int main()
{
    Callback cb;
    ReceiverA r1;
    ReceiverB r2;

    cb.registerCallback<0, 100>([&r1](){r1.EventZeroHappened();});
    cb.registerCallback<1, 101>([&r1](int i, std::string s){r1.EventOneHappened(i,s);});
    cb.registerCallback<2, 102>([&r1](int i, int j){r1.EventTwoHappened(i,j);});

    cb.registerCallback<0, 103>([&r2](){r2.EventZeroHappened();});

    cb.raiseEvent<0>();
    cb.raiseEvent<1>(37,"Hello There");
    cb.raiseEvent<2>(182,150);

    std::cout << "pre";

    cb.unregisterCallback<0, 104>([&r2](){r2.EventZeroHappened();});

    std::cout << "apres";

    cb.raiseEvent<0>();
}
