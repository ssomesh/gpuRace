# Evaluation Test for *GPU Race for Particle Hunting*

### Getting the code

- Clone the code into a directory called gpuRace
    ```
    git clone --branch=master https://github.com/ssomesh/gpuRace
    ```
- The source code is present in the file *matrixInverse.cpp*

### Building Kokkos

- Build Kokkos with the default configuration
  - {Kokkos root directory path}/generate_makefile.bash --kokkos-path={Kokkos root directory path} --prefix={install path} 

### Compiling and Testing the code

- Inside the folder *gpuRace*, do the following :
    - set the environment variable **KOKKOS_PATH** 
        ```
        > export KOKKOS_PATH=*path_to_kokkos_root_directory*
  
        ```
      Example: 
        ```
        > export KOKKOS_PATH=${HOME}/Software/kokkos 

        ```
    - Compile *matrixInverse.cpp* and execute
        ```    
        > make
        > ./matrixInverse.host
        ```
- There are 7 test cases in *matrixInverse.cpp*. The output of each of the test cases will be printed to stdout upon executing *matrixInverse.host*.
- The code has been tested on a machine running CentOS 7.4 . It was compiled with GCC version 4.8.4 and the latest version of [Kokkos](https://github.com/kokkos/kokkos) (cloned from github).

