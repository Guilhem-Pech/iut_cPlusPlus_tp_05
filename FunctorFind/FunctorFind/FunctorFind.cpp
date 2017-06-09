/**
 *
 * @file     FunctorSort.cpp
 *
 * @authors  M. Laporte, D. Mathieu
 *
 * @date     26/04/2010
 *
 * @version  V1.0
 *
 **/
#include <iostream>
#include <string>
#include <algorithm>            // sort()
#include <vector>

using namespace std;

namespace
{
template <typename T>
class IPredicatGen
{
public :
    virtual ~IPredicatGen (void) {}
    virtual bool operator () (const T & pers) const noexcept = 0;

}; // IPredicatGen

class CPers
{
    string   m_Nom;
    unsigned m_Age;

public :
    CPers (const string & Nom, unsigned Age)
        : m_Nom (Nom), m_Age (Age) {}

    const string & GetNom (void) const noexcept { return m_Nom; }
    unsigned       GetAge (void) const noexcept { return m_Age; }

private :
    ostream & _Edit (ostream & os)  const
    {
        return os << GetAge () << " - " << GetNom ();

    } // _Edit()

public :
    friend ostream & operator << (ostream & os, const CPers & P)
    {
        return P._Edit (os);

    }

}; // CPers


class CSelParTrancheAge : public IPredicatGen <CPers>{
    unsigned m_AgeMin;
    unsigned m_AgeMax;
public:
    CSelParTrancheAge(const unsigned & ageMin, const unsigned & ageMax ):
        m_AgeMin(ageMin),m_AgeMax(ageMax){}
    virtual ~CSelParTrancheAge() noexcept {}
    virtual bool operator () (const CPers & pers) const noexcept
    {
        return pers.GetAge() >= m_AgeMin and pers.GetAge()<= m_AgeMax;

    } // operator ()

};

class  CSelParNomMin :public IPredicatGen <CPers>{
    string m_NomMin;
public:
    CSelParNomMin(const string & nomMin) noexcept:
        m_NomMin(nomMin){}
    virtual ~CSelParNomMin() noexcept {}
    virtual bool operator () (const CPers & pers) const noexcept
    {
        return pers.GetNom() > m_NomMin;

    } // operator ()

};

void FunctorFind (void)
{
    cout << "FunctorFind : \n";

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

    for (IndPers_t i (0); i < VPers.size (); ++i)
        cout << VPers [i] << '\n';

    CVPers::const_iterator Pos;

    cout << "\nRecherche sur  43 <= age <= 75 : ";

    Pos = find_if (VPers.begin (), VPers.end (), CSelParTrancheAge(43,75));
    if (VPers.end () == Pos)
        cout << "Aucun element ne correspond a ce critere\n";
    else
        cout << *Pos << '\n';

    cout << "\nRecherche sur  43 <= age <= 45 : ";

    Pos = find_if (VPers.begin (), VPers.end (), CSelParTrancheAge(43,45));
    if (VPers.end () == Pos)
        cout << "Aucun element ne correspond a ce critere\n";
    else
        cout << *Pos << '\n';

    cout << '\n';


    ///////////////////////////////////////////////////////////////////////////
    cout << "\nRecherche sur nom > Noemie : ";

           Pos = find_if (VPers.begin (),  VPers.end (), CSelParNomMin("Noemie"));

           if (VPers.end () == Pos)
               cout  << "Aucun element ne correspond a ce critere\n";
           else
               cout << *Pos << '\n';

           cout  << "\nRecherche sur nom > alfred : ";

           Pos = find_if (VPers.begin (),  VPers.end (), CSelParNomMin("alfred"));

           if (VPers.end () == Pos)
               cout  << "Aucun element ne correspond a ce critere\n";
           else
               cout << *Pos << '\n';

} // FunctorFind()
}
int main (void)
{
    FunctorFind ();

    return 0;

} // main()
