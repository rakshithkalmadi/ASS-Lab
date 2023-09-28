#!/bin/bash

# Get the current directory
current_dir=$(pwd)

# Get the user's permissions for all files in the current directory
permissions=$(ls -la | awk '{print $1}')


# Loop through all files in the current directory
for file in $current_dir/*; do

  # Check if the user has read, write and execute permissions for the file
  if [ "${permissions}" == "-rwxrwxr-x" ]; then
    echo $file
  fi

done

