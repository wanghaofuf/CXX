  #include   <stdlib.h>
  #include   <fcntl.h>
  #include   <linux/kd.h>
  #include <sys/ioctl.h>
 
 // a.out 800 1000   (频率是800 响1秒) 
 //  
  int   main(int   argc,   char   *argv[])
  {
          int   fd   =   open("/dev/tty10",   O_RDONLY);
          if   (fd   ==   -1   ||   argc   !=   3)
                  return   -1;
          return   ioctl(fd,   KDMKTONE,   (atoi(argv[2])<<16)+(1193180/atoi(argv[1])));
  }