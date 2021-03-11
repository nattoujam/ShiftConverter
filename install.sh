#!/bin/sh

if [ $# != 1 ]
then
  echo "$ ./install.sh [install dir]"
  return 1
fi

echo "install at $1"
dir=$(cd $1 && pwd)/ShiftConverter
shell=${dir}/run.sh
service=${dir}/shiftConverter.service

mkdir $dir

echo "gcc -o ${dir}/shitConverter shiftConverter.c"
gcc -o ${dir}/shiftConverter shiftConverter.c

echo "#!/bin/sh" > $shell
echo "exec ${dir}/shiftConverter < /dev/input/event3" >> $shell
chmod 700 $shell
echo "create execute file: $shell"

echo "create service file: $service"
if [ ! -d ~/.config/systemd/user/ ]
then
  mkdir -p ~/.config/systemd/user/
fi
echo "[Unit]" > $service
echo "Description=Shift Converter" >> $service
echo "[Service]" >> $service
echo "Type=simple">>$service
echo "ExecStart=${shell}">> $service
echo "Restart=always">> $service
echo "[Install]">> $service
echo "WantedBy=default.target">> $service
mv $service ~/.config/systemd/user/
