import sys
import numpy as np
import matplotlib.pyplot as plt
plt.rcParams["font.family"] = "Times New Roman"
plt.rcParams.update({'font.size': 18})

def main():
	file = sys.argv[1]
	data = []
	with open(file) as f:
		for line in f:
			data = [float(x) for x in line.split()]
			break

	b_min, b_max = min(data), max(data)
	#fine = 25
	#bins_ = [b_min + (b_max-b_min)/fine * float(i) for i in range(fine + 1)]
	plt.hist(data)#,bins = bins_)
	plt.show()

if __name__ == '__main__':
	main()