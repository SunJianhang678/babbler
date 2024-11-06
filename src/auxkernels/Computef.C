#include "Computef.h"

registerMooseObject("BabblerApp", Computef);

InputParameters
Computef::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("v", "the velocity");
  params.addParam<Real>("mu", 1.01e-3, "dynamic viscosity");
  params.addParam<Real>("rho", 1.0e3, "density");
  params.addRequiredParam<Real>("De", "the dia in water");  
  return params;
}

Computef::Computef(const InputParameters & parameters)
  : AuxKernel(parameters),
    _v(coupledValue("v")),
    _mu(getParam<Real>("mu")),
    _rho(getParam<Real>("rho")),
    _De(getParam<Real>("De"))
{
}

Real
Computef::computeValue()
{
  Real _Re = _De * _rho * _v[_qp] / _mu;
  return std::max(64.0/_Re, 0.204 * std::pow(_Re, -0.2));
}