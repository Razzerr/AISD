def plotdata():
    import matplotlib.pyplot as plt

    x = range(1, 1000, 1)
    y_merge = [[], [], [], [], []]
    y_insert = [[], [], [], [], []]
    y_quick = [[], [], [], [], []]
    with open('results_for_additional_task.txt', 'r') as f:
        for line in f.readlines():
            linetab = line.split(', ')
            linetab[4] = linetab[4].replace("\n", '')
            if linetab[0] == 'merge':
                y_merge[0] += [float(linetab[2])]
                y_merge[1] += [float(linetab[3])]
                y_merge[2] += [float(linetab[4])]
                y_merge[3] += [float(linetab[2])/float(linetab[1])]
                y_merge[4] += [float(linetab[3])/float(linetab[1])]
            elif linetab[0] == 'insert':
                y_insert[0] += [float(linetab[2])]
                y_insert[1] += [float(linetab[3])]
                y_insert[2] += [float(linetab[4])]
                y_insert[3] += [float(linetab[2]) / float(linetab[1])]
                y_insert[4] += [float(linetab[3]) / float(linetab[1])]
            else:
                y_quick[0] += [float(linetab[2])]
                y_quick[1] += [float(linetab[3])]
                y_quick[2] += [float(linetab[4])]
                y_quick[3] += [float(linetab[2]) / float(linetab[1])]
                y_quick[4] += [float(linetab[3]) / float(linetab[1])]

    fig1 = plt.figure()
    ax1_1 = fig1.add_subplot(111)
    ax1_1.scatter(x, y_insert[0], s=10, c='b', marker="s", label='IS')
    ax1_1.scatter(x, y_merge[0], s=10, c='r', marker="s", label='MS')
    ax1_1.scatter(x, y_quick[0],  s=10, c='g', marker="s", label='QS')

    plt.legend(loc='upper left')
    plt.ylabel('Comparisons [c]')
    plt.xlabel('Data size [n]')

    fig2 = plt.figure()
    ax1_2 = fig2.add_subplot(111)
    ax1_2.scatter(x, y_insert[1], s=10, c='b', marker="s", label='IS')
    ax1_2.scatter(x, y_merge[1], s=10, c='r', marker="s", label='MS')
    ax1_2.scatter(x, y_quick[1],  s=10, c='g', marker="s", label='QS')

    plt.legend(loc='upper left')
    plt.ylabel('Switches [s]')
    plt.xlabel('Data size [n]')

    fig3 = plt.figure()
    ax1_3 = fig3.add_subplot(111)
    ax1_3.scatter(x, y_insert[2], s=10, c='b', marker="s", label='IS')
    ax1_3.scatter(x, y_merge[2], s=10, c='r', marker="s", label='MS')
    ax1_3.scatter(x, y_quick[2],  s=10, c='g', marker="s", label='QS')

    plt.legend(loc='upper left')
    plt.ylabel('Time [t]')
    plt.xlabel('Data size [n]')

    fig4 = plt.figure()
    ax1_4 = fig4.add_subplot(111)
    ax1_4.scatter(x, y_insert[3], s=10, c='b', marker="s", label='IS')
    ax1_4.scatter(x, y_merge[3], s=10, c='r', marker="s", label='MS')
    ax1_4.scatter(x, y_quick[3],  s=10, c='g', marker="s", label='QS')

    plt.legend(loc='upper left')
    plt.ylabel('Comparisons/Time [c/t]')
    plt.xlabel('Data size [n]')

    fig5 = plt.figure()
    ax1_5 = fig5.add_subplot(111)
    ax1_5.scatter(x, y_insert[4], s=10, c='b', marker="s", label='IS')
    ax1_5.scatter(x, y_merge[4], s=10, c='r', marker="s", label='MS')
    ax1_5.scatter(x, y_quick[4],  s=10, c='g', marker="s", label='QS')

    plt.legend(loc='upper left')
    plt.ylabel('Switches/Time [c/t]')
    plt.xlabel('Data size [n]')

    plt.show()

plotdata()