echo "--- started executing... ---"
cd bin
echo "java palette.Main $1 < ../img/baboon-deb.pgm > ../img/baboon-fin.pgm"
java palette.Main $1 < ../img/baboon-deb.pgm > ../img/baboon-fin.pgm
echo "java palette.Main $1 < ../img/cameraman-deb.pgm > ../img/cameraman-fin.pgm"
java palette.Main $1 < ../img/cameraman-deb.pgm > ../img/cameraman-fin.pgm
echo "java palette.Main $1 < ../img/lamp-deb.pgm > ../img/lamp-fin.pgm"
java palette.Main $1 < ../img/lamp-deb.pgm > ../img/lamp-fin.pgm
echo "java palette.Main $1 < ../img/palettes-deb.pgm > ../img/palettes-fin.pgm"
java palette.Main $1 < ../img/palettes-deb.pgm > ../img/palettes-fin.pgm
echo "java palette.Main $1 < ../img/storm-deb.pgm > ../img/storm-fin.pgm"
java palette.Main $1 < ../img/storm-deb.pgm > ../img/storm-fin.pgm
echo "--- finished executing (exiting)... ---"
