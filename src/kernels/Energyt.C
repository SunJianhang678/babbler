#include "Energyt.h"

registerMooseObject("BabblerApp", Energyt);

InputParameters
Energyt::validParams()
{
  InputParameters params = TimeDerivative::validParams();
  params.addClassDescription("Compute residual of energy eq relating to time");
  return params;
}

Energyt::Energyt(const InputParameters & parameters)
  : TimeDerivative(parameters),
  _rho(getMaterialProperty<Real>("rho")),
  _Cp(getMaterialProperty<Real>("Cp"))
{
}

Real
Energyt::computeQpResidual()
{  
  return _rho[_qp] * _Cp[_qp] * TimeDerivative::computeQpResidual();
}

Real
Energyt::computeQpJacobian()
{
  return _rho[_qp] * _Cp[_qp] * TimeDerivative::computeQpJacobian();
}
