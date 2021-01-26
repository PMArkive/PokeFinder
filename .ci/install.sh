#!/bin/bash

case $OS in
  linux)
  {
    sudo sudo apt-get update
    sudo apt-get install -y libgl1-mesa-dev
  } ;;
  macOS)
  {
    echo 'export PATH="/$HOME/Qt/5.15/clang_64/bin:$PATH"' >> /Users/appveyor/.bash_profile
  } ;;
esac