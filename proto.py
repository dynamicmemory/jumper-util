import os 
import sys


def main() -> None:
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <directory_name>", file=sys.stderr)
        sys.exit(1)

    jump_to = sys.argv[1]
    directory_options = []

    for root, dirs, files in os.walk("/"):
        for d in dirs:
            if d == jump_to:
                directory_options.append(os.path.join(root,d))

    if not directory_options:
        print(f"No directories named '{jump_to}' found.", file=sys.stderr)
        sys.exit(1)

    if len(directory_options) == 1:
        print(directory_options[0])
        return 

    print("Pick which directory you want:", file=sys.stderr)
    for idx, option in enumerate(directory_options, 1):
        print(f"{idx}) {option}", file=sys.stderr)

    while True:
        try:
            print("Enter selection: ", end='', file=sys.stderr)
            choice = input()
            index = int(choice) - 1
            if 0 <= index < len(directory_options):
                print(directory_options[index])
                return 
            else:
                print(f"Invalid selection. Enter a number between 1 and {len(directory_options)}.", file=sys.stderr)
        except ValueError:
            print("Please enter a vliad number.", file=sys.stderr) 

# def main() -> None:
#     current_directory: str = os.getcwd()
#     argv: list = sys.argv
#
#     if len(argv) > 2: 
#         print(f"Error: Too many arguments - Found: {len(argv)} Allowed: 2")
#         exit(0)
#
#     jump_to: str = argv[1]
#     flag: bool = False 
#     directory_options: list = []
#     for root, dirs, files in os.walk("/"):
#         for d in dirs:
#             if d == jump_to:
#                 directory_options.append(os.path.join(root, d)) 
#
#     if len(directory_options) > 1:
#         print("Pick which directory you want?") 
#
#         counter = 1
#         for option in directory_options:
#             print(counter, option)
#             counter += 1
#
#         sys.stdout.flush()
#     if len(directory_options) > 1:
#         select_dir: str = input("")
#
#         print(directory_options[int(select_dir)-1])
#         return 
#
#     print(directory_options[0])
#     return

if __name__ == "__main__":
    main()
