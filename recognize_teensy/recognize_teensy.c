#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/slab.h>

#include "recognize_teensy.h"

struct usb_teensy {
    struct usb_device *udev;
    char *message;
};

static int init_my_module(void) {
    int register_error = usb_register(&teensy_driver);
    if (register_error) {
        printk(KERN_ERR "%s%d\n", "Failed to register Teensy driver. Error number: ", register_error);
        return 1;
    }

    printk("%s%s%s%s\n", "Loaded ", THIS_MODULE->name, " module version ", THIS_MODULE->version);

    return 0;
}

static void exit_my_module(void) {
    usb_deregister(&teensy_driver);

    printk("%s%s%s\n", "Unloaded ", THIS_MODULE->name, " module");
}

/*
 *  Called after hotplug, when USB device ID is recognized
 *  Initialize device
 */
static int teensy_probe(struct usb_interface *intf,
                        const struct usb_device_id *id) {

    struct usb_teensy *dev = NULL;

    /* Allocate memory and empty it */
    dev = kmalloc(sizeof(struct usb_teensy), GFP_KERNEL);
    memset(dev, 0x00, sizeof(*dev));

    /* Get the device pointer */
    dev->udev = usb_get_dev(interface_to_usbdev(intf));

    /* Keep the device pointer in an interface
     * in the USB core, which we can call from
     * anywhere later
     */
    usb_set_intfdata(intf, dev);

    /*
     *Print serial number via the interface
     *
     */
    printk("%s%s\n", "You plugged in a Teensy with serial number ", dev->udev->serial);

    return 0;
}

static void teensy_disconnect(struct usb_interface *intf) {
    struct usb_teensy *dev = NULL;

    dev = usb_get_intfdata(intf);

    /* Clean up the interface's device pointer */
    usb_set_intfdata(intf, NULL);
    /* Clean up device */
    usb_put_dev(dev->udev);
    kfree(dev);

    printk("%s\n", "Teensy USB device disconnected.");
}

static struct usb_device_id id_table [] = {
    { USB_DEVICE(VENDOR_ID, PRODUCT_ID) },
    { },
};

static struct usb_driver teensy_driver = {
    .name = "recognize_teensy",
    .probe = teensy_probe,
    .disconnect = teensy_disconnect,
    .id_table = id_table
};

/*
 *  Registers device table for hotplugging
 *  Creates an alias that is seen by file2alias
 *  The USB device is recognized, and the driver
 *  is loaded.
 */
MODULE_DEVICE_TABLE(usb, id_table);

module_init(init_my_module);
module_exit(exit_my_module);

MODULE_VERSION("0.1.0");
MODULE_LICENSE("GPL v2");


