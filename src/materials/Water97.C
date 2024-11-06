#include "Water97.h"
#include "Water97FluidProperties.h"

registerMooseObject("BabblerApp", Water97);

InputParameters
Water97::validParams()
{
  InputParameters params = Material::validParams();
  
  params.addRequiredCoupledVar("T", "The temperature at qp");
  params.addRequiredCoupledVar("p", "The pressure at qp");
  params.addRequiredCoupledVar("v", "The velocity at qp");
  
  params.addParam<Real>("De", 0.02, "The water dia");
  
  
  params.addRequiredParam<UserObjectName>("fp", "The name of the user object for fluid properties");
  
  return params;
}

Water97::Water97(const InputParameters & parameters)
  : Material(parameters),
    _T(coupledValue("T")),
    _p(coupledValue("p")),
    _v(coupledValue("v")),
    
    _De(getParam<Real>("De")),
    
    _rho(declareProperty<Real>("rho")),
    _f(declareProperty<Real>("f")),
    _Cp(declareProperty<Real>("Cp")),
    _k(declareProperty<Real>("k")),
    _beta(declareProperty<Real>("beta")),
    _drho_dT(declareProperty<Real>("drho_dT")),
    _drho_dp(declareProperty<Real>("drho_dp")),
    
    _fluid(getUserObject<Water97FluidProperties>("fp"))
    
{
}

void
Water97::computeQpProperties()
{
  Real rho, drho_dT, drho_dp;
  _fluid.rho_from_p_T(_p[_qp], _T[_qp], rho, drho_dp, drho_dT);
  _rho[_qp] = rho;
  _drho_dT[_qp] = drho_dT;
  _drho_dp[_qp] = drho_dp;

  _Cp[_qp] = _fluid.cp_from_p_T(_p[_qp], _T[_qp]);
  _k[_qp] = _fluid.k_from_p_T(_p[_qp], _T[_qp]);
  _beta[_qp] = _fluid.beta_from_p_T(_p[_qp], _T[_qp]);
    
  Real _mu = _fluid.mu_from_p_T(_p[_qp], _T[_qp]);
  Real _Re = _rho[_qp] * _v[_qp] * _De / _mu;
  _f[_qp] = std::max(64.0/_Re, 0.204 * std::pow(_Re, -0.2));

}
