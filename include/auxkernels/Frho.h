#pragma once

#include "AuxKernel.h"

class Frho : public AuxKernel
{
public:

  Frho(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  const VariableValue & _T;
  
};
