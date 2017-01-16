#ifndef _FROG_H
#define _FROG_H
#include "dice.h"

class Frog
{
  public:
    Frog();
    
    //accessors
    int GetPosition()    const;
    int GetSteps()    const;
    
    //mutators
    void SetPosition(int pos);
    void Jump();
    
    private:
      int myPosition;
      int mySteps;
      Dice myCoin;
 };
 
 #endif;