#pragma once
#include "yaEngine.h"



namespace ya
{

    template <typename T, size_t pool_size>
    class ObjectPool
    {
    public:
        T* allocate()
        {
            auto ret = available_list.front();
            available_list.pop_front();
            return ret;
        }

        void deallocate(T* exhausted)
        {
            available_list.push_back(exhausted);
        }

        ObjectPool() : objects{ new T[pool_size] }
        {
            for (size_t i = 0; i < pool_size; ++i)
            {
                available_list.push_back(&objects[i]);
            }
        }

        ~ObjectPool() { delete[] objects; }
        ObjectPool(const ObjectPool& other) = delete;
        ObjectPool& operator=(const ObjectPool&) = delete;

    private:
        T* objects;
        std::list<T*> available_list;
    };
}
//class Object
//{
//public:
//    Object()
//    {
//        cout << "오브젝트 생성자!\n";
//    }
//    ~Object()
//    {
//        cout << "오브젝트 소멸자!\n";
//    }
//    int woon2[100];
//    int world[100];
//};
