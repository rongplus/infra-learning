192.168.56.111  k8s-master1
192.168.56.114  k8s-master2
192.168.56.112  k8s-node1
192.168.56.113  k8s-node2
192.168.56.117  k8s-node3
192.168.56.115  k8s-lb1
192.168.56.116  k8s-lb2

---nginx path
/usr/share/nginx

kubeadm join k8s-master1:6443 --token 5wcutd.7ak4ez8ybirrkgcs \
        --discovery-token-ca-cert-hash sha256:251ffbe7e2d2a69294cb9545134b46828d13a00c56aed5d10827c9285359be2e \
        --control-plane --certificate-key 83b7df540d8734c4e4d8a5e15acf2422465d6f5684344a70cf5f8daf61249d61