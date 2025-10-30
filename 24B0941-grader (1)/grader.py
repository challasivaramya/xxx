#!/usr/bin/env python3
# coding: utf-8

import sys
# caution: path[0] is reserved for script path (or '' in REPL)


#------------------------------
# Setup for problem
#------------------------------
exam                 = "Lab 10"
problem              = "max-fish"
prob_files           = ['main.cpp', 'max-fish.h']
student_files        = ['max-fish.cpp']
allowed_include      = ['max-fish.h']
disallowed_functions = ['cout','cerr', #'new ',
                        #'alloc(','malloc(', #'append', #'free', #'delete ' #,'['
                       ]

#------------------------------
# test cases
#------------------------------

tests    = [
    'test1',
    'test2',
    'test3',
    'test4',
    # 'test5',
    # 'test6',
    'test7',
    'test8',
    # 'test9',
    # 'test10',
    'test11',
]

grades_file = "grade.csv"

#---------------------------
# Paths
#---------------------------
sys.path.insert( 1,    '../../../../utils' )
students_path        = '../../submissions/'
prob_path            = './harness/'
tests_path           = './tests'
students_path = "./students/"
prob_path = "./harness/"
tests_path = "./tests/"


import autograder
import pandas as pd
import numpy as np
import os
import copy
import matplotlib.pyplot as plt

pd.set_option('display.max_rows', 200)

#---------------------------------
# Allocate auto-grader
#--------------------------------
base_grader = autograder.Autograder(
    exam                 = exam, 
    problem              = problem, 
    prob_path            = prob_path, 
    prob_files           = prob_files, 
    students_path        = students_path, 
    student_files        = student_files, 
    tests_path           = tests_path,
    tests                = tests,
    allowed_include      = allowed_include, 
    disallowed_functions = disallowed_functions,
    timeout              = 1,
)
base_grader.parallel = 1
# base_grader.allowed_recursion = False

if len(sys.argv) < 2 : base_grader.display_usage(sys.argv[0])
if len(sys.argv) == 3: base_grader.set_student( grades_file, sys.argv[2] )

def cmp( expected, output ):
    results = {'':False}
    if output == None or (len(output) < 1): return results
    results = autograder.text_to_map( output )
    if ('Result' in results) and (results['Result'] == expected[0]):
        results[''] = True
    else:
        results[''] = False 
        results['Time'] = None
    rem_keys = [ key for key in results if not key in ['','Time'] ] 
    for key in rem_keys: results.pop(key)
    return results 

base_grader.cmp_function = cmp

# ---------------------
# Actions of auto-grader
# --------------------
act  = sys.argv[1]
#----------------------------------------
# Policy check, compile, run, and results
#----------------------------------------
base_grader.action(act)
#-----------------------------------------------
# Assign grade
#-----------------------------------------------
if act in ['grade','all']:
    full =  base_grader.get_results()
    #----------------------------------
    # Compute total score 
    #----------------------------------
    full['total'] = full[tests].sum( axis = 1 )

    # Extra include -> 0 marks
    n_tests = len(tests)

    full['total'] = np.where(
        (full['total'] >= n_tests) & (full['test11Time'] <= 10000000), 4,
        np.where(
            (full['total'] >= n_tests) &  (full['test11Time'] > 10000000), 3,
            np.where(
                (full['total'] >= n_tests-3) & (full['total'] < n_tests), 2,
                0
            )
        )
    )
    testtime = [f'{test}Time' for test in tests]
    full.to_csv(grades_file, index=False)
    full = full[['Roll No','Compile Success','Policy Error']+tests+testtime+['total']]
    # full = full[full['total'] >= 3]
    # full = full.sort_values(['total','test6Time'],ascending=[False,True])

    base_grader.save_marks(full,'total')

#-----------------------------------------------
# create package before sending emails
#-----------------------------------------------
if act in ['package']:
    base_grader.grading_files = ['./grader.py','../../../../utils/autograder.py']
    base_grader.package_replace_sequence = auto_remove
    base_grader.create_packages()

