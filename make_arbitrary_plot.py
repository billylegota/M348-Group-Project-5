import matplotlib.pyplot as plt
import numpy as np


def main():
    data = np.loadtxt('output.txt', delimiter=',')
    t = data[:, 0]
    y = data[:, 1:]

    plt.figure()
    plt.plot(t, y)
    plt.title('Component-wise Solution Plot')
    plt.xlabel('$t$')
    plt.ylabel('$y$')
    plt.legend([f'$y_{i}$' for i in range(1, data.shape[1])])
    plt.grid(True)
    plt.show()


if __name__ == '__main__':
    main()
