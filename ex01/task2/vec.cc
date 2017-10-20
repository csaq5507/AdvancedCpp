class Vec3 {
    int x, y, z;

  public:
    Vec3() = default;
    Vec3(int x, int y, int z) : x(x), y(y), z(z) {}
};

int main() {
    Vec3 v0;
    Vec3 v1();
    Vec3 v2(1, 2, 3);
    Vec3 v3{1, 2, 3};
    Vec3 v4 = {1, 2, 3};
}
