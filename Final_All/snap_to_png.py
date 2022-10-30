import os
import sys
import numpy as np
import scipy.misc as smp
from PIL import Image

# Create a 1024x1024x3 array of 8 bit unsigned integers
def main():
	name = sys.argv[1]
	data = []

	pixsize = 4
	row = 100
	data = np.zeros( (pixsize * row,pixsize * row,3), dtype=np.uint8 ) #
	with open(name) as file:
		for line in file:
			loc, typ = line.split()
			tx,ty = loc[1:-1].split(',')
			x,y = int(tx),int(ty)
			if x >= 100 or y >= 100:
				continue

			#y = (y+100) % 400
			x*= pixsize
			y*= pixsize
			if typ == '5':
				for i in range(pixsize):
					for j in range(pixsize):
						data[x +i,y+j] = [255, 255, 255]
			if typ == '0':
				for i in range(pixsize):
					for j in range(pixsize):
						data[x+i,y+j] = [203, 67, 53]
			if typ == '1':
				for i in range(pixsize):
					for j in range(pixsize):
						data[x+i,y+j] = [40, 116, 166]
			if typ == '2':
				for i in range(pixsize):
					for j in range(pixsize):
						data[x+i,y+j] = [250,128,114]	
			if typ == '3':
				for i in range(pixsize):
					for j in range(pixsize):
						data[x+i,y+j] = [133,193,233]					

		image = Image.fromarray(data)
		print(name.split('.')[0])
		image.save(name.split('.')[0] + '.png') 

if __name__ == '__main__':
	main()