#!/bin/bash

case $OS in
  linux)
  {
    sudo sudo apt-get update
    sudo apt-get install -y libgl1-mesa-dev
  } ;;
  macOS)
  {
    PATH="$HOME/Qt/5.15:$PATH"
  } ;;
esac