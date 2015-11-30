#!/usr/bin/env python

"""
BagOfWords.py

Changelog
    Version 0.0:
        Initial Version

This python file will take in two text files and output the angle between the frequency of words of the two files.

"""

__author__ = "Ben Zheng"
__copyright__ = "MIT License"
__credits__ = []
__license__ = "MIT"
__version__ = "None"
__maintainer__ = "Ben Zheng"
__email__ = ""
__status__ = "Prototype"

import math
import string
import sys

#Read the text file input
def read_file(filename):
    """
    Read a text file of filename and return the list of text from the file.

    :param filename: the text file
    :return: return a list of text
    """

    try:
        fp = open(filename)
        L = fp.readlines()
    except IOError:
        print "Error opening the file ", filename
        sys.exit()
    return L

#Break the list of words into individual words.
def get_words_from_list(L):
    """
    Reads a list of words from from read_file and return list of all of the words in the list. Duplicate words will be
    included.

    :param L: List of text
    :return: list of words
    """

    word_list = []
    for line in L:
        words_in_the_line = get_words_from_list(line)
        word_list = word_list + words_in_the_line
    return word_list

#Count the frequency of each word in the list
def count_frequency(word_list):
    """

    :param word_list: A list of words
    :return: Returns a list in the form of a pair (word, frequency)
    """
    L = []
    for new_word in word_list:
        for entry in L:
            if new_word == entry[0]:
                entry [1] = entry[1] + 1
                break
            else:
                L.append([new_word,1])
    return L


#Sort the list
def insertion_sort(word_list):
    """
    Goes through the list and sort the word_list by adjusting the pivot

    :param word_list: a list of words
    :return: a sorted list of words
    """
    for j in range(len(word_list)):
        key = word_list[j]
        i = j-1
        while i>-1 and word_list[i]>key:
            word_list[i+1] = word_list[i]
            i = i-1
        word_list[i+1] = key
    return word_list



#Compute the word frequency of each file.
def word_frequencies_for_text_file(filename):
    """

    :param filename:
    :return:
    """
    Pass

#Calculate the inner product of the two files.
def inner_product(list1, list2):
    """

    :param list1:
    :param list2:
    :return:
    """
    Pass

def main():
    Pass

if __name__ == "__main__":
    main()