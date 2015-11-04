#!/usr/bin/env python

"""OOP.py: OOP is a boilerplate template for OOP"""

__author__ = "Ben Zheng"
__copyright__ = "MIT License"
__credits__ = []
__license__ = "MIT"
__version__ = "None"
__maintainer__ = "Ben Zheng"
__email__ = ""
__status__ = "Prototype"

class myClass:
    def __init__(self, name, month, day, year, action):
        """Constructor"""
        self.name = name
        self.month = month
        self.day = day
        self.action = action

    def do(self):
        """Accessor Method """
        return self.action

    def getName(self):
        """Accessor Method that returns the name"""
        return self.name

    def setName(self, newName):
        """Mutator Method that change the name"""
        self.name = newName

    def birthDate(self):
        """Accessor Method that returns string of birth date"""
        return str(self.month) + "/" + str(self.day) + "/" + str(self.year)

    def __add__(self, other):
        """Method overloading of the __add__ function to return the string of the action and birthday rather than the sum of two.
        #Note: repr(x) is called when the class needs to be evaluated, whereas str(x) is a string. Example: repr(x) would return myClass('John', 1, 12, 1982, sleep) and str(x) return "John" """
        return myClass("New Class" + self.name + " and " + other.name , self.month, self.day, self.year + 1, self.action + other.action)

def main():
    if __name__ == "__main__":
        main()
