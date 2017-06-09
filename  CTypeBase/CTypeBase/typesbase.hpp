#ifndef TYPESBASE_HPP
#define TYPESBASE_HPP
#include <cstdint>

namespace std {



template <typename T>
class CTypeBase {
private:
    T m_Val;
public:
    explicit CTypeBase(const T & val=T()) :
        m_Val(val){}

    operator T () {
        return this->m_Val;
    }

    CTypeBase<T> & operator ++ (void) noexcept{
        ++m_Val;
        return *this;
    }
    CTypeBase<T> operator ++ (int) noexcept {
        CTypeBase copy(*this);
        ++(*this);
        return copy;
    }

};
typedef CTypeBase<uint16_t> Short ;
typedef CTypeBase<uint32_t> Integer ;
typedef CTypeBase<uint8_t> Character ;
}


#endif // TYPESBASE_HPP
