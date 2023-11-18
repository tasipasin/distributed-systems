#!/usr/bin/env python3
from kazoo.client import KazooClient
from kazoo.exceptions import NodeExistsError

zk = KazooClient()
zk.start()

try:
    znode = "/sdc/tasi"
    # 'b' significa que é um array de bytes (string basica)
    zk.create(znode, b"mingau")
except NodeExistsError:
    print("Node já criado")

print(zk.get_children("/sdc"))

zk.stop()
