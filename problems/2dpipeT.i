[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 3
  nx = 20
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
[]

[Kernels]
  [continu]
    type = Mass
    variable = v
  []
  
  [momentum]
    type = Momentum
    variable = p
    f = f
    v = v
    De = 0.02
  []
  
  [energy]
    type = Energy
    variable = T
    q = 1.04e8
    v = v
  []
[]

[AuxKernels]
  [computef]
    type = Computef
    variable = f
    v = v
    De = 0.02
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
