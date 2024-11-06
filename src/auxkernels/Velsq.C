#include "Velsq.h"

registerMooseObject("BabblerApp", Velsq);

InputParameters
Velsq::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("v", "the velocity");
  return params;
}

Velsq::Velsq(const InputParameters & parameters)
  : AuxKernel(parameters),
    _v(coupledValue("v"))
{
}

Real
Velsq::computeValue()
{
  return _v[_qp] * _v[_qp];
}
