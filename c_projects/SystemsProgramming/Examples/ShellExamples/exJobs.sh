#!/bin/bash
Directory="~/Desktop"
NewDir="~/Desktop/Test"
if [ -d "$Directory" ]; then
  # Control will enter here if $DIRECTORY exists.
  cd "$Directory"
  ls
fi
if [ ! -d "$NewDir" ]; then
  # Control will enter here if $DIRECTORY doesn't exist.
  mkdir "$NewDir" -p
fi