#pragma once

#include "Kernel.h"

class Mass : public Kernel
{
public:
  Mass(const InputParameters & parameters);
  static InputParameters validParams();

protected:

  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  
  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _drho_dT;
  const MaterialProperty<Real> & _drho_dp;

  const VariableGradient & _grad_T;
  const VariableGradient & _grad_p;
  const VariableValue & _T_dot;
  const VariableValue & _p_dot;

  
};
