#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>

template<typename T, typename... U>
size_t getAddress(std::function<T(U...)> f) {
    typedef T(fnType)(U...);
    fnType ** fnPointer = f.template target<fnType*>();
    return (size_t) *fnPointer;
}

template<typename ... Funcs>
class CallbackBase
{
public:
    //using ObserverList = std::tuple<std::vector<std::weak_ptr<std::function<Funcs>>>...>;
    using ObserverList = std::tuple<std::map<unsigned int, std::function<Funcs>>...>;
    //using ObserverList = std::map<unsigned int, std::tuple<std::vector<std::function<Funcs>>...>>;

    template<unsigned int eventidx, unsigned int handle, typename Callable>
    void registerCallback(Callable c)
    {
        //std::get<eventidx>(observers).emplace_back(c);
        std::get<eventidx>(observers)[handle] = c;
    }

    template<unsigned int eventidx>
    void unregisterCallback(unsigned int handle)
    //void unregisterCallback(Callable c)
    {
        std::cout << "unregister";
        std::get<eventidx>(observers).erase(handle);

        //std::vector<std::function<void()>>::iterator it = std::find(std::get<eventidx>(observers).begin(), std::get<eventidx>(observers).end(), c);
        //auto it = std::find(std::get<eventidx>(observers).begin(), std::get<eventidx>(observers).end(), c);
//        for (auto it = std::get<eventidx>(observers).begin(); it != std::get<eventidx>(observers).end(); it++) {
//            if (*it)
//            {
//                std::cout << "erasing";
//                std::get<eventidx>(observers).erase(it);
//            }
//            else {
//                std::cout << "nope";
//            }
//        }
        //std::get<eventidx>(observers).erase(c);
    }

    template<unsigned int eventidx, typename ... T>
    void raiseEvent(T ... args)
    {
        auto fMap = std::get<eventidx>(observers);
        for (auto const& x : fMap) {
            x.second(std::forward<T>(args)...);
        }
    }

private:
    ObserverList observers;
};

#endif // OBSERVABLE_HPP
