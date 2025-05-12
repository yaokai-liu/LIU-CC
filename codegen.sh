#!/usr/bin/env bash

if [ -d "json/parse" ]; then
  echo ''
else
  mkdir -p json/parse
fi
if [ -d "json/preprocess" ]; then
  echo ''
else
  mkdir -p json/preprocess
fi


python liu-cc/generate.py json
if [ -d "grammar/generated/parse" ]; then
  echo ''
else
  mkdir -p grammar/generated/parse
fi
if [ -d "grammar/generated/preprocess" ]; then
  echo ''
else
  mkdir -p grammar/generated/preprocess
fi
python xnf-json2C/codegen.py json template grammar/generated
