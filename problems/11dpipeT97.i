[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 3
  nx = 1
[]

[Variables]
  [p]
    initial_condition = 101e3
  []
  
  [v]
    initial_condition = 2
  []
  
  [T]
    initial_condition = 300
  []
[]

[AuxVariables]
  [rho]
    family = MONOMIAL
  []
[]

[Kernels]
  [continu]
    type = Mass
    variable = v
    rho = rho
  []
  
  [momentum]
    type = Momentum
    variable = p    
    De = 0.02
    v = v
    
  []
  
  [energy]
    type = Energy
    variable = T
    q = 1.04e8
    v = v
    p = p
  []
[]

[AuxKernels]
  [rho97]
    type = MaterialRealAux
    variable = rho
    property = rho
  []
[]


[BCs]
  [inlet_v]
    type = ADDirichletBC
    variable = v
    boundary = 'left'
    value = 2 # m/s
  []
  
  [inlet_T]
    type = ADDirichletBC
    variable = T
    boundary = 'left'
    value = 300 # K
  []
  
  [outlet_p]
    type = ADDirichletBC
    variable = p
    boundary = 'right'
    value = 101e3  # Pa
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
    De = 0.02
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
  
  
[]   

[Executioner]
  type = Steady
  solve_type = JFNK

  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = ' hypre    boomeramg'
[]

[Outputs]
  exodus = true
  csv = true
[]
