#######Version#########  
V1.1.2

#######compiling environment#########  
ubuntu 64-bit LSB

#######install toolchain#########  
cd toolchain  
tar -vxzf OpenWrt-Toolchain-ramips-for-mipsel_24kec+dsp-gcc-4.8-linaro_uClibc-0.9.33.2.tar.gz  
sudo cp -rf OpenWrt-Toolchain-ramips-for-mipsel_24kec+dsp-gcc-4.8-linaro_uClibc-0.9.33.2.9.33.2 /opt/  
vim ~/.profile  
	export PATH="$PATH:/opt/OpenWrt-Toolchain-ramips-for-mipsel_24kec+dsp-gcc-4.8-linaro_uClibc-0.9.33.2/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin"  
exit  

#######make blepub#########  
cd blepub/src  
make  

#######clean image temporary files (Nonessential step)########    
cd image  
./mksysupgrade clean  

#######unsquashfs rootfs########  
cd image  
./mksysupgrade unrootfs  

#######modify rootfs########  
cd image  

cp ../blepub/src/blepub squashfs-root/usr/bin  
cp ../blepub/files/bleserve squashfs-root/etc/init.d/  

vim squashfs-root/etc/config/bleserve  
	bleserve.custom.enable=1  
	bleserve.custom.fifo=raw        
	//or bleserve.custom.fifo=beacon        

#######package firmware########  
./mksysupgrade package  
