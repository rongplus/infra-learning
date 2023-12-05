$ kubectl get nodes
$ kubectl get pods -A


source <(kubectl completion bash)
echo "source <(kubectl completion bash)" >> ~/.bashrc

$ kubectl apply -f flannel.yaml

添加worker节点非常简单，直接在worker节点上运行join即可，注意–token
$ sudo kubeadm join 192.168.56.10:6443 --token 0pdoeh.wrqchegv3xm3k1ow \
  --discovery-token-ca-cert-hash sha256:f4e693bde148f5c0ff03b66fb24c51f948e295775763e8c5c4e60d24ff57fe82



  token 可以通过 kubeadm token list``获取到，比如 ``0pdoeh.wrqchegv3xm3k1ow

$ kubeadm token list
TOKEN                     TTL         EXPIRES                USAGES                   DESCRIPTION                                                EXTRA GROUPS
0pdoeh.wrqchegv3xm3k1ow   23h         2022-07-19T20:13:00Z   authentication,signing   The default bootstr


修改文件 /etc/systemd/system/kubelet.service.d/10-kubeadm.conf ， 在最后一行末尾增加一个新的变量KUBELET_EXTRA_ARGS， 指定node ip是本机的enp0s8的地址，保存退出。

ExecStart=/usr/bin/kubelet $KUBELET_KUBECONFIG_ARGS $KUBELET_CONFIG_ARGS $KUBELET_KUBEADM_ARGS $KUBELET_EXTRA_ARGS --node-ip=192.168.56.10


重启kubelet，就会发现本机master节点的internal IP显示正确了。

vagrant@k8s-master:~$ sudo systemctl daemon-reload
vagrant@k8s-master:~$ sudo systemctl restart kubelet
vagrant@k8s-master:~$ kubectl get node -o wide

得到详细信息
 kubectl get nodes -o wide

创建一个nginx的pod，pod能成功过running
vagrant@k8s-master:~$ kubectl run web --image nginx
pod/web created
vagrant@k8s-master:~$ kubectl get pods
NAME   READY   STATUS    RESTARTS   AGE
web    1/1     Running   0          5s
vagrant@k8s-master:~$

kubectl delete pod web

给nginx pod创建一个service, 通过curl能访问这个service的cluster ip地址。
vagrant@k8s-master:~$ kubectl expose pod web  --port=80 --name=web-service
service/web-service exposed
vagrant@k8s-master:~$ kubectl get service
NAME          TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)   AGE
kubernetes    ClusterIP   10.96.0.1       <none>        443/TCP   3h53m
web-service   ClusterIP   10.98.102.238   <none>        80/TCP    4s
vagrant@k8s-master:~$ curl 10.98.102.238



$ kubectl delete service web-service
$ kubectl delete pod web



$ kubectl apply -f nginx.yml  # Declarative Configuration
$ kubectl run web --image=nginx # Imperative Configuration



一次性运行的Pod，一般为执行某个命令或者脚本，执行结束后pod的生命随之结束

create job
$ kubectl create job my-job --image=busybox -- sh -c "sleep 50"



CronJob
计划任务


Deploy a sample Nginx app and see if you can access it over the nodePort.

kubectl apply -f https://raw.githubusercontent.com/scriptcamp/kubeadm-scripts/main/manifests/sample-app.yaml
You should be able to access Nginx on any of the node’s IPs on port 32000. For example, http://10.0.0.11:32000



进入容器执行命令
kubectl exec client -it -- sh

Fix the Error – The connection to the server localhost:8080 was refused
sudo cp /etc/kubernetes/admin.conf $HOME/
sudo chown $(id -u):$(id -g) $HOME/admin.conf
export KUBECONFIG=$HOME/admin.conf



因此，解决方法如下，将主节点中的【/etc/kubernetes/admin.conf】文件拷贝到工作节点相同目录下：

#复制admin.conf，请在主节点服务器上执行此命令
scp /etc/kubernetes/admin.conf 172.16.2.202:/etc/kubernetes/admin.conf
scp /etc/kubernetes/admin.conf 172.16.2.203:/etc/kubernetes/admin.conf
1
2
3
然后分别在工作节点上配置环境变量：

#设置kubeconfig文件
export KUBECONFIG=/etc/kubernetes/admin.conf
echo "export KUBECONFIG=/etc/kubernetes/admin.conf" >> ~/.bash_profile


kubeadm join添加新节点报错


[root@node03 ~]# kubeadm join 192.168.99.10:6443 --token ysrv0l.1d9f6g1ecgv5yryl \
>         --discovery-token-ca-cert-hash sha256:9f1adb5597a3df3df6afc86c8610792fd2e89840657380ddc56d9f4ba81d4c97 --ignore-preflight-errors=Swap
[preflight] Running pre-flight checks
	[WARNING Swap]: swap is enabled; production deployments should disable swap unless testing the NodeSwap feature gate of the kubelet
error execution phase preflight: couldn't validate the identity of the API Server: could not find a JWS signature in the cluster-info ConfigMap for token ID "ysrv0l"
To see the stack trace of this error execute with --v=5 or higher
如上，主要看报错信息的最后一行，原因是原来的token过期了

可以通过以下命令验证，没有任何输出

$ kubeadm token list
# 此处没有任何输出, 表明没有存活的token
解决办法，生成个新的token

# 在 master 节点执行
kubeadm token create --print-join-command --ttl=0
其中 --ttl=0 表示生成的 token 永不失效. 如果不带 --ttl 参数, 默认有效时间为24小时

kubectl uncordon <node-name> to re-scheduleable a node

要防止节点调度新的 Pod，请使用：

kubectl cordon <node-name>
这将导致节点处于状态：Ready,SchedulingDisabled。

要告诉的是恢复调度使用：

kubectl uncordon <node-name>



kubectl run nginx --image=nginx --restart=Never. This will create a pod named nginx, running with the nginx image on Docker Hub. And by setting the flag --restart=Never we tell Kubernetes to create a single pod rather than a Deployment.

kubectl get pods 
 kubectl describe pod nginxin
 kubectl delete pod nginx. 

--restart master 
sudo kubeadm reset

 ----restart node
 
sudo kubeadm reset
 sudo kubeadm init --control-plane-endpoint=k8s-master1 --upload-certs
 follow the output

sudo systemctl enable docker

sudo systemctl enable kubelet

sudo systemctl daemon-reload

sudo systemctl restart docker

sudo netstat -lnp | grep 1025

sudo rm -rf /etc/kubernetes/kubelet.conf /etc/kubernetes/pki/ca.crt
sudo rm -rf /etc/kubernetes/*

sudo kubeadm join ipaddress:6443 --token