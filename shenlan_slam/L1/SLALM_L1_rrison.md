# Lecture 1
## 2.1 安装软件
```
sudo apt-get install <var>
```
安装路径一般在/usr/share  
## 2.2 环境变量
环境变量是PATH；  
添加环境变量：export PATH = <var>:$PATH  
## 2.3 根目录的目录结构
- /home 用户目录;
- /dev 系统设备文件;
- /etc 系统配置文件；
- /sbin 系统管理命令  

## 2.4 给a.sh添加可执行权限：
```
chmod +x a.sh
```  
## 2.5 修改所有者：
```
chmown xiang:xiang a.sh
```
## 3.1 应用场景
- 自动驾驶
- 3D重建
- 增强现实
- 无人机建图，定位

## 3.2 定位与建图的关系
准确的定位需要精确的地图，精确的地图来自于准确的定位  
因为只有建立好地图才能更好的定位  
## 3.3 SLAM发展历程
- 史前时期 根据已知地图来定位
- EKF主流 1990-2005，用EKF模型求解SLAM  
- BA转型时期 2006 - 2010
- 前沿研究，更多的传感器，更复杂的环境-

## 3.4 经典文献
- D. Scaramuzza, F. Fraundorfer, "Visual Odometry: Part I - The First 30 Years and Fundamentals IEEE Robotics and Automation Magazine", Volume 18, issue 4, 2011.
- F. Fraundorfer and D. Scaramuzza, "Visual Odometry : Part II: Matching, Robustness, Optimization, and Applications," in IEEE Robotics & Automation Magazine, vol. 19, no. 2, pp. 78-90, June 2012.
- Stephan Weiss and Roland Siegwart. Real-Time Metric State Estimation for Modular Vision-Inertial Systems. in IEEE International Conference on Robotics and Automation (ICRA), 2011.
- Dorian Gálvez-López and Juan D. Tardós. Bags of Binary Words for Fast Place Recognition in Image Sequences. IEEE Transactions on Robotics, vol. 28, no. 5, pp. 1188-1197, 2012.
