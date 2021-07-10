# teensy-drivers
Linux kernel drivers for the Teensy 3.5

Intended as a learning exercise for kernel module and driver development

## Install

```
sudo apt-get install linux-headers-$(uname -r)
git clone https://github.com/banada/teensy-drivers
cd teensy-drivers
make
```

Run `dmesg -w` to watch the kernel logs

## Load module

```
insmod module_boilerplate.ko
```

## Remove module

```
rmmod module_boilerplate.ko
```

