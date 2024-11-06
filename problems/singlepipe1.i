[Mesh]
  type = GeneratedMesh
  dim = 2 # Dimension of the mesh
  nx = 100 # Number of elements in the x direction
  ny = 10 # Number of elements in the y direction
  xmax = 1 # Length of test chamber
  ymax = 0.04 # Test chamber radius
[]

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
  coord_type = RZ # Axisymmetric RZ
  rz_coord_axis = X # Which axis the symmetry is around
[]

[Variables]
  [pressure]
    # Adds a Linear Lagrange variable by default
  []
  
  [ux]
    # Add x-derection velocity
  []
[]

[Kernels]
  [i]
    type = Convection
    variable = ux
    i = '1.0 0.0 0.0'
  []

  [ii]
    type = Convection
    variable = p
    i = '1.0 0.0 0.0'
  []
  
  [diff]
    type = Mudiff
    variable = ux
    # mu default
  []
  
  
    [jpnabla]
    type = Convection
    variable = pressure
    iaxis = '0.0 -1.0 0.0'
  []
  
  [uydiff]
    type = Mudiff
    variable = uy
    
  []
  
  [kpnabla]
    type = Convection
    variable = pressure
    iaxis = '0.0 0.0 -1.0'
  []
  
  [uzdiff]
    type = Mudiff
    variable = uz
    
  []
  
  
  
[]


[BCs]
  [inlet]
    type = ADDirichletBC # Simple u=value BC
    variable = ux # Variable to be set
    boundary = left # Name of a sideset in the mesh
    value = 1 # (m/s) 
  []
  
  [outlet]
    type = ADDirichletBC
    variable = pressure
    boundary = right
    value = 15.5 # (MPa) Gives the correct pressure drop from Figure 2 for 1mm spheres
  []
  
   [inlet_ux]
    type = ADDirichletBC
    variable = ux
    boundary = left
    value = 2
  []
  
  [inlet_uy]
    type = ADDirichletBC
    variable = uy
    boundary = left
    value = 0
  []
  [inlet_uz]
    type = ADDirichletBC
    variable = uz
    boundary = left
    value = 0
  []
  
  
  [top_ux]
    type = ADDirichletBC
    variable = ux
    boundary = top
    value = 0
  []
  
  [top_uy]
    type = ADDirichletBC
    variable = uy
    boundary = top
    value = 0
  []
  [top_uz]
    type = ADDirichletBC
    variable = uz
    boundary = top
    value = 0
  []
  
  
  [bottom_ux]
    type = ADDirichletBC
    variable = ux
    boundary = bottom
    value = 0
  []
  
  [bottom_uy]
    type = ADDirichletBC
    variable = uy
    boundary = bottom
    value = 0
  []
  [bottom_uz]
    type = ADDirichletBC
    variable = uz
    boundary = bottom
    value = 0
  []
[]

[Executioner]
  type = Steady # Steady state problem
  solve_type = NEWTON # Perform a Newton solve

  # Set PETSc parameters to optimize solver efficiency
  petsc_options_iname = '-pc_type -pc_hypre_type' # PETSc option pairs with values below
  petsc_options_value = ' hypre    boomeramg'
[]

[Outputs]
  exodus = true # Output Exodus format
[]



[Executioner]
  type = Steady
  solve_type = 'PJFNK'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
