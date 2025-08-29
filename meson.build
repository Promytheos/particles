project('particles', 'c',
  version : '1.0.0',
  default_options : [
    'warning_level=2',
    'c_std=c99'
  ]
)

# Find raylib dependency
raylib_dep = dependency('raylib', required : true)
cc = meson.get_compiler('c')
math_dep = cc.find_library('m', required: false)
# Source files
main_src = 'src/main.c'
# common_src = files(
#   'src/common.c'
# )
# game_sources = files(
#   'src/games/pong.c',
#   'src/games/tictactoe.c'
# )

# All source files
# all_sources = [main_src, common_src, game_sources]

# Main executable
executable('particles',
  sources : main_src,
  dependencies : [raylib_dep, math_dep],
  install : true
)
