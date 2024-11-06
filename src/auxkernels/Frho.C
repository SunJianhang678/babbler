#include "Frho.h"

registerMooseObject("BabblerApp", Frho);

InputParameters
Frho::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("T", "the Temperature");
  return params;
}

Frho::Frho(const InputParameters & parameters)
  : AuxKernel(parameters),
    _T(coupledValue("T"))
{
}

Real
Frho::computeValue()
{
  return 1000 - 2.5 * (_T[_qp] - 300);
}
