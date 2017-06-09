/**
 *
 * @file    LessThanAbstrGen.cpp
 *
 * @authors M. Laporte, D. Mathieu
 *
 * @date    26/04/2010
 *
 * @version V1.0
 *
 **/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

namespace 
{
    template <typename T>
    class ILessThanGen
    {
      public :
        virtual ~ILessThanGen (void) {}
        virtual bool operator () (const T &, const T &) const = 0;

    }; // ILessThanGen

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

    class CTriParAgeAsc : public ILessThanGen <CPers>
    {
      public :
        virtual ~CTriParAgeAsc (void) noexcept {}
        
        virtual bool operator () (const CPers & P1, const CPers & P2)
                        const noexcept
        {
            return P1.GetAge () <= P2.GetAge ();

        } // operator ()

    }; // CTriParAgeAsc

    class CTriParNomDesc : public ILessThanGen <CPers>
    {
      public :
        virtual ~CTriParNomDesc (void) noexcept {}
        
        virtual bool operator () (const CPers & P1, const CPers & P2)
                        const noexcept
        {
            return P1.GetNom () >= P2.GetNom ();

        } // operator ()

    }; // CTriParNomDesc


    void LessThanAbstrGen (void)
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

        cout << "Tri par age croissant\n\n";

        sort (VPers.begin (), VPers.end (), CTriParAgeAsc ());

        for (IndPers_t i (0); i < VPers.size (); ++i)
            cout << VPers [i] << '\n';

        cout << "Tri par nom decroissant\n\n";

        sort (VPers.begin (), VPers.end (), CTriParNomDesc ());

        for (IndPers_t i (0); i < VPers.size (); ++i)
            cout << VPers [i] << '\n';

    } // LessThanAbstrGen()

} // namespace anonyme

int main (void)
{
    LessThanAbstrGen ();

    return 0;

} // main()
