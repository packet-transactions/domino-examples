#! /bin/bash
if [ $# -ne 5 ]; then
  echo "Usage: ./compile.sh domino_program atom_template pipeline_depth pipeline_width run_preproc";
  exit;
fi;

domino_program=$1
atom_template=$2
pipeline_depth=$3
pipeline_width=$4
run_preproc=$5

domino $domino_program $atom_template $pipeline_depth $pipeline_width $run_preproc 2> /tmp/error.log > /tmp/out.log

if grep --quiet "exceeds allowed pipeline" /tmp/error.log; then
  echo "Failed to find mapping: pipeline is too small"
  grep "exceeds allowed pipeline" /tmp/error.log;
elif grep --quiet "Sketch Not Resolved" /tmp/error.log; then
  echo "Failed to find mapping: atom isn't expressive enough"
  exit;
elif grep --quiet "Sketch failed" /tmp/out.log; then
  echo "Failed to find mapping: other reasons"
  exit;
else
  echo "Found a mapping"
  grep "stages" /tmp/out.log
  grep "atoms/stage" /tmp/out.log
  gvpr -f secondgraph.gv /tmp/error.log | neato -n -T png > /tmp/pipeline.png
  echo "Pipeline diagram at /tmp/pipeline.png"
fi
