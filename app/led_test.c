#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
 
int main(int argc, char **argv){
    int fd;
    int ret = 0;
    char buf[3];
    char buf_write[3];
    
    memset(buf, '0', sizeof(buf));
    memset(buf_write, '0', sizeof(buf_write));
    
    fd = open("/dev/led", O_RDWR);
    if (fd < 0){
        perror("open /dev/led error, exit\n");
        exit(1);
    }
    printf("open /dev/led success\n");
    
    //open led 1
    buf_write[0] = '0';
    buf_write[1] = '1';
    buf_write[2] = '1';
    
    ret = write(fd, buf_write, sizeof(buf_write));
    if(ret > 0){
        printf("write /dev/led success\n");
    }
    else{
        printf("write /dev/led error\n");
    }
    
    ret = read(fd, buf, sizeof(buf));
    if(ret > 0){
        printf("read /dev/led success: %s\n", buf);
    }
    else{
        printf("read /dev/led error\n");
    }        
    
    sleep(1);

    //open led 2
    buf_write[0] = '0';
    buf_write[1] = '0';
    buf_write[2] = '1';

    ret = write(fd, buf_write, sizeof(buf_write));
    if (ret > 0) {
        printf("write /dev/led success\n");
    }
    else {
        printf("write /dev/led error\n");
    }

    ret = read(fd, buf, sizeof(buf));
    if (ret > 0) {
        printf("read /dev/led success: %s\n", buf);
    }
    else {
        printf("read /dev/led error\n");
    }

    sleep(1);

    //open led 3
    buf_write[0] = '0';
    buf_write[1] = '0';
    buf_write[2] = '0';

    ret = write(fd, buf_write, sizeof(buf_write));
    if (ret > 0) {
        printf("write /dev/led success\n");
    }
    else {
        printf("write /dev/led error\n");
    }

    ret = read(fd, buf, sizeof(buf));
    if (ret > 0) {
        printf("read /dev/led success: %s\n", buf);
    }
    else {
        printf("read /dev/led error\n");
    }

    sleep(3);
    
    //close led 1
    buf_write[0] = '1';
    buf_write[1] = '0';
    buf_write[2] = '0';
    
    ret = write(fd,buf_write, sizeof(buf_write));
    if(ret > 0){
        printf("write /dev/led success\n");
    }
    else{
        printf("write /dev/led error\n");
    }
    
    ret = read(fd, buf, sizeof(buf));
    if(ret > 0){
        printf("read /dev/led success: %s\n", buf);
    }
    else{
        printf("read /dev/led error\n");
    }

    sleep(1);

    //close led 2
    buf_write[0] = '1';
    buf_write[1] = '1';
    buf_write[2] = '0';

    ret = write(fd, buf_write, sizeof(buf_write));
    if (ret > 0) {
        printf("write /dev/led success\n");
    }
    else {
        printf("write /dev/led error\n");
    }

    ret = read(fd, buf, sizeof(buf));
    if (ret > 0) {
        printf("read /dev/led success: %s\n", buf);
    }
    else {
        printf("read /dev/led error\n");
    }

    sleep(1);

    //close led 3
    buf_write[0] = '1';
    buf_write[1] = '1';
    buf_write[2] = '1';

    ret = write(fd, buf_write, sizeof(buf_write));
    if (ret > 0) {
        printf("write /dev/led success\n");
    }
    else {
        printf("write /dev/led error\n");
    }

    ret = read(fd, buf, sizeof(buf));
    if (ret > 0) {
        printf("read /dev/led success: %s\n", buf);
    }
    else {
        printf("read /dev/led error\n");
    }
    
    close(fd);
    return 0;
}
