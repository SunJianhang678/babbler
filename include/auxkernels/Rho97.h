#pragma once

#include "AuxKernel.h"

class Rho97 : public AuxKernel
{
public:

  Rho97(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  const MaterialProperty<Real> & _rho;
  
};
