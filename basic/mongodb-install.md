https://www.fosstechnix.com/how-to-install-mongodb-on-ubuntu-22-04-lts/

How to Install MongoDB on Ubuntu 22.04 LTS
by Shweta Mamidwar

Home » How to Install MongoDB on Ubuntu 22.04 LTS

In this article we are going to learn Import the MongoDB public key on Ubuntu 22.04 LTS, Configure MongoDB Repo on Ubuntu 22.04 LTS, How to Install MongoDB on Ubuntu 22.04 LTS, Login MongoDB 6.0 Database on Ubuntu 22.04 LTS,Enable MongoDB authentication.

Table of Contents
Prerequisite:

    Ubuntu Server with 22.04 LTS
    Good Internet Connection

Step #1:Perform System Update

Before we can proceed with our installation, let’s update system and install the required packages:

sudo apt update

sudo apt install wget curl gnupg2 software-properties-common apt-transport-https ca-certificates lsb-release

Step #2:Import the MongoDB public key on Ubuntu 22.04 LTS

Run the following command to import the MongoDB public GPG Key:

curl -fsSL https://www.mongodb.org/static/pgp/server-6.0.asc|sudo gpg --dearmor -o /etc/apt/trusted.gpg.d/mongodb-6.gpg

Step #3:Configure MongoDB Repo on Ubuntu 22.04 LTS

Using the following commands, add the repository to your system right away:

echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu $(lsb_release -cs)/mongodb-org/6.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-6.0.list

Step #4:Install MongoDB on Ubuntu 22.04 LTS

Use the following command to install MongoDB 6.0 on Ubuntu on 22.04 LTS.

sudo apt update

sudo apt install mongodb-org

After successful installation, start and enable MongoDB:

sudo systemctl enable --now mongod

Check MongoDB Status:

sudo systemctl status mongod

Check MongoDB installed version:

mongod --version

Step #5:Allow Remote Access in MongoDB

Open MongoDB configuration file /etc/mongod.conf and change bindIp by adding required

sudo nano /etc/mongod.conf

# network interfaces
net:
  port: 27017
  bindIp: 127.0.0.1  # Enter 0.0.0.0,:: to bind to all IPv4 and IPv6 addresses or, alternatively, use the net.bindIpAll setting.
To bind to all IPv4 and IPv6 address you’ll set:
 bindIp: 0.0.0.0

Save the file after making the required changes, then restart the service:

sudo systemctl restart mongod

sudo systemctl stop mongod

sudo systemctl daemon-reload

sudo systemctl start mongod

Step #6:Login MongoDB 6.0 Database on Ubuntu 22.04 LTS

You can use the following command to reach the MongoDB shell:

mongosh

Inside the mongo shell type this command to switch to the admin database: 

 > use admin

Now let’s create the administrator username and set a password for the username:

> db.createUser({user:"devopshint", pwd:"devopshint", roles:[{role:"root", db:"admin"}]})

Type this command in the shell to exit the shell:

>exit

Step #7:Enable MongoDB authentication

Open /lib/systemd/system/mongod.service with nano:

sudo nano /lib/systemd/system/mongod.service

Add this line into this file

ExecStart=/usr/bin/mongod --quiet --auth --config /etc/mongod.conf

Now connect to the MongoDB shell using this command:

mongosh -u demo -p --authenticationDatabase admin

> db.runCommand({connectionStatus : 1})

we have covered How to Install MongoDB on Ubuntu 22.04 LTS.

Conclusion:

In this article we have covered Import the MongoDB public key on Ubuntu 22.04 LTS, Configure MongoDB Repo on Ubuntu 22.04 LTS, How to Install MongoDB on Ubuntu 22.04 LTS, Login MongoDB 6.0 Database on Ubuntu 22.04 LTS,Enable MongoDB authentication.

Related Articles: