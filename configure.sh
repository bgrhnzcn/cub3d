if [[ "$1" == "Linux" ]]; then
	if [ ! -d "./lib/linuxmlx" ]; then
		cd ./lib;
		echo "Downloading MiniLibX For Linux..."
		curl https://cdn.intra.42.fr/document/document/18343/minilibx-linux.tgz -o libx.tgz &> /dev/null
		echo "\033[4A\033[53DBuilding CUB3D[##############----------------------]\033[3B"
		tar xvzf libx.tgz &> /dev/null
		rm -rf limbx.tgz
		mv minilib_linux linuxmlx &> /dev/null
		echo "Compiling MiniLibx For Linux..."
		cd linuxmlx && make &> /dev/null
		echo "\033[5A\033[53DBuilding CUB3D[############################--------]\033[4B"
	elif [ ! -f "./linuxmlx/libmlx.a" ]; then
		echo "Compiling MiniLibx For Linux...\c"
		cd ./lib/linuxmlx && make &> /dev/null
		echo "\033[4A\033[53DBuilding CUB3D[############################--------]\033[3B"
	fi
else
	if [ ! -d "./lib/macmlx" ]; then
		cd ./lib
		echo "Downloading Dependencies..."
		curl https://cdn.intra.42.fr/document/document/18344/minilibx_opengl.tgz -o libx.tgz &> /dev/null
		echo "\033[4A\033[53DBuilding CUB3D[##############----------------------]\033[3B"
		echo "Extracting Downloaded Files..."
		tar xvzf libx.tgz &> /dev/null
		rm -rf libx.tgz
		mv minilibx_opengl_20191021 macmlx &> /dev/null
		echo "\033[5A\033[53DBuilding CUB3D[################--------------------]\033[4B"
		echo "Compiling MiniLibx For MacOS..."
		cd macmlx && make &> /dev/null
		echo "\033[6A\033[53DBuilding CUB3D[############################--------]\033[5B"
	elif [ ! -f "./lib/macmlx/libmlx.a" ]; then
		echo "Compiling MiniLibx For MacOS..."
		cd ./lib/macmlx && make &> /dev/null
		echo "\033[4A\033[53DBuilding CUB3D[####################################]\033[3B"
	fi
fi
