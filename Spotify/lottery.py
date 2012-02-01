import sys, math
from math import factorial as fac
from decimal import *

def nCr(n,r):
    return Decimal(fac(n) / (fac(r) * fac(n-r)))

def hyperGeo(goodWays, badWays, totalWinners, numberOfWins):
    if numberOfWins > goodWays:
        return 0
    if totalWinners - numberOfWins > badWays:
        return 0

    return (nCr(goodWays, numberOfWins) * nCr(badWays, totalWinners - numberOfWins)) / nCr(goodWays + badWays, totalWinners)

def go(arr):
    players, maxWinners, tickets, group = arr
    minGWinners = int(math.ceil(group/tickets))
    if minGWinners > maxWinners:
        return 0

    prob = Decimal(0);
    for i in xrange(minGWinners, maxWinners+1):
        prob += hyperGeo(group, players - group, maxWinners, i)
    
    return prob

if __name__ == '__main__':
    for line in sys.stdin:
        print '{0:.10f}'.format(go(map(Decimal, map(int, line.strip().split(' ')))))
