#include "Mass.h"

registerMooseObject("BabblerApp", Mass);

InputParameters
Mass::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addCoupledVar("T", "Temperature");
  params.addCoupledVar("p", "pressure");
  return params;
}

Mass::Mass(const InputParameters & parameters)
  : Kernel(parameters),
  _grad_T(coupledGradient("T")),
  _T_dot(coupledDot("T")),
  _grad_p(coupledGradient("p")),
  _p_dot(coupledDot("p")),
  _rho(getMaterialProperty<Real>("rho")),
  _drho_dT(getMaterialProperty<Real>("drho_dT")),
  _drho_dp(getMaterialProperty<Real>("drho_dp"))
{
}

Real
Mass::computeQpResidual()
{
  RealVectorValue _dir = RealVectorValue(1.0, 0.0, 0.0);
  return _test[_i][_qp] * ((_rho[_qp] * _grad_u[_qp] + _u[_qp] * _drho_dT[_qp] * _grad_T[_qp] + _u[_qp] * _drho_dp[_qp] * _grad_p[_qp]) * _dir 
    + _drho_dT[_qp] * _T_dot[_qp] + _drho_dp[_qp] * _p_dot[_qp]);
}

Real
Mass::computeQpJacobian()
{
  RealVectorValue _dir = RealVectorValue(1.0, 0.0, 0.0);
  return _test[_i][_qp] * (_rho[_qp] * _grad_phi[_j][_qp] + _phi[_j][_qp] * (_drho_dT[_qp] * _grad_T[_qp] + _drho_dp[_qp] * _grad_p[_qp])) * _dir;
}

