project('particles', 'c',
  version : '1.0.0',
  default_options : [
    'warning_level=2',
    'c_std=c99'
  ]
)

raylib_dep = dependency('raylib', required : true)
cc = meson.get_compiler('c')
math_dep = cc.find_library('m', required: false)

common_deps = [raylib_dep, math_dep]

main_src = 'src/main.c'

# Define all your simulation modules
simulations = {
  'particles': 'src/particles.c',
  # 'boids': 'src/boids.c',
  'gravity': 'src/gravity.c',
  # Add more as you create them
}

# Build an executable for each simulation
foreach name, impl : simulations
  executable(name,
    sources : [main_src, impl],
    dependencies : common_deps,
    install : true
  )
endforeach
