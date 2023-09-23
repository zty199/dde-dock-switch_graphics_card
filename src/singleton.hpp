#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<typename T>
class Singleton final
{
public:
    Singleton() = default;
    ~Singleton() = default;

    static T *instance()
    {
        static T object;
        return &object;
    };

    Singleton(const T &) = delete;
    T &operator=(const T &other) = delete;

    Singleton(T &&) = delete;
    T &operator=(T &&other) = delete;
};

#endif // SINGLETON_HPP
