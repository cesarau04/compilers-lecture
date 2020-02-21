import sys
import re

BEGIN_ITALICS = '\x1B[3m'
END_ITALICS = '\x1B[23m'
RE_FUNCTIONS = re.compile(r'<.*>:')
RE_INSTRUCTIONS = re.compile(r'\s[a-z]+[0-9]*[a-z]*\s\s*')

FUNCTIONS_DICT = dict()
INSTRUCTIONS_DICT = dict()

if (len(sys.argv) != 2):
    print('Usage: "python[3] asm-analitics.py ' +
          BEGIN_ITALICS + 'filename' + END_ITALICS + '"')
    exit(0)

with open(file=sys.argv[1], mode='r') as f:
    for line in f:
        if (re.search(RE_FUNCTIONS, line) != None):
            arr = line.split(' ')
            FUNCTIONS_DICT[arr[1].strip()] = arr[0]
            continue

        m = re.search(RE_INSTRUCTIONS, line)
        if (m != None):
            instruction = m.group().strip()
            if instruction not in INSTRUCTIONS_DICT:
                INSTRUCTIONS_DICT[instruction] = 1
            else:
                INSTRUCTIONS_DICT[instruction] += 1

    print("Results of the analysis:")
    print("\tYou have {0} kind of instructions in this object file:".format(
        len(INSTRUCTIONS_DICT)))

    for instruction, freq in INSTRUCTIONS_DICT.items():
        print("\t\t{:10s}: Executed {} times".format(instruction, freq))

    print("\tYou have {0} functions:".format(len(FUNCTIONS_DICT)))
    for function, addr in FUNCTIONS_DICT.items():
        print("\t\t{:30s}: Located at {} addr".format(
            function[1:len(function)-2], addr))

    f.close()
