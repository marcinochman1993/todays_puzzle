
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider

Nzc = 839

def zadoff_chu(u, cs):
    n = np.arange(0, Nzc)
    n_mod = np.mod(n-cs, Nzc)

    return np.exp(-1j*np.pi*u*n_mod*(n_mod+1) / Nzc)

def correlete_sequence(u, cs):
    root_sequence = zadoff_chu(u, 0)
    prach_sequence = zadoff_chu(u, cs)

    root_sequence_fft = np.fft.fft(root_sequence)
    prach_sequence_fft = np.fft.fft(prach_sequence)
    correleted = np.fft.ifft(prach_sequence_fft*np.conj(root_sequence_fft))
    abs_correleted = np.abs(correleted)

    return (abs_correleted/np.max(correleted))**2


def plot_prach(u, cs):
    fig, _ = plt.subplots()
    pdp = correlete_sequence(u, cs)
    l, = plt.plot(pdp)
    plt.grid()
    plt.xlim([-5, Nzc+1])
    plt.title('PDP u:{}'.format(u))
    ax_cs = plt.axes([0.1, 0.1, 0.8, 0.03])
    cs_slider = Slider(ax_cs, 'cs', 0, 838, valfmt='%0.0f', valinit=cs)

    def update(new_cs):
        new_cs = np.round(new_cs)
        pdp = correlete_sequence(u, new_cs)
        l.set_ydata(pdp)
        fig.canvas.draw_idle()


    cs_slider.on_changed(update)
    plt.subplots_adjust(bottom=0.25)

    plt.show()


if __name__ == "__main__":
    root_sequence = 309
    cs = 0
    plot_prach(root_sequence, cs)
