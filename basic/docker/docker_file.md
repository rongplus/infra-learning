# Use root/example as user/password credentials
version: "3.1"

services:

  db:
    image: mysql:latest
    container_name: zh_mysql
    environment:
      - MYSQL_ROOT_PASSWORD=123456
      - TZ=Asia/Shanghai
    volumes:
      - /home/peng/docker/data/mysql:/var/lib/mysql
    ports:
      - 3306:3306

  redis:
    image: redis:latest
    container_name: zh_redis
    ports:
      - 6379:6379

  etcd:
    image: bitnami/etcd:latest
    container_name: zh_etcd
    environment:
      - ALLOW_NONE_AUTHENTICATION=yes
    ports:
      - 2379:2379

  es:
    image: elasticsearch:7.17.5
    container_name: zh_es
    environment:
      - discovery.type=single-node
    volumes:
      - /home/peng/docker/conf/elasticsearch/elasticsearch.yml:/usr/share/elasticsearch/config/elasticsearch.yml
      - /home/peng/docker/conf/elasticsearch/plugins:/usr/share/elasticsearch/plugins

    ports:
      - 9200:9200

  kibana:
    image: kibana:7.17.5
    container_name: zh_kibana
    volumes:
      - /home/peng/docker/conf/kibana/kibana.yml:/usr/share/kibana/config/kibana.yml
    ports:
      - 5601:5601
    depends_on:
      - es

  zookeeper:
    image: bitnami/zookeeper:latest
    container_name: zh_zookeeper
    environment:
      - ALLOW_ANONYMOUS_LOGIN=yes
    ports:
      - 2181:2181

  kafka:
    image: bitnami/kafka:latest
    container_name: zh_kafka
    environment:
      - ALLOW_ANONYMOUS_LOGIN=yes
      - ALLOW_PLAINTEXT_LISTENER=yes
      - KAFKA_CFG_ZOOKEEPER_CONNECT=zookeeper:2181
    ports:
      - 9092:9092
    depends_on:
      - zookeeper

  kafka-map:
    image: dushixiang/kafka-map:latest
    container_name: zh_kafka-map
    volumes:
      - /home/peng/docker/data/kafka-map:/usr/local/kafka-map/data
    environment:
      - DEFAULT_USERNAME=admin
      - DEFAULT_PASSWORD=admin
    ports:
      - 8089:8080
    depends_on:
      - kafka