




#include <ostream>

extern "C" void* sub_18007A010(void* p) {
    std::ostream& os = *reinterpret_cast<std::ostream*>(p);
    os.put(os.widen('\n'));
    os.flush();
    return p;
}
