# To the extent possible under law, the author(s) have dedicated all
# copyright and related and neighboring rights to this software to the
# public domain worldwide. This software is distributed without any warranty.
# You should have received a copy of the CC0 Public Domain Dedication along
# with this software.
# If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

# base-files version 4.3-3

# ~/.bashrc: executed by bash(1) for interactive shells.

# The latest version as installed by the Cygwin Setup program can
# always be found at /etc/defaults/etc/skel/.bashrc

# Modifying /etc/skel/.bashrc directly will prevent
# setup from updating it.

# The copy in your home directory (~/.bashrc) is yours, please
# feel free to customise it to create a shell
# environment to your liking.  If you feel a change
# would be benifitial to all, please feel free to send
# a patch to the cygwin mailing list.

# User dependent .bashrc file

# If not running interactively, don't do anything
[[ "$-" != *i* ]] && return


echo "starting .bashrc"


# Shell Options
#
# See man bash for more options...
#
# Don't wait for job termination notification
# set -o notify
#
# Don't use ^D to exit
# set -o ignoreeof
#
# Use case-insensitive filename globbing
# shopt -s nocaseglob
#
# Make bash append rather than overwrite the history on disk
# shopt -s histappend
#
# When changing directory small typos can be ignored by bash
# for example, cd /vr/lgo/apaache would find /var/log/apache
# shopt -s cdspell

# Programmable completion enhancements are enabled via
# /etc/profile.d/bash_completion.sh when the package bash_completetion
# is installed.  Any completions you add in ~/.bash_completion are
# sourced last.

# History Options
#
# Don't put duplicate lines in the history.
# export HISTCONTROL=$HISTCONTROL${HISTCONTROL+,}ignoredups
#
# Ignore some controlling instructions
# HISTIGNORE is a colon-delimited list of patterns which should be excluded.
# The '&' is a special pattern which suppresses duplicate entries.
# export HISTIGNORE=$'[ \t]*:&:[fb]g:exit'
# export HISTIGNORE=$'[ \t]*:&:[fb]g:exit:ls' # Ignore the ls command as well
#
# Whenever displaying the prompt, write the previous line to disk
# export PROMPT_COMMAND="history -a"

# Aliases
#
# Some people use a different file for aliases
# if [ -f "${HOME}/.bash_aliases" ]; then
#   source "${HOME}/.bash_aliases"
# fi
#
# Some example alias instructions
# If these are enabled they will be used instead of any instructions
# they may mask.  For example, alias rm='rm -i' will mask the rm
# application.  To override the alias instruction use a \ before, ie
# \rm will call the real rm not the alias.
#
# Interactive operation...
alias rm='rm -i'
# alias cp='cp -i'
# alias mv='mv -i'
#
# Default to human readable figures
# alias df='df -h'
# alias du='du -h'
#
# Misc :)
# alias less='less -r'                          # raw control characters
# alias whence='type -a'                        # where, of a sort
alias grep='grep --color'                     # show differences in colour
# alias egrep='egrep --color=auto'              # show differences in colour
# alias fgrep='fgrep --color=auto'              # show differences in colour
#
# Some shortcuts for different directory listings
alias ls='ls -hF --color=tty'                 # classify files in colour
# alias dir='ls --color=auto --format=vertical'
# alias vdir='ls --color=auto --format=long'
# alias ll='ls -l'                              # long list
# alias la='ls -A'                              # all but . and ..
# alias l='ls -CF'                              #

# Umask
#
# /etc/profile sets 022, removing write perms to group + others.
# Set a more restrictive umask: i.e. no exec perms for others:
# umask 027
# Paranoid: neither group nor others have any perms:
# umask 077

# Functions
#
# Some people use a different file for functions
# if [ -f "${HOME}/.bash_functions" ]; then
#   source "${HOME}/.bash_functions"
# fi
#
# Some example functions:
#
# a) function settitle
# settitle ()
# {
#   echo -ne "\e]2;$@\a\e]1;$@\a";
# }
#
# b) function cd_func
# This function defines a 'cd' replacement function capable of keeping,
# displaying and accessing history of visited directories, up to 10 entries.
# To use it, uncomment it, source this file and try 'cd --'.
# acd_func 1.0.5, 10-nov-2004
# Petar Marinov, http:/geocities.com/h2428, this is public domain
# cd_func ()
# {
#   local x2 the_new_dir adir index
#   local -i cnt
#
#   if [[ $1 ==  "--" ]]; then
#     dirs -v
#     return 0
#   fi
#
#   the_new_dir=$1
#   [[ -z $1 ]] && the_new_dir=$HOME
#
#   if [[ ${the_new_dir:0:1} == '-' ]]; then
#     #
#     # Extract dir N from dirs
#     index=${the_new_dir:1}
#     [[ -z $index ]] && index=1
#     adir=$(dirs +$index)
#     [[ -z $adir ]] && return 1
#     the_new_dir=$adir
#   fi
#
#   #
#   # '~' has to be substituted by ${HOME}
#   [[ ${the_new_dir:0:1} == '~' ]] && the_new_dir="${HOME}${the_new_dir:1}"
#
#   #
#   # Now change to the new dir and add to the top of the stack
#   pushd "${the_new_dir}" > /dev/null
#   [[ $? -ne 0 ]] && return 1
#   the_new_dir=$(pwd)
#
#   #
#   # Trim down everything beyond 11th entry
#   popd -n +11 2>/dev/null 1>/dev/null
#
#   #
#   # Remove any other occurence of this dir, skipping the top of the stack
#   for ((cnt=1; cnt <= 10; cnt++)); do
#     x2=$(dirs +${cnt} 2>/dev/null)
#     [[ $? -ne 0 ]] && return 0
#     [[ ${x2:0:1} == '~' ]] && x2="${HOME}${x2:1}"
#     if [[ "${x2}" == "${the_new_dir}" ]]; then
#       popd -n +$cnt 2>/dev/null 1>/dev/null
#       cnt=cnt-1
#     fi
#   done
#
#   return 0
# }
#
# alias cd=cd_func

#
# define global aliases
#
alias evs='env | sort'
alias edit='vim'
alias rebash='. ./.bashrc'
alias tlocal='telnet localhost'


#
# useful aliases
#
alias h='history'
alias j='jobs -l'
alias r='rlogin'
alias du='du -h'
alias df='df -kh'
alias cls='clear'

alias d2u='dos2unix'
alias u2d='unix2dos'

alias pretty4='/usr/bin/indent -bl -bli0 -cli4 -di4 -i4 -l160 -lc160 -npcs -nut'
alias prettyold='/usr/bin/indent -bli0 -i4 -l120 -lc120 -nut'
alias pretty='/usr/bin/indent -bl -bli0 -cli2 -di2 -i2 -l160 -lc160 -npcs -nut'

alias snarf='wget --recursive --page-requisites --html-extension --convert-links'
alias webgrab='wget -r -p -k'

alias today='day.sh'

alias psgrep='ps -aef | grep'

alias print='lpr -d //printserver/fmc4rich'


#
# patching stuff
#
#alias createpatch original/ new/ > original.patch
#alias applypatch original.patch
alias createpatch='diff -rupN'
alias applypatch='patch -p0 <'


#
# cygwin x server
#
alias X='/usr/bin/X -multiwindow &'
alias x='rm -f ~/X.log ; /usr/bin/X -multiwindow &> ~/X.log &'

export DISPLAY="localhost:0.0"
echo "display is $DISPLAY"


#
# shortcuts to github and other projects
#
alias gh='cd /home/bslin/gitwork'
alias adgf='cd /home/bslin/gitwork/adgf'
alias rav='cd /home/bslin/gitwork/RetroAV'
alias rcomp='cd /home/bslin/gitwork/RetroComp'
alias scpu='cd /home/bslin/gitwork/StackCPU'

alias dbox='cd /cygdrive/c/Users/bslin/Dropbox'
alias onedrive='cd /cygdrive/c/Users/bslin/OneDrive'
alias mydrive='cd /cygdrive/c/Users/bslin/My\ Drive/'


#
# setting paths
#
export PATH=/cygdrive/c/Utils/Python/Python313/Scripts:/cygdrive/c/Utils/Python/Python313:$PATH:/home/bslin/bin:.:/cygdrive/c/Utils/cc65-snapshot-win32/bin:/cygdrive/c/Utils/SDL2VICE-3.9-win64:/cygdrive/c/Utils/trs80gp-2.5.4/windows:/cygdrive/c/Utils/PuTTY:/cygdrive/c/Utils/teraterm-5.0:/cygdrive/c/Utils/arduino-cli:/usr/local/bin

export MANPATH="$MANPATH:/home/bslin/man"

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/bslin/lib:/usr/local/lib"

export EDITOR="/usr/bin/vi"


#
# aliases for windows utils
#
alias gvim='/cygdrive/c/Utils/Vim/vim91/gvim.exe'
alias gv='/cygdrive/c/Utils/Vim/vim91/gvim.exe'

alias npp='/cygdrive/c/Utils/Notepad++/notepad++.exe'

alias cb='/cygdrive/c/Utils/CodeBlocks/codeblocks.exe'

alias merge='/cygdrive/c/Utils/WinMerge/WinMergeU.exe'
alias compare='/cygdrive/c/Utils/WinMerge/WinMergeU.exe'

alias vscode='/cygdrive/c/Users/bslin/AppData/Local/Programs/Microsoft\ VS\ Code/Code.exe'

alias tterm='/cygdrive/c/Utils/teraterm-5.0/ttermpro.exe'

alias flogo='/cygdrive/c/Utils/FMSLogo/fmslogo.exe'

alias wlogo='/cygdrive/c/Utils/Softronics/Microsoft\ Windows\ Logo/logo32.exe'

alias draw='/cygdrive/c/Utils/draw.io/draw.io.exe'

alias dosbox='/cygdrive/c/Utils/DOSBox-0.74-3/DOSBox -c "MOUNT C C:\DOS"'

alias arduino='/cygdrive/c/Utils/Arduino\ IDE/Arduino\ IDE.exe'


#
echo "cygwin bashrc done."
# end
#
