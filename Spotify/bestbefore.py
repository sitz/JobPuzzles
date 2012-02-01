from sys import argv
from datetime import date
from itertools import permutations

def illegal(error):
    #Error processing params
    print '%s is illegal' % error 
    exit()

class bestbefore(object):
    def __init__(self, A, B, C):
        self.MAX_YEAR = 2999
        self.MIN_YEAR = 2000

        if A == 0: A = 2000
        if B == 0: B = 2000
        if C == 0: C = 2000
    
        self.A, self.B, self.C = (A, B, C)

    def compute(self):
        # Test all possible options
        all_dates = []
        for A, B, C in permutations([self.A, self.B, self.C]):
            try:
                d = date(A, B, C)
                # Check year in MIN_YEAR..MAX_YEAR range
                if d.year < self.MIN_YEAR:
                    year = d.year + self.MIN_YEAR
                    if year > self.MAX_YEAR:
                        # year not in range!
                        continue
                    d = date(year, d.month, d.day)
                all_dates.append(d.isoformat())
            except ValueError:
                continue
        return all_dates

if __name__ == "__main__":
    data = raw_input()
    try:
        A, B, C = map(int, data.split('/'))
        b = bestbefore(A, B, C)
        all_dates = b.compute()
        # Get earliest legal date
        print min(all_dates)
    except:
        illegal(data)
