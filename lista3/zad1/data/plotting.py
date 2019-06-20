def plotdata():
    import matplotlib.pyplot as plt

    x = [10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000]
    y_merge = [[], [], [], []]
    y_insert = [[], [], [], []]
    y_quick = [[], [], [], []]
    y_radix = [[], [], [], []]
    with open('data1.txt', 'r') as f:
        for line in f.readlines():
            linetab = line.split(', ')
            print(linetab)
            linetab[5] = linetab[5].replace("\n", '')
            if linetab[0] == 'merge':
                y_merge[0] += [float(linetab[2])]
                y_merge[1] += [float(linetab[3])]
                y_merge[2] += [float(linetab[4])]
                y_merge[3] += [float(linetab[5])]
            elif linetab[0] == 'insert':
                y_insert[0] += [float(linetab[2])]
                y_insert[1] += [float(linetab[3])]
                y_insert[2] += [float(linetab[4])]
                y_insert[3] += [float(linetab[5])]
            elif linetab[0] == 'quick':
                y_quick[0] += [float(linetab[2])]
                y_quick[1] += [float(linetab[3])]
                y_quick[2] += [float(linetab[4])]
                y_quick[3] += [float(linetab[5])]
            else:
                y_radix[0] += [float(linetab[2])]
                y_radix[1] += [float(linetab[3])]
                y_radix[2] += [float(linetab[4])]
                y_radix[3] += [float(linetab[5])]

    fig1 = plt.figure()
    ax1_1 = fig1.add_subplot(111)
    ax1_1.plot(x, y_insert[0], c='b', marker="s", label='IS')
    ax1_1.plot(x, y_merge[0], c='r', marker="s", label='MS')
    ax1_1.plot(x, y_quick[0],  c='g', marker="s", label='QS')
    ax1_1.plot(x, y_radix[0],  c='y', marker="s", label='RS')

    plt.legend(loc='upper left')
    plt.ylabel('Comparisons [c]')
    plt.xlabel('Data size [n]')

    fig2 = plt.figure()
    ax1_2 = fig2.add_subplot(111)
    ax1_2.plot(x, y_insert[1], c='b', marker="s", label='IS')
    ax1_2.plot(x, y_merge[1], c='r', marker="s", label='MS')
    ax1_2.plot(x, y_quick[1],  c='g', marker="s", label='QS')
    ax1_2.plot(x, y_radix[1],  c='y', marker="s", label='RS')

    plt.legend(loc='upper left')
    plt.ylabel('Switches [s]')
    plt.xlabel('Data size [n]')

    fig3 = plt.figure()
    ax1_3 = fig3.add_subplot(111)
    ax1_3.plot(x, y_insert[2], c='b', marker="s", label='IS')
    ax1_3.plot(x, y_merge[2], c='r', marker="s", label='MS')
    ax1_3.plot(x, y_quick[2],  c='g', marker="s", label='QS')
    ax1_3.plot(x, y_radix[2],  c='y', marker="s", label='RS')

    plt.legend(loc='upper left')
    plt.ylabel('Time [t]')
    plt.xlabel('Data size [n]')

    fig4 = plt.figure()
    ax1_4 = fig4.add_subplot(111)
    ax1_4.plot(x, y_insert[3], c='b', marker="s", label='IS')
    ax1_4.plot(x, y_merge[3], c='r', marker="s", label='MS')
    ax1_4.plot(x, y_quick[3],  c='g', marker="s", label='QS')
    ax1_4.plot(x, y_radix[3],  c='y', marker="s", label='RS')

    plt.legend(loc='upper left')
    plt.ylabel('Total memory usage')
    plt.xlabel('Data size [n]')

    plt.show()

plotdata()