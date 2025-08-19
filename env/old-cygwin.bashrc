# Local Cygwin .bashrc file
#

echo "starting .bashrc"

#umask 022

#noclobber=1
set -o noclobber

histsize=50

stty erase ^H
stty kill ^U
stty intr ^C
stty susp ^Z


#
# aliases
#

alias ls='ls -F --color'
alias lsc='ls --color=auto -F'
alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'

alias h='history'
alias j='jobs -l'
alias r='rlogin'
alias du='du -h'
alias df='df -kh'
alias cls='clear'
alias xt='xterm -bg black -fg white &'

alias more='less'

alias d2u='dos2unix'
alias u2d='unix2dos'

alias pretty4='/usr/bin/indent -bl -bli0 -cli4 -di4 -i4 -l160 -lc160 -npcs -nut'
alias prettyold='/usr/bin/indent -bli0 -i4 -l120 -lc120 -nut'
alias pretty='/usr/bin/indent -bl -bli0 -cli2 -di2 -i2 -l160 -lc160 -npcs -nut'

alias print='lpr -d //printserver/fmc4rich'
alias print3='lpr -d //printserver/fmc3rich'

alias th='telnet 192.168.0.200'
alias thpl='telnet 192.168.0.200'
alias treh='telnet reh'
alias tripley='telnet ripley'

alias fhpl='ftp 192.168.0.200'

alias pbishop='ping bishop'
alias tbishop='telnet bishop 8081'
alias fbishop='ftp bishop'

alias bose='cd /home/bl12960/bose'
alias demo='cd /home/bl12960/bose/demo'
alias qnx='cd /home/bl12960/bose/qnx'
alias litebsp='cd /home/bl12960/bose/qnx/litebsp'
alias misc='cd /home/bl12960/misc'
alias adgf='cd /home/bl12960/misc/adgf'

alias dm='cd /home/bl12960/bose/common/platform/cpu/diags/diagmon'

alias today='day.sh'

alias snarf='wget --recursive --page-requisites --html-extension --convert-links'
alias webgrab='wget -r -p -k'

alias pwr='~/bin/power-ctl'
alias on='~/bin/power-ctl 1'
alias off='~/bin/power-ctl 0'
alias toggle='off ; sleep 10 ; on'
alias tog='~/bin/toggle.sh'
alias state='cat ~/var/powerstate.log'

alias tone='~/bin/tonetest-exp 192.168.0.10 '
alias sweep='~/bin/sweeptest-exp 192.168.0.10 '

alias sysreset='~/bin/sysreset-exp 192.168.0.10'
alias rst='~/bin/sysreset-exp 192.168.0.10'

alias npp='/cygdrive/c/Utils/Notepad++/Notepad++.exe'

alias merge='/cygdrive/c/Utils/WinMerge/WinMergeU.exe'
alias compare='/cygdrive/c/Utils/WinMerge/WinMergeU.exe'

alias meld='/cygdrive/c/Utils/Meld/meld/meld.exe'

alias araxis='/cygdrive/c/Utils/Araxis/Araxis_Merge_v6.5/Merge.exe'

export SVNDIFF="/cygdrive/c/Utils/WinMerge/WinMergeU.exe"
#export SVNDIFF=/usr/bin/diff

alias svndiff='svn diff --diff-cmd $SVNDIFF'
#alias svndiff='svn diff --diff-cmd ~/bin/svndiff'

alias kdiff='/cygdrive/c/Utils/KDiff3/kdiff3.exe'

alias vicon='vicon-exp 192.168.0.10'


alias osm='cd ~/smtools/osm/ui'


export PERLDIR="/usr"

#alias eclipse='/cygdrive/c/Utils/eclipse/eclipse.exe'

# google web toolkit
export GWTBASE="/cygdrive/c/Utils/gwt-windows-1.5.3"
export PATH="$PATH:$GWTBASE"

# codeblocks IDE
export CBBASE="/cygdrive/c/Utils/CodeBlocks"
export PATH="$PATH:$CBBASE"


#
# functions
#
export GVIMPATH="/cygdrive/c/Utils/vim/vim82/gvim.exe"
function gvim() { $GVIMPATH $1 & }
function gv() { $GVIMPATH $1 & }
function ed() { $GVIMPATH $1 & }
#function pretty() { /usr/bin/indent -bli0 -i4 -l120 -lc120 $1 }

export NPPPATH="/cygdrive/c/Utils/Notepad++/Notepad++.exe"
function nv() { $NPPPATH $1 & }

export VSPATH="/cygdrive/c/Users/bl12960/AppData/Local/Programs/Microsoft\ VS\ Code/Code.exe"
function vs() { $VSPATH $1 & }

export ATOMPATH="/cygdrive/c/Users/bl12960/AppData/Local/atom/atom.exe"
function av() { $ATOMPATH $1 & }

alias pretty='/usr/bin/indent -bli0 -i4 -l120 -lc120 -nut'

function reconcile_wa {
    echo "Updating workspace for ${project} now..."
    cmd="ccm reconcile /project ${project} /missing_wa_file /recurse /report /update_wa /iu"
    echo "$cmd"
    $cmd
    echo $status
}




#
# cygwin x server
#
alias X='/usr/bin/X -multiwindow &'
alias x='rm -f ~/X.log ; /usr/bin/X -multiwindow &> ~/X.log &'


# 
# env variables
#
export DISPLAY="localhost:0.0"
echo "display is $DISPLAY"

export MAIL="~/Mail/inbox"

export PATH=".:/home/$USER/bin:/usr/sbin:/opt/cdrtools/bin:$PATH"

export MANPATH="$MANPATH:/opt/cdrtools/man"

#export SVNROOT="http://svn.fooe.net/slate"

#export EDITOR="gvim"
export EDITOR="/usr/bin/vi"


#
# java jdk stuff
#
export JAVAPATH="/cygdrive/c/Utils/Java/jdk1.7.0_13"
export PATH="$JAVAPATH/bin:$JAVAPATH/jre/bin:$PATH:$JAVAPATH/lib"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$JAVAPATH/lib:$JAVAPATH/jre/lib"
export MANPATH="$MANPATH:$JAVAPATH/man"


# Graphviz
export PATH="$PATH:/cygdrive/c/Utils/Graphviz2.30/bin"


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
# -- Generic SVN stuff --
#

alias scan='svn -q status | sort'
alias scanl='svn -N -q status | sort'
alias scanu='svn status -u | sort'
alias scani='svn status -u --ignore-externals'

alias update='svn update'
alias updatel='svn -N update'

alias ci='svn ci -m'
alias add='svn add'

alias externals='svn propget svn:externals'
alias lsexternals='svn propget svn:externals'
alias editexternals='svn propedit svn:externals'



# 
# QT stuff
#
export QTDIR="/cygdrive/c/QtSDK/Desktop/Qt/4.8.0/mingw"
export QTCREATORDIR="/cygdrive/c/QtSDK/QtCreator"
export MINGPATH="/cygdrive/c/QtSdk/mingw"
export PATH="$PATH:$QTDIR/bin:$QTCREATORDIR/bin"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$QTDIR/lib"
export QMAKESPEC="C:\QtSDK\Desktop\Qt\4.8.0\mingw\mkspecs\cygwin-g++"


# 
# LibSDL stuff
#
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/lib"


#
# -- HEPD bvn SVN stuff --
#
alias coswtools='svn co https://svn.bose.com/hepd/swtools/trunk swtools'
alias cobvn='svn co https://svn.bose.com/hepd/swtools/trunk/bvn bvn'
alias gobvn='cd /svnwork/bvn'

alias cocommon='svn co svn+ssh://svn.bose.com/svn/hepd/common/trunk common'
alias common='cd /svnwork/common'

alias coverlib='svn co svn+ssh://svn.bose.com/svn/hepd/common/trunk/VersionLib VersionLib'
alias verlib='cd /svnwork/VersionLib'


#
# -- HEPD MDD SVN stuff -- (local repository on "hepdsw34")
#
alias comdd='svn co svn+ssh://hepdsw34/scratch/svn/MDD/trunk MDD'
alias mdd='cd /svnwork/MDD'


#
# -- HEPD Shelby SVN stuff --
#
export WHIPWORK="/svnwork/whippet"

alias cowhippet='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/trunk trunk'
alias cowhippet2='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/trunk trunk2'

alias codp2='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/dp2_dce dp2'
alias comfg='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/manufacturing-0.7.2 manufacturing'
alias coexp='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/experimental experimental'
#alias cocert='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/airplay_cert airplay_cert'
alias cocert='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/airplay_cert_1.1.5 airplay_cert'
alias cotelnet='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/telnet bco_telnet'
alias co11x='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/1.1.x-release 1.1.x-release'
alias co12x='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/1.2.x-release 1.2.x-release'

alias cosop='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/tags/trunk/1.0.0.4632 100_sop'
alias cosos='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/tags/trunk/1.1.6.5412 116_sos'

alias codp0='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/DP0 dp0'
alias comaxbdsp='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/port_max_bdsp maxbdsp'
alias cooldbdsp='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/old_bdsp oldbdsp'
alias codcedp1='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/dce_dp1 dce_dp1'

#alias mkbranch='svn copy svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/trunk svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches/old_bdsp -m "branch with cinnamon BDSP and with Airplay still working"'

alias whippet='cd $WHIPWORK/trunk'
alias whippet2='cd $WHIPWORK/trunk2'

alias trunk='cd $WHIPWORK/trunk'
alias trunk2='cd $WHIPWORK/trunk2'


alias dcedp1='cd $WHIPWORK/dce_dp1'
#alias dp2='cd $WHIPWORK/dp2'
alias exp='cd $WHIPWORK/experimental'
alias mfg='cd $WHIPWORK/manufacturing'
alias cert='cd $WHIPWORK/airplay_cert'
alias bco_telnet='cd $WHIPWORK/bco_telnet'
alias 11x='cd $WHIPWORK/1.1.x-release'
alias 12x='cd $WHIPWORK/1.2.x-release'

export WHIPSPACE="trunk"

alias bco='cd $WHIPWORK/$WHIPSPACE/Apps/BCO'
alias bsl='cd $WHIPWORK/$WHIPSPACE/UnitTests/bsl'
alias pp='cd $WHIPWORK/$WHIPSPACE/UnitTests/pingpong'
alias dsp='cd $WHIPWORK/$WHIPSPACE/Apps/DSP'
alias dspmain='cd $WHIPWORK/$WHIPSPACE/Apps/DSP/Main'
alias dspboot='cd $WHIPWORK/$WHIPSPACE/Apps/DSP/Boot'
alias dspmfg='cd $WHIPWORK/$WHIPSPACE/Apps/DSP/Manufacturing'
alias lpm='cd $WHIPWORK/$WHIPSPACE/Apps/LPM'
alias lpmapp='cd $WHIPWORK/$WHIPSPACE/Apps/LPM/LpmApp/LpmApp'
alias lpmboot='cd $WHIPWORK/$WHIPSPACE/Apps/LPM/LpmBoot/LpmBoot'

alias coslisa='svn co svn+ssh://svn.bose.com/svn/hepd/Shelby/products/lisa/trunk lisa'
alias lisa='cd /svnwork/shelby/lisa'

alias codonut='svn co svn+ssh://svn.bose.com/svn/hepd/ShelbyTCS/products/donut/trunk donut'
alias donut='cd /svnwork/donut'

alias cosdp='svn co svn+ssh://svn.bose.com/svn/hepd/Max/tags/01.02.02 sdp'
alias sdp='cd /svnwork/sdp'

alias cocinnamon='svn co svn+ssh://svn.bose.com/svn/hepd/Cinnamon/trunk cinnamon'
alias cinnamon='cd /svnwork/cinnamon'

alias coonyx='svn co svn+ssh://svn.bose.com/svn/hepd/Onyx/trunk onyx'
alias onyx='cd /svnwork/onyx'

alias copharos='svn co svn+ssh://svn.bose.com/svn/hepd/Pharos/trunk pharos'
alias pharos='cd /svnwork/pharos'

alias lsbranch='svn ls svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/branches'
alias lstag='svn ls svn+ssh://svn.bose.com/svn/hepd/Shelby/products/whippet/tags'


#
# -- CEPE Advanced Development --
#

alias cochipmunk='svn co https://svn.bose.com/nrtg/RAD_Labs/SmartANR_RevC/trunk chipmunk'
alias chipmunk='cd /svnwork/ad/chipmunk'

alias cochipmunkbdsp='svn co https://svn.bose.com/nrtg/RAD_Labs/ChipmunkBDSP/trunk chipmunkbdsp'
alias chipmunkbdsp='cd /svnwork/ad/chipmunkbdsp'

alias cogoodyear='svn co https://svn.bose.com/nrtg/RAD_Labs/Goodyear_Frankenstein/trunk goodyear'
alias goodyear='cd /svnwork/ad/goodyear'


#
# -- HEPD Soundlink Mobile (Sente) SVN stuff --
#
export SENTEWORK="/svnwork/sente"
export SENTESPACE="trunk"

alias 000champ='cd /cygdrive/c/cygwin/000champ'
alias 000kcup='cd /cygdrive/c/cygwin/000kcup'
alias 000folgers='cd /cygdrive/c/cygwin/000folgers'
alias 000harvey='cd /cygdrive/c/cygwin/000harvey'
alias 000foreman='cd /cygdrive/c/cygwin/000foreman'
alias 000m3='cd /cygdrive/c/cygwin/000m3'

alias cosente='svn co https://svn.bose.com/hepd/Sente Sente'


alias csrmake='/svnwork/sente/foreman/BT/sh_adk3.5/ADK3.5/tools/bin/make.exe'


# Minnow
alias cominnow='svn co https://svn.bose.com/hepd/Sente/products/Minnow/trunk minnow'
alias minnow='cd $SENTEWORK/minnow'
alias msink='cd $SENTEWORK/minnow/BT/sh_adk4.0.1/projects/sink'

# BigBen
alias cofolgers='svn co https://svn.bose.com/hepd/Sente/products/Folgers/trunk folgers'
alias folgers='cd $SENTEWORK/folgers'
alias fbt='cd $SENTEWORK/folgers/BT'
alias fsink='cd $SENTEWORK/folgers/BT/sh_adk4.0.1/projects/sink'

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
alias hsink='cd $SENTEWORK/harvey/BT/sh_adk4.0.1/projects/sink'

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

alias cokcup30='svn co https://svn.bose.com/hepd/Sente/products/KCup/branches/KCup_adk3.x kcup30'
alias kcup30='cd $SENTEWORK/kcup30'

alias cokcup40='svn co https://svn.bose.com/hepd/Sente/products/KCup/branches/KCup_adk4.x_rev3539 kcup40'
alias kcup40='cd $SENTEWORK/kcup40'

alias mkkcupdp25branch='svn copy -r 2432 https://svn.bose.com/hepd/Sente/products/KCup/trunk https://svn.bose.com/hepd/Sente/products/KCup/branches/kcup_dp25_2432 -m "branch of kcup trunk at rev 2432 for dp2.5"'
alias cokcupdp25='svn co https://svn.bose.com/hepd/Sente/products/KCup/branches/kcup_dp25_2432 kcupdp25'
alias kcupdp25='cd $SENTEWORK/kcupdp25'

# create branch for M3 development (new battery pack for KCup)
alias mkm3branch='svn copy -r 3827 https://svn.bose.com/hepd/Sente/products/KCup/trunk https://svn.bose.com/hepd/Sente/products/KCup/branches/kcup_m3_3827 -m "branch of kcup trunk at rev 3827 for m3 dev work"'
alias com3='svn co https://svn.bose.com/hepd/Sente/products/KCup/branches/kcup_m3_3827 kcupm3'
alias kcupm3='cd $SENTEWORK/kcupm3'

alias com3='svn co https://svn.bose.com/hepd/Sente/products/KCup/branches/m3 m3'
alias m3='cd $SENTEWORK/m3'

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
alias moonraker='cd /svnwork/nrtg/moonraker'

alias coisaac='svn co https://svn.bose.com/nrtg/Isaac2.0/trunk isaac'
alias isaac='cd /svnwork/nrtg/isaac'

alias comonet='svn co https://svn.bose.com/nrtg/Monet_HS/trunk monet'
alias monet='cd /svnwork/nrtg/monet'

alias coavalanche401='svn co https://svn.bose.com/nrtg/Avalanche/branches/Avalanche-ADK4.0.1 avalanche401'
alias avalanche401='cd /svnwork/nrtg/avalanche401'

alias copagera4vr='svn co https://svn.bose.com/nrtg/RAD_Labs/Pager/branches/a4vr pagera4vr'
alias pagera4vr='cd /svnwork/nrtg/pagera4vr'


# Hadrian
#alias corio='git clone ssh://git@github.com:BoseCorp/rio.git rio'
alias corio='git clone https://github.com/BoseCorp/rio.git rio'
alias rio='cd /svnwork/nrtg/rio'

alias cocase='git clone https://github.com/BoseCorp/rio_charging_case.git case'
alias case='cd /svnwork/nrtg/case'

alias cocypress='git clone https://github.com/BoseCorp/rio_sensor_cypress.git cypress'
alias cypress='cd /svnwork/nrtg/rio_sensor_cypress'

alias coearbud='git clone https://github.com/BoseCorp/rio_earbud_application.git earbud'
alias earbud='cd /svnwork/nrtg/earbud'

alias cohadrian='git clone https://github.com/BoseCorp/CE-CD-Hadrian-Demo.git hadrian'
alias hadrian='cd /svnwork/nrtg/HadrianDisney'
alias hadrianproject='cd /svnwork/nrtg/HadrianDisney/sinkapp/apps/applications/sink/qcc512x_qcc302x/CF376_CF429'


alias gwen='cd ~/gitwork/nrtg/gwen/rio'

alias ov='cd ~/gitwork/nrtg/olivia-vedder/rio'
alias ovcypress='cd ~/gitwork/nrtg/olivia-vedder/rio_sensor_cypress'

alias riocase='cd ~/gitwork/nrtg/rio_charging_case'

alias left='cd /svnwork/nrtg/HadrianDisney/earbudapp'

alias demo='cd /cygdrive/c/Users/bl12960/Documents/MySink-6-3-0-154'
alias demoproject='cd /cygdrive/c/Users/bl12960/Documents/MySink-6-3-0-154/apps/applications/sink/qcc512x_qcc302x/CF376_CF212'

alias builds='cd /svnwork/nrtg/builds'


alias status='git status --untracked-files=no .'


# MTL
alias comtl='svn co https://svn.bose.com/hepd/MTL/trunk mtl'
alias mtl='cd /svnwork/mtl'

alias comtlcdc='svn co https://svn.bose.com/hepd/MTL/branches/USBCDC mtlcdc'
alias mtlcdc='cd /svnwork/mtlcdc'


alias covia='svn co https://svn.bose.com/hepd/Chihuahua/branches/Via_Palladium_2013'
alias coteacup='svn co https://svn.bose.com/hepd/Chihuahua/branches/Teacup_DP1_2013'
alias via='cd /svnwork/sente/Via_Palladium_2013'
alias teacup='cd /svnwork/sente/Teacup_DP1_2013'


# branch of kcup BDSP tree for prototyping bdsp code for folgers and harvey platforms
alias mkfolgersonkcup='svn copy -r 379 https://svn.bose.com/hepd/SenteBDSP/products/KCup/trunk https://svn.bose.com/hepd/SenteBDSP/products/KCup/branches/FolgersOnKcup -m "branch of kcup bdsp trunk at 379 for running folgers on kcup hw"'
alias mkharveyonkcup='svn copy -r 379 https://svn.bose.com/hepd/SenteBDSP/products/KCup/trunk https://svn.bose.com/hepd/SenteBDSP/products/KCup/branches/HarveyOnKcup -m "branch of kcup bdsp trunk at 379 for running harvey on kcup hw"'
alias cofolgersonkcup='svn co https://svn.bose.com/hepd/SenteBDSP/products/KCup/branches/FolgersOnKcup folgersonkcup'
alias folgersonkcup='cd $SENTEWORK/folgersonkcup'
alias coharveyonkcup='svn co https://svn.bose.com/hepd/SenteBDSP/products/KCup/branches/HarveyOnKcup harveyonkcup'
alias harveyonkcup='cd $SENTEWORK/harveyonkcup'


# branches of folgers and harvey bdsp prototyping branches for running on DP1 hw
alias mkfolgersdp1bdsp='svn copy -r HEAD https://svn.bose.com/hepd/SenteBDSP/products/KCup/branches/FolgersOnKcup https://svn.bose.com/hepd/SenteBDSP/products/KCup/branches/FolgersDP1adk251BDSP -m "branch of FolgersOnKcup for running on folgers DP1 hw under adk2.5.1"'
alias mkharveydp1bdsp='svn copy -r HEAD https://svn.bose.com/hepd/SenteBDSP/products/KCup/branches/HarveyOnKcup https://svn.bose.com/hepd/SenteBDSP/products/KCup/branches/HarveyDP1adk251BDSP -m "branch of HarveyOnKcup for running on harvey DP1 hw under adk2.5.1"'
alias cofolgersdp1bdsp='svn co  https://svn.bose.com/hepd/SenteBDSP/products/KCup/branches/FolgersDP1adk251BDSP folgersdp1bdsp'
alias coharveydp1bdsp='svn co  https://svn.bose.com/hepd/SenteBDSP/products/KCup/branches/HarveyDP1adk251BDSP harveydp1bdsp'

# branches of folgers and harvey trunks for running adk2.5.1 on DP1 hw
alias mkfolgers251branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Folgers/trunk https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_ADK2_5 -m "branch of Folgers trunk for running adk2.5.1 on Folgers DP1 hardware"'
alias mkharvey251branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Harvey/trunk https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_ADK2_5 -m "branch of Harvey trunk for running adk2.5.1 on Harvey DP1 hardware"'

alias mkharveydp2branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Harvey/trunk https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_DP2 -m "branch of Harvey trunk for running adk3.5 on Harvey DP2 hardware"'
alias mkharvey40branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_DP2 https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_ADK4.0 -m "branch of Harvey DP2 branch for running adk4.0 on Harvey DP2 hardware"'

alias mkshbuild8675branch='svn copy https://svn.bose.com/nrtg/SharedComponents/sh_headset_build/tags/trunk/00.00.91 https://svn.bose.com/nrtg/SharedComponents/sh_headset_build/branches/folgers_8675_tag_00.00.91 -m "branch of sh_build from trunk tag 00.00.91 for folgers 8675 changes"'



# archive branches for Folgers DP1.5 and Harvey DP1 using ADK3.5
alias mkfolgersdp15adk35branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Folgers/trunk https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_DP15_ADK3.5 -m "branch Folgers trunk DP1.5 hardware with adk3.5"'
alias mkharveydp1adk35branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Harvey/trunk https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_DP1_ADK3.5 -m "branch Harvey trunk DP1 hardware with adk3.5"'



# branch of folgers trunk for ADK4.0.1 porting work
alias mkfolgersadk401branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Folgers/trunk https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_DP2_ADK4.0.1 -m "branch Folgers trunk DP2 hardware with adk4.0.1"'
# branch of harvey trunk for ADK4.0.1 porting work
alias mkharveyadk401branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Harvey/trunk https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_DP2_ADK4.0.1 -m "branch Harvey trunk DP2 hardware with adk4.0.1"'


# branch of folgers trunk for ADK4.0.1 SOP releases
alias mkfolgerssopbranch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Folgers/trunk https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_SOP_ADK4.0.1 -m "branch Folgers trunk for SOP with adk4.0.1"'
# branch of harvey trunk for ADK4.0.1 SOP releases
alias mkharveysopbranch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Harvey/trunk https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_SOP_ADK4.0.1 -m "branch Harvey trunk for SOP with adk4.0.1"'

# Big Ben SOP branch of mobile audio branch of ADK4.0.1 "BIGBEN_SOP_MA_adk4.0.1"
alias mkadk401bgibensopbranch='svn copy -r 7375 https://svn.bose.com/nrtg/SharedComponents/sh_adk4.0.1/branches/MA_adk4.0.1_tag_00.00.01 https://svn.bose.com/nrtg/SharedComponents/sh_adk4.0.1/branches/BIGBEN_SOP_MA_adk4.0.1 -m "branch of mobile audio ADK4.0.1 branch for BIGBEN SOP"'




# branch of folgers trunk for EFE2 reference (i.e. ADK4.0)
alias mkfolgersefe2branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Folgers/trunk https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_EFE2_ADK4.0 -m "branch Folgers trunk as EFE2 reference on ADK4.0"'
# branch of harvey trunk for EFE2 reference (i.e. ADK4.0)
alias mkharveyefe2branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Harvey/trunk https://svn.bose.com/hepd/Sente/products/Harvey/branches/Harvey_EFE2_ADK4.0 -m "branch Harvey trunk as EFE2 reference on ADK4.0"'



# tag sh_Tools for ADK2.5.1 version of CLiUpdater
alias tagshtools='svn copy -r 3615 https://svn.bose.com/hepd/Sente/common/Tools/trunk https://svn.bose.com/hepd/Sente/common/Tools/tags/trunk/TAG_sh_Tools_ADK251_rev3615 -m "tag of Sente sh_Tools that works with ADK2.5.1"'


# branch of folgers trunk for running adk3.5 on DP1.5 hw
alias mkfolgersdp15branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Folgers/trunk https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_ADK35_DP15 -m "branch of Folgers trunk for running adk3.5 on Folgers DP1.5 hardware"'

# branch of folgers trunk for running adk3.5 on DP1 hw (snapshot, not to be actually used)
alias mkfolgersadk35dp1branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Folgers/trunk https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_ADK35_DP1 -m "branch of Folgers trunk for running adk3.5 on Folgers DP1 hardware"'

# branch of folgers Folgers_ADK35_DP15 branch for running adk3.5 on DP1.5 hw for 8675 (Folgers trunk will become DP1.5 for 8670)
alias mkfolgers8675branch='svn copy -r HEAD  https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_ADK35_DP15 https://svn.bose.com/hepd/Sente/products/Folgers/branches/Folgers_ADK35_DP15_8675 -m "branch of Folgers trunk for running adk3.5 on Folgers DP1.5 hardware with 8675"'


# branch of Foreman trunk for running ADK3.5 on DP1 hw (Foreman trunk is now on ADK4.0)
alias mkforeman35branch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Foreman/trunk https://svn.bose.com/hepd/Sente/products/Foreman/branches/Foreman_ADK3.5_DP1 -m "branch of Foreman trunk for running adk3.5 on Foreman DP1 hardware"'

# branch of Foreman trunk for running ADK4.0 via tags on DP1 hw
alias mkforeman40tagbranch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Foreman/trunk https://svn.bose.com/hepd/Sente/products/Foreman/branches/Foreman_ADK4.0_via_tags -m "branch of Foreman trunk for running adk4.0 via tags on Foreman DP1 hardware"'


# branch of Foreman trunk for 
alias mkforeman40tagbranch='svn copy -r HEAD https://svn.bose.com/hepd/Sente/products/Foreman/trunk https://svn.bose.com/hepd/Sente/products/Foreman/branches/Foreman_ADK4.0_via_tags -m "branch of Foreman trunk for running adk4.0 via tags on Foreman DP1 hardware"'


# helios branch of ADK3.5 "helios_adk3.5_tag_00.00.84"
alias mkadk35heliosbranch='svn copy -r 3885 https://svn.bose.com/nrtg/SharedComponents/sh_adk3.5/tags/trunk/00.00.84 https://svn.bose.com/nrtg/SharedComponents/sh_adk3.5/branches/helios_adk3.5_tag_00.00.84 -m "branch of adk3.5 from tag 00.00.84 for helios"'

# kleos branch of ADK4.0 "kleos_adk4.0_tag_00.00.57"
alias mkadk40kleosbranch='svn copy -r 5177 https://svn.bose.com/nrtg/SharedComponents/sh_adk4.0.0/tags/trunk/00.00.57 https://svn.bose.com/nrtg/SharedComponents/sh_adk4.0.0/branches/kleos_adk4.0_tag_00.00.57 -m "branch of adk4.0 from tag 00.00.57 for kleos"'


# kcup branch of ADK4.0 "kcup_adk4.0_tag_00.00.09"
alias mkadk40kcupbranch='svn copy -r 4615 https://svn.bose.com/nrtg/SharedComponents/sh_adk4.0.0/tags/trunk/00.00.09 https://svn.bose.com/nrtg/SharedComponents/sh_adk4.0.0/branches/kcup_adk4.0_tag_00.00.09 -m "branch of adk4.0 from tag 00.00.09 for kcup4.x work"'


# mobile audio branch of ADK4.0.1 "MA_adk4.0.1_tag_00.00.01"
alias mkadk401branch='svn copy -r 6333 https://svn.bose.com/nrtg/SharedComponents/sh_adk4.0.1/tags/trunk/00.00.01 https://svn.bose.com/nrtg/SharedComponents/sh_adk4.0.1/branches/MA_adk4.0.1_tag_00.00.01 -m "branch of adk4.0.1 from tag 00.00.01 for mobile audio ADK4.0.1 work"'


# champ trunk now uses sh_adk2.5.1 branch "champ_sos_release_2870"
alias mkadksopbranch='svn copy -r 2625 https://svn.bose.com/nrtg/SharedComponents/sh_adk2.5.1/branches/trunk/champ02_00.00.02 https://svn.bose.com/nrtg/SharedComponents/sh_adk2.5.1/branches/trunk/champ_sop_release_2625 -m "branch of champ02_00.00.02 rev 2625 for SOP release"'
alias mkadksosbranch='svn copy -r 2870 https://svn.bose.com/nrtg/SharedComponents/sh_adk2.5.1/branches/trunk/champ02_00.00.02 https://svn.bose.com/nrtg/SharedComponents/sh_adk2.5.1/branches/trunk/champ_sos_release_2870 -m "branch of champ02_00.00.02 rev 2870 for SOS release"'

# rocky dev branch based on Champ sos release branch "rocky_hfp_dev_3445"
alias mkadkrockybranch='svn copy -r 3445 https://svn.bose.com/nrtg/SharedComponents/sh_adk2.5.1/branches/trunk/champ_sos_release_2870 https://svn.bose.com/nrtg/SharedComponents/sh_adk2.5.1/branches/trunk/rocky_hfp_dev_3445 -m "branch of champ_sos_release_2870 at rev 3445 for rocky hfp development"'

# champ dev branch continues to use sh_adk2.5.1 branch "champ02_00.00.02"
alias mkdevbranch='svn copy -r 1746 https://svn.bose.com/hepd/Sente/products/Champ/trunk https://svn.bose.com/hepd/Sente/products/Champ/branches/champ_dev_1746 -m "branch of champ trunk at rev 1746 for development"'

# champ sop branch uses sh_adk2.5.1 branch "champ_sop_release_2625" [reference only - this branch is now orphaned]
alias mkchsopbranch='svn copy -r 2076 https://svn.bose.com/hepd/Sente/products/Champ/trunk https://svn.bose.com/hepd/Sente/products/Champ/branches/champ_sop_2076 -m "branch of champ trunk at rev 2076 for SOP reference"'

alias mkkcupadksopbranch='svn copy -r 3737 https://svn.bose.com/nrtg/SharedComponents/sh_adk2.5.1/branches/trunk/champ02_00.00.02 https://svn.bose.com/nrtg/SharedComponents/sh_adk2.5.1/branches/trunk/kcup_sop_release_3737 -m "branch of champ02_00.00.02 rev 3737 for KCup SOP release"'
alias mkkcupsopbranch='svn copy -r 2948 https://svn.bose.com/hepd/Sente/products/KCup/trunk https://svn.bose.com/hepd/Sente/products/KCup/branches/kcup_sop_2948 -m "branch of kcup trunk at rev 2948 for SOP reference"'

# kcup 4.x branch of 3.x branch for 4.0 porting/development
alias mkkcup40branch='svn copy -r 3539 https://svn.bose.com/hepd/Sente/products/KCup/branches/KCup_adk3.x https://svn.bose.com/hepd/Sente/products/KCup/branches/KCup_adk4.x_rev3539 -m "branch of KCup_adk3.x at rev 3539 for 4.0 development"'

#alias mkbranch='svn copy svn+ssh://svn.bose.com/svn/hepd/SenteBDSP/products/Champ/trunk svn+ssh://svn.bose.com/svn/hepd/SenteBDSP/products/Champ/branches/hiding_secrets -m "branch with our secret sauce hidden/removed"'
alias cochampbdspbranch='svn co http:://svn.bose.com/hepd/SenteBDSP/products/Champ/branches/hiding_secrets champbdspbranch'
alias champbdspbranch='cd $SENTEWORK/champbdspbranch'



#
# -- HEPD Springfield SVN stuff --
#
export SFWORK="/scratch/springfield"

alias codocs='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/documentation docs'

alias coherschel='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/targets/herschel/trunk herschel'
alias colisa='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/targets/lisa/trunk oldlisa'

alias herschel='cd $SFWORK/herschel'
alias oldlisa='cd $SFWORK/oldlisa'



# Atheros PB93 SDK stuff
alias copb93='svn co svn+ssh://svn.bose.com/svn/hepd/Springfield/sdk/atheros/pb93/trunk pb93'
alias pb93='cd $SFWORK/pb93'
export PB93_SDK_DIR=$SFWORK/pb93

alias buildsys='cd ~/bose/predev/buildsys'


#
# -- HEPD Defender SVN stuff --
#
#export SVNBASE="/cygdrive/c/Utils/CollabNetSubversionClient"
#export PATH="$PATH:$SVNBASE"

#alias cotrunk='svn co svn+ssh://svn.bose.com/svn/hepd/Defender/trunk Defender'
#alias cobranch='svn co svn+ssh://svn.bose.com/svn/hepd/Defender/branches/Common/integration Defender'
#alias cotag   ='svn co svn+ssh://svn.bose.com/svn/hepd/Defender/tags/$1'
alias comarley='svn co svn+ssh://svn.bose.com/svn/hepd/Defender/branches/marley_efe2 Defender'

alias lsbranch='svn ls svn+ssh://svn.bose.com/svn/hepd/Defender/branches/Common'
alias lsbranchpriv='svn ls svn+ssh://svn.bose.com/svn/hepd/Defender/branches/Common/private'

alias lstag='svn ls svn+ssh://svn.bose.com/svn/hepd/Defender/tags'
alias lstagbr='svn ls svn+ssh://svn.bose.com/svn/hepd/Defender/tags/branches'
alias lstagtrunk='svn ls svn+ssh://svn.bose.com/svn/hepd/Defender/tags/trunk'

alias mkmarley01='svn copy svn+ssh://svn.bose.com/svn/hepd/Defender/trunk svn+ssh://svn.bose.com/svn/hepd/Defender/branches/marley_efe2 -m "new Marley efe branch"'
alias mkmarley='mkmarley01'


alias corosetta='svn co svn+ssh://svn.bose.com/svn/hepd/Rosetta/trunk Rosetta'
alias rosetta='cd /scratch/rosetta/Rosetta'



#
# -- Volo SVN stuff --
#
alias covolo='svn co svn+ssh://svn.bose.com/svn/asdmedia/volopre/trunk volopre'
alias covos='svn co svn+ssh://svn.bose.com/svn/asdmedia/volo_os'
alias covarchive='svn co svn+ssh://svn.bose.com/svn/asdmedia/volo_archive/trunk volopre'

function cobranch() { svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 PS_HU & }
function cotag() { svn co svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 PS_HU & }

function branchtrunk() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/trunk svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 -m "New dev branch" & }
function branchbranch() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$2 -m "New dev branch" & }
function branchtag() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$2 -m "New dev branch" & }

function tagtrunk() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/trunk svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 -m "Tagging trunk" & }
function tagbranch() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/branches/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$2 -m "Tagging branch" & }
function tagtag() { svn copy svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$1 svn+ssh://svn.bose.com/svn/asdmedia/PS_HU/tags/$2 -m "Tagging tag" & }




#
# -- Bouml stuff --
#

export BOUMLBASE="/cygdrive/c/Utils/Bouml"
export PATH="$PATH:$BOUMLBASE"



#
# VOLO project stuff
#
#export VOLOWORK="/net/asdmedbld04/scratch/bl12960"
export VOLOWORK="/scratch/volowork"
export VOLOSPACE="trunk"
export VOLOPROJ="volopre"
export VOLOBASE="$VOLOWORK/$VOLOSPACE/$VOLOPROJ"

alias volopre='cd $VOLOBASE'
alias vp='cd $VOLOBASE'

alias bsp='cd $VOLOBASE/platform/bsp'
alias hw='cd $VOLOBASE/platform/hw'

alias bsptests='cd $VOLOBASE/platform/bsp/bsptests'
alias perftests='cd $VOLOBASE/platform/bsp/perftests'
alias benchmarks='cd $VOLOBASE/platform/bsp/benchmarks'
alias packages='cd $VOLOBASE/platform/bsp/packages'

alias fbtest='cd $VOLOBASE/platform/bsp/bsptests/fbtest'


#
# HEPD project stuff
#
# source project specific setup script
# {modify PROJBASE to point to your SVN work area}
#
# HEPDWORK order -- C drive
#

export HEPDWORK="/scratch"

export PROJECT="Defender"

#alias trunk='cd $HEPDWORK/trunk/$PROJECT'
#alias branch='cd $HEPDWORK/branch/$PROJECT'
#alias marley='cd $HEPDWORK/marley/$PROJECT'

export WORKSPACE=trunk
#export WORKSPACE=branch
#export WORKSPACE=marley

export PROJBASE="$HEPDWORK/$WORKSPACE"

export PROJHOME="$PROJBASE/$PROJECT"

alias ws='echo "workspace = $WORKSPACE"'

alias def='cd $PROJHOME'

alias layer='cd $PROJHOME/Balboa/7200/Apps/Main/ModelControllers/LayerStates'
alias options='cd $PROJHOME/Balboa/7200/Apps/Main/ModelControllers/LayerStates/OptionsListController'
alias oval='cd $PROJHOME/Balboa/7200/Apps/Main/ModelControllers/LayerStates/OvaltineController'
alias mb='cd $PROJHOME/Balboa/7200/Apps/Main/ModelControllers/LayerStates/MoreButtonsController'
alias sl='cd $PROJHOME/Balboa/7200/Apps/Main/ModelControllers/LayerStates/SourceListController'
alias vm='cd $PROJHOME/Components/ViewManager'
alias vmui='cd $PROJHOME/Balboa/7200/UI/ViewManager'


#
# define global aliases
#
alias evs='env | sort'
alias edit='vim'
alias rebash='. ./.bashrc'
alias tlocal='telnet localhost'

alias psgrep='ps -aef | grep'
alias grepch='grep --include=*.c --include=*.cpp --include=*.h -r -n --color'

alias dbox='cd /cygdrive/c/Users/bl12960/Dropbox'
alias cpdbox='cpdbox.sh'

alias github='cd /cygdrive/c/Users/bl12960/Documents/GitHub'

alias speedtest='/cygdrive/c/Utils/speedtest-64.exe'

alias mplab='/cygdrive/c/"Program Files (x86)"/Microchip/"MPLAB IDE"/Core/mplab.exe'
#unalias mplab
#export MPLABBASE='/cygdrive/c/"Program Files (x86)"/Microchip/"MPLAB IDE"/Core'
#export PATH=$PATH:$MPLABBASE

export PATH=$PATH:/cygdrive/c/"Program Files (x86)"/VideoLAN/VLC


#
echo "cygwin bashrc done."

