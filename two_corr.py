import os
import numpy as np

def caculate_one(name,length):
	pixsize = 1
	matrix = np.zeros( (length, length)) #
	corr_matrix = np.zeros((4,4),)
	with open(name) as file:
		for line in file:
			loc, typ = line.split()
			tx,ty = loc[1:-1].split(',')
			x,y = int(tx),int(ty)
			matrix[x,y] = typ
		# when typ == 5, means empty


		for i in range(length):
			for j in range(length):
				t1 = min(matrix[i,j],matrix[i, (j+1) % length])
				t2 = max(matrix[i,j],matrix[i, (j+1) % length])
				if t2 != 5:
					corr_matrix[int(t1),int(t2)] += 1

				t1 = min(matrix[i,j],matrix[(i+1) % length,j])
				t2 = max(matrix[i,j],matrix[(i+1) % length,j])
				if t2 != 5:
					corr_matrix[int(t1),int(t2)] += 1

	return corr_matrix

def main():
	for root,dirs,files in sorted(os.walk('.',topdown = False)):
		arrays = []
		for name in sorted(files):
			length = 400
			arrays.append(caculate_one(name,length))

		all_num = np.mean( np.array(arrays), axis=0 )
		Type = ['FD','FC','SD', 'SC']
		for i in range(4):
			for j in range(i+1):
				print( 'Player{},{}:'.format(Type[j],Type[i]), float(all_num[j,i])/ (2 * length * length) )

	print(all_num.sum()/(2 * length * length))

if __name__ == '__main__':
	main()
