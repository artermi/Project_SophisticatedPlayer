import os
import numpy as np

def caculate_one(name,length):
	pixsize = 1
	matrix = np.zeros( (length, length)) #
	corr = 0
	with open(name) as file:
		for line in file:
			loc, typ = line.split()
			tx,ty = loc[1:-1].split(',')
			x,y = int(tx),int(ty)
			matrix[x,y] = typ
		# when typ == 5, means empty


		for i in range(length):
			for j in range(length):
				t2 = max(matrix[i,j],matrix[i, (j+1) % length])
				if t2 != 5:
					corr += 1

				t2 = max(matrix[i,j],matrix[(i+1) % length,j])
				if t2 != 5:
					corr += 1

	return corr

def main():
	for root,dirs,files in sorted(os.walk('.',topdown = False)):
		arrays = []
		length = 400
		for name in sorted(files):
			arrays.append(caculate_one(name,length))

		for ele in arrays:
			print(ele/(2*length *length), end = ' ')
		

if __name__ == '__main__':
	main()
