#include "frog.h"

Frog::Frog()
  :  myPosition(0), mySteps(0), myCoin(2)
  {
  }
  
int Frog::GetPosition() const
{
  return myPosition;
}

int Frog::GetSteps()  const
{
  return mySteps;
}

void Frog::SetPosition(int pos)
{
  myPosition = pos;
}

void Frog::Jump()
{
  if (myCoin.Roll() == 1)
    myPosition++;
  else
    myPosition--;
}