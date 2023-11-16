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