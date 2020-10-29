#######development environment#########  
window10 

#######development tool#########  
JetBrains WebStorm

#######install Project#########   
npm install  
  
#######modify web_source#########  


#######generate web(dir dist)#########    
npm run build  

#######install web#########  
cp -rf dist/* image/squashfs-root/etc_ro/web/  

