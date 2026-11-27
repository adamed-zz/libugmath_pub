













#include <exception>


extern "C" int b43_uncaught_exceptions_ref()
{
    return std::uncaught_exceptions();
}
