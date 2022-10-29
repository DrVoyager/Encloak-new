

### What is this repository for?  
this repo contains the necessary file for users to bulid or test a control flow project

### How do I get set up?  

* 1.build the c++ shared object in SGX folder
* 2.bulid JNI
* 3.bulid java or hadoop project
* 4.use soot to transform your code
* 5.use the benchmark test cases to test

# FOLDERS  
### JNI  
this folder contains the JNI (cpp headers) for the java project to call the c++ shared object

### SGX  
this folder contains the source code to build the c++ shared object
##### (note) config the sgx in Enclave/Enclave.config.xml ,especially for the heap and stack

### soot code  
use soot to transform the java or hadoop code into a control flow version

### tests  
benchmark test cases for the projects

## Contribution  

* Yongzhi Wang
* Ke Cheng
* Yibo Yang
* Cuicui Su

### feedback  

* contact bobyangpopo@gmail.com  
