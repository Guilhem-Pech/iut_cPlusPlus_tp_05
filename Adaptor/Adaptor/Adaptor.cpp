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
template <typename T1, typename T2, typename TRes>
    class IBinaryFunction
    {
      public :
        typedef T1   first_argument_type;
        typedef T2   second_argument_type;
        typedef TRes result_type;

        virtual ~IBinaryFunction (void) {}
        virtual result_type operator () (const first_argument_type &, const second_argument_type &) const = 0;

    }; // IBinaryFunction

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


    class CTriParAgeAsc : public IBinaryFunction <CPers,CPers,bool>
    {
      public :

        virtual ~CTriParAgeAsc (void) noexcept {}
        
        virtual bool operator () (const CPers & P1, const CPers & P2)
                        const noexcept
        {
            return P1.GetAge () <= P2.GetAge ();            

        } // operator ()

    }; // CTriParAgeAsc

    class CTriParNomDesc : public IBinaryFunction <CPers, CPers,bool>
    {
      public :
        virtual ~CTriParNomDesc (void) noexcept {}

        virtual bool operator () (const CPers & P1, const CPers & P2)
                        const noexcept
        {
            return P1.GetNom () >= P2.GetNom ();

        } // operator ()

    }; // CTriParNomDesc

    void Adaptator (void)
    {

        cout << "FunctorSort : \n";

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

        sort (VPers.begin (), VPers.end (), CTriParAgeAsc ());

        for (IndPers_t i (0); i < VPers.size (); ++i)
            cout << VPers [i] << '\n';

        cout << "\nTri par nom decroissant\n\n";

        sort (VPers.begin (), VPers.end (), CTriParNomDesc ());

        for (IndPers_t i (0); i < VPers.size (); ++i)
            cout << VPers [i] << '\n';

        cout << "\nRecherche de la premiere personne d'age <= 40 : ";

              CVPers::const_iterator Pos =
                  find_if (VPers.begin (), VPers.end (), bind2nd(CTriParAgeAsc(),CPers("",40)));

              if (VPers.end () == Pos)
                  cout << "Aucun element correspondant\n";
              else
                  cout << *Pos << '\n';

              cout << "\nRecherche de la premiere personne d'age <= 4 : ";

              Pos = find_if (VPers.begin (), VPers.end (),  bind2nd(CTriParAgeAsc(),CPers("",4)));

              if (VPers.end () == Pos)
                  cout << "Aucun element correspondant\n";
              else
                  cout << *Pos << '\n';

    } // Adaptator()

} // namespace anonyme

int main (void)
{
    Adaptator ();

    return 0;

} // main()
