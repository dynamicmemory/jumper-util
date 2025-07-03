import os 
import sys


def main() -> None:
    current_directory: str = os.getcwd()
    argv: list = sys.argv

    if len(argv) > 2: 
        print(f"Error: Too many arguments - Found: {len(argv)} Allowed: 2")
        exit(0)

    jump_to: str = argv[1]
    flag: bool = False 
    directory_options: list = []
    for root, dirs, files in os.walk("/"):
        for d in dirs:
            if d == jump_to:
                directory_options.append(os.path.join(root, d)) 

    if len(directory_options) > 1:
        print("Pick which directory you want?") 
        
        counter = 1
        for option in directory_options:
            print(counter, option)
            counter += 1

        sys.stdout.flush()
    if len(directory_options) > 1:
        select_dir: str = input("")

        print(directory_options[int(select_dir)-1])
        return 
    
    print(directory_options[0])
    return

if __name__ == "__main__":
    main()
