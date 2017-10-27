#ifndef ADVANCEDCPP_MY_UNIQUE_PTR_H
#define ADVANCEDCPP_MY_UNIQUE_PTR_H


#ifndef Vec3_H
#define Vec3_H
struct Vec3 {
    int x, y, z;
};
#endif

class unique_ptr_to_vec3 {

private:
    Vec3 * ptr;
public:

    unique_ptr_to_vec3()
    {
        this->ptr = new Vec3();
        this->ptr->x=0;
        this->ptr->y=0;
        this->ptr->z=0;
    }

    ~unique_ptr_to_vec3()
    {
        if(ptr != nullptr)
        delete ptr;
    }

    unique_ptr_to_vec3(unique_ptr_to_vec3&& from) noexcept {
        ptr = from.ptr;
        delete from.ptr;
    }
    unique_ptr_to_vec3(unique_ptr_to_vec3& from) = delete;

    unique_ptr_to_vec3 operator=(const unique_ptr_to_vec3 & from) = delete;

    Vec3 operator*()
    {
        return *ptr;
    }

    Vec3 operator->()
    {
        return *ptr;
    }
};


#endif //ADVANCEDCPP_MY_UNIQUE_PTR_H
