#!/bin/sh
#
# createbranch
#
#	Creates a branch type in ClearCase and generates 
#	corresponding config spec in the current directory.
#
# Usage:
#	createbranch <type> <name> [<label>]
#
# Options:
#	<type>			- type of branch [DEV, INT, BUG, ER]
#
#	<branch_name>		- name of the new branch
#
#	[<label>]		- label for ER branch type
#
#
# Revisions:
#	06/18/98 BSL 	originated
#


#
# verify arguments
#
if [ $# -lt 2 ]
then
  echo "Usage: createbranch <type> <branch_name>    [<label>]"
  echo "(i.e.  createbranch DEV    dev_ne_feature)"
  echo "(i.e.  createbranch INT    int_ne_smm_beta_01.03.00)"
  echo "(i.e.  createbranch BUG    dev_ne_mr0225)"
  echo "(i.e.  createbranch ER     smm_er_01.05.00  REL_SMM_PROD_01.05.00)"
  exit 1
else
  TYPE=$1
  NAME=$2
fi

if [ $# -eq 3 ]
then
  LABEL=$3
fi


case $TYPE in
  DEV)
	;;
  INT)
	;;
  BUG)	
	;;
  ER)
	;;
  *)
	echo "Error - unsupported type specified - $TYPE"
	echo "        Valid type are  DEV, INT, BUG, ER"
	exit 1
	;;
esac

echo "Creating branch $NAME as type $TYPE"

$CCHOME/bin/mktype.pl br -nc $NAME

if [ $# -eq 3 ]
then
  $PROJHOME/bin/smm_csgen.pl $TYPE $NAME $LABEL
else
  $PROJHOME/bin/smm_csgen.pl $TYPE $NAME
fi


echo "Done"

exit 0
