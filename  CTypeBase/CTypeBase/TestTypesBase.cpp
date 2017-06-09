/**
 *
 * @file     TestTypesBase.cpp
 *
 * @authors  M. Laporte, D. Mathieu
 *
 * @date     26/04/2010
 *
 * @version  V2.0
 *
 **/
#include <iostream>
#include <exception>
#include <cassert>
#include <sstream>

#include "C2LinksGenIsA.hpp"
#include "TypesBase.hpp"        // Character

using namespace std;
using namespace nsSdD;        // C2LinksGenIsA

#define classdef typedef

namespace 
{


    classdef C2LinksGenIsA <Character> C2LinksAndChar;
    typedef C2LinksAndChar::Ptr2L_t Ptr2L_t;

    void TestTypesBase (void)
    {
        cout << "TestTypesBase : ";

        {
            Ptr2L_t Tete  = new C2LinksAndChar;
            Ptr2L_t Queue = new C2LinksAndChar;
            Tete ->SetSuivant   (Queue);
            Queue->SetPrecedent (Tete);

            for (unsigned char C = 'a'; C < 'f'; ++C)
                Tete->InsereApres (new C2LinksAndChar (Character (C)));

            ostringstream os;
            for (Ptr2L_t Ptr = Tete->GetSuivant(); 
                 Ptr != Queue; Ptr = Ptr->GetSuivant ()) os << *Ptr;

            assert (os.str() == "edcba");

            // Suppression des elements a partir de la fin

            for (unsigned char C = 'a'; C < 'f'; ++C)
            {
                Ptr2L_t Last = Queue->GetPrecedent()->Supprime();
                assert (*Last == Character (C));
                delete Last;
            }
        }
        // Verification de l'arithmetique des entiers avec la classe
        //   Short

        Short S1 (12), S2 (34);
        assert (S1 == 12);
        assert (S2 == 34);
        assert ((S1 + S2) == 46);
        assert (S1++ == 12);
        assert (++S1 == 14);

        cout << "OK\n";

    }// TestTypesBase ()

} // namespace

int main ()
{
    TestTypesBase();    // Attention : exception bad_alloc possible ...

    return 0;

} // main()
