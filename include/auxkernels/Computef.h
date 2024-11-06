#pragma once

#include "AuxKernel.h"

class Computef : public AuxKernel
{
public:

  Computef(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  const VariableValue & _v;
  const Real _mu;
  const Real _rho;
  const Real _De;

};
