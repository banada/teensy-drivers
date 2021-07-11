# teensy-drivers
Linux kernel drivers for the Teensy 3.5

Intended as a learning exercise for kernel module and driver development

## Getting started

```
sudo apt-get install linux-headers-$(uname -r)
git clone https://github.com/banada/teensy-drivers
cd teensy-drivers/recognize_teensy
make
```

Load the module:
```
insmod ./module_boilerplate.ko
```

The `usbhid` module will always recognize the device first, so we need to override it. Add a udev rule:

```
sudo cp 10-teensy.rules /etc/udev/rules.d/10-teensy.rules
sudo udevadm trigger
```

Run `dmesg -w` to watch the kernel logs, and plug in your device. You should see:

<pre><font color="#859900">[ 3417.961202] </font><b>You plugged in a Teensy with serial number XXXXXXX</b></pre>

You can manually remove the module with `rmmod module_boilerplate.ko`.

