import sys


def sum_two_numbers(a, b):
    """
    Add two number
    """
    return a+b


if __name__ == '__main__':
    if len(sys.argv) == 3:
        print(sum_two_numbers(int(sys.argv[1]), int(sys.argv[2])))
    else:
        print("please input two numbers")
