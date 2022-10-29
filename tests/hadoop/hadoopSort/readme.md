## Specify a sensitive variable
Refer to **soot-code/readme.md** to specify a sensitive variable.

## Build and run original java files
    $ mkdir bin Origin replaceOutput   
    $ ./build-origin.sh  
    $ ./run-origin.sh  

## transform origin class files to new ones with SGX
    $ ./replace-transformer.sh  

## encrypt SGXindex  
    $ ./encrypt_SXGindex.sh  
> the encrypted SGXindex file should be */tmp/* on every nodes in the cluster.(scp)  

## runing this new files
    $ ./run-replace.sh  

## NOTICE: BEFORE TRANSFORM THE CLASS FILES, TO CLEAN THE *SGXindex* AND *counter* IN THE */tmp*.
