#pragma once

#include "TimeDerivative.h"

class Energyt : public TimeDerivative
{
public:
  static InputParameters validParams();

  Energyt(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _Cp;
  
};