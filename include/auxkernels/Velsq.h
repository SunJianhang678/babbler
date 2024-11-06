#pragma once

#include "AuxKernel.h"

class Velsq : public AuxKernel
{
public:

  Velsq(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  const VariableValue & _v;
  
};
