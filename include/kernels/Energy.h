#pragma once

#include "Kernel.h"

class Energy : public Kernel
{
public:
  static InputParameters validParams();

  Energy(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _Cp;
  const MaterialProperty<Real> & _beta;

  const Real _q;

  const VariableValue & _v;
  const VariableGradient & _grad_p;
  const VariableValue & _p_dot;
};
