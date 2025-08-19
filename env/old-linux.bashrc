# .bashrc

# User specific aliases and functions

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

#umask 0000

#echo "PATH is $PATH"

set bell-style visible

#noclobber=1
set -o noclobber

histsize=50

#stty erase ^?

xset r on

if [ "$PS1" ]; then
#stty erase ^?
stty erase ^H
stty kill ^U
stty intr ^C
stty susp ^Z
fi

#alias ls='ls -F --color=tty'
alias ls='ls -F --color'
alias rm='rm -i'

alias h='history'
alias j='jobs -l'
alias r='rlogin'
alias cls='clear'

alias evs='env | sort'

alias tfm10295='telnet fm10295'
alias thpl='telnet hpl'
alias treh='telnet reh'
alias tripley='telnet ripley'
alias tlocal='telnet localhost'
alias tmb='telnet 10.2.32.157'

alias psgrep='ps -aef | grep'

alias xt='xterm -bg black -fg white &'

alias hexedit='/usr/bin/ghex2'

alias pretty4='/usr/bin/indent -bl -bli0 -cli4 -di4 -i4 -l160 -lc160 -npcs -nut'
alias prettyold='/usr/bin/indent -bli0 -i4 -l120 -lc120 -nut'
alias pretty='/usr/bin/indent -bl -bli0 -cli2 -di2 -i2 -l160 -lc160 -npcs -nut'

alias today='day.sh'

alias d2u='dos2unix'
alias u2d='unix2dos'

alias pwr='~/bin/power-ctl'
alias on='~/bin/power-ctl 1'
alias off='~/bin/power-ctl 0'
alias toggle='off ; sleep 10 ; on'
alias tog='~/bin/toggle.sh'
alias state='cat ~/var/powerstate.log'

alias wack='~/bin/wackgamserver.sh'

alias purge='shred -uz'

alias snarf='wget --recursive --page-requisites --html-extension --convert-links'

#alias gv='$HOME/bin/gvim.sh'
#alias gv='/usr/X11R6/bin/gvim'
function gvim() { /usr/bin/gvim $1 & }
function gv() { /usr/bin/gvim $1 & }
function ed() { /usr/bin/gvim $1 & }
function xm() { /usr/bin/xemacs $1 & }


function dmalloc { eval `command dmalloc -b $*`; }


alias kdiff='kdiff3'
alias compare='kompare'

export LPDEST="rd2c059b"
export LPDEST2="mezz8150dn"
alias print='/usr/bin/lpr -P $LPDEST'
#alias print='/usr/bin/lp -o nobanner -d $LPDEST'
alias pjet='enscript -h -G -fCourier9 -d $LPDEST'
alias print2='/usr/bin/lp -o nobanner -d $LPDEST2'
alias pjet2='enscript -h -G -fCourier9 -d $LPDEST2'

alias setdislap='export DISPLAY=10.66.14.180:0.0'
alias setdispc='export DISPLAY=10.66.14.180:0.0'
alias setdis='export DISPLAY=10.66.14.180:0.0'
alias clrdis='export DISPLAY=:0.0'

alias rebash='. ./.bashrc'

alias dm='cd /home/bl12960/bose/common/platform/cpu/diags/diagmon'
alias vt='cd /home/bl12960/bose/common/platform/cpu/diags/vidtest'
alias bsp='cd /home/bl12960/bose/common/platform/cpu/bsp'

alias bose='cd /scratch/bl12960/bose'
alias demo='cd /scratch/bl12960/bose/demo'
alias misc='cd /scratch/bl12960/misc'
alias adgf='cd /scratch/bl12960/misc/adgf'

alias kd='/usr/bin/kdevelop &'
alias kdev='/usr/bin/kdevelop &'

alias adsminicom='minicom ttyS1'
alias adsconsole='gnome-terminal --geometry=80x40 -t ADS -x minicom ttyS1'

alias gettext='svn status | grep -v "?" | grep -v "\." | cut --delimiter=" " --fields 7 | xargs head -3 | grep -v "format "'
alias gettext2='gettext > /solid/bl12960/checkin.txt'

alias svnhome='cd /home/revctrl/asdsvn'


export PATH="$PATH:/sbin:/usr/sbin:.:$HOME/bin"

export MANPATH="$MANPATH:$HOME/man:/opt/STM/STLinux-2.3/devkit/sh4/man"

export LD_LIBRARY_PATH=/usr/lib:/usr/local/lib:/usr/X11R6/lib
#export LD_LIBRARY_PATH=/usr/lib:/usr/X11R6/lib

#export DISPLAY=$REMOTEHOST:0.0

export EDITOR="/usr/bin/vim"


alias krishna='ssh -l root 10.66.43.37'


# ltap does not work on USB serial port for some reason
#alias ltap='sudo /scratch/bl12960/bin/local-ltap /dev/ttyS0'
#alias ltap='sudo /scratch/bl12960/bin/DEF_2010-03-03_0230.ltap /dev/ttyS0'
#alias ltap='sudo /scratch/bl12960/bin/DEF_2010-04-20_1645.ltap /dev/ttyS0'
#alias ltap='sudo /scratch/bl12960/bin/DEF_2010-05-27_1155.ltap /dev/ttyS0'
alias ltap='sudo /scratch/bl12960/bin/DEF_2010-06-29_1145.ltap /dev/ttyS0'

# busybox console on target (requires sudo for some reason)
alias console='sudo minicom /dev/ttyUSB0'

# looks in public rpm repository
alias yumalt='yum --enablerepo=rpmforge'
alias yumlist='yum --enablerepo=rpmforge list'
alias yuminstall='sudo yum --enablerepo=rpmforge install'

alias fixhosts='/tools/hepdsw/uptime/fix_known_hosts.sh'


alias github='cd /scratch/bl12960/github'


# 
# audio stuff
#

alias audio='mplayer -loop 0'

alias player='mplayer -loop 0'

alias playloop='mplayer -loop 0'

alias playlist='mplayer -playlist'

alias playlistloop='mplayer -loop 0 -playlist'

alias listloop='mplayer -loop 0 -playlist'

alias testtones='cd /media/usbdisk1/laptop/MyDocuments/MyMusic/MyMusic/TestTones' 

#alias music='cd /media/disk/laptop/MyDocuments/MyMusic/MyMusic'
#alias music='cd /media/usbdisk1/laptop/MyDocuments/MyMusic/MyMusic'
alias music='cd /scratch/MUSIC'


# 
# qt4 stuff
#

export QTPATH="/opt/qt/native-gui"
#export QTPATH="/opt/qtsdk-2010.05"
export QTDIR="$QTPATH/qt"
export QTINC="$QTDIR/include"
export QTLIB="$QTDIR/lib"

export PATH="$QTPATH/qt/bin:$QTPATH/bin:$PATH"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$QTLIB:/scratch/svnwork/whippet/whippet/Tools/QtDspUpdateApp/build/lib"
export MANPATH="$MANPATH:$QTPATH/man"

export QT_LIB_PATH= 
export QT_INC_PATH= 

export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig"


#
# java jdk stuff
#
export JAVAPATH="/scratch/tools/jdk1.6.0_16"
export PATH="$JAVAPATH/bin:$JAVAPATH/jre/bin:$JAVAPATH/lib:$PATH"
#export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$JAVAPATH/lib:$JAVAPATH/jre/lib"
export MANPATH="$MANPATH:$JAVAPATH/man"


#
# patching stuff
#
#alias createpatch='diff -rupN original/ new/ > original.patch'
#alias applypatch='patch -p0 < original.patch'

# create SVN patch 
# 
# svn diff > file.patch
#

alias createpatch='diff -rupN'
alias applypatch='patch -p0 <'

#alias createsvnpatch='svn diff --diff-cmd /usr/bin/diff -x "-i -b" >'
alias createsvnpatch='svn diff >'
alias applysvnpatch='patch -p0 <'

# awk example -- ls -al | awk '{print $9}'



#
# -- CVS stuff --
#

#CVSROOT=":pserver:bl12960@oempserver.bose.com:/home/oemcom/cvsroot"
#CVSROOT=":pserver:bl12960@hammer.bose.com:2408/cvsroot_asd"
CVSROOT=":pserver:bl12960@asdpserver.bose.com:2408/cvsroot_asd"
export CVSROOT

alias clogin='cvs login'

#alias scan='cvs -q -n update'
#alias scanl='cvs -q -n update -l'
#alias update='cvs -q update -d'
#alias status='cvs status'
#alias tags='cvs status -v Makefile'

alias cvs='echo "yo, dummy!"'


#
# -- Generic SVN stuff --
#

alias scan='svn -q status | sort'
alias scanl='svn -N -q status | sort'
alias scanu='svn status -u | sort'
alias scani='svn status -u --ignore-externals'

alias update='svn update'
alias updatel='svn -N update'

alias externals='svn propget svn:externals'
alias lsexternals='svn propget svn:externals'
alias editexternals='svn propedit svn:externals'

#export SVNDIFF="/usr/bin/meld"
#export SVNDIFF="/usr/bin/kdiff3"
export SVNDIFF="/usr/bin/kompare"


#
# -- HEPD ATG SVN stuff --
#

alias coatgsente='svn co https://svn.bose.com/hepd/ATG_Sente/trunk/ATGMobile ATGMobile'
alias atgsente='cd /scratch/svnwork/ATGMobile'


#
# -- HEPD bvn SVN stuff --
#
alias coswtools='svn co https://svn.bose.com/hepd/swtools/trunk swtools'
alias cobvn='svn co https://svn.bose.com/hepd/swtools/trunk/bvn bvn'
alias gobvn='cd /scratch/svnwork/bvn'


#
# -- HEPD MDD SVN stuff -- (local repository on "hepdsw34")
#
alias comdd='svn co svn+ssh://hepdsw34/scratch/svn/MDD/trunk MDD'
alias mdd='cd /scratch/svnwork/MDD'


#
# -- HEPD Shelby SVN stuff --
#

alias cowhippet='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/trunk whippet'
alias cowhippet2='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/trunk whippet2'

alias codp2='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/dp2_dce dp2'
alias comfg='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/manufacturing-0.7.2 manufacturing'
alias coexp='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/experimental experimental'
#alias cocert='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/airplay_cert airplay_cert'
alias cocert='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/airplay_cert_1.1.5 airplay_cert'
alias cotelnet='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/telnet bco_telnet'
alias co11x='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/1.1.x-release 1.1.x-release'
alias co12x='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/1.2.x-release 1.2.x-release'

alias cobeta='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/tags/trunk/0.9.0.4322 0.9.0.4322'
alias cosop='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/tags/trunk/1.0.0.4632 1.0.0.4632'
alias cosos='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/tags/trunk/1.1.6.5412 1.1.6.5412'

alias codp0='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/DP0 dp0'
alias comaxbdsp='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/port_max_bdsp maxbdsp'
alias cooldbdsp='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/old_bdsp oldbdsp'
alias codcedp1='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/dce_dp1 dce_dp1'

alias mkbranch='svn copy svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/trunk svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/old_bdsp -m "branch with cinnamon BDSP and with Airplay still working"'

alias whippet='cd $HEPDWORK/svnwork/whippet/whippet'
alias whippet2='cd $HEPDWORK/svnwork/whippet/whippet2'

alias dp0='cd $HEPDWORK/svnwork/whippet/dp0'
alias dcedp1='cd $HEPDWORK/svnwork/whippet/dce_dp1'
alias dp2='cd $HEPDWORK/svnwork/whippet/dp2'
alias exp='cd $HEPDWORK/svnwork/whippet/experimental'
alias mfg='cd $HEPDWORK/svnwork/whippet/manufacturing'
alias cert='cd $HEPDWORK/svnwork/whippet/airplay_cert'
alias bco_telnet='cd $HEPDWORK/svnwork/whippet/bco_telnet'
alias 11x='cd $HEPDWORK/svnwork/whippet/1.1.x-release'
alias 12x='cd $HEPDWORK/svnwork/whippet/1.2.x-release'

alias bco='cd $HEPDWORK/svnwork/whippet/whippet/Apps/BCO'
alias bsl='cd $HEPDWORK/svnwork/whippet/whippet/UnitTests/bsl'
alias pp='cd $HEPDWORK/svnwork/whippet/whippet/UnitTests/pingpong'
alias dsp='cd $HEPDWORK/svnwork/whippet/whippet/Apps/DSP'
alias dspmain='cd $HEPDWORK/svnwork/whippet/whippet/Apps/DSP/Main'
alias dspboot='cd $HEPDWORK/svnwork/whippet/whippet/Apps/DSP/Boot'
alias dspmfg='cd $HEPDWORK/svnwork/whippet/whippet/Apps/DSP/Manufacturing'
alias lpm='cd $HEPDWORK/svnwork/whippet/whippet/Apps/LPM'
alias lpmapp='cd $HEPDWORK/svnwork/whippet/whippet/Apps/LPM/LpmApp/LpmApp'
alias lpmboot='cd $HEPDWORK/svnwork/whippet/whippet/Apps/LPM/LpmBoot/LpmBoot'

alias colisa='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/lisa/trunk lisa'
alias lisa='cd $HEPDWORK/svnwork/shelby/lisa'

alias codonut='svn co svn+ssh://svn.bose.com/svn/hepd/ShelbyTCS/products/donut/trunk donut'
alias donut='cd $HEPDWORK/svnwork/whippet/donut'

alias cosdp='svn co svn+ssh://svn.bose.com/svn/hepd/Max/tags/01.02.02 sdp'
alias sdp='cd $HEPDWORK/svnwork/sdp'

alias cocinnamon='svn co svn+ssh://svn.bose.com/svn/hepd/Cinnamon/trunk cinnamon'
alias cinnamon='cd $HEPDWORK/svnwork/cinnamon'

alias coonyx='svn co svn+ssh://svn.bose.com/svn/hepd/Onyx/trunk onyx'
alias onyx='cd $HEPDWORK/svnwork/onyx'

alias copharos='svn co svn+ssh://svn.bose.com/svn/hepd/Pharos/trunk pharos'
alias pharos='cd $HEPDWORK/svnwork/pharos'

alias lsbranch='svn ls svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches'
alias lstag='svn ls svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/tags'


#
# -- HEPD Soundlink Mobile (Sente) SVN stuff --
#
export SENTEWORK="/scratch/svnwork/sente"
export SENTESPACE="trunk"

alias cosente='svn co https://svn.bose.com/hepd/Sente Sente'

# BigBen

alias cofolgers='svn co https://svn.bose.com/hepd/Sente/products/Folgers/trunk folgers'
alias folgers='cd $SENTEWORK/folgers'
alias fbt='cd $SENTEWORK/folgers/BT'
alias fsink='cd $SENTEWORK/folgers/BT/sh_adk4.0.0/projects/sink'

alias cofolgers251='svn co https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_ADK2_5 folgers251'
alias folgers251='cd $SENTEWORK/folgers251'

alias cofolgersdp15='svn co https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_DP15_ADK3.5 folgersdp15'
alias folgersdp15='cd $SENTEWORK/folgersdp15'

alias cofolgers8675='svn co https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_ADK35_DP15_8675 folgers8675'
alias folgers8675='cd $SENTEWORK/folgers8675'

alias cofolgers401='svn co https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_DP2_ADK4.0.1 folgers401'
alias folgers401='cd $SENTEWORK/folgers401'

alias cofolgersefe2='svn co https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_EFE2_ADK4.0 folgersefe2'
alias folgersefe2='cd $SENTEWORK/folgersefe2'

alias coharvey='svn co https://svn.bose.com/hepd/Sente/products/Harvey/trunk harvey'
alias harvey='cd $SENTEWORK/harvey'
alias hbt='cd $SENTEWORK/harvey/BT'
alias hsink='cd $SENTEWORK/harvey/BT/sh_adk3.5/projects/sink'

alias coharvey251='svn co https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_ADK2_5 harvey251'
alias harvey251='cd $SENTEWORK/harvey251'

alias coharveydp1='svn co https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_DP1_ADK3.5 harveydp1'
alias harveydp1='cd $SENTEWORK/harveydp1'

alias coharveydp2='svn co https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_DP2 harveydp2'
alias harveydp2='cd $SENTEWORK/harveydp2'

alias coharvey40='svn co https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_ADK4.0 harvey40'
alias harvey40='cd $SENTEWORK/harvey40'

alias coharvey401='svn co https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_DP2_ADK4.0.1 harvey401'
alias harvey401='cd $SENTEWORK/harvey401'

alias coharveyefe2='svn co https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_EFE2_ADK4.0 harveyefe2'
alias harveyefe2='cd $SENTEWORK/harveyefe2'

# Cleopatra
alias cohelios='svn co https://svn.bose.com/hepd/Sente/products/Helios/trunk helios'
alias helios='cd $SENTEWORK/helios'

alias cokleos='svn co https://svn.bose.com/hepd/Sente/products/Kleos/trunk kleos'
alias kleos='cd $SENTEWORK/kleos'

# Foreman
alias corocky='svn co https://svn.bose.com/hepd/Sente/products/Rocky/trunk rocky'
alias rocky='cd $SENTEWORK/rocky'

alias coforeman='svn co https://svn.bose.com/hepd/Sente/products/Foreman/trunk foreman'
alias foreman='cd $SENTEWORK/foreman'

alias coforemansop='svn co https://svn.bose.com/hepd/Sente/products/Foreman/branches/foreman_sop foremansop'
alias foremansop='cd $SENTEWORK/foremansop'

alias coforeman35='svn co https://svn.bose.com/hepd/Sente/products/Foreman/branches/Foreman_ADK3.5_DP1 foreman35'
alias foreman35='cd $SENTEWORK/foreman35'

alias covirtual='svn co https://svn.bose.com/hepd/Sente/products/VirtualSpeaker/trunk virtual'
alias virtual='cd $SENTEWORK/virtual'

# KCup
alias cokcup='svn co https://svn.bose.com/hepd/Sente/products/KCup/trunk kcup'
alias kcup='cd $SENTEWORK/kcup'
alias kbt='cd $SENTEWORK/kcup/BT'
alias ksink='cd $SENTEWORK/kcup/BT/sh_adk2.5.1/projects/sink'
alias klibs='cd $SENTEWORK/kcup/BT/sh_adk2.5.1/ADK2.5.1/src/lib'

alias cokcupsop='svn co https://svn.bose.com/hepd/Sente/products/KCup/branches/kcup_sop_2948 kcupsop'
alias kcupsop='cd $SENTEWORK/kcupsop'

alias cokcup40='svn co https://svn.bose.com/hepd/Sente/products/KCup/branches/KCup_adk4.x_rev3539 kcup40'
alias kcup40='cd $SENTEWORK/kcup40'

alias cokcup30='svn co https://svn.bose.com/hepd/Sente/products/KCup/branches/KCup_adk3.x kcup30'
alias kcup30='cd $SENTEWORK/kcup30'

alias cokcupdp25='svn co https://svn.bose.com/hepd/Sente/products/KCup/branches/kcup_dp25_2432 kcupdp25'
alias kcupdp25='cd $SENTEWORK/kcupdp25'

# Champ
alias cochamp='svn co https://svn.bose.com/hepd/Sente/products/Champ/trunk champ'
alias champ='cd $SENTEWORK/champ'

alias cochampdev='svn co https://svn.bose.com/hepd/Sente/products/Champ/branches/champ_dev_1746 champdev'
alias champdev='cd $SENTEWORK/champdev'

alias cochampsop='svn co https://svn.bose.com/hepd/Sente/products/Champ/branches/champ_sop_2076 champsop'
alias champsop='cd $SENTEWORK/champsop'

alias cochamp060='svn co https://svn.bose.com/hepd/Sente/products/Champ/tags/trunk/0.6.0.1496 champ060'
alias champ060='cd $SENTEWORK/champ060'

alias cochamphidden='svn co https://svn.bose.com/hepd/Sente/products/Champ/trunk champhidden'
alias champhidden='cd $SENTEWORK/champhidden'

alias bt='cd $SENTEWORK/champ/BT'
alias examples='cd $SENTEWORK/champ/BT/Examples'
alias dp0='cd $SENTEWORK/champ/BT/Examples/dp0_test_app'
alias dp1='cd $SENTEWORK/champ/BT/Examples/dp1_test_app'
alias dp2='cd $SENTEWORK/champ/BT/Examples/dp2_test_app'
alias sink='cd $SENTEWORK/champ/BT/sh_adk2.5.1/projects/sink'
alias vmlib='cd $SENTEWORK/champ/BT/sh_adk2.5.1/ADK2.5.1/src/lib'
alias libs='cd $SENTEWORK/champ/BT/sh_adk2.5.1/ADK2.5.1/src/lib'
alias sh_adk='cd $SENTEWORK/champ/BT/sh_adk2.5.1'
alias sh_build='cd $SENTEWORK/champ/BT/sh_build'

# BDSP
alias cosentebdsp='svn co https://svn.bose.com/hepd/SenteBDSP SenteBDSP'

alias cochampbdsp='svn co https://svn.bose.com/hepd/SenteBDSP/products/Champ/trunk champbdsp'
alias champbdsp='cd $SENTEWORK/champbdsp'
alias cokcupbdsp='svn co https://svn.bose.com/hepd/SenteBDSP/products/KCup/trunk kcupbdsp'
alias kcupbdsp='cd $SENTEWORK/kcupbdsp'
alias cofolgersbdsp='svn co https://svn.bose.com/hepd/SenteBDSP/products/Folgers/trunk folgersbdsp'
alias folgersbdsp='cd $SENTEWORK/folgersbdsp'
alias coharveybdsp='svn co https://svn.bose.com/hepd/SenteBDSP/products/Harvey/trunk harveybdsp'
alias harveybdsp='cd $SENTEWORK/harveybdsp'
alias coheliosbdsp='svn co https://svn.bose.com/hepd/SenteBDSP/products/Helios/trunk heliosbdsp'
alias heliosbdsp='cd $SENTEWORK/heliosbdsp'
alias coforemanbdsp='svn co https://svn.bose.com/hepd/SenteBDSP/products/Foreman/trunk foremanbdsp'
alias foremanbdsp='cd $SENTEWORK/foremanbdsp'

# NRTG
alias comoonraker='svn co https://svn.bose.com/nrtg/Moonraker/trunk moonraker'
alias moonraker='cd /scratch/svnwork/nrtg/moonraker'

alias coisaac='svn co https://svn.bose.com/nrtg/Isaac2.0/trunk isaac'
alias isaac='cd /scratch/svnwork/nrtg/isaac'

alias cowolf='svn co https://svn.bose.com/nrtg/Wolfcastle/trunk wolfcastle'
alias wolf='cd /scratch/svnwork/nrtg/wolfcastle'

alias coavalanche401='svn co https://svn.bose.com/nrtg/Avalanche/branches/Avalanche-ADK4.0.1 avalanche401'
alias avalanche401='cd /scratch/svnwork/nrtg/avalanche401'

alias comonet='svn co https://svn.bose.com/nrtg/Monet_HS/trunk monet'
alias monet='cs /scratch/svnwork/nrtg/monet'

# MTL
alias comtl='svn co https://svn.bose.com/hepd/MTL/trunk mtl'
alias mtl='cd /scratch/svnwork/mtl'

alias comtlcdc='svn co https://svn.bose.com/hepd/MTL/branches/USBCDC mtlcdc'
alias mtlcdc='cd /svnwork/mtlcdc'


alias covia='svn co https://svn.bose.com/hepd/Chihuahua/branches/Via_Palladium_2013'
alias coteacup='svn co https://svn.bose.com/hepd/Chihuahua/branches/Teacup_DP1_2013'
alias via='cd /scratch/svnwork/sente/Via_Palladium_2013'
alias teacup='cd /scratch/svnwork/sente/Teacup_DP1_2013'


#
# -- HEPD Springfield SVN stuff --
#
alias codocs='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/documentation docs'
alias codevtools='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/DevTools/trunk DevTools'

alias coherschel='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/targets/herschel/trunk herschel'
alias herschel='cd $HEPDWORK/svnwork/springfield/herschel'

alias cohomer='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/targets/homer/trunk homer'
alias homer='cd $HEPDWORK/svnwork/springfield/homer'

alias cosmithers='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/targets/smithers/trunk smithers'
alias smithers='cd $HEPDWORK/svnwork/springfield/smithers'

alias coslisa='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/targets/lisa/trunk lisa'
alias slisa='cd $HEPDWORK/svnwork/springfield/lisa'
alias slisa2='cd $HEPDWORK/svnwork/springfield/lisa2'

# Atheros PB93 SDK stuff
alias copb93='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/sdk/atheros/pb93/trunk pb93'
alias pb93='cd $HEPDWORK/svnwork/springfield/pb93'
#export PB93_SDK_DIR=$HEPDWORK/svnwork/springfield/pb93
export PB93_SDK_DIR=/opt/pb93
export DEFENDER_SDK_DIR=/opt/STM/STLinux-2.3/devkit

# Freescale ARM stuff
export FREESCALE_ARM=/opt/freescale/usr/local/gcc-4.1.2-glibc-2.5-nptl-3/arm-none-linux-gnueabi
#export CROSS_COMPILE=arm-none-linux-gnueabi-
export PATH="$PATH:$FREESCALE_ARM/bin"

# Chumby SDK stuff
alias cochumby='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/sdk/chumby/trunk chumby'
alias chumby='cd $HEPDWORK/svnwork/springfield/chumby'
export CHUMBY_SDK_DIR=$HEPDWORK/svnwork/springfield/chumby

alias buildsys='cd /scratch/bl12960/bose/predev/buildsys'
alias buildeval='cd $HEPDWORK/svnwork/springfield/DevTools/experimental/buildeval'


#
# -- HEPD Defender SVN stuff --
#
alias cotrunk='svn co svn+ssh://svn.bose.com/svn/hepd/Defender/trunk Defender'
alias codefender='svn co svn+ssh://svn.bose.com/svn/hepd/Defender/trunk Defender'

alias corosetta='svn co svn+ssh://svn.bose.com/svn/hepd/Rosetta/trunk Rosetta'
alias corosettabranch='svn co svn+ssh://svn.bose.com/svn/hepd/Rosetta/branches/rel_2.0 Rosetta'

alias cobranch='svn co svn+ssh://svn.bose.com/svn/hepd/Defender/branches/rel_01.04 Defender'
alias corelease='svn co svn+ssh://svn.bose.com/svn/hepd/Defender/branches/rel_01.04 Defender'

alias coefe='svn co svn+ssh://svn.bose.com/svn/hepd/Defender/branches/marley_efe2 Defender'

alias cocommon='svn co svn+ssh://svn.bose.com/svn/hepd/common/trunk common'
alias common='cd $HEPDWORK/svnwork/common'

#alias cotag='svn co svn+ssh://svn.bose.com/svn/hepd/Defender/tags/$1'

alias mergein="/scratch/bl12960/bin/mergein.sh"
alias mergeout="/scratch/bl12960/bin/mergeout.sh"

alias createbranch="/scratch/bl12960/bin/createbranch.sh"
alias createtag="/scratch/bl12960/bin/createtag.sh"
alias tagbranch="/scratch/bl12960/bin/tagbranch.sh"


#alias lsbranch='svn ls svn+ssh://svn.bose.com/svn/hepd/Defender/branches/Common'
#alias lsbranchpriv='svn ls svn+ssh://svn.bose.com/svn/hepd/Defender/branches/Common/private'

#alias lstag='svn ls svn+ssh://svn.bose.com/svn/hepd/Defender/tags'
#alias lstagbr='svn ls svn+ssh://svn.bose.com/svn/hepd/Defender/tags/branches'
#alias lstagtrunk='svn ls svn+ssh://svn.bose.com/svn/hepd/Defender/tags/trunk'

alias mkmarley='svn copy svn+ssh://svn.bose.com/svn/hepd/Defender/trunk svn+ssh://svn.bose.com/svn/hepd/Defender/branches/marley_04 -m "new Marley dev branch"'


#
# HEPD Defender project stuff
#

export HEPDWORK="/scratch"
export HEPDSPACE="svnwork/defender/trunk"
#export HEPDSPACE="svnwork/defender/branch"
#export HEPDSPACE="svnwork/defender/release"

alias scratch='cd /scratch/bl12960'
alias def='cd $HEPDWORK/$HEPDSPACE/Defender'
alias output='cd $HEPDWORK/$HEPDSPACE/Defender/BbOutput~/st7200c2-D'

alias branch='cd $HEPDWORK/svnwork/defender/branch/Defender'
alias release='cd $HEPDWORK/svnwork/defender/release/Defender'
alias trunk='cd $HEPDWORK/svnwork/defender/trunk/Defender'
alias trunk2='cd $HEPDWORK/svnwork/defender/trunk2/Defender'

alias rosetta='cd $HEPDWORK/svnwork/rosetta/rosetta2/Rosetta'

alias tools='cd /opt/STM/STLinux-2.3/devkit/sh4'

alias dynamic='cd $HEPDWORK/hepd/dynamic'
#alias dyntest='cd $HEPDWORK/hepd/dynamic/tests/dyntest'

alias avrd='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Infrastructure/AvRouting/AVRD'
alias avrdeh='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Apps/Main/ModelControllers/AVRDEventHandler'
alias defaults='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Infrastructure/DefaultsManager'
alias dprint='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Infrastructure/DebugPrint'
alias ext='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Apps/Main/ModelControllers/ExternalSource'
alias keys='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/LPM/LPMcode'
alias layer='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Apps/Main/ModelControllers/LayerStates'
alias lpmcode='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/LPM/LPMcode'
alias oval='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Apps/Main/ModelControllers/LayerStates/OvaltineController'
alias ovaltine='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Apps/Main/Ovaltine'
alias mb='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Apps/Main/ModelControllers/LayerStates/MoreButtonsController'
alias sl='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Apps/Main/ModelControllers/LayerStates/SourceListController'
alias options='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Apps/Main/ModelControllers/LayerStates/OptionsListController'
alias pdo='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/PDO'
alias paint='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Infrastructure/PaintBox'
alias uei='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/Infrastructure/ControlIntegration'
alias vm='cd $HEPDWORK/$HEPDSPACE/Defender/Components/ViewManager'
alias vmui='cd $HEPDWORK/$HEPDSPACE/Defender/Balboa/7200/UI/ViewManager'

#export CROSS_COMPILE="sh4-linux-"
export PATH="$PATH:/opt/STM/STLinux-2.3/devkit/sh4/bin:/tools/hepdsw/STM/ST40R4.0.2/bin:/tools/hepdsw/gnu-arm/bin"

export INSTALL_DIR="/scratch/target/home"

alias cachecheck='/usr/local/bin/valgrind --tool=cachegrind'
alias memcheck='/usr/local/bin/valgrind --tool=memcheck --leak-check=yes -v --show-reachable=yes'

alias callcheck='/usr/local/bin/valgrind --tool=callgrind --dump-instr=yes --trace-jump=yes'
alias kcall='kcachegrind callgrind.out.* &'

alias yamd='run-yamd -n -o yamd.log'

alias avrdbb='bb -debug target=avrdc3'
alias avrdbbc='bb -debug target=avrdc3 -clean'
alias defbb='bb -debug target=st7200c3'
alias defbbc='bb -debug target=st7200c3 -clean'
alias defdist='bb -distcc -debug target=st7200c3'
alias defut='bb -debug -unittest'

alias defmake='make'

# copy BoseApp data files to mounted target directory
#
# /tools/hepdsw/scripts/prepBoseAppData.sh <source> <dest>
#
alias defcopy='/tools/hepdsw/scripts/prepBoseAppData.sh $HEPDWORK/$HEPDSPACE/Defender $HEPDWORK/$HEPDSPACE/Defender/BbOutput~/st7200c3-D/Balboa/7200'

alias defcopyt='/tools/hepdsw/scripts/prepBoseAppData.sh $HEPDWORK/svnwork/defender/trunk/Defender $HEPDWORK/svnwork/defender/trunk/Defender/BbOutput~/st7200c3-D/Balboa/7200'

alias defcopyb='/tools/hepdsw/scripts/prepBoseAppData.sh $HEPDWORK/svnwork/defender/branch/Defender $HEPDWORK/svnwork/defender/branch/Defender/BbOutput~/st7200c3-D/Balboa/7200'




#
# -- ASD VOLO SVN stuff --
#

alias covolo='svn co svn+ssh://svn.bose.com/svn/asdmedia/volopre/trunk volopre'
alias covos='svn co svn+ssh://svn.bose.com/svn/asdmedia/volo_os/trunk volo_os'
alias covarchive='svn co svn+ssh://svn.bose.com/svn/asdmedia/volo_archive/trunk volo_archive'

#alias lsbranch='svn ls svn+ssh://svn.bose.com/svn/asdmedia/volopre/branches'
#alias lstag='svn ls svn+ssh://svn.bose.com/svn/asdmedia/volopre/tags'

#alias cobranch='~/bin/cobranch.sh'
#alias cotag='~/bin/cotag.sh'

#alias cobranch='svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1'
#alias cotag='svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1'

#function cobranch() { svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 PS_HU & }
#function cotag() { svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 PS_HU & }

function branchtrunk() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/trunk svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 -m "New dev branch" & }
function branchbranch() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$2 -m "New dev branch" & }
function branchtag() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$2 -m "New dev branch" & }

function tagtrunk() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/trunk svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 -m "Tagging trunk" & }
function tagbranch() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$2 -m "Tagging branch" & }
function tagtag() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$2 -m "Tagging tag" & }


#
# -- ASD EQUUS SVN stuff --
#

alias copshu='svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/trunk PS_HU'

#alias lsbranch='svn ls svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches'
#alias lstag='svn ls svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags'

#alias cobranch='svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1'
#alias cotag='svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1'

#function cobranch() { svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 PS_HU & }
#function cotag() { svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 PS_HU & }

function branchtrunk() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/trunk svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 -m "New dev branch" & }
function branchbranch() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$2 -m "New dev branch" & }
function branchtag() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$2 -m "New dev branch" & }

function tagtrunk() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/trunk svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 -m "Tagging trunk" & }
function tagbranch() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$2 -m "Tagging branch" & }
function tagtag() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$2 -m "Tagging tag" & }


#
# VOLO project stuff
#
#export VOLOWORK="/net/asdmedbld04/scratch/bl12960"
export VOLOWORK="/scratch/svnwork"
export VOLOSPACE="volo"
export VOLOPROJ="volopre"
export VOLOBASE="$VOLOWORK/$VOLOSPACE/$VOLOPROJ"

alias volopre='cd $VOLOBASE'
alias vp='cd $VOLOBASE'
alias vos='cd $VOLOBASE/../volo_os/OSfreescale'

alias vbranch='cd $VOLOWORK/branch/$VOLOPROJ'
alias vb='cd $VOLOWORK/branch/$VOLOPROJ'
alias vtrunk='cd $VOLOWORK/trunk/$VOLOPROJ'
alias vt='cd $VOLOWORK/trunk/$VOLOPROJ'

alias predev='cd $VOLOBASE/demo/predev'
#alias buildsys='cd $VOLOBASE/demo/predev/buildsys'
alias bsp='cd $VOLOBASE/demo/predev/bsp'
alias hw='cd $VOLOBASE/demo/predev/hw'

alias bsptests='cd $VOLOBASE/demo/predev/bsp/bsptests'
alias perftests='cd $VOLOBASE/demo/predev/bsp/perftests'
alias benchmarks='cd $VOLOBASE/demo/predev/bsp/benchmarks'
alias packages='cd $VOLOBASE/demo/predev/bsp/packages'
alias fbtest='cd $VOLOBASE/demo/predev/bsp/bsptests/fbtest'
alias pqtest='cd $VOLOBASE/demo/predev/bsp/perftests/pqtest'

## volo specific shortcuts
export LTIBBASE="/home/bl12960/volo"
alias volo='cd $LTIBBASE'
alias goltib='cd $LTIBBASE/OS/Linux/LTIB'

export LTIB_LITEB="$LTIBBASE/OS/Linux/LTIB/ltib-mpc5200-20070203"
#export LTIB_ADS="$LTIBBASE/OS/Linux/LTIB/ltib-mpc5121ads-20070830"
export LTIB_ADS="/scratch/volo/volo_os/OSfreescale/prebuilt/ltib-ads"

alias liteb='cd $LTIB_LITEB'
alias ads='cd $LTIB_ADS'

#export INSTALL_DIR="$LTIB_LITEB/rootfs/home"
#export INSTALL_DIR="$LTIB_ADS/rootfs/home"

# alternate 
#export PATH="/scratch/tools/cmake-2.8.3-Linux-i386/bin:$PATH"

export PATH="$PATH:/scratch/tools/firefox"
alias firefoxalt='/scratch/tools/firefox/firefox'

alias firefox='/usr/bin/firefox &'


#
# EQUUS project stuff
#
#
# source project specific setup script
# {modify PROJBASE to point to your Synergy work area}
#


#alias trunk='cd $CVSWORK/trunk/PS_HU'
#alias mainline='cd $CVSWORK/mainline/PS_HU'
#alias branch='cd $CVSWORK/branch/PS_HU'
#alias merge='cd $CVSWORK/merge/PS_HU'
#alias release='cd $CVSWORK/release/PS_HU'
#alias bugfix='cd $CVSWORK/bugfix/PS_HU'
#alias base='cd $CVSWORK/base/PS_HU'
#alias pv='cd $CVSWORK/pv/PS_HU'

#export WORKSPACE=trunk
export WORKSPACE=branch
export PROJBASE="$CVSWORK/$WORKSPACE"
export PROJECT="PS_HU"
export PROJHOME="$PROJBASE/$PROJECT"
alias progsrc='cd $PROJHOME'
alias ws='echo "workspace = $WORKSPACE"'

# -- Integrity stuff --
#export INTEGRITYBASE="/cygdrive/i/int505"
#export MULTIBASE="/cygdrive/c/ghs/ppc407"
#export MULTIBASE="/opt/ghs/multi/linux86"
#export PATH="$PATH:$MULTIBASE"
#export GHS_LMHOST="@Greenhills-lic"
#export GHS_LMPORT="27015"


#
# -- ELDK Linux stuff --
#
#export CROSS_COMPILE="ppc_82xx-"
#export PATH="$PATH:/opt/eldk/usr/bin:/opt/eldk/bin"
#alias crossgdb='ppc_82xx-gdb'
#alias mkcramfs='/opt/eldk/usr/bin/mkcramfs'


#
# -- Eclipse --
#
#export PATH="/scratch/tools/eclipse:$PATH"
#alias eclipse='/opt/tools/eclipse/eclipse'


#
# -- Source Navigator --
#
export PATH="$PATH:/scratch/tools/SN-NG3/bin"
alias snav='snavigator'
alias navb='snavigator /home/bl12960/Balboa.proj &'


#
# -- Other tools --
#

alias screenc='/usr/bin/synergyc -f USMA-0141-SD.bose.com &'
alias screens='/usr/bin/synergys --daemon --config /etc/synergy.conf'
#alias screens='/scratch/opt/bin/synergys --daemon --config /etc/synergy.conf'

export PATH="/scratch/opt/bin:$PATH"                      # python 2.7

export PATH="$PATH:/scratch/tools/scitools/bin/linux32"   # understand
export PATH="$PATH:/scratch/tools/eagle-5.6.0/bin"        # eagle cad
export PATH="$PATH:/scratch/tools/slickedit/bin"          # slickedit 11
alias slick='vs'

alias storybook='cd /scratch/tools/storybook ; ./storybook.sh'

alias wc2='/scratch/bl12960/bin/writerscafe2'

alias ecosenv='. /scratch/tools/ecos/ecosenv.sh'

alias deheader='/scratch/tools/deheader-0.6/deheader'

alias chrome='/opt/google/chrome/google-chrome &'


# QM / QP modeling tool
export QPC="/scratch/tools/qpc"
export QPCPP="/scratch/tools/qpcpp"
export QPN="/scratch/tools/qn"
export PATH="/scratch/tools/qm/bin:$PATH"


# USB devices

alias usbdev='cat /proc/bus/usb/devices'
alias goprocusb='cd /proc/bus/usb'

alias speedtest='/scratch/bl12960/bin/speedtest-linux'


# set prompt
PS1="[\u@\h \W]\\$ "

#export LD_LIBRARY_PATH=

# we're done here!!
if [ "$PS1" ]; then
echo "$HOSTNAME bashrc done."
fi
