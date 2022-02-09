static inline int iround(float x) {
    int r = int(x);
    if (x < 0)
        r--;
    return r;
}

struct IVec2 {
    int x, z;
    IVec2(Vec3 l) {
        x = iround(l.x);
        z = iround(l.z);
    }
    IVec2(int a, int b) : x(a), z(b) {}
    void operator+=(int v) {
        x += v;
        z += v;
    }
};