Setup zookeeper:

    vpc
        --> subnet   at least 3
            remember the cidr with the AZ

    instance 
        --> at lease 4GB memory
        --> choose the right subnet (172.31.0.0/20)
        --> set the primary IP
        --> group security
            add custom tcp for zookeeper, port =  2181,2888,3888
            set source as 172.31.0.0/16
            add tcp for my-ip for 2181
        --> get pem file and launch
    
    SSH to the instance
        refer to platform_dev\code\setup\setup-1-zookeeper-single.sh


    create a image base on this instance
    from ami launch it