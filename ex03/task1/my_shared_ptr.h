#ifndef ADVANCEDCPP_MY_SHARED_PTR_H
#define ADVANCEDCPP_MY_SHARED_PTR_H

#include <map>
#include <iostream>

#ifndef Vec3_H
#define Vec3_H
struct Vec3 {
    int x, y, z;
};
#endif



class my_shared_ptr {
private:

    class my_shared_ptr_container {
    public:
        static my_shared_ptr_container& getInstance()
        {
            static my_shared_ptr_container    instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
            return instance;
        }
    private:
        std::map<Vec3*,int> num_of_ptrs;

        my_shared_ptr_container() {}                    // Constructor? (the {} brackets) are needed here.


        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
    public:
        my_shared_ptr_container(my_shared_ptr_container const&)               = delete;
        void operator=(my_shared_ptr_container const&)  = delete;


        void add_ptr(Vec3 *ptr)
        {
            num_of_ptrs[ptr]++;
        }

        void remove(Vec3 *ptr)
        {
            num_of_ptrs[ptr]--;
        }

        int get_number_of_ptr(Vec3 *ptr)
        {
            return num_of_ptrs[ptr];
        }

    };




    Vec3 * ptr;


public:

    my_shared_ptr(Vec3 * ptr)
    {
        this->ptr = ptr;
        my_shared_ptr_container::getInstance().add_ptr(ptr);
    }

    ~my_shared_ptr()
    {
        if(ptr!= nullptr)
        {
            my_shared_ptr_container::getInstance().remove(ptr);
            delete ptr;
        }
    }

    my_shared_ptr(my_shared_ptr&& from) {
        ptr = from.ptr;
    }

    my_shared_ptr(my_shared_ptr& from) {
        ptr = from.ptr;
    }
};


#endif //ADVANCEDCPP_MY_SHARED_PTR_H
