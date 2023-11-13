# Сборка dpdk
```
sudo apt-get update && sudo apt-get upgrade -y
sudo apt-get install build-essential -y
sudo apt-get install meson -y
sudo apt-get install python3-pyelftools -y
sudo apt-get install libnuma-dev -y
sudo apt-get install libncurses-dev -y
sudo apt-get install libpcap-dev -y
sudo apt-get install python3-pip -y
pip3 install meson ninja

cd ~
wget https://fast.dpdk.org/rel/dpdk-23.07.tar.xz
tar xJf dpdk-23.07.tar.xz
rm -rf dpdk-23.07.tar.xz
cd dpdk-23.07
sudo meson setup build
cd build
sudo ninja
sudo meson install
sudo ldconfig
```

# Bind interfaces

### Посмотреть имеющиейся интерфейсы
```
dpdk-devbind.py -s
```

### Bind
```
dpdk-devbind --bind=vfio-pci <name>
```

# Установка и настройка dpdkcap

```
export RTE_SDK=~/dpdk-23.07
export RTE_TARGET=x86_64-native-linuxapp-gcc
```

### \#/sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
```
1024
```

### \#/etc/default/grub
```
...
GRUB_CMDLINE_LINUX="default_hugepagesz=1G hugepagesz=1G hugepages=8"
...
```

### 
```
sudo mkdir -p /dev/hugepages
sudo mountpoint -q /dev/hugepages || sudo mount -t hugetlbfs nodev /dev/hugepages
sudo mount -t hugetlbfs hugetlbfs /dev/hugepages -o pagesize=2M

git clone https://github.com/bogdann29/dpdkcap.git
cd dpdkcap
make
```

### Запуск
```
sudo ./build/dpdkcap --huge-dir /dev/hugepages --no-telemetry
```


