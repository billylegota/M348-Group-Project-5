import os
import glob

import matplotlib.pyplot as plt
import numpy as np


def make_plot(path: str) -> tuple:
    data = np.loadtxt(path, delimiter=',')
    t = data[:, 0]
    y = data[:, 1:]

    # Time domain plot.
    plt.figure()
    plt.plot(t, y)
    plt.title('Predator and Prey Population vs Time')
    plt.xlabel('Time')
    plt.ylabel('Population (tens of thousands)')
    plt.legend(['Prey', 'Predator'])
    plt.grid(True)
    plt.savefig(os.path.basename(path)[:-4] + '_time.png', dpi=1200)
    plt.close(plt.gcf())

    # Predator-prey domain plot.
    plt.figure()
    plt.plot(y[:, 0], y[:, 1], zorder=2)
    plt.scatter(y[0, 0], y[0, 1], c='r', zorder=3)
    plt.title('Predator vs Prey Population')
    plt.xlabel('Prey Population')
    plt.ylabel('Predator Population')
    plt.grid(True)
    plt.savefig(os.path.basename(path)[:-4] + '_orbit.png', dpi=1200)

    # Save the predator and prey values.
    predator, prey = y[:, 0], y[:, 1]

    # Predator-prey domain plot width vector field.
    x, y = np.meshgrid(
        np.linspace(*plt.gca().get_xlim(), 50),
        np.linspace(*plt.gca().get_ylim(), 50)
    )
    plt.xlim(plt.gca().get_xlim())
    plt.ylim(plt.gca().get_ylim())

    a = 2
    b = 0.01
    c = 1
    d = 0.01

    u = a * x - b * x * y
    v = -c * y + d * x * y

    norm = np.sqrt(u ** 2 + v ** 2)
    u /= norm
    v /= norm

    plt.quiver(x, y, u, v, headwidth=1, headaxislength=5, zorder=1)
    plt.savefig(os.path.basename(path)[:-4] + '_orbit_vector.png', dpi=1200)
    plt.close(plt.gcf())

    return predator, prey


def main():
    labels = []
    orbits = []
    for path in glob.glob('*.txt'):
        labels.append(os.path.basename(path)[:-4].replace('_', ' '))
        orbits.append(make_plot(path))

    plt.figure()
    for prey, predator in orbits:
        plt.plot(prey, predator, zorder=2)
        plt.scatter(prey[0], predator[0], c='r', zorder=3)

    plt.title('Predator vs Prey Population')
    plt.xlabel('Prey Population')
    plt.ylabel('Predator Population')
    plt.grid(True)
    plt.legend(labels, prop={'size': 6})
    plt.savefig('all_orbits.png', dpi=1200)

    # Make vector plot.
    x, y = np.meshgrid(
        np.linspace(*plt.gca().get_xlim(), 50),
        np.linspace(*plt.gca().get_ylim(), 50)
    )
    plt.xlim(plt.gca().get_xlim())
    plt.ylim(plt.gca().get_ylim())

    a = 2
    b = 0.01
    c = 1
    d = 0.01

    u = a * x - b * x * y
    v = -c * y + d * x * y

    norm = np.sqrt(u ** 2 + v ** 2)
    u /= norm
    v /= norm

    plt.quiver(x, y, u, v, headwidth=1, headaxislength=5, zorder=1)
    plt.savefig('all_orbits_vector.png', dpi=1200)
    plt.close(plt.gcf())


if __name__ == '__main__':
    main()
