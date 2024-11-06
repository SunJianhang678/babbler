#include "Energy.h"

registerMooseObject("BabblerApp", Energy);

InputParameters
Energy::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("Compute residual of energy eq");
  params.addRequiredParam<Real>("q", "heat per volumn");
  params.addRequiredCoupledVar("v", "the velocity");
  
  params.addRequiredCoupledVar("p", "pressure");
  return params;
}

Energy::Energy(const InputParameters & parameters)
  : Kernel(parameters),
  _rho(getMaterialProperty<Real>("rho")),
  _Cp(getMaterialProperty<Real>("Cp")),
  _beta(getMaterialProperty<Real>("beta")),
  
  _q(getParam<Real>("q")),
  
  _v(coupledValue("v")),
  
  _grad_p(coupledGradient("p")),
  _p_dot(coupledDot("p"))
{
}

Real
Energy::computeQpResidual()
{  
  RealVectorValue _dir = RealVectorValue(1.0, 0.0, 0.0);
  return _test[_i][_qp] * (_rho[_qp] * _v[_qp] * _Cp[_qp] * _grad_u[_qp] * _dir - _q - _beta[_qp] * _u[_qp] * _v[_qp] * _grad_p[_qp] * _dir);
}

Real
Energy::computeQpJacobian()
{
  RealVectorValue _dir = RealVectorValue(1.0, 0.0, 0.0);
  return _test[_i][_qp] * (_rho[_qp] * _v[_qp] * _Cp[_qp] * _grad_phi[_j][_qp] * _dir - _beta[_qp] * _phi[_j][_qp] * _v[_qp] * _grad_p[_qp] * _dir);
}
