import psutil
import platform
from datetime import datetime
#import cpuinfo
import socket
import uuid
import re

from confluent_kafka import Producer
from confluent_kafka import SerializingProducer
from confluent_kafka.serialization import StringSerializer
from confluent_kafka.schema_registry import SchemaRegistryClient
from confluent_kafka.schema_registry.protobuf import ProtobufSerializer
from confluent_kafka import Producer
import socket
import socket

import sysinfo_pb2 as sp

conf = {'bootstrap.servers': "192.168.1.118:9092,192.168.135.133:9092",
        'client.id': socket.gethostname()}

producer = Producer(conf)
a = sp.Status()
a.ip="123"
a.email="huang"


def get_size(bytes, suffix="B"):
    """
    Scale bytes to its proper format
    e.g:
        1253656 => '1.20MB'
        1253656678 => '1.17GB'
    """
    factor = 1024
    for unit in ["", "K", "M", "G", "T", "P"]:
        if bytes < factor:
            return f"{bytes:.2f}{unit}{suffix}"
        bytes /= factor
def acked(err, msg):
    if err is not None:
        print("Failed to deliver message: %s: %s" % (str(msg), str(err)))
    else:
        print("Message produced: %s" % (str(msg)))



def System_information():
    print("="*40, "System Information", "="*40)
    uname = platform.uname()
    producer.produce('some-topic', key="key", value=f"System: {uname.system} {psutil.cpu_percent()}%")
    #producer.produce('some-topic', key="key", value=a)

    print(f"System: {uname.system}")
    producer.produce("test123", key="System", value=uname.system, callback=acked)

    print(f"Node Name: {uname.node}")
    producer.produce("test123", key="Node Name", value=uname.node, callback=acked)

    print(f"Release: {uname.release}")
    producer.produce("test123", key="Release", value=uname.release, callback=acked)
    print(f"Version: {uname.version}")
    producer.produce("test123", key="Version", value=uname.version, callback=acked)
    print(f"Machine: {uname.machine}")
    producer.produce("test123", key="Machine", value=uname.machine, callback=acked)
    print(f"Processor: {uname.processor}")
    producer.produce("test123", key="Processor", value=uname.processor, callback=acked)
    #print(f"Processor: {cpuinfo.get_cpu_info()['brand_raw']}")
    print(f"Ip-Address: {socket.gethostbyname(socket.gethostname())}")
    producer.produce("test123", key="Ip-Address", value=socket.gethostbyname(socket.gethostname()), callback=acked)
    print(f"Mac-Address: {':'.join(re.findall('..', '%012x' % uuid.getnode()))}")
    
    # Boot Time
    print("="*40, "Boot Time", "="*40)
    boot_time_timestamp = psutil.boot_time()
    bt = datetime.fromtimestamp(boot_time_timestamp)
    print(f"Boot Time: {bt.year}/{bt.month}/{bt.day} {bt.hour}:{bt.minute}:{bt.second}")


    # print CPU information
    print("="*40, "CPU Info", "="*40)
    # number of cores
    print("Physical cores:", psutil.cpu_count(logical=False))
    print("Total cores:", psutil.cpu_count(logical=True))
    # CPU frequencies
    cpufreq = psutil.cpu_freq()
    print(f"Max Frequency: {cpufreq.max:.2f}Mhz")
    print(f"Min Frequency: {cpufreq.min:.2f}Mhz")
    print(f"Current Frequency: {cpufreq.current:.2f}Mhz")
    # CPU usage
    print("CPU Usage Per Core:")
    for i, percentage in enumerate(psutil.cpu_percent(percpu=True, interval=1)):
        print(f"Core {i}: {percentage}%")
    print(f"Total CPU Usage: {psutil.cpu_percent()}%")


    # Memory Information
    print("="*40, "Memory Information", "="*40)
    # get the memory details
    svmem = psutil.virtual_memory()
    print(f"Total: {get_size(svmem.total)}")
    print(f"Available: {get_size(svmem.available)}")
    print(f"Used: {get_size(svmem.used)}")
    print(f"Percentage: {svmem.percent}%")



    print("="*20, "SWAP", "="*20)
    # get the swap memory details (if exists)
    swap = psutil.swap_memory()
    print(f"Total: {get_size(swap.total)}")
    print(f"Free: {get_size(swap.free)}")
    print(f"Used: {get_size(swap.used)}")
    print(f"Percentage: {swap.percent}%")



    # Disk Information
    print("="*40, "Disk Information", "="*40)
    print("Partitions and Usage:")
    # get all disk partitions
    partitions = psutil.disk_partitions()
    for partition in partitions:
        print(f"=== Device: {partition.device} ===")
        print(f"  Mountpoint: {partition.mountpoint}")
        print(f"  File system type: {partition.fstype}")
        try:
            partition_usage = psutil.disk_usage(partition.mountpoint)
        except PermissionError:
            # this can be catched due to the disk that
            # isn't ready
            continue
        print(f"  Total Size: {get_size(partition_usage.total)}")
        print(f"  Used: {get_size(partition_usage.used)}")
        print(f"  Free: {get_size(partition_usage.free)}")
        print(f"  Percentage: {partition_usage.percent}%")
    # get IO statistics since boot
    disk_io = psutil.disk_io_counters()
    print(f"Total read: {get_size(disk_io.read_bytes)}")
    print(f"Total write: {get_size(disk_io.write_bytes)}")

    ## Network information
    print("="*40, "Network Information", "="*40)
    ## get all network interfaces (virtual and physical)
    if_addrs = psutil.net_if_addrs()
    for interface_name, interface_addresses in if_addrs.items():
        for address in interface_addresses:
            print(f"=== Interface: {interface_name} ===")
            if str(address.family) == 'AddressFamily.AF_INET':
                print(f"  IP Address: {address.address}")
                print(f"  Netmask: {address.netmask}")
                print(f"  Broadcast IP: {address.broadcast}")
            elif str(address.family) == 'AddressFamily.AF_PACKET':
                print(f"  MAC Address: {address.address}")
                print(f"  Netmask: {address.netmask}")
                print(f"  Broadcast MAC: {address.broadcast}")
    ##get IO statistics since boot
    net_io = psutil.net_io_counters()
    print(f"Total Bytes Sent: {get_size(net_io.bytes_sent)}")
    print(f"Total Bytes Received: {get_size(net_io.bytes_recv)}")
    #producer.poll(1)
    producer.flush()


if __name__ == "__main__":

    System_information()