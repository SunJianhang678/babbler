[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 50
[]

[Variables]
  [p] 
  []
  
  [v]
    initial_condition = 2
  []
  
  [T]
    initial_condition = 300
  []
[]

[AuxVariables]  
  [f]
  []
  
  [rho]
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
    f = f
    v = v
    De = 0.02
    rho = rho
  []
  
  [energy]
    type = Energy
    variable = T
    q = 1.04e8
    v = v
    rho = rho
  []
[]

[AuxKernels]
  [computef]
    type = Computef
    variable = f
    v = v
    De = 0.02
  []
  
  [false_rho]
    type = Frho
    variable = rho
    T = T
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
    value = 0  # Pa
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
  
  [outlet_rho]
    type = SideAverageValue
    boundary = 'right'
    variable = rho
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
