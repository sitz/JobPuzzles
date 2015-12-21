#!/usr/bin/python

"""
Solution
--------
Total = 100000000
Index = [0, 1, 2, 3, 5, 6, 8, 9, 10, 11, 12, 15, 16, 17, 20, 22, 24, 25]
"""
def getSubsets(targetPopulation, censusPopulation, fpRate = 0.000003):
	censusSize = len(censusPopulation)
	oldCandidates = [(0, [])]
	for index in range(len(censusPopulation)):
		newCandidates = []
		for oldCandidate in oldCandidates:
			newCandidates.append((oldCandidate[0] + censusPopulation[index], oldCandidate[1] + [index]))

		possibleCandidates = sorted(oldCandidates + newCandidates)
		
		minCandidate = min(possibleCandidates)
		oldCandidates[:] = [minCandidate]

		for possibleCandidate in possibleCandidates:
			if possibleCandidate[0] > minCandidate[0] + fpRate * targetPopulation / censusSize and possibleCandidate[0] <= targetPopulation:
				minCandidate = possibleCandidate
				oldCandidates.append(possibleCandidate)

	for oldCandidate in oldCandidates:
		if oldCandidate[0] >= (1 - fpRate) * targetPopulation and oldCandidate[0] <= targetPopulation:
			total = 0
			for i in oldCandidate[1]:
				total += censusPopulation[i]
			if total == targetPopulation:
				print "Yes!", oldCandidate


if '__main__' == __name__:
	censusPopulation = [18897109, 12828837, 9461105, 6371773, 5965343, 5946800, 5582170, 5564635, 5268860, 4552402, 4335391, 4296250, 4224851, 4192887, 3439809, 3279833, 3095313, 2812896, 2783243, 2710489, 2543482, 2356285, 2226009, 2149127, 2142508, 2134411]
	targetPopulation = 100000000

	getSubsets(targetPopulation, censusPopulation)
