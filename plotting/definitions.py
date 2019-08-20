stat_names = {
    'curvature': 'Maximum Curvature',
    'max_clearing_distance': 'Maximum Clearing Distance',
    'mean_clearing_distance': 'Mean Clearing Distance',
    'median_clearing_distance': 'Median Clearing Distance',
    'min_clearing_distance': 'Minimum Clearing Distance',
    'path_length': 'Path Length',
    'smoothness': 'Smoothness',
    'planning_time': 'Computation Time',
    'cost': 'Path Length',
    'cusps': 'Cusps',
    'aggregate': 'Aggregate',
    'exact_solutions': 'Exact Solutions'
}

metric_properties = {
    'path_found': {
        'sum': True
    },
    'planning_time': {
        'show_std': True,
        'highlight_optimum': True
    },
    'path_length': {
        'show_std': True
    },
    'curvature': {
        'show_std': True,
        'minimize': True
    },
    'cusps': {
        'minimize': True,
        'sum': True
    }
}

steer_function_names = {
    'reeds_shepp': 'Reeds-Shepp',
    'dubins': 'Dubins',
    'posq': 'POSQ',
    'clothoid': 'G1 Clothoid',
    'linear': 'Linear',
    'cc_dubins': 'CC Dubins',
    'hc_reeds_shepp': 'HC Reeds-Shepp',
    'cc_reeds_shepp': 'CC Reeds-Shepp'
}

steer_functions = [
    'reeds_shepp',
    'dubins',
    'posq',
    'clothoid',
    'linear',
    'cc_dubins',
    'hc_reeds_shepp',
    'cc_reeds_shepp'
]

smoother_names = {
    'grips': 'GRIPS',
    'ompl_bspline': 'B-Spline',
    'ompl_shortcut': 'Shortcut',
    'ompl_simplify_max': 'SimplifyMax'
}

smoothers = list(smoother_names.values())

sampling_planners = ['rrt', 'est', 'sbl', 'prm', 'theta_star', 'sst', 'fmt', 'kpiece', 'pdst', 'stride']
anytime_planners = ['rrt_star', 'rrt_sharp', 'informed_rrt_star', 'sorrt_star', 'prm_star', 'bfmt', 'cforest',
                    'bit_star', 'spars', 'spars2']
sbpl_planners = ['sbpl_adstar', 'sbpl_anastar', 'sbpl_arastar', 'sbpl_lazy_ara', 'sbpl_mha']
all_planners = sampling_planners + anytime_planners + sbpl_planners
