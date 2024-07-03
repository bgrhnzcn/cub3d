os_data=$(uname)
if [ $os_data == "Linux" ]; then
	if [ -d "./lib/linuxmlx" ]; then
		echo true
		exit 0
	fi
else
	if [ -d "./lib/macmlx" ]; then
		echo true
		exit 0
	fi
fi
echo false
