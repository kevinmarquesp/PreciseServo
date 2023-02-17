#!/usr/bin/env python

import serial
import os

port = os.getenv('PORT')
baudrate = os.getenv('BAUDRATE')


def controller(line):
    is_test = 'Test' in line[:4]
    is_summary = 'Test summary:' in line
    has_passed = line.split(' ')[-1] == 'passed'
    exit_code = int('0 failed' not in line)

    if is_summary:
        print('\n' + line.replace(' test(s).', ''))
        exit(exit_code)

    elif is_test:
        color = '\033[32m' if has_passed else '\033[31m'
        line_words = line.split(' ')
        line_words[1] = color + line_words[1] + '\033[m'
        line = ' '.join(line_words) + '\033[m'

    print(line)


def main():
    if None in [port, baudrate]:
        exit(1)

    ser = serial.Serial(port=port, baudrate=baudrate)

    while True:
        line = str(ser.readline(), 'utf-8').replace('\n', '').strip()
        controller(line)


if __name__ == '__main__':
    main()
