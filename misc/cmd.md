# Linux  
image format convert
```
convert p1.jpg p2.png
```
# LaTex

lie algebra: $a^\wedge$, $a^\vee$

# Read binary file into float buffer
```cpp
FILE* fp;
float f;
fp = fopen("data.bin", "rb");           // read file in binary mode
fseek(fp,0,SEEK_END);                   // jump to the end of file
long filelen = ftell(fp);               // get current byte offset in file
rewind(fp);                             // jump back to begin of file

float *buf = (float*)malloc((filelen)*sizeof(float));
fread(buf,filelen,4,fp);                // read the entire file
```
