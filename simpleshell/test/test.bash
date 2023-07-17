#!/bin/bash

# This script create test/ dir and subdirs for each task and
# download test scripts, also runs tests for a specific folder or file
#
# Usage: ./test.bash -help
#
# ===========V1.0===========

# -help argument: display usage
if [ "${1}" == "-help" ] || [ -z "${1}" ]; then
	echo -e "Usage: ./test.bash [-init | FOLDER | FOLDER/FILE]\n"

	echo "This script runs the checker.bash script on a set of .bash scripts"
	echo -e "located in a specified folder. and initialze test/ dir and subdirs
for each task and download test scripts\n"

	echo "Options:"
	echo "  -init       : Create test dir and subdirs and download test scripts"
	echo "		Ex: ./test.bash -init"
	echo "  FOLDER      : Name of the folder to run all test scripts in that folder"
	echo "		Ex: ./test.bash 1-command/"
	echo "  FOLDER/FILE : Run specific test script"
	echo "		Ex: ./test.bash 1-command/bin_ls.bash"
	echo "  -help       : Display help\n"
	exit 0
fi

# -init argument: create test dir and subdirs, download test scriptes
if [ "$1" == "-init" ]; then

mkdir -p test && cd test
mkdir -p    1-command 2-args 3-PATH 4-exit 5-env \
			6-getline 7-strtok 8-exit_status 9-setenv \
			10-cd 11-seperator 12-logical \
			13-alias 14-variables 15-comments 16-file

# Set the base URL
base_url="https://simple-shell-tests.vercel.app/assets/files"

# Set the number of tasks
num_tasks=16

# arrays hold the script names for each task
script_names_1=("bin_ls:bin_ls_3_times:bin_ls_spaces:ls_in_current_dir:empty_input_small:empty_input_large:empty_input_medium")
script_names_2=("bin_ls_1_arg:bin_ls_1_arg_1:echo_1_arg")
script_names_3=("ls_:bin_ls_1_arg_1:ls_in_two_parent_dir_2:ls_1_arg:bin_ls_1_arg_1:ls_in_parent_dir:ls_in_two_parent_dir:ls_in_two_parent_dir_3:bin_ls:ls_path_bin_last:bin_ls_large_input:bin_ls_empty_path:bin_ls_1_arg:mix_ls_bin_ls_spaces:ls_spaces:ls_empty_path:bin_ls_spaces:ls_in_current_dir:ls_dot_ls:env_ignore_ls:ls_path_bin_first:env_ignore_bin_ls:bin_ls_3_times:bin_ls_medium_input:mix_ls_bin_ls:ls_path_no_bin:ls_path_bin_middle:empty_path_failing_cmd:path_path1_var:path_current_dir_ls:unknown_command_no_fork")
script_names_4=("exit_no_arg:exit_no_arg_1")
script_names_5=("env_one_var:env:env_ignore_env")
script_names_6=("bin_ls:bin_ls_medium_input:bin_ls_large_input")
script_names_7=("bin_ls")
script_names_8=("exit_1000:exit_with_status:exit_neg_number:exit_no_arg_1:exit_no_arg:exit_string")
script_names_9=("setenv_one_param:setenv_no_param:setenv_existing_var:setenv:unsetenv:unsetenv_not_existing_var:unsetenv_no_param")
script_names_10=("cd_no_arg:cd_no_arg_rm_home:cd_no_permission:cd_dash_rm_oldpwd:cd_dash:cd_normal:cd_not_existing_dir:cd_dash_change_oldpwd:cd_no_arg_change_home")
script_names_11=("cmd_sep_cmd_sep_cmd:cmdfail_sep_cmd:cmdfail_sep_cmdfail:cmd_sep_cmd_no_space:cmd_sep:cmd_sep_cmd")
script_names_12=("cmd_and_cmd_no_space:cmd_and_cmd:cmd_and_cmd_and_cmd:cmd_and_cmdfail:cmd_and_cmdfail_and_cmd:cmdfail_and_cmd:cmd_and_cmd_and_cmdfail:cmdfail_and_cmd_and_cmd:cmd_or_cmd:cmd_or_cmd_or_cmd:cmdfail_or_cmd_or_cmd:cmdfail_or_cmd_no_space:cmd_or_cmdfail:cmdfail_or_cmdfail:cmd_or_cmdfail_or_cmd:cmdfail_or_cmd:cmdfail_or_cmdfail_or_cmdfail:cmdfail_or_cmd_and_cmd:cmd_and_cmdfail_or_cmd")
script_names_13=("alias_list:alias_ls_double:alias_several:alias_specific:alias_several_and_display:alias_ls:alias_several_override:alias_overwrite")
script_names_14=("echo_status_fail:ls_var:echo_status:echo_as_var:echo_unknown_var:echo_pid:echo_pid_fake:echo_var")
script_names_15=("comment_after_cmd:comment_after_cmd_print_no_space:comment:comment_after_cmd_print:comment_after_cmd_print_space")
script_names_16=("shell_with_unknown_file:shell_with_empty_file:shell_with_file:shell_with_file_1")

# Loop over the tasks
echo -e "\n\\033[33mDownloading test scripts...\\033[0m"
for ((task=1; task<=num_tasks; task++)); do
    # Set the task directory
    task_dir=$(find . -type d -name "${task}-*")
    # Get the name of the array for the current task
    script_names="script_names_${task}"
    # Split the string into an array of individual elements
    IFS=':' read -ra scripts <<< "${!script_names}"
    check=2
    # Loop over the script names for the current task
    for script in "${scripts[@]}"; do
        # Append the .bash extension to the script name
        script="${script}.bash"
        # Set the script URL
        url="${base_url}/${task}/${check}/${script}"
        # Download the script
        curl -s -S -f -L -o "${task_dir}/${script}" "${url}"
        # Clear the line
        echo -ne "\r\033[K"
        # Display output to user
        echo -ne "\r[${task}/${num_tasks}] $(basename "${task_dir}") : [$(( check - 1 ))/${#scripts[@]}] ${script}"
        ((check++))
    done
done

# Download checker.bash in test/ dir
curl -s -S -f -L -o checker.bash https://simple-shell-tests.vercel.app/assets/files/1/2/checker.bash

# Sets the exec permission for download scripts
find . -type f -name "*.bash" -exec chmod u+x {} \;

# move test.bash from project/ dir to test/ dir
mv ../test.bash .

echo -e "\n\n\\e[32mSuccess\\e[0m: to download scriptes"
echo -e "\\033[33mRun\\033[0m: \\033[1mcd test/ && ./test.bash -help\\033[0m for more infos"

exit 0
fi

########################
folder=$1

# Download the checker.bash file
if [ ! -f "./checker.bash" ]; then
curl -o checker.bash https://simple-shell-tests.vercel.app/assets/files/1/2/checker.bash
fi
# Check if the specified folder contains any .bash scripts
script_count=$(find "${folder}" -maxdepth 1 -name "*.bash" | wc -l)
if [ "${script_count}" -eq 0 ]; then
    echo -e "\\e[31mError:\\e[0m can't find any .bash scripts in ${folder}"
	echo -e "\n- Run: ./test.bash -init, to set up test subdirs and download scripts for you\n"
    exit 1
fi

# Complie c files from parent dir
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 ../*.c -o hsh
if [ ! -f "./hsh" ]; then
	echo -e "\\e[31mError:\\e[0m fail to compile 'hsh'"
fi

# User provided a file
if [ -f "${1}" ]; then
    script_name=$(basename "${1}")
    echo -e "\n\033[33m${script_name}\033[0m"
    ./checker.bash --valgrind ./hsh "${1}"
# User provided a folder
elif [ -d "${1}" ]; then
    for script in "${1}"/*.bash; do
        script_name=$(basename "${script}")
        echo -e "\n\033[33m${script_name}\033[0m"
        ./checker.bash --valgrind ./hsh "${script}"
    done
fi

echo -e "\n"
exit 0

# If you find any bugs or issues please report.
# feel free to edit the code, but question of million dollars: u gonna keep credits 🤔 ?

# Credit:
# - test.bash script: BIO.
# - website: i don't know who, but thanks to him <3.
