--disable firewall
 关闭防火墙
sudo ufw disable
sudo ufw status

关闭 selinux

--turn off swap
sudo swapoff -a

--- add user to su
1,su root
2,vi /etc/sudoers
3, add user as root format
4 run usermod -aG sudo username


---change host name
sudo nano /etc/hostname
sudo nano /etc/hostname
sudo nano /etc/hosts
sudo reboot


sudo apt  install curl
sudo apt install docker.io


sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys <PUBKEY>
where <PUBKEY> is your missing public key for repository, e.g. 8BAF9A6F.

Then update

sudo apt-get update
ALTERNATE METHOD:

sudo gpg --keyserver pgpkeys.mit.edu --recv-key  <PUBKEY>
sudo gpg -a --export <PUBKEY> | sudo apt-key add -
sudo apt-get update

------reset software repo
software-properties-gtk


"cniVersion": "0.3.1",


 uname -m
 check ubuntu server type



 vim /run/flannel/subnet.env

FLANNEL_NETWORK=10.240.0.0/16 --- your address
FLANNEL_SUBNET=10.240.0.1/24
FLANNEL_MTU=1450
FLANNEL_IPMASQ=true