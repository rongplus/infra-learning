Save a docker image
 - docker save -o d:/u.zip ubuntu:latest

run a docker image with share folder as a new container
 - docker run -it --name="U1"  -v D:/git/rong.plus/cppblog:/mycpp ubuntu bash
 - docker run -it --name="dev" -v D:/git/rong.plus/cppblog:/mycpp my_dev bash
 - to set mysql
 run a docker image with port mapping
  - docker run -it -p 3306:3306 -p 33060:33060 --name mysqlServer -e MYSQL_ROOT_PASSWORD=Good2017! -d mysql:tag
  - docker run -p 3306:3306 --name=mysql57 -d mysql/mysql-server:5.7
  - docker run -p 3306:3306 -p 33060:33060 --name=mysql57 -d mysql/mysql-server:5.7

docker cp <CONTAINER ID>:/home/docker/data/io_example.txt .

run a docker container
    docker exec -it
     docker exec -it ymwx-mysql bash


sudo apt install default-jre
 update-alternatives --config java

check ip in a container
 -  docker inspect U1
package to ping
 - apt install iputils-ping
make a docker image
 - docker build -t hello-world .
-------docker file-----------------
FROM ubuntu:18.04

# Install dependencies
RUN apt-get update && \
 apt-get -y install apache2

# Install apache and write hello world message
RUN echo 'Hello World!' > /var/www/html/index.html

# install dev
RUN apt-get install -y g++
RUN apt-get install -y git
RUN apt-get install -y cmake
RUN apt-get install -y libgtest-dev
RUN cd /usr/src/googletest && cmake CMakeLists.txt && make 

RUN apt install -y libgoogle-glog-dev
RUN apt-get install -y libgflags-dev
RUN apt-get install -y libboost-all-dev

RUN apt-get install -y software-properties-common
RUN apt-get install -y libghc-double-conversion-dev
RUN apt install -y default-jre
# Configure apache
RUN echo '. /etc/apache2/envvars' > /root/run_apache.sh && \
 echo 'mkdir -p /var/run/apache2' >> /root/run_apache.sh && \
 echo 'mkdir -p /var/lock/apache2' >> /root/run_apache.sh && \ 
 echo '/usr/sbin/apache2 -D FOREGROUND' >> /root/run_apache.sh && \ 
 chmod 755 /root/run_apache.sh

EXPOSE 80

CMD /root/run_apache.sh


--------------------setting--------------------
mysql password Good2017!
