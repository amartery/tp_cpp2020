from random import randint
import sys


def sys_argv_input():
    result = list()
    for i in sys.argv[1:]:
        try:
            result.append(int(i))
            continue
        except ValueError:
            print("ValueError - некорректный ввод аргументов командной строки!")
            return None
    return {'size': result[0], 'min_val': result[1], 'max_val': result[2]}


if __name__ == "__main__":
    if len(sys.argv) == 4:
        argv_coefficients = sys_argv_input()
        if argv_coefficients:
            with open("generated_with_python.txt", "w") as f:
                f.write(str(argv_coefficients['size']) + "\n")
                for _ in range(argv_coefficients['size']):
                    f.write(str(randint(argv_coefficients['min_val'], argv_coefficients['max_val'])) + " ")
        else:
            print("попробуйте еще раз")
    else:
        print("неверно указаны аргументы командной строки")
