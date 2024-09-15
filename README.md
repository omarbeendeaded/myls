# myls
My own implementation of some of the functionality of the `ls` function in the linux terminal

It supports all of the following options `-atucifd1`

## Compilation Command
`gcc myls.c util.c -o myls`

## Example Output
``` sh
omar@Ubuntu22:~/Desktop/myls/proj$ gcc myls.c util.c -o myls
omar@Ubuntu22:~/Desktop/myls/proj$ ./myls /dev
autofs           block            bsg              btrfs-control    bus              cdrom            char             console          core             
cpu              cpu_dma_latency  cuse             disk             dma_heap         dri              ecryptfs         fb0              fd               full             
fuse             hidraw0          hpet             hugepages        hwrng            i2c-0            initctl          input            kmsg             log              
loop0            loop1            loop10           loop11           loop12           loop13           loop14           loop2            loop3            loop4            
loop5            loop6            loop7            loop8            loop9            loop-control     mapper           mcelog           mem              mqueue           
net              null             nvram            port             ppp              psaux            ptmx             pts              random           rfkill           
rtc              rtc0             sda              sda1             sda2             sda3             sdb              sdb1             sdb10            sdb3             
sdb5             sdb6             sdb7             sdb8             sdb9             sg0              sg1              sg2              shm              snapshot         
snd              sr0              stderr           stdin            stdout           tty              tty0             tty1             tty10            tty11            
tty12            tty13            tty14            tty15            tty16            tty17            tty18            tty19            tty2             tty20            
tty21            tty22            tty23            tty24            tty25            tty26            tty27            tty28            tty29            tty3             
tty30            tty31            tty32            tty33            tty34            tty35            tty36            tty37            tty38            tty39            
tty4             tty40            tty41            tty42            tty43            tty44            tty45            tty46            tty47            tty48            
tty49            tty5             tty50            tty51            tty52            tty53            tty54            tty55            tty56            tty57            
tty58            tty59            tty6             tty60            tty61            tty62            tty63            tty7             tty8             tty9             
ttyprintk        ttyS0            ttyS1            ttyS10           ttyS11           ttyS12           ttyS13           ttyS14           ttyS15           ttyS16           
ttyS17           ttyS18           ttyS19           ttyS2            ttyS20           ttyS21           ttyS22           ttyS23           ttyS24           ttyS25           
ttyS26           ttyS27           ttyS28           ttyS29           ttyS3            ttyS30           ttyS31           ttyS4            ttyS5            ttyS6            
ttyS7            ttyS8            ttyS9            udmabuf          uhid             uinput           urandom          userfaultfd      userio           vboxguest        
vboxuser         vcs              vcs1             vcs2             vcs3             vcs4             vcs5             vcs6             vcsa             vcsa1            
vcsa2            vcsa3            vcsa4            vcsa5            vcsa6            vcsu             vcsu1            vcsu2            vcsu3            vcsu4            
vcsu5            vcsu6            vfio             vga_arbiter      vhci             vhost-net        vhost-vsock      zero             zfs
omar@Ubuntu22:~/Desktop/myls/proj$
```
           
