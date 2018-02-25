# OpenCV3.1 programming
general heading

```cpp
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
```

### Mat
assign and construct donnot copy matrix  
clone() and copyTo() will copy matrix data.  

```cpp
// construct random matrix using randu()
Mat r = Mat(10, 3, CV_8UC3);
randu(r, Scalar::all(0), Scalar::all(255));
```
OPENCV use **BGR**.  
randu()函数可以初始化矩阵
### 点的表示
Point_<int> = Point2i = Point
Point_<float> = float2f
### 颜色的表示
Scalar(b,g,r)
### 矩阵的表示
```cpp
Rect rect = rect1 & rect2; \\矩阵的交集
Rect rect = rect1 | rect2; \\矩阵的并集
```
计时函数

```cpp
double time0 = static_cast<double>(getTickCount());
// run
time0 = ((double)getTickCount() - time0) / getTickFrequency();
```

分离通道：split()
合并通道：merge()

DFT
对于图像，高频部分代表图像的细节、纹理信息；低频部分代表了图像了轮廓信息。
DFT可以做图像增强，去噪，边缘检测，特征提取，压缩。

向下取偶数操作，整数以补码的形式存储：
(-5 & -2) == -6; (101 & -2) == 100;

中值滤波，去除脉冲噪声，椒盐噪声(椒噪声：高灰度噪声，盐噪声：低灰度噪声),保护边缘信息。
- 优点：不太受噪声影响
- 缺点：运算多，不适合细节多（尖、细）的图像

#issues
- cannot load jpg image  
