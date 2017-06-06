import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import time



def main():
	nom_f = 50.0
	rms_V = 230.0
	V = 230.0 / 0.707
	t_y = V * abs(np.sin(0.25 * np.pi))
	
	half_period = 1.0 / (2 * nom_f)
	timer_period = (1.0/(55.0))/2.0
	ref_period = (1.0/(55.0))/2.0
	error = 0.0
	I_err = 0.0
	a_x = 1.75*half_period
	a_y = V * abs(np.sin(a_x * np.pi / half_period))
	b_x = [a_x - ref_period / 20, a_x + ref_period / 20]
	b_y = [V * abs(np.sin(b_x[0] * np.pi / half_period)),
			V * abs(np.sin(b_x[1] * np.pi / half_period))]
	l_y = a_y
	
	plt.ion()
	fig, ax = plt.subplots()
	ax.plot([], [], '-b', [], [], 'or', [], [], 'xr')
	ax.set_xlim(0.0,(1.0/nom_f) * 1.5 )
	ax.set_ylim(0.0,V * 1.5 )
	
	v_x,v_y = get_mains(nom_f, V)
	
	while True:
		
		#v_x,v_y, half_period, last_half_period = get_mains(nom_f, V, half_period)
		#t_x = get_target(half_period, V)
		#a_x,a_y,timer_period,error,i_err = get_actual(t_y, a_x, a_y, V, timer_period, error, i_err, P, I, D, half_period, last_half_period)
		a_x,a_y,l_x,l_y,b_x,b_y,timer_period,I_err = get_actual(l_y,a_x, a_y,b_x,b_y, V, timer_period, half_period, ref_period, I_err)
		
		ax.lines[0].set_data(v_x,v_y)
		ax.lines[1].set_data([a_x,l_x],[a_y,l_y])
		ax.lines[2].set_data(b_x,b_y)
		
		draw_plot()
		
		

		
def get_mains(nom_f, V):
	#freq = nom_f - (0.02 * nom_f) + (np.random.random() * 0.01 * nom_f)
	freq = nom_f
	half_period = 1.0 / (2.0 * freq)
	V_x = np.linspace(0,3.0 * half_period,300)
	V_y = V * abs(np.sin(V_x * np.pi / half_period))
	return V_x, V_y
	
def get_target(half_period, V):
	x = 0.25 * half_period
	return x

def get_actual(l_y,a_x, a_y, b_x, b_y, V, last_timer_period, half_period, ref_period, I_err):
	P_err = 0.000001 * a_y 
	#I_err += 0.0000001 * a_y
	D_err = 0.00001 * (l_y - a_y)
	error = P_err + I_err + D_err
	l_x = a_x - half_period
	l_y = a_y
	if (l_y > b_y[1]):
		timer_period = last_timer_period + error
	elif (l_y > b_y[0]):
		timer_period = last_timer_period - error
	else:
		timer_period = last_timer_period
	if (timer_period > ref_period * 1.5) or (timer_period < ref_period * 0.5):
		timer_period = ref_period
		print "period reset to ref"
	a_x = l_x + timer_period
	### hile a_x > TODO
	a_y = V * abs(np.sin(a_x * np.pi / half_period))
	b_x = [a_x - ref_period / 50, a_x + ref_period / 50]
	b_y = [V * abs(np.sin(b_x[0] * np.pi / half_period)),
			V * abs(np.sin(b_x[1] * np.pi / half_period))]
	print "a: ",a_x,a_y,"l: ",l_x,l_y,"b: ",b_x,b_y
	return a_x,a_y,l_x,l_y,b_x,b_y,timer_period,I_err
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
    plt.pause(0.1)
    

if __name__ == '__main__':
	main()
	
