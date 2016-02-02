#ifndef ACTION_HPP
#define ACTION_HPP

template<class T>
struct Action
{
    void (*callback)(T*);
    T* data;
};

template<class T>
void SafeCall(const Action<T>& action)
{
    if (action.callback) action.callback(action.data);
}

#endif

