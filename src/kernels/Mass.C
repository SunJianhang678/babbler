#include "Mass.h"

registerMooseObject("BabblerApp", Mass);

InputParameters
Mass::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addCoupledVar("rho", "density");
  
  return params;
}

Mass::Mass(const InputParameters & parameters)
  : Kernel(parameters),
  _rho(coupledValue("rho")),
  _grad_rho(coupledGradient("rho")),
  _rho_dot(coupledDot("rho"))
{
}

Real
Mass::computeQpResidual()
{
  RealVectorValue _dir = RealVectorValue(1.0, 0.0, 0.0);
  return _test[_i][_qp] * ((_rho[_qp] * _grad_u[_qp] + _u[_qp] * _grad_rho[_qp]) * _dir + _rho_dot[_qp]);
}

Real
Mass::computeQpJacobian()
{
  RealVectorValue _dir = RealVectorValue(1.0, 0.0, 0.0);
  return _test[_i][_qp] * (_rho[_qp] * _grad_phi[_j][_qp] + _phi[_j][_qp] * _grad_rho[_qp]) * _dir;
}

