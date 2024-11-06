[Mesh]
  type = GeneratedMesh
  dim = 2 # Dimension of the mesh
  nx = 500 # Number of elements in the x direction
  ny = 20 # Number of elements in the y direction
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

[]

[Kernels]

  [ipnabla]
    type = Convection
    variable = pressure
    iaxis = '-1.0 0.0 0.0'
  []
  

[]


[BCs]
  
  [inlet_p]
    type = ADDirichletBC
    variable = pressure
    boundary = left
    value = 4000 # (Pa) Gives the correct pressure drop from Figure 2 for 1mm spheres
  []
  
  [outlet_p]
    type = ADDirichletBC
    variable = pressure
    boundary = right
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
  exodus = true
[]
