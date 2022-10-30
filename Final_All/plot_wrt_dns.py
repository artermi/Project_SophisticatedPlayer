import sys
import os
import matplotlib.pyplot as plt
from labellines import labelLines
plt.rcParams["font.family"] = "Times New Roman"
plt.rcParams.update({'font.size': 18})

def read_dir(DName):
	rate = []
	coor = []
	fd = []
	fc = []
	sd = []
	sc = []


	for root,dirs,files in sorted(os.walk(DName,topdown = False)):
		for name in sorted(files):
			if name.find('.dat') < 0 or name.find('SNAP') >= 0:
				continue
			r = float(name[10:14])/1000
			dns = float(name[4:7])/100
			if dns != float(sys.argv[1]):
				continue
			avg_am = 10
			nmbs = [0,0.0,0.0,0.0,0.0]
			len_file = sum(1 for line in open(os.path.join(root, name)))

			with open(os.path.join(root, name)) as file:				
				for ind, line in enumerate(file):
					if ind >= len_file - avg_am:
						ele = line.split()
						for k in range(4):
							nmbs[k+1] += float(ele[k+1])
							
				for i in range(4):
					nmbs[i+1] /= float(avg_am)

				rate.append(r)
				coor.append(float(nmbs[2])  + float(nmbs[4]) )
				fd.append( float(nmbs[1]) )
				fc.append( float(nmbs[2]) )
				sd.append( float(nmbs[3]) ) 
				sc.append( float(nmbs[4]) ) 

	return rate, coor

def main():

	rate_1, coor_1 = read_dir('./DTA')
	rate_2, coor_2 = read_dir('./DTA_two')


	ax = plt.subplot(111)
	box = ax.get_position()
	ax.plot(rate_1, coor_1, color='#2874a6', marker= '.',label = '"4"')
	ax.text(4.7,0.85,'"4"')
	ax.plot(rate_2, coor_2, color='#cb4335', marker= '.',label = '"2"')
	ax.text(4.7,0.5,'"2"')
	ax.set_position([box.x0, box.y0 + box.height * 0.05, box.width, box.height])	
#	ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.15), fancybox=True, shadow=True, ncol=2)

	xvals = [3.5,3.25]
#	labelLines(ax.get_lines(), zorder=2.5, align=False,xvals = xvals)


	plt.xlabel('synergy, $r$')
	plt.ylabel('Fractions')
	plt.ylim([-0.1, 1.1])	
	#plt.grid(True)
	plt.show()

if __name__ == '__main__':
	main()