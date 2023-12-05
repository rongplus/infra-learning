  -  machines
192.168.56.111  k8s-master1
192.168.56.114  k8s-master2
192.168.56.112  k8s-node1
192.168.56.113  k8s-node2
192.168.56.117  k8s-node3
192.168.56.115  k8s-lb1
192.168.56.116  k8s-lb2
 
 
 - 1 user as root
 1,su root
2,vi /etc/sudoers
3, add user as root format
4 run usermod -aG sudo username

 - 2 update apt list
 sudo apt update list

  - 3 install ssh server
  sudo apt install openssh-server

 - 4 hosts and machine name
sudo nano /etc/hostname
sudo nano /etc/hosts
sudo reboot

 - 5 follow steps in 
https://www.knowledgehut.com/blog/devops/install-kubernetes-on-ubuntu#what-is%C2%A0kubeadm?

Step 1: Installing Docker   (master and node)
$ sudo apt-get install docker.io 
$ docker --version 
$ sudo usermod -aG docker $USER 
$ sudo systemctl start docker 
$ sudo systemctl enable docker 


Step 2: Installing Kubernetes  (master and node)
$ curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add 
$ sudo apt install curl 
$ sudo apt-add-repository "deb http://apt.kubernetes.io/ kubernetes-xenial main" 
$ sudo apt-get install kubeadm kubelet kubectl 
$ sudo apt-mark hold kubeadm kubelet kubectl
$ kubeadm version 


Step 3: Running and Deploying Kubernetes
 - 1. Disable swap memory:
 $ sudo swapoff -a 
 - 2. Initialize Kubernetes on Master Node:
  $ sudo kubeadm init –pod-network-cidr=192.168.43.211/24  
  - q. You can find pod network CIDR in /etc/kubernetes/manifests/kube-controller-manager.yaml
  sudo grep cidr /etc/kubernetes/manifests/kube-* 

 - 3. You need to run the following as a daily user to start using your cluster:
 $ mkdir  -p $HOME/ .kube 
$ sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config 
 $sudo chown $(id -u):$(id -g) $HOME/.kube/config 

4. Deploy Pod Network to Cluster:
$ sudo kubectl apply -f  https://raw.githubusercontent.com/coreos/  flannel/master/Documentation/kube-flannel.yml 

$ kubectl get pods --all-namespaces

5. Add the slave node to form a cluster: (copy from step 4)
$ sudo kubeadm join 192.168.100.6:6443 --token        06tl4c.oqn35jzecidg0r0m --discovery-token-ca-cert-hash                            sha256:c40f5fa0aba6ba311efcdb0e8cb637ae0eb8ce27b7a03d47be6d966142f2204c 


6 Uninstalling Kubernetes
1. Clear Pods

Using this command, you can delete all the nodes: 

$ kubectl delete node --all 

2. Remove  kubeadm completely 

$ sudo apt-get purge kubeadm kubectl kubelet kubernetes-cni kube* 
$ sudo apt-get autoremove 



------------notes----------------
 - 1 Fix the Error – The connection to the server localhost:8080 was refused
sudo cp /etc/kubernetes/admin.conf $HOME/
sudo chown $(id -u):$(id -g) $HOME/admin.conf
export KUBECONFIG=$HOME/admin.conf


 - 2 error execution phase preflight: couldn't validate the identity of the API Server: could not find a JWS signature in the cluster-info ConfigMap for token ID "ysrv0l"
To see the stack trace of this error execute with --v=5 or higher

如上，主要看报错信息的最后一行，原因是原来的token过期了
可以通过以下命令验证，没有任何输出
$ kubeadm token list
# 此处没有任何输出, 表明没有存活的token
解决办法，生成个新的token

# 在 master 节点执行
kubeadm token create --print-join-command --ttl=0
其中 --ttl=0 表示生成的 token 永不失效. 如果不带 --ttl 参数, 默认有效时间为24小时