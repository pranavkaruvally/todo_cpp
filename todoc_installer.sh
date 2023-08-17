#!/bin/bash

echo ""
echo "Todoc Installer"
echo ""

make # Compiles the c++ program

PROGRAM_PATH="${HOME}/.todoc"
mkdir -p ${PROGRAM_PATH}
cp ./todoc ${PROGRAM_PATH}/
touch ${PROGRAM_PATH}/tasks.txt

echo "export TODOC_ROOT=${PROGRAM_PATH}" >> ${HOME}/.bashrc
echo "export PATH=${PROGRAM_PATH}:$PATH" >> ${HOME}/.bashrc

echo ""
echo "Installation complete."
echo "Type in the command"
echo "source ~/.bashrc"
echo "or open a new terminal for changes to take place"
echo ""

exit 0