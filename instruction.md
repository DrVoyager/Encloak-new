### JNI与c++的编译

#### JNI

根据需要修改~/SGX/Encloak/SGX/EnhancedSGX/App/App.cpp

### c++

根据需要修改~/SGX/Encloak/SGX/EnhancedSGX/Enclave/Enclave.cpp

#### 编译

~/SGX/Encloak/SGX/EnhancedSGX下执行

```
$ make clean
$ make
$ ./scpso-hadoop.sh(hadoop case时执行，按照cluster各节点的实际IP值对脚本进行修改)
```



## java（binarysearch为例）

#### 指定敏感变量

1. 将~/SGX/Encloak/tests/java/src/test/case中的java文件拷贝到上一级目录
2. 修改~/SGX/Encloak/soot-code/EhancedCFHider/src中的MyMain函数（152,153,155行）

3. ~/SGX/Encloak/soot-code/EhancedCFHider目录下执行build-jar.sh

> 注：以下命令均在~/SGX/Encloak/tests/java目录下执行

#### 编译

```
$ ./build-origin.sh  
```

#### 清理缓存

```
$ ./rmtmp.sh 
```

#### 转换

```
$ ./transformer.sh
```

#### 加密

```
$ source /opt/intel/sgxsdk/environment
$ ./encrypt_SGXindex.sh
```

#### 执行

```
$ cd replaceOutput
$ java test.BinarySearch（注意执行的文件的名称应当与指定敏感源时选择的文件相同，此处以BinarySearch为例）
```



## hadoop（hadoopPI为例）

#### 指定敏感变量

1. 修改~/SGX/Encloak/soot-code/EhancedCFHider/src中的MyMain函数（143-145行）

2. ~/SGX/Encloak/soot-code/EhancedCFHider目录下执行build-jar.sh

> 注：以下命令均在~/SGX/Encloak/tests/hadoop/hadoopPI目录下执行

#### 编译

```
$ ./build-origin.sh  
$ ./origin-run.sh（执行PI的源代码，可略过，若要执行需切换至hadoop用户，密码为123）
```

#### 清理缓存

```
$ ./rmtmp.sh 
```

#### 转换

```
$ ./replace-transform.sh 
```

#### 加密

```
$ source /opt/intel/sgxsdk/environment
$ ./encrypt_SGXindex.sh  
```

#### 执行

```
$ ./replace-run.sh （hadoop用户下执行）
```