# This stuff is for jumper 
jmp() {
    local dest 
    dest=$(python ~/projects/jumper/proto.py "$1")

    if [[ -z "$dest" ]]; then 
        echo "jmp: No directory found or invalid input."
        return 1 
    fi 

    cd "$dest" || echo "jmp: failed to jump to $dest"

}

# jmp_list tab complete
_jmp_complete() {
    local word 
    word="${words[2]}"

    # read all the entries from the jmp list 
    local -a favs
    favs=($(cat ~/.jmp_list))

    # auto complete 
    compadd -W '' -a favs
}
compdef _jmp_complete jmp
