#include "Drho_dT97.h"

registerMooseObject("BabblerApp", Drho_dT97);

InputParameters
Drho_dT97::validParams()
{
  InputParameters params = AuxKernel::validParams();
  
  return params;
}

Drho_dT97::Drho_dT97(const InputParameters & parameters)
  : AuxKernel(parameters),
    _drho_dT(getMaterialProperty<Real>("drho_dT"))
{
}

Real
Drho_dT97::computeValue()
{
  return _drho_dT[_qp];
}