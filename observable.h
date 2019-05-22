#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>

template<typename T, typename... U>
size_t getAddress(std::function<T(U...)> f) {
    typedef T(fnType)(U...);
    fnType ** fnPointer = f.template target<fnType*>();
    return (size_t) *fnPointer;
}

template<typename ... Funcs>
class Observable
{
public:
    using ObserverList = std::tuple<std::map<unsigned int, std::function<Funcs>>...>;

    template<unsigned int eventidx, unsigned int handle, typename Callable>
    void registerCallback(Callable c)
    {
        std::get<eventidx>(observers).insert(handle, c);
    }

    template<unsigned int eventidx, unsigned int handle, typename Callable>
    void unregisterCallback(Callable c)
    {
        std::cout << "unregister";
        //std::vector<std::function<void()>>::iterator it = std::find(std::get<eventidx>(observers).begin(), std::get<eventidx>(observers).end(), c);
        //auto it = std::find(std::get<eventidx>(observers).begin(), std::get<eventidx>(observers).end(), c);
        for (auto it = std::get<eventidx>(observers).begin(); it != std::get<eventidx>(observers).end(); it++) {
//            if (getAddress( c) == getAddress(*it))
//            {
//                std::cout << "erasing";
//                std::get<eventidx>(observers).erase(it);
//            }
//            else {
//                std::cout << "nope";
//            }
        }
        //std::get<eventidx>(observers).erase(c);
    }

    template<unsigned int eventidx, typename ... T>
    void raiseEvent(T ... args)
    {
        for(auto f: std::get<eventidx>(observers))
        {
            //f(std::forward<T>(args)...);
        }
    }

private:
    ObserverList observers;
};

#endif // OBSERVABLE_HPP
