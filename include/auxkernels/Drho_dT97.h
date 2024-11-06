#pragma once

#include "AuxKernel.h"

class Drho_dT97 : public AuxKernel
{
public:

  Drho_dT97(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  const MaterialProperty<Real> & _drho_dT;
  
};