--disable firewall
sudo ufw disable
sudo ufw status

--turn off swap
sudo swapoff -a

--- add user to su
1,su root
2,vi /etc/sudoers
3, add user as root format
4 run usermod -aG sudo username


---change host name
sudo nano /etc/hostname



sudo apt  install curl
sudo apt install docker.io