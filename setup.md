# OPENCV  compile and install
cmake   -D CMAKE_BUILD_TYPE=RELEASE   -D CMAKE_INSTALL_PREFIX=/usr/local  -D BUILD_TIFF=ON  -D WITH_TIFF=ON  -D WITH_TBB=ON   -D WITH_V4L=ON   -D WITH_QT=ON   -D WITH_OPENGL=ON   -D WITH_CUDA=ON   -D ENABLE_FAST_MATH=1   -D CUDA_FAST_MATH=1   -D CUDA_NVCC_FLAGS="-D_FORCE_INLINES"   -D WITH_CUBLAS=1 -D WITH_OPENMP=ON ..

make -j8  
sudo make make install  

# QT
## Download
wget http://mirrors.ustc.edu.cn/qtproject/archive/qt/5.6/5.6.2/qt-opensource-linux-x64-5.6.2.run
## install
sudo ./qt-opensource-linux-x64-5.6.2.run
chmod +x qt-opensource-linux-x64-5.6.2.run
## set library path in .bashrc
export LD_LIBRARY_PATH="/home/xd/Qt5.6.2/5.6/gcc_64/lib/:LD_LIBRARY_PATH"
export QT_PLUGIN_PATH=/home/xd/Qt5.6.2/5.6/gcc_64/plugins/platforms

# PCL

sudo apt-get install libpcl-dev   
I had the exact same error after installing from the same source. I finally tracked down the error to a wrong entry in the PCLConfig.cmake file. The PCL_ROOT variable there is beeing set to /usr/local, while the files were actually installed into /usr. Changing this variable resolved the problem for me.

# Ceres
http://ceres-solver.org/installation.html

# g2o
