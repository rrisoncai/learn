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
#issues
- cannot load jpg image  
