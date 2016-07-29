#! /bin/bash
if [ $# -ne 4 ]; then
  echo "Usage: ./compile.sh domino_program atom_template pipeline_depth pipeline_width";
  exit;
fi;

domino_program=$1
atom_template=$2
pipeline_depth=$3
pipeline_width=$4

~/domino/pytoc.py $domino_program > /tmp/file.c
domino /tmp/file.c $atom_template $pipeline_depth $pipeline_width 2> /tmp/error.log > /tmp/out.log

if grep --quiet "exceeds allowed pipeline" /tmp/error.log; then
  echo "Failed to find mapping: pipeline is too small"
  grep "exceeds allowed pipeline" /tmp/error.log;
elif grep --quiet "Sketch Not Resolved" /tmp/error.log; then
  echo "Failed to find mapping: atom isn't expressive enough"
#  grep "Sketch failed " /tmp/error.log;
  exit;
else
  echo "Found a mapping"
  grep "stages" /tmp/out.log
  grep "atoms/stage" /tmp/out.log
  gvpr -f secondgraph.gv /tmp/error.log | neato -n -T png > /tmp/pipeline.png
  open /tmp/pipeline.png
fi
