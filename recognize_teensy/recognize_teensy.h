/*
 *
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#define VENDOR_ID   0x16c0
#define PRODUCT_ID  0x0486

static int teensy_probe(struct usb_interface *intf,
                        const struct usb_device_id *id);
static void teensy_disconnect(struct usb_interface *intf);

static struct usb_device_id id_table [];

static struct usb_driver teensy_driver;
