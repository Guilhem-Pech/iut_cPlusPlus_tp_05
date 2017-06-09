#include <iostream>
#include <string>
#include <cctype>               // ispunct(), islower(), isalpha()
// tolower(), toupper()
#include <cassert>
#include <vector>
using namespace std;

namespace {
class CPers /* : public CEditable */
{
    string   m_Nom;
    unsigned m_Age;

public :
    CPers (const string & Nom, unsigned Age)
        : m_Nom (Nom), m_Age (Age) {}

    const string & GetNom (void) const throw () { return m_Nom; }
    unsigned       GetAge (void) const throw () { return m_Age; }

private :
    ostream & _Edit (ostream & os)  const
    {
        return os << GetAge () << " - " << GetNom ();

    } // _Edit()

public :    // ajouté pour faciliter les essais

    friend ostream & operator << (ostream & os, const CPers & P)
    {
        return P._Edit (os);
    }

}; // CPers



class ILessThanGen {
public:
    virtual ~ILessThanGen (void) {}
    virtual bool operator () (const CPers & p1, const CPers & p2) const = 0 ;
};

class CTriParAgeAsc : public ILessThanGen{
public :
    virtual ~CTriParAgeAsc (void) {}
    virtual bool operator () (const CPers & p1, const CPers & p2) const noexcept
    {
        return p1.GetAge()<p2.GetAge();

    } // operateur()
};

class CTriParNomDesc : public ILessThanGen{
public:
    virtual ~CTriParNomDesc (void) {}
    virtual bool operator () (const CPers & p1, const CPers & p2) const noexcept
    {
        return p1.GetNom()[0]>p2.GetNom()[0];

    } // operateur()
};
}

template <typename Iter_t, typename T>
void SelectSort (Iter_t Deb, Iter_t Fin,
                 const T & IsInf)
{
    if (Fin <= Deb) return;

    for ( ; Deb < Fin - 1; ++Deb)
    {
        Iter_t RgMin = Deb;
        for (Iter_t j (Deb + 1); j < Fin; ++j)
            if (IsInf (*j, *RgMin)) RgMin = j;
        swap (*Deb, *RgMin);
    }

} // SelectSort()





void TestLessThanAbstrGen (void)
{
    cout << "LessThanAbstrGen : \n";

    typedef vector <CPers> CVPers;
    typedef CVPers::size_type IndPers_t;
    CVPers VPers;

    VPers.push_back ( CPers ("Charlotte", 21));
    VPers.push_back ( CPers ("Alfred",    12));
    VPers.push_back ( CPers ("Jean",      42));
    VPers.push_back ( CPers ("Noemie",    11));
    VPers.push_back ( CPers ("Berthe",    99));
    VPers.push_back ( CPers ("Agathe",    29));
    VPers.push_back ( CPers ("Sylvain",   42));
    VPers.push_back ( CPers ("Pierre",    75));

    cout << "\nTri par age croissant\n\n";

    SelectSort (VPers.begin(), VPers.end(), CTriParAgeAsc());

    for (IndPers_t i (0); i < VPers.size (); ++i)
        cout << VPers [i] << '\n';

    cout << "\nTri par nom decroissant\n\n";

    SelectSort (VPers.begin (), VPers.end (), CTriParNomDesc ());

    for (IndPers_t i (0); i < VPers.size (); ++i)
        cout << VPers [i] << '\n';

} // TestLessThanAbstrGen()


int main(int argc, char *argv[])
{
    TestLessThanAbstrGen();    
    return 0;
}
