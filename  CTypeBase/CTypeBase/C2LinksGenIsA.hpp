/**
 *
 * @file    C2LinksGenIsA.hpp
 *
 * @authors D. Mathieu, M. Laporte
 *
 * @date    23/04/2010
 *
 * @Version V1.0
 *
 * @brief   Classe C2LinksGenIsA d'une liste double generique
 *
 **/

#pragma once

#include <stdexcept>

namespace nsSdD
{
    template <class T>
    class C2LinksGenIsA : public T
    {
      public :
        typedef C2LinksGenIsA <T> * Ptr2L_t;

      protected :
        Ptr2L_t m_Precedent;
        Ptr2L_t m_Suivant;
      
      private :
        // Fonctions membres interdites :

        C2LinksGenIsA (const C2LinksGenIsA &);
        C2LinksGenIsA & operator = (const C2LinksGenIsA &);
    
      public :
        C2LinksGenIsA (const T &     Info      = T(), 
                       const Ptr2L_t Precedent = 0,
                       const Ptr2L_t Suivant   = 0)    throw ();
        ~C2LinksGenIsA (void)                          throw ();
    
        Ptr2L_t  GetPrecedent (void) const             throw ();
        Ptr2L_t  GetSuivant   (void) const             throw ();
    
        void SetSuivant   (const Ptr2L_t Suivant)      throw ();
        void SetPrecedent (const Ptr2L_t Precedent)    throw ();
    
        Ptr2L_t InsereAvant (Ptr2L_t NewElem)          throw ();
        Ptr2L_t InsereApres (Ptr2L_t NewElem)          throw ();
        Ptr2L_t Supprime    (void)                     throw ();

    }; // C2LinksGenIsA

} // nsSdD

#define TEMPL    template <class T>
#define TEMPLINL TEMPL inline

#define SDDELEM nsSdD::C2LinksGenIsA <T> 

TEMPLINL 
SDDELEM::C2LinksGenIsA (const T &     Info      /* = T() */, 
                        const Ptr2L_t Precedent /* = 0   */,
                        const Ptr2L_t Suivant   /* = 0   */) throw ()
    : T (Info), m_Precedent (Precedent), m_Suivant (Suivant) {} 

TEMPLINL SDDELEM::~C2LinksGenIsA (void) throw () { }

TEMPLINL SDDELEM * SDDELEM::GetPrecedent (void) const throw ()
{
    return m_Precedent;

} // GetPrecedent()

TEMPLINL SDDELEM * SDDELEM::GetSuivant (void) const throw ()
{
    return m_Suivant;

} // GetSuivant()

TEMPLINL void SDDELEM::SetPrecedent (Ptr2L_t Precedent) throw ()
{
    m_Precedent = Precedent;

} // SetPrecedent()

TEMPLINL void SDDELEM::SetSuivant (Ptr2L_t Suivant) throw ()
{
    m_Suivant = Suivant;

} // SetSuivant()

TEMPL SDDELEM * SDDELEM::InsereApres (Ptr2L_t NewElem) throw ()
{
   NewElem->SetPrecedent (this);
   NewElem->SetSuivant   (GetSuivant());
   GetSuivant ()->SetPrecedent (NewElem);
   SetSuivant (NewElem);

   return NewElem;

} // InsereApres()

TEMPL SDDELEM * SDDELEM::InsereAvant (Ptr2L_t NewElem) throw ()
{
    return GetPrecedent ()->InsereApres (NewElem);

} // InsereAvant()

TEMPL SDDELEM * SDDELEM::Supprime (void) throw ()
{
   GetSuivant   ()->SetPrecedent (GetPrecedent ());
   GetPrecedent ()->SetSuivant   (GetSuivant   ());

   return this;

} // Supprime()

#undef  SDDELEM
