mv -f $1 img.png
python preprocess.py > img.txt
sed -i 's/\s+/\n/g' img.txt
sed -i 's/\[//g' img.txt
sed -i 's/\]//g' img.txt
