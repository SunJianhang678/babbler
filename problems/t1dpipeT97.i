[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 1
[]

[Variables]
  [p]
    initial_condition = 15.5e6
  []
  
  [v]
    initial_condition = 1
  []
  
  [T]
    initial_condition = 533
  []
[]

[AuxVariables]
  [rho]
    family = MONOMIAL
  []

  [drho_dT]
    family = MONOMIAL
  []
[]

[Kernels]
  [continu]
    type = Mass
    variable = v
    T = T
    p = p
  []
  
  [momentum]
    type = Momentum
    variable = p    
    De = 0.025
    v = v
  []
  
  [energy]
    type = Energy
    variable = T
    q = 2.037e8
    v = v
    p = p
  []

  [energyt]
    type = Energyt
    variable = T
  []
[]

[AuxKernels]
  [rho97]
    type = MaterialRealAux
    variable = rho
    property = rho
  []

  [T97]
    type = MaterialRealAux
    variable = drho_dT
    property = drho_dT
  []
[]


[BCs]
  [inlet_v]
    type = ADDirichletBC
    variable = v
    boundary = 'left'
    value = 1 # m/s
  []
  
  [inlet_T]
    type = ADDirichletBC
    variable = T
    boundary = 'left'
    value =533 # K
  []
  
  [outlet_p]
    type = ADDirichletBC
    variable = p
    boundary = 'right'
    value = 15.5e6  # Pa
  []
[]


[FluidProperties]
  [water]
    type = Water97FluidProperties
  []
[]


[Materials]
  [1dpipe]
    type = Water97
    p = p
    T = T
    v = v
    De = 0.025
    fp = water
  []
[]


[Postprocessors]
  [inlet_p]
    type = SideAverageValue
    boundary = 'left'
    variable = p
  []
  
  [outlet_v]
    type = SideAverageValue
    boundary = 'right'
    variable = v
  []
  
  [outlet_T]
    type = SideAverageValue
    boundary = 'right'
    variable = T
  []

  [outlet_drho_dT]
    type = SideAverageValue
    boundary = 'right'
    variable = drho_dT
  []
  
  [inlet_drho_dT]
    type = SideAverageValue
    boundary = 'left'
    variable = drho_dT

  []

  [outlet_rho]
    type = SideAverageValue
    variable = rho
    boundary = 'right'
    
  []
[]   

[Executioner]
  type = Transient
  dt = 1
  num_steps = 1
  solve_type = JFNK

  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = ' hypre    boomeramg'
[]

[Outputs]
  exodus = true
  csv = true
[]
