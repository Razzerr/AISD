def plotdata():
    import matplotlib.pyplot as plt
    import numpy as np

    x = range(10, 10000, 10)
    y_S = [[], [], [], []]
    y_R = [[], [], [], []]

    with open('data.txt', 'r') as f:
        for line in f.readlines():
            linetab = line.split(', ')
            linetab[5] = linetab[5].replace("\n", '')
            if linetab[0] == 'S':
                y_S[0] += [float(linetab[2])]
                y_S[1] += [float(linetab[3])]
                y_S[2] += [float(linetab[4])]
                y_S[3] += [float(linetab[5])]
            elif linetab[0] == 'R':
                y_R[0] += [float(linetab[2])]
                y_R[1] += [float(linetab[3])]
                y_R[2] += [float(linetab[4])]
                y_R[3] += [float(linetab[5])]

    fig1 = plt.figure()
    ax1_1 = fig1.add_subplot(111)
    ax1_1.scatter(x, y_S[0], c='b', marker="s", label='Select')
    ax1_1.scatter(x, y_R[0], c='r', marker="s", label='Random')
    ax1_1.plot(x, np.poly1d(np.polyfit(x, y_S[0], 1))(x))
    ax1_1.plot(x, np.poly1d(np.polyfit(x, y_R[0], 1))(x))

    plt.legend(loc='upper left')
    plt.ylabel('Min')
    plt.xlabel('Data size [n]')

    fig2 = plt.figure()
    ax1_2 = fig2.add_subplot(111)
    ax1_2.scatter(x, y_S[1], c='b', marker="s", label='Select')
    ax1_2.scatter(x, y_R[1], c='r', marker="s", label='Random')
    ax1_2.plot(x, np.poly1d(np.polyfit(x, y_S[1], 1))(x))
    ax1_2.plot(x, np.poly1d(np.polyfit(x, y_R[1], 1))(x))


    plt.legend(loc='upper left')
    plt.ylabel('Max')
    plt.xlabel('Data size [n]')

    fig3 = plt.figure()
    ax1_3 = fig3.add_subplot(111)
    ax1_3.scatter(x, y_S[2], c='b', marker="s", label='Select')
    ax1_3.scatter(x, y_R[2], c='r', marker="s", label='Random')
    ax1_3.plot(x, np.poly1d(np.polyfit(x, y_S[2], 1))(x))
    ax1_3.plot(x, np.poly1d(np.polyfit(x, y_R[2], 1))(x))

    
    plt.legend(loc='upper left')
    plt.ylabel('Avg')
    plt.xlabel('Data size [n]')

    fig4 = plt.figure()
    ax1_4 = fig4.add_subplot(111)
    ax1_4.scatter(x, y_S[3], c='b', marker="s", label='Select')
    ax1_4.scatter(x, y_R[3], c='r', marker="s", label='Random')
    ax1_4.plot(x, np.poly1d(np.polyfit(x, y_S[3], 1))(x))
    ax1_4.plot(x, np.poly1d(np.polyfit(x, y_R[3], 1))(x))


    plt.legend(loc='upper left')
    plt.ylabel('Var')
    plt.xlabel('Data size [n]')

    plt.show()

plotdata()