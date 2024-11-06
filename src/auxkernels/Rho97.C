#include "Rho97.h"

registerMooseObject("BabblerApp", Rho97);

InputParameters
Rho97::validParams()
{
  InputParameters params = AuxKernel::validParams();
  
  return params;
}

Rho97::Rho97(const InputParameters & parameters)
  : AuxKernel(parameters),
    _rho(getMaterialProperty<Real>("rho"))
{
}

Real
Rho97::computeValue()
{
  return _rho[_qp];
}