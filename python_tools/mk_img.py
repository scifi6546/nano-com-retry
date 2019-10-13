from PIL import Image
import math
import sys
im = Image.open(sys.argv[1]+".png")
data = []
pixel_colors = []
for i in im.getdata():
    data.append(i)
    found = False
    for j in pixel_colors:
        if(i==j):
            found = True
    if(found==False):
        pixel_colors.append(i)
img = []
for i in data:
    for j in range(0,len(pixel_colors)):
        if(i==pixel_colors[j]):
            img.append(j)
#print(len(data))
print("const char " + sys.argv[1] + "[]=")
print("{")
for i in img:
    print(str(i)+",",end="")
print("};")

