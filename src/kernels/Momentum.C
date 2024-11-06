#include "Momentum.h"

registerMooseObject("BabblerApp", Momentum);

InputParameters
Momentum::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("Compute residual of momentum eq");
  params.addRequiredCoupledVar("v", "the velocity");
  params.addRequiredParam<Real>("De", "the dia in water");
  params.addParam<Real>("theta", 0.0, "the angle between pipe and vertical direction");
  return params;
}

Momentum::Momentum(const InputParameters & parameters)
  : Kernel(parameters),
  _g(9.8),
  _De(getParam<Real>("De")),
  
  _v(coupledValue("v")),
  _grad_v(coupledGradient("v")),
  _v_dot(coupledDot("v")),

  _theta(getParam<Real>("theta")),
  _f(getMaterialProperty<Real>("f")),
  _rho(getMaterialProperty<Real>("rho"))
{
}


Real
Momentum::computeQpResidual()
{  
  RealVectorValue _dir = RealVectorValue(1.0, 0.0, 0.0);
  return _test[_i][_qp] * (_rho[_qp] * _v_dot[_qp] + _grad_u[_qp] * _dir + _rho[_qp] * _v[_qp] * _grad_v[_qp] * _dir + _rho[_qp] * _g * cos(_theta) + _rho[_qp] * _f[_qp] * _v[_qp] * _v[_qp] / 2 / _De);
}

Real
Momentum::computeQpJacobian()
{
  RealVectorValue _dir = RealVectorValue(1.0, 0.0, 0.0);
  return _test[_i][_qp] * _grad_phi[_j][_qp] * _dir;
}

