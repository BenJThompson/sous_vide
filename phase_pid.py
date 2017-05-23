import pylab as plt
import numpy as np
import time

def main():
	nom_freq = 50.0
	nom_V = 230.0
	
	X,Y = get_mains(nom_freq * 0.95, nom_V)

	plt.ion()
	x = 0.75 * (1 / nom_freq * 2.0)
	y = nom_V
	
	graph = plt.plot(X,Y,'-b',x,y,'or')[0]
	
	while True:
		X,Y = get_mains(nom_freq, nom_V)
		#x,y,P,D = get_control()
		draw_plot(graph, X,Y,x,y)
		time.sleep(0.1)
	
def get_mains(nom_freq, nom_V):
	freq = nom_freq - (0.02 * nom_freq) + (np.random.random() * 0.04 * nom_freq)
	half_period = 1.0 / (2.0 * freq)
	V_x = np.linspace(0,half_period,200)
	V_y = nom_V * np.sin(V_x * np.pi / half_period)
	return V_x, V_y


def draw_plot(graph, X,Y,x,y):
    graph.set_data(np.hstack((X,x)),np.hstack((Y,y)))
    plt.draw()


if __name__ == '__main__':
	main()
