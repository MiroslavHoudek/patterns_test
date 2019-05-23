#ifndef CALLBACKBASE_H
#define CALLBACKBASE_H

#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>

template<typename ... Funcs>
class CallbackBase
{
public:
    using ObserverList = std::tuple<std::map<unsigned int, std::function<Funcs>>...>;

    template<unsigned int eventidx, unsigned int handle, typename Callable>
    void registerCallback(Callable c)
    {
        std::get<eventidx>(observers)[handle] = c;
    }

    template<unsigned int eventidx>
    void unregisterCallback(unsigned int handle)
    {
        std::get<eventidx>(observers).erase(handle);
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

#endif // CALLBACKBASE_H
