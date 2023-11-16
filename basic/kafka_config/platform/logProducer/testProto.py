import sysinfo_pb2 as sp

a = sp.Status()
a.ip="123"
a.email="huang"
print(a)

b = a.SerializeToString()

d = sp.Status()
d.ParseFromString(b)