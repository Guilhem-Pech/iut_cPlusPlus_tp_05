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

using namespace std;

namespace 
{
class  ITraitCar {
public:
    virtual int operator () (int Caract) const = 0 ;
};

class CToLower : public ITraitCar
{
public :
    virtual ~CToLower (void) {}
    virtual int operator () (int Caract) const
    {
        return tolower (Caract);

    } // operateur()

}; // CToLower


class CToUpper : public ITraitCar
{
public :
    virtual ~CToUpper (void) {}
    virtual int operator () (int Caract) const
    {
        return toupper (Caract);

    } // operateur()

}; // CToUpper

class  CIgnPunct : public ITraitCar
{
public :
    virtual ~ CIgnPunct (void) {}
    virtual int operator () (int Caract) const
    {
        if (ispunct(Caract)){
            return ' ';
        }
        else {
           return Caract;
        }


    } // operateur()

}; // CToUpper




string & Moulinette (string & Str, const ITraitCar & Transf)
{
    for (string::size_type i (Str.size ()); i--; )
        Str [i] = Transf (Str [i]);

    return Str;

} // Moulinette()

void TestFunctor (void)
{
    cout << "Functor abstrait : ";

    string Ligne     ("azert:;,.?GFDSQ");
    string Minusc    ("azert:;,.?gfdsq");
    string Majusc    ("AZERT:;,.?GFDSQ");
    string SansPunct ("AZERT     GFDSQ");

    // ToDo

    assert (Minusc    == Moulinette (Ligne, CToLower()));
            assert (Majusc    == Moulinette (Ligne, CToUpper()));
            assert (SansPunct == Moulinette (Ligne, CIgnPunct()));

            cout << "OK\n";

} // TestFunctor ()



} // namespace anonyme

int main (void)
{
    /*      */    TestFunctor ();     /*           */

    return 0;

} // main()
