[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 3
  nx = 1
[]

[Variables]
  [p]
    initial_condition = 15.5e6
  []
  
  [v]
    initial_condition = 4.43
  []
  
  [T]
    initial_condition = 553
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
    De = 0.00465
    v = v
    
  []
  
  [energy]
    type = Energy
    variable = T
    q = 2.085e8
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
    value = 4.43 # m/s
  []
  
  [inlet_T]
    type = ADDirichletBC
    variable = T
    boundary = 'left'
    value =553 # K
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
    De = 0.00465
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
  
  [outlet_p]
    type = SideAverageValue
    boundary = 'right'
    variable = p
  []
  
  [delta_p]
    type = ParsedPostprocessor
    pp_names = 'inlet_p outlet_p'
    expression = 'inlet_p - outlet_p'
  []
[]   

[Executioner]
  type = Transient
  dt = 0.01
  num_steps = 480
  solve_type = JFNK

  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = ' hypre    boomeramg'
[]

[Outputs]
  exodus = true
  csv = true
[]
