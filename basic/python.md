multiple python in ubtuntu

1. install python 
   sudo apt install python2
   sudo apt install python3
2. Intstall python to system 
 sudo update-alternatives --install /usr/bin/python python /usr/bin/python2 1
 sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 2

3. update-alternatives --list python

4. sudo update-alternatives --config python