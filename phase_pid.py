import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import time



def main():
	nom_f = 50.0
	rms_V = 230.0
	V = 230.0 / 0.707
	t_y = V * np.sin(0.25 * np.pi)
	
	initial_guess = 1.0/55.0
	half_period = 1.0 / (2.0 * nom_f)
	
	plt.ion()
	fig, ax = plt.subplots()	
	ax.plot([], [], '-b', [], [], 'og', [], [], 'or')
	ax.set_xlim(0.0,(1.0/nom_f) * 0.5 * 1.1)
	ax.set_ylim(0.0,V * 2.0 )
	
	while True:
		
		v_x,v_y, half_period, last_half_period = get_mains(nom_f, V, half_period)
		t_x = get_target(half_period, V)
		a_x,a_y = get_actual(t_y, a_y, timer_period, P, I, D)
		
		ax.lines[0].set_data(v_x,v_y)
		ax.lines[1].set_data(t_x,t_y)
		ax.lines[2].set_data(a_x,a_y)
		
		draw_plot()
		
		

		
def get_mains(nom_f, V, last_half_period):
	freq = nom_f - (0.02 * nom_f) + (np.random.random() * 0.04 * nom_f)
	half_period = 1.0 / (2.0 * freq)
	V_x = np.linspace(0,half_period,100)
	V_y = V * np.sin(V_x * np.pi / half_period)
	return V_x, V_y, half_period, last_half_period
	
def get_target(half_period, V):
	x = 0.25 * half_period
	return x,y

def get_actual(t_y):
	error = t_y - a_y
	x = 0.25 * (1 / (nom_f * 2.0))
	y = V
	return x,y

def draw_plot():
    plt.draw()
    plt.pause(0.01)
    

if __name__ == '__main__':
	main()
	
