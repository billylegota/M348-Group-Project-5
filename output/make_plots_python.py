import matplotlib.pyplot as plt
import numpy as np
import scipy.integrate


def f(t, y):
    _ = t

    a = 2
    b = 0.01
    c = 1
    d = 0.01

    return np.array([
        a * y[0] - b * y[0] * y[1],
        -c * y[1] + d * y[0] * y[1]
    ])


def solve(x0, y0, t0, t1, n):
    solution = scipy.integrate.solve_ivp(f, (t0, t1), (x0, y0), t_eval=np.linspace(t0, t1, n))
    return solution.t, solution.y.T


def main():
    t, y = solve(1000, 560, 0, 10, 100000)

    # Time domain plot.
    plt.figure()
    plt.plot(t, y)
    plt.title('Predator and Prey Population vs Time')
    plt.xlabel('Time')
    plt.ylabel('Population (tens of thousands)')
    plt.legend(['Prey', 'Predator'])
    plt.grid(True)

    # Predator-prey domain plot.
    plt.figure()
    plt.plot(y[:, 0], y[:, 1], zorder=2)
    plt.scatter(y[0, 0], y[0, 1], c='r', zorder=3)
    plt.title('Predator vs Prey Population')
    plt.xlabel('Prey Population')
    plt.ylabel('Predator Population')
    plt.grid(True)
    plt.show()


if __name__ == '__main__':
    main()
