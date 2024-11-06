#pragma once

#include "AuxKernel.h"

class KgradT : public AuxKernel
{
public:

  KgradT(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  const VariableGradient & _grad_T;
  const MaterialProperty<Real> & _k;
  
};
