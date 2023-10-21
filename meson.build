#project('parallel_search_min_max', 'c', default_options: ['b_sanitize' = 'address'])

project('parallel_search_min_max', 'c')
#executable('parallel_search_min_max', 'parallel_search_min_max.c', dependencies: dependency('lua'))
add_project_arguments('-std=c2x', language: 'c')
add_project_arguments('-ggdb3', language: 'c')
#add_project_arguments('-fsanitize=address', language: 'c')
executable('parallel_search_min_max', 'parallel_search_min_max.c')
