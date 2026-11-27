












namespace UGS
{
namespace Error
{
class Precondition
{
public:
    virtual ~Precondition();
};
}
}


extern "C" void b41_precondition_dtor_ref(void* self)
{

    static_cast<UGS::Error::Precondition*>(self)->UGS::Error::Precondition::~Precondition();
}
