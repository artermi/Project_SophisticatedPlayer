import os
import numpy as np
import scipy.misc as smp
from PIL import Image

# Create a 1024x1024x3 array of 8 bit unsigned integers


for root,dirs,files in sorted(os.walk('raw',topdown = False)):
	for name in sorted(files):
		data = np.zeros( (400,400,3), dtype=np.uint8 )
		with open(os.path.join(root, name)) as file:
			for line in file:
				loc, typ = line.split()
				tx,ty = loc[1:-1].split(',')
				x,y = int(tx),int(ty)
				#y = (y+100) % 400
				x*=2
				y*=2
				if typ == '5':
					data[x,y] = [255, 255, 255]
					data[x+1,y] = [255, 255, 255]
					data[x,y+1] = [255, 255, 255]
					data[x+1,y+1] = [255, 255, 255]

				if typ == '0':
					data[x,y] = [231, 76, 60]
					data[x+1,y] = [231, 76, 60]
					data[x,y+1] = [231, 76, 60]
					data[x+1,y+1] = [231, 76, 60]
				if typ == '1':
					data[x,y] = [46, 204, 113]
					data[x+1,y] = [46, 204, 113]
					data[x,y+1] = [46, 204, 113]
					data[x+1,y+1] = [46, 204, 113]
				if typ == '2':
					data[x,y] = [245, 183, 177]
					data[x+1,y] = [245, 183, 177]
					data[x,y+1] = [245, 183, 177]
					data[x+1,y+1] = [245, 183, 177]	
				if typ == '3':
					data[x,y] = [171, 235, 198]
					data[x+1,y] = [171, 235, 198]
					data[x,y+1] = [171, 235, 198]
					data[x+1,y+1] = [171, 235, 198]					

			image = Image.fromarray(data)
			image.save(name.split('.')[0] + '.png')                      # View in default viewer
