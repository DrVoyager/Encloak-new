

### What is this repository for?  
this repo contains the necessary file for users to bulid or test a data flow project

### How do I get set up?  

* 0. Install JDK and SGX on your computer
* 1. Build the c++ shared object in SGX folder
* 2. Bulid the transform tool in soot-code folder
* 3. Bulid java or hadoop project
* 4. Transform your code using the tool generated in step 2
* 5. Test the benchmark test cases

# FOLDERS  
### JNI  
this folder contains the JNI (cpp headers) for the java project to call the c++ shared object

### SGX  
this folder contains the source code to build the c++ shared object
##### (note) config the sgx in Enclave/Enclave.config.xml ,especially for the heap and stack

### soot code  
use soot to transform the java or hadoop code into a data flow version

### tests  
benchmark test cases for the projects

## Contribution  


### feedback  
 
