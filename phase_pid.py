import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import time



def main():
	nom_f = 50.0
	rms_V = 230.0
	V = 230.0 / 0.707
	t_y = V * np.sin(0.25 * np.pi)
	P = 0.5
	I = 0.0000
	D = 0.0000
	
	timer_period = 0
	error = 0.0
	i_err = 0.0
	half_period = 1.0 / (2.0 * nom_f)
	a_x = 0.75*half_period
	a_y = V * np.sin(a_x * np.pi / half_period)
	
	plt.ion()
	fig, ax = plt.subplots()	
	ax.plot([], [], '-b', [], [], 'og', [], [], 'or')
	ax.set_xlim(0.0,(1.0/nom_f) * 0.5 * 1.1)
	ax.set_ylim(0.0,V * 2.0 )
	
	while True:
		
		v_x,v_y, half_period, last_half_period = get_mains(nom_f, V, half_period)
		t_x = get_target(half_period, V)
		#a_x,a_y,timer_period,error,i_err = get_actual(t_y, a_x, a_y, V, timer_period, error, i_err, P, I, D, half_period, last_half_period)
		a_x,a_y,timer_period,error = get_actual(t_y, a_x, a_y, V, timer_period, half_period, last_half_period)
		
		ax.lines[0].set_data(v_x,v_y)
		ax.lines[1].set_data(t_x,t_y)
		ax.lines[2].set_data(a_x,a_y)
		
		draw_plot()
		
		

		
def get_mains(nom_f, V, last_half_period):
	freq = nom_f - (0.02 * nom_f) + (np.random.random() * 0.01 * nom_f)
	half_period = 1.0 / (2.0 * freq)
	V_x = np.linspace(0,half_period,100)
	V_y = V * np.sin(V_x * np.pi / half_period)
	return V_x, V_y, half_period, last_half_period
	
def get_target(half_period, V):
	x = 0.25 * half_period
	return x

def get_actual(t_y,last_a_x, last_a_y, V, last_timer_period, half_period, last_half_period):
	error = t_y - last_a_y
	timer_period = last_timer_period + (0.000001 * error)
	print timer_period
	a_x = last_half_period - last_a_x + timer_period
	while (a_x < 0):
		a_x += half_period
	if (a_x > half_period):
		a_x %= half_period
	a_y = V * np.sin(a_x * np.pi / half_period)
	return a_x,a_y,timer_period,error
'''	
def get_actual(t_y,last_a_x, last_a_y, V, last_timer_period, last_error, i_err, P, I, D, half_period, last_half_period):
	error = t_y - last_a_y
	p_err = P * error
	i_err += I * error + i_err
	d_err = D * (error-last_error)
	timer_period = last_timer_period - (p_err + i_err + d_err)
	print timer_period
	a_x = last_half_period - last_a_x + timer_period
	while (a_x < 0):
		a_x += half_period
	if (a_x > half_period):
		a_x %= half_period
	a_y = V * np.sin(a_x * np.pi / half_period)
	return a_x,a_y,timer_period,error,i_err
'''
def draw_plot():
    plt.draw()
    plt.pause(0.01)
    

if __name__ == '__main__':
	main()
	
