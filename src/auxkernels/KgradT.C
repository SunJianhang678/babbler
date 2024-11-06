#include "KgradT.h"

registerMooseObject("BabblerApp", KgradT);

InputParameters
KgradT::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("T", "the Temperature");
  return params;
}

KgradT::KgradT(const InputParameters & parameters)
  : AuxKernel(parameters),
    _grad_T(coupledGradient("T")),
    _k(getMaterialProperty<Real>("k"))
{
}

Real
KgradT::computeValue()
{
  RealVectorValue _dir = RealVectorValue(1.0, 0.0, 0.0);
  return _k[_qp] * _grad_T[_qp] * _dir;
}
