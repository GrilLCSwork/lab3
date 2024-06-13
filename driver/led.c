#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/gpio.h>

#define DEVICE_NAME "led"

static int LED_MAJOR = 0;
static int GPIO_LED1_PIN = 77;
static int GPIO_LED2_PIN = 64;
static int GPIO_LED3_PIN = 65;
static int GPIO_LED_N[3] = {65, 64, 77}; 

static int led_open(struct inode *inode, struct file *file){
    printk(KERN_DEBUG "LED open\n");
    return 0;
}

static ssize_t led_read(struct file *filp, char *buffer, size_t count, loff_t *ppos){
    char tmp[3];
    int ret;
    
    if(gpio_get_value(GPIO_LED1_PIN) == 1){
        tmp[0] = '1';
    }
    else{
        tmp[0] = '0';
    }
    
    if(gpio_get_value(GPIO_LED2_PIN) == 1){
        tmp[1] = '1';
    }
    else{
        tmp[1] = '0';
    }
    
    if(gpio_get_value(GPIO_LED3_PIN) == 1){
        tmp[2] = '1';
    }
    else{
        tmp[2] = '0';
    }
    
    printk(KERN_DEBUG "LED read\n");
    
    ret = copy_to_user(buffer, tmp, sizeof(tmp));

    return count;
}

static ssize_t led_write(struct file *filp, const char *buffer, size_t count, loff_t *f_pos){
    int ret;
    char tmp[3];
    int i;
    
    memset(tmp,0,3);
    
    if(count > 3){
        printk(KERN_DEBUG "invalid argument\n");
        return count;
    }
	
    ret = copy_from_user(tmp, buffer, count);
    if(!ret){
        printk(KERN_DEBUG "copy from user:%s\n",buffer);
    }
    
    for(i = 0; i < count; i++){
        gpio_direction_output(GPIO_LED_N[i], !strncmp(&tmp[i], "1", 1) ? 1 : 0);
    }
    
    printk(KERN_DEBUG "LED write\n");
    return count;
}

static long led_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
    printk(KERN_DEBUG "LED ioctl\n");
    return 0;
}

static int led_release(struct inode *inode, struct file *filp){    
    printk(KERN_DEBUG "LED release\n");
    return 0;    
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .read = led_read,
    .write = led_write,
    .unlocked_ioctl = led_ioctl,
    .release = led_release,
};

static struct class *led_class;

static int __init led_init(void){
    int ret;
    printk(KERN_DEBUG "LED init\n");
    LED_MAJOR = register_chrdev(0, DEVICE_NAME, &led_fops);

    if(LED_MAJOR < 0){
        printk(KERN_DEBUG "Can't register led major number\n");
        return LED_MAJOR;
    }
    
    printk(KERN_DEBUG "Register led driver OK! Major = %d\n", LED_MAJOR);
 
    led_class = class_create(THIS_MODULE, DEVICE_NAME);
    if(IS_ERR(led_class)){
        printk(KERN_DEBUG "Err: create led class failed.\n");
        return -1;
    }

    device_create(led_class, NULL, MKDEV(LED_MAJOR, 0), NULL, DEVICE_NAME);
    
    ret = gpio_request(GPIO_LED1_PIN, "GPIO_LED1_PIN");
    if(ret < 0){
        printk("Request led1 pin fail\n");
    }
    gpio_direction_output(GPIO_LED1_PIN, 1);
    
    ret = gpio_request(GPIO_LED2_PIN, "GPIO_LED2_PIN");
    if(ret < 0){
        printk("Request led2 pin fail\n");
    }
    gpio_direction_output(GPIO_LED2_PIN, 1);

    ret = gpio_request(GPIO_LED3_PIN, "GPIO_LED3_PIN");
    if(ret < 0){
        printk("Request led3 pin fail\n");
    }
    gpio_direction_output(GPIO_LED3_PIN, 1);
    
    printk(KERN_DEBUG "LED initialized\n");
    
    return 0;
}

static void __exit led_exit(void){
    printk(KERN_DEBUG "LED exit\n");
    gpio_free(GPIO_LED1_PIN);
    gpio_free(GPIO_LED2_PIN);
    gpio_free(GPIO_LED3_PIN);
    device_destroy(led_class, MKDEV(LED_MAJOR, 0));
    class_destroy(led_class);
    unregister_chrdev(LED_MAJOR, DEVICE_NAME);
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
