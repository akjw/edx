from sys import argv
import csv
import re

# verify num of arguments
if len(argv) < 3:
    print("Usage: python dna.py data.csv sequence.txt")

# init dictionary
strs = {}

# read db file to memory
with open(argv[1], "r") as csvfile:
    csvreader = csv.reader(csvfile)
    # get first line of file
    first_line = next(csvreader)
    # remove name from first line
    first_line.pop(0)
    # remaining values will be the keys to the strs dict
    keys = first_line
    for key in keys:
        # init values for str patterns
        strs[key] = 0


# read txt file to memory
with open(argv[2], "r") as txtfile:
    dna_sequence = txtfile.read()

# regex method:
# get count of each pattern in dna sequence
for pattern in strs:
    # concatenate pattern with the rest of regex flags; () indicates capture group,
    # \2 indicates repeating what is inside second pair of parantheses (pattern) vs. the first
    # * allows multiple matches
    regex = r"((" + re.escape(pattern) + r")\2*)"
    matches = re.findall(regex, dna_sequence)
    if matches:
        # sorts matches by length
        sorted_matches = sorted(matches)
        # take last match from sorted list (longest), take first index[0] (the match itself, not the pattern)
        longest_match = sorted_matches[-1][0]
        # count repetitions within longest match
        strs[pattern] = str(longest_match).count(pattern)
    else:
        strs[pattern] = 0

#  alternate:
for pattern in strs:
    # index as loop iterates over entire dna sequence
    index = 0
    # length of pattern to match against
    pat_length = len(pattern)
    # maximum number of pattern repetitions
    max_reps = 0
    # current number of pattern repetitions
    curr_reps = 0
    # iterate until the end of the dna sequence
    while index < len(dna_sequence):
        # window is a section of the dna sequence, with a length that matches the current pattern being matched against
        window = dna_sequence[index: index + pat_length]
        # check if the characters in window match pattern
        if window == pattern:
            # increment current repetitions
            curr_reps += 1
            # reassign maximum repetitions
            max_reps = max(max_reps, curr_reps)
            # slide window over to next set of characters
            index += pat_length
        else:
            # if not a match, reset counter of repetitions, since the sequence is broken
            curr_reps = 0
            # increment index
            index += 1
    # assign max_reps to pattern count
    strs[pattern] = max_reps


with open(argv[1], "r") as csvfile:
    people = csv.DictReader(csvfile)
    for person in people:
        # reset match to 0 on every iteration
        matches = 0
        for pattern_count in strs:
            if int(person[pattern_count]) == strs[pattern_count]:
                matches += 1
        if matches == len(strs):
            print(f"{person['name']}")
            exit()
    print('No match.')