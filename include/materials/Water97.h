/// copied from ex08

#pragma once

#include "Material.h"

class Water97FluidProperties;

class Water97 : public Material
{
public:
  Water97(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties() override;

private:
  /// some properties of water
  
  MaterialProperty<Real> & _rho;
  MaterialProperty<Real> & _f;
  MaterialProperty<Real> & _Cp;
  MaterialProperty<Real> & _k;
  MaterialProperty<Real> & _beta;
  MaterialProperty<Real> & _drho_dT;
  MaterialProperty<Real> & _drho_dp;

  const VariableValue & _T;
  const VariableValue & _p;
  const VariableValue & _v;
  
  const Real _De;
  
  const Water97FluidProperties & _fluid;


};
