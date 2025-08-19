# .bashrc

# User specific aliases and functions

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

umask 0000

#noclobber=1
set -o noclobber

histsize=50

if [ "$PS1" ]; then
stty erase ^H
stty kill ^U
stty intr ^C
stty susp ^Z
fi


# pick the one you like
alias ls='ls -F --color'
#alias ls='ls -F'


alias rm='rm -i'

alias h='history'
alias j='jobs -l'
alias r='rlogin'
alias cls='clear'

alias evs='env | sort'

alias tlocal='telnet localhost'

alias psgrep='ps -aef | grep'

alias xt='xterm -bg black -fg white &'

alias scratch='cd /scratch'

#alias gv='/usr/X11R6/bin/gvim'
function gvim() { /usr/X11R6/bin/gvim $1 & }
function gv() { /usr/X11R6/bin/gvim $1 & }
function ed() { /usr/X11R6/bin/gvim $1 & }
function xm() { /usr/bin/xemacs $1 & }

alias pretty='/usr/bin/indent -bli0 -i4 -l120 -lc120 -nut'

alias rebash='. ./.bashrc'

export PATH="$PATH:/sbin:/usr/sbin:.:$HOME/bin"

LD_LIBRARY_PATH=/usr/lib:/usr/local/lib:/usr/X11R6/lib
export LD_LIBRARY_PATH

DISPLAY=$REMOTEHOST:0.0
export DISPLAY


#
# -- CVS stuff --
#

#CVSROOT=":pserver:bl12960@asdpserver.bose.com:2408/cvsroot_asd"
CVSROOT=":pserver:$USER@asdpserver.bose.com:2408/cvsroot_asd"
export CVSROOT

alias clogin='cvs login'

#alias scan='cvs -n update | grep -v "^?"'
alias scan='cvs -q -n update'
alias scanl='cvs -q -n update -l'
alias update='cvs -q update -d'
alias status='cvs status'
alias tags='cvs status -v Makefile'

alias mainline='cd /scratch/$USER/mainline/PS_HU'
alias branch='cd /scratch/$USER/branch/PS_HU'
alias merge='cd /scratch/$USER/merge/PS_HU'
alias release='cd /scratch/$USER/release/PS_HU'


#
# -- Integrity stuff --
#

export MULTIBASE="/opt/ghs/multi/linux86"
export PATH="$PATH:$MULTIBASE"

#export GHS_LMHOST="@Greenhills-lic"
#export GHS_LMPORT="27015"


#
# source project specific setup script
# {modify PROJBASE to point to your Synergy work area}
#

export WORKSPACE=mainline
#export WORKSPACE=branch
#export WORKSPACE=merge
#export WORKSPACE=release


export PROJBASE="/scratch/$USER/$WORKSPACE"
export PROJECT="PS_HU"


export PROJHOME="$PROJBASE/$PROJECT"
alias progsrc='cd $PROJHOME'


alias ws='echo "workspace = $WORKSPACE"'

alias mysix='cd $PROJHOME/OS/Integrity/int506/mysix'
alias revb='cd $PROJHOME/OS/Integrity/int506/mysix_revb'
alias vow='cd $PROJHOME/OS/Integrity/int506/mysix_vow'

alias mbarch='cd $PROJHOME/common/modules/MainBoardArch'
alias vowarch='cd $PROJHOME/common/modules/VowArch'
alias mbconfig='cd $PROJHOME/common/modules/MainBoardArch/config'
alias vowconfig='cd $PROJHOME/common/modules/VowArch/config'

alias common='cd $PROJHOME/common'
alias modules='cd $PROJHOME/common/modules'
alias MYSIX='cd $PROJHOME/lectronix'

alias headunit='cd $PROJHOME/common/Build/IDE_Projects/ghs'
alias vsnet='cd $PROJHOME/common/Build/IDE_Projects/VS.NET'

alias sysdbg='cd $PROJHOME/common/modules/CommonServices/SystemDebug'

alias intf='cd $PROJHOME/common/modules/Interfaces'
alias logger='cd $PROJHOME/common/modules/Infrastructure/SystemServices/Logger'
alias sysmgr='cd $PROJHOME/common/modules/SystemManagement/SystemManager'
alias tuner='cd $PROJHOME/common/modules/Applications/TunerCore'
alias vehicle='cd $PROJHOME/common/modules/DeviceServices/VehicleLocation'
alias vic='cd $PROJHOME/common/modules/DeviceServices/VICControl'
alias xmdsl='cd $PROJHOME/common/modules/DeviceServices/XMDsl'




# we're done here!!
if [ "$PS1" ]; then
echo "$HOSTNAME bashrc done."
fi
