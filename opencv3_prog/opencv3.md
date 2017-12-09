# OpenCV3.1 programming
general heading
```cpp
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
```
**Mat** assign and construct donnot copy matrix  
clone() and copyTo() will copy matrix data.  

```cpp
// construct random matrix using randu()
Mat r = Mat(10, 3, CV_8UC3);
randu(r, Scalar::all(0), Scalar::all(255));
```
OPENCV use **BGR**.  
#issues
- cannot load jpg image  
