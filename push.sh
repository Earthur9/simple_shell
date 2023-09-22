#!/bin/bash

# Function to push a random .c file
push_random_c_file() {
    # Search for .c files in the current directory (excluding .h files)
    c_files=($(find . -type f -name "*.c" ! -name "*.h"))
    
    # Check if there are any .c files
    if [ ${#c_files[@]} -eq 0 ]; then
        echo "No .c files found in the directory."
        exit 0
    fi
    
     # Shuffle the array to randomize file selection
         shuf -o c_files < <(shuf -n ${#c_files[@]} -e "${c_files[@]}")


    # Generate a random index that hasn't been used before
    while true; do
        rand_index=$((RANDOM % ${#c_files[@]}))
        random_c_file="${c_files[$rand_index]}"
        
        # Check if the file has already been used
        if [ ! "${used_files[$rand_index]}" ]; then
            used_files[$rand_index]=1
            break
        fi
    done

    commit_counter=$((commit_counter + 1))
    
    # Add and commit the file
    git add "$random_c_file"
    git commit -m "Update 0.$commit_counter $random_c_file"
    
    # Push to GitHub
    git push
}

# Declare an array to keep track of used files
declare -a used_files
unset 'c_files[$rand_index]'

# Loop for up to an hour (3600 seconds)
end_time=$((SECONDS + 400))
while [ $SECONDS -lt $end_time ]; do
    # Push a random .c file
    push_random_c_file
    
    # Sleep for a random amount of time (between 1 and 10 minutes)
    sleep_duration=$((RANDOM % 60))
    sleep $sleep_duration
done

echo "Script completed."

