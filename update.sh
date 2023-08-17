echo ""
echo "Updating..."
echo ""

make clean
make

if [ -f ${HOME}/.todoc/todoc ]; then
    echo "Older version found. Removing..."
    rm ${HOME}/.todoc/todoc
fi

echo "Copying new version"
cp ./todoc ${HOME}/.todoc/todoc

echo "Successfully updated"
echo ""