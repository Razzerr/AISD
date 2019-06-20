import sys
import numpy.random as rand
import math
import time

def getMedian(list, p, q, count):
    return randomSelect(list, p, q, math.floor((q-p)/2), count)

def select(list, p, q, i, count):
    if p == q:
        return p
    medians = []
    for j in range(p,q,5):
        if q-j<4:
            medians.append(getMedian(list, j, q, count))
        else:
            medians.append(getMedian(list, j, j+4, count))

    x = medians[0]
    if (len(medians)>1):
        x = medians[select(medians, 0, len(medians)-1, math.floor(len(medians)/2), count)]

    index = p
    for j in range(p, q+1, 1):
        if (list[j] == x):
            index = j

    x = partition(list, p, q, index, count) #+1

    if i == x:
        return i#-1
    elif i < x:
        return select(list, p, x-1, i, count)#x-2
    else:
        return select(list, x+1, q, i, count)

def partition(list, p, q, pivot, count):
    list[p], list[pivot] = list[pivot], list[p]
    i = p #i == position of pivot
    for z in range(i+1,q+1):
        count[0] += 1
        if list[z]<list[p]:
            i += 1
            list[z], list[i] = list[i], list[z]
    list[p], list[i] = list[i], list[p]
    return i #number in table



def randomSelect(list, p, q, i, count):
    if p == q:
        return p
    num = rand.randint(p, q)
    r = partition(list, p, q, num, count)
    print(p, num, q, r)
    k = r-p+1
    if i == k:
        return r
    if i < k:
        return randomSelect(list, p, r-1, i, count)
    else:
        return randomSelect(list, r+1, q, i-k, count)


def main():
    n=10
    i = 3
    list = rand.randint(0,50,n)
    count = [0,0]
    print(list[randomSelect(list, 0, n-1, i, count)])

main()