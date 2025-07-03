# Add this to your .bash or .zsh file 
# Multiple input does not work currently
jmp() {
    local dest 
    dest=$(python ~/projects/jumper/proto.py "$1" 2>/dev/null)

    if [[ -z "$dest" ]]; then 
        echo "jmp: No directory found or invalid input."
        return 1 
    fi 

    if [[ "$dest" == Multiple* ]]; then 
        echo "$dest"
        return 1 
    fi 


    cd "$dest" || echo "jmp: failed to jump to $dest"

}
