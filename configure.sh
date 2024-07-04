if [ ! -d "./lib/mlx" ]; then
	if [ ! -f "./mlx/libmlx.a" ]; then
		echo "Compiling MiniLibx..."
		cd ./lib/mlx && make &> /dev/null
	else
			cd ./lib;
			echo "Downloading MiniLibX For Linux..."

		if [[ "$1" == "Linux" ]]; then
			curl https://cdn.intra.42.fr/document/document/18343/minilibx-linux.tgz -o libx.tgz &> /dev/null
			tar xvzf libx.tgz &> /dev/null
			rm -rf limbx.tgz
			mv minilib_linux mlx &> /dev/null
		else
			curl https://cdn.intra.42.fr/document/document/18344/minilibx_opengl.tgz -o libx.tgz &> /dev/null
		fi
			echo "Compiling MiniLibx For Linux..."
			cd linuxmlx && make &> /dev/null
		else
			cd ./lib
			echo "Downloading Dependencies..."
			echo "Extracting Downloaded Files..."
			tar xvzf libx.tgz &> /dev/null
			rm -rf libx.tgz
			mv minilibx_opengl_20191021 macmlx &> /dev/null
		fi
	fi
fi
else
	if [ ! -d "./lib/macmlx" ]; then
fi
