/**
 *
 * @file    TestFunctorAbstrait.cpp
 *
 * @authors M. Laporte, D. Mathieu
 *
 * @date    27/04/2010
 *
 * @version V1.0
 *
 * @brief   functor abstrait
 *
 **/
#include <iostream>
#include <string>
#include <cctype>               // ispunct(), islower(), isalpha()
                                // tolower(), toupper()
#include <cassert>
#include <vector>
using namespace std;

namespace 
{
    class ITraitCar
    {
    private:
        static  int m_Cpt;
    public :
        ITraitCar() noexcept {}

        static inline const int& getCpt()  noexcept{
            return m_Cpt;
        }

         virtual ~ITraitCar (void) {}
         virtual int operator () (int Caract) const = 0 ;
    protected:
        static inline void setCpt(int newCpt) noexcept{
            m_Cpt = newCpt;
        }


    }; // ITraitCar
int ITraitCar::m_Cpt=0;

    int ITraitCar::operator () (int) const { m_Cpt++; return 0;}

    class CToLower  : public ITraitCar
    {
      public :
        virtual ~CToLower (void) {}
        virtual int operator () (int Caract) const noexcept
        {
            this->ITraitCar::operator() (Caract) ;
            return tolower (Caract);

        } // operateur()

    }; // CToLower

    class CToUpper : public ITraitCar
    {
      public :
        virtual ~CToUpper (void) {}
        virtual int operator () (int Caract) const noexcept
        {
            this->ITraitCar::operator() (Caract) ;
            return toupper (Caract);

        } // operateur()

    }; // CToUpper

    class CIgnPunct : public ITraitCar
    {
      public :
        virtual ~CIgnPunct (void) {}
        virtual int operator () (int Caract) const noexcept
        {
            this->ITraitCar::operator() (Caract) ;
            return ispunct (Caract) ? ' ' : Caract;

        } // operateur()

    }; // CIgnPunct

   template < typename T, typename R=std::string> R & Moulinette (R & Str, const T & Transf)
    {

        for (unsigned i (Str.size ()); i--; ) Str [i] = Transf (Str [i]);
        return Str;

    } // Moulinette()

    int plus(int i) { return ++i; }

    void TestFunctor (void)
    {
        cout << "Functor abstrait : ";
        std::vector <int> vec(10);
        Moulinette<int(*)(int), std::vector <int>>(vec,plus);
        assert (1 == vec[2]);


        string Ligne     ("azert:;,.?GFDSQ");
        string Minusc    ("azert:;,.?gfdsq");
        string Majusc    ("AZERT:;,.?GFDSQ");
        string SansPunct ("AZERT     GFDSQ");
        assert (Minusc    == Moulinette <int(*)(int)>(Ligne, tolower));
        // ToDo
        assert (0 == ITraitCar::getCpt() );
        assert (Minusc    == Moulinette (Ligne, CToLower  ()));
        assert (15 == ITraitCar::getCpt() );
        assert (Majusc    == Moulinette (Ligne, CToUpper  ()));
        assert (30 == ITraitCar::getCpt() );
        assert (SansPunct == Moulinette (Ligne, CIgnPunct ()));
        assert (45 == ITraitCar::getCpt() );

        cout << "OK\n";

    } // TestFunctor ()

} // namespace anonyme

int main (void)
{
    /*      */    TestFunctor ();     /*           */

    return 0;

} // main()
