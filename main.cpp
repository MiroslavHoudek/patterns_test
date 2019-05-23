#include <iostream>
#include <functional>
#include <vector>

#include "callbackbase.h"

class Callback : public CallbackBase<
                            void(void),
                            void(int,std::string),
                            void(int,int)
                            >
{
public:

private:

};

class ReceiverA
{
public:
    void eventCallback1()
    {
        std::cout << "Receiver A - event 1\n";
    }

    void eventCallback2(int a, std::string s)
    {
        std::cout << "Receiver A - event 2 " << a << " and " << "\"" << s << "\"" <<'\n';
    }

    void eventCallback3(int a, int b)
    {
        std::cout << "Receiver A - event 3 " << a << " and " << b <<'\n';
    }
};

class ReceiverB
{
public:
    inline ReceiverB(Callback * cb) {
        mCb = cb;
    }

    void eventCallback1()
    {
        std::cout << "Receiver B - event 1\n";
    }

    void eventCallback2(int a, std::string s)
    {
        std::cout << "Receiver B - event 2 " << a << " and " << "\"" << s << "\"" <<'\n';
        std::cout << "And unregistering\n";
        mCb->unregisterCallback<1>(104);
    }

private:
    Callback * mCb;
};

int main()
{
    Callback cb;
    ReceiverA r1;
    ReceiverB r2(&cb);

    cb.registerCallback<0, 100>([&r1](){r1.eventCallback1();});
    cb.registerCallback<1, 101>([&r1](int i, std::string s){r1.eventCallback2(i,s);});
    cb.registerCallback<2, 102>([&r1](int i, int j){r1.eventCallback3(i,j);});

    cb.registerCallback<0, 103>([&r2](){r2.eventCallback1();});
    cb.registerCallback<1, 104>([&r2](int i, std::string s){r2.eventCallback2(i,s);});

    cb.raiseEvent<0>();
    cb.raiseEvent<1>(37,"Hello There");
    cb.raiseEvent<2>(182,150);

    std::cout << "pre\n";

    cb.unregisterCallback<0>(103);
    //cb.unregisterCallback<1>(104);

    std::cout << "post\n";

    cb.raiseEvent<0>();
    cb.raiseEvent<1>(37,"Hello There");
}
