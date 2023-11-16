docker安装ES、MySQL、PostgreSQL、Nginx、zookeeper、Kafka、confluence
confluence
docker run --name ymwx-confluence -p 8090:8090 --privileged=true -v /data/docker/confluence/var:/var/atlassian/confluence  --user root:root -d atlassian/confluence-server:latest
es
docker run -d --name elasticsearch --net es-kibana -p 9200:9200 -p 9300:9300 -e "discovery.type=single-node" elasticsearch:6.8.7
filebrowser
docker run --name filebrowser -d -v /data/docker/filebrowser/srv:/srv -v /data/docker/filebrowser/config.json:/etc/config.json -v /data/docker/filebrowser/database.db:/etc/database.db -p 8090:80 filebrowser/filebrowser
gitlab
docker run \
    --detach \
    --publish 8443:443 \
    --publish 8090:80 \
    --name gitlab \
    --restart unless-stopped \
    --name ymwx gitlab \
    -v /data/docker/gitlab/etc:/etc/gitlab \
    -v /data/docker/gitlab/log:/var/log/gitlab \
    -v /data/docker/gitlab/data:/var/opt/gitlab \
     beginor/gitlab-ce:11.3.0-ce.0
kafka-manager
docker run --name ymwx-kafka-manager --link ymwx-zookeeper:zk --link ymwx-kafka:kafka -e ZK_HOSTS=zk:2181 -p 9000:9000 -d docker.io/sheepkiller/kafka-manager:latest
kafka
docker run --name ymwx-kafka --privileged=true -v /data/docker/kafka/logs:/kafka -v /data/docker/kafka/run/docker.sock:/var/run/docker.sock --link ymwx-zookeeper:zk -e KAFKA_ZOOKEEPER_CONNECT="zk:2181" -e KAFKA_ADVERTISED_HOST_NAME=localhost -e KAFKA_ADVERTISED_PORT=9092 -p 9092:9092 -d docker.io/wurstmeister/kafka:latest
kibana
docker run -d --name kibana --net es-kibana -p 5601:5601 kibana:6.8.7
mysql
docker run --name ymwx-mysql --privileged=true -v /data/docker/mysql/conf:/etc/mysql/conf.d -v /data/docker/mysql/logs:/logs -v /data/docker/mysql/data:/var/lib/mysql -p 53306:3306 -e MYSQL_ROOT_PASSWORD=ymwx171902 -d docker.io/mysql:8.0.19
nginx
docker run --name ymwx-nginx --privileged=true -p 80:80 -v /data/docker/nginx/www:/usr/share/nginx/html -v /data/docker/nginx/conf/nginx.conf:/etc/nginx/nginx.conf -v /data/docker/nginx/logs:/var/log/nginx -d docker.io/nginx:1.17.9
postgresql
docker run --name ymwx-postgresql --privileged=true -v /date/docker/postgresql/date:/var/lib/postgresql/date -e POSTGRES_PASSWORD=ymwx171902 -p 55432:5432 -d docker.io/postgres:12.1
zookeeper
docker run --name ymwx-zookeeper --privileged=true -p 2181:2181 -v /data/docker/zookeeper/data:/opt/zookeeper-3.4.13/data -v /data/docker/zookeeper/conf:/opt/zookeeper-3.4.13/conf -v /data/docker/zookeeper/conf/zoo.cfg:/opt/zookeeper-3.4.13/conf/zoo.cfg -d docker.io/wurstmeister/zookeeper:latest
起风了，努力生存