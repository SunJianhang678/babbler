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
  
  const VariableValue & _rho;
  const VariableGradient & _grad_rho;
  const VariableValue & _rho_dot;
  
};
