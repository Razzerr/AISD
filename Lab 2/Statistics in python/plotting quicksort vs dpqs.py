import math


def plotdata():
    import matplotlib.pyplot as plt

    x = range(100, 10001, 100)
    y_quick = [[], [], [], [], []]
    y_dpqs = [[], [], [], [], []]
    with open('dpqs_vs_qs_k_1000.txt', 'r') as f:
        for line in f.readlines():
            linetab = line.split(', ')
            linetab[4] = linetab[4].replace("\n", '')
            if linetab[0] == 'dpqs':
                y_dpqs[0] += [float(linetab[2])]
                y_dpqs[1] += [float(linetab[3])]
                y_dpqs[2] += [float(linetab[4])]
                y_dpqs[3] += [float(linetab[2])/float(linetab[1])]
                y_dpqs[4] += [float(linetab[3])/float(linetab[1])]
            else:
                y_quick[0] += [float(linetab[2])]
                y_quick[1] += [float(linetab[3])]
                y_quick[2] += [float(linetab[4])]
                y_quick[3] += [float(linetab[2]) / float(linetab[1])]
                y_quick[4] += [float(linetab[3]) / float(linetab[1])]

    def nlogntest():
        avg_c=0
        for i in range(0, 100):
            n=(i+1)*100
            avg_c += y_dpqs[0][i]/(n*math.log(n, 3))
        print(avg_c/100)
    nlogntest()

    fig1 = plt.figure()
    ax1_1 = fig1.add_subplot(111)
    ax1_1.scatter(x, y_dpqs[0], s=10, c='r', marker="s", label='DPQS')
    ax1_1.scatter(x, y_quick[0],  s=10, c='g', marker="s", label='QS')

    plt.legend(loc='upper left')
    plt.ylabel('Comparisons [c]')
    plt.xlabel('Data size [n]')

    fig2 = plt.figure()
    ax1_2 = fig2.add_subplot(111)
    ax1_2.scatter(x, y_dpqs[1], s=10, c='r', marker="s", label='DPQS')
    ax1_2.scatter(x, y_quick[1],  s=10, c='g', marker="s", label='QS')

    plt.legend(loc='upper left')
    plt.ylabel('Switches [s]')
    plt.xlabel('Data size [n]')

    fig3 = plt.figure()
    ax1_3 = fig3.add_subplot(111)
    ax1_3.scatter(x, y_dpqs[2], s=10, c='r', marker="s", label='DPQS')
    ax1_3.scatter(x, y_quick[2],  s=10, c='g', marker="s", label='QS')

    plt.legend(loc='upper left')
    plt.ylabel('Time [t]')
    plt.xlabel('Data size [n]')

    fig4 = plt.figure()
    ax1_4 = fig4.add_subplot(111)
    ax1_4.scatter(x, y_dpqs[3], s=10, c='r', marker="s", label='DPQS')
    ax1_4.scatter(x, y_quick[3],  s=10, c='g', marker="s", label='QS')

    plt.legend(loc='upper left')
    plt.ylabel('Comparisons/Time [c/t]')
    plt.xlabel('Data size [n]')

    fig5 = plt.figure()
    ax1_5 = fig5.add_subplot(111)
    ax1_5.scatter(x, y_dpqs[4], s=10, c='r', marker="s", label='DPQS')
    ax1_5.scatter(x, y_quick[4],  s=10, c='g', marker="s", label='QS')

    plt.legend(loc='upper left')
    plt.ylabel('Switches/Time [c/t]')
    plt.xlabel('Data size [n]')

    plt.show()

plotdata()