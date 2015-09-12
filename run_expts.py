#! /usr/bin/python

# Imports
import sys
import subprocess
import os

# Program wrapper
# Takes a command line of program arguements,
# executes it, and prints something out whether it succeeds or fails
def program_wrapper(program, environment, t_stdout = subprocess.PIPE, t_stderr = subprocess.PIPE):
  sp = subprocess.Popen(program, stdout = t_stdout, stderr = t_stderr, env = env_vars)
  out, err = sp.communicate()
  if (sp.returncode != 0):
    print " ".join(program), " failed with stdout:"
    print out
    print "stderr:"
    print err
    sys.exit(sp.returncode)
  else :
    print " ".join(program), " completed execution"
    return (out, err)

# Command line arguments
domino_file_list   = sys.argv[1]
atom_template_list = sys.argv[2]

# result matrix:
result_matrix = dict()
for domino_file in open(domino_file_list, "r").read().splitlines():
  result_matrix[domino_file] = dict()
  for atom_template in open(atom_template_list, "r").read().splitlines():
    result_matrix[domino_file][atom_template] = []

# fill in result matrix
for domino_file in open(domino_file_list, "r").read().splitlines():
  for atom_template in open(atom_template_list, "r").read().splitlines():
    env_vars = os.environ.copy()
    env_vars["ATOM_TEMPLATE"] = atom_template
    out,err = program_wrapper(program = ["domino", domino_file, "int_type_checker,desugar_comp_asgn,if_converter,algebra_simplify,array_validator,stateful_flanks,ssa,expr_propagater,expr_flattener,partitioning,sketch_backend"], environment = env_vars)
    for line in err.splitlines():
      if "with random seed" in line:
        if "succeeded" in line:
          result_matrix[domino_file][atom_template] += [1]
        if "failed" in line:
          result_matrix[domino_file][atom_template] += [0]

# first print out atom templates
print " "*15,
for atom_template in open(atom_template_list, "r").read().splitlines():
  print "%15s"%atom_template,
print

# Print out result matrix 
for domino_file in result_matrix:
  print "%15s"%domino_file,
  for atom_template in open(atom_template_list, "r").read().splitlines():
    print "%15s"%result_matrix[domino_file][atom_template],
  print
