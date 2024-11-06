#pragma once

#include "Kernel.h"

class Momentum : public Kernel
{
public:
  static InputParameters validParams();

  Momentum(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const Real _g;
  const Real _De;
  const Real _theta;
  
  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _f;
  
  const VariableValue & _v;
  const VariableGradient & _grad_v;
  const VariableValue & _v_dot;
};
