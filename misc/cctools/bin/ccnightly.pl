#!/usr/local/bin/perl
#
# ccnightly.pl - Merge and Build script for use with cron jobs
#                and at jobs under ClearCase.  
#
# Usage:
#	ccnightly <BOTH|MERGE|BUILD> <viewname> [<src_br_list>]
#
# Options:
#
#	<BOTH|MERGE|BUILD>	- perform merge and build, 
# 				  merge only, or build only
#
#	<view_name>		- name of a ClearCase view {verified to exist}
#
#	<src_br_list>		- source branch list file 
#				  {required for merge, but used for build
#				  to send result email; see format below}
#
#
# Source Branch List Format:
#
#	branch <source_branch_1>
#	branch <source_branch_2>
#	...
#	branch <source_branch_N>
#	email <email_address_1>
#	email <email_address_2>
#	...
#	email <email_address_N>
#
#
# Revisions:
#	06/17/98 BSL	source branch list file also used for build results
#	05/15/98 BSL	modified format of source branch list file 
#	05/14/98 BSL	added mailing of result log 
#	05/13/98 BSL	added checks for merge conflicts 
#	05/11/98 BSL	added merge function 
#	05/06/98 BSL	converted from prototype shell script
#	04/23/98 BSL 	originated
#


if (@ARGV < 2) {
   print "Not enough arguments!\n";
   &Usage;
   exit 1;
}
else {
   $action = $ARGV[0];
   $viewname = $ARGV[1];
}

if (@ARGV == 3) {
   $listpath = $ARGV[2];
}


#
# define environment variables
#
$smmroot = $ENV{SMMROOT};
$projhome = $ENV{PROJHOME};



#
# define common variables
#
$maillog = "$smmroot/mail_log";

$mailtool = "/usr/ucb/mail";
$mailuser = "null";

$mailsubject = "null";



#
# define build variables
#
$buildscript = "$projhome/bin/smm_ccbuild.sh";

$makelog = "$smmroot/make_log";
$checkbuild = "grep -cw Error $makelog";

$target = "ALL";
$level = "root";

$buildsuccess = 0;


#
# define merge variables
#
$fmctl = "/usr/atria/bin/cleartool";
$fmcmd = "findmerge";

$fmvobs = "-avobs";
$fmfver = "-fver";

$fmnc = "-nc";
$fmmerge = "-merge";
$fmabort = "-abort";

$fmlog = "-log";
$fmdevnull = "/dev/null";
$fmprint = "-print";

$srcbranch = "null";

$mergesuccess = 0;



#
# if specified, perform build action only
#
if ($action =~ /BUILD/) {
   &BuildAction;
   &VerifyBuild;
   if ( $buildsuccess == 1 ) {
      print "Build completed with no errors\n";
      &HandleSucceeded;
   }
   else {
      print "Build failed, please review $makelog\n";
      &HandleBuildFailed;
   }
   exit 0;
}


#
# if specified, perform merge action only
#
if ($action =~ /MERGE/) {
   &MergeAction;
   if ( $mergesuccess == 1 ) {
      print "Merge completed with no conflicts\n";
      &HandleSucceeded;
   }
   else {
      print "Merge failed, please review $maillog\n";
      &HandleMergeFailed;
   }
   exit 0;
} 


#
# if specified, perform merge then build action
#
if ($action =~ /BOTH/) {
   &MergeAction;
   if ( $mergesuccess == 1 ) {
      print "Merge completed with no conflicts\n";
      &BuildAction;
      &VerifyBuild;
      if ( $buildsuccess == 1 ) {
         print "Build completed with no errors\n";
         $CheckinFiles;
         &HandleSucceeded;
      }
      else {
         print "Build failed, please review $maillog\n";
         &HandleBuildFailed;
      }
   }
   else {
      print "Merge failed, please review $maillog\n";
      &HandleMergeFailed;
   }
   exit 0;
} 


#
# if we get to here, an unknown action was specified
#
print "Error - unknown action specified - $action \n"; 
exit 1;




#
# Function to print usage statement
# 
sub Usage
{
   print "Usage: ccnightly <BOTH|MERGE|BUILD> <view_name> [<src_br_list>]\n";
   print "(i.e.  ccnightly BUILD main)\n";
   print "(i.e.  ccnightly MERGE dev_ne_feature dev_ne_feature.lst)\n";
   print "(i.e.  ccnightly BOTH  int_ne_prod    int_ne_prod.lst)\n";
}


#
# Function to send mail log message to users in source branch list
# 
sub SendMail
{
   unless (open SBL, $listpath) {
      print "Couldn't open source branch list file!\n";
      print "Warning, no email message was sent.\n";
   }
   while ( $line = <SBL> ) {
      chop $line;

      if ( $line =~ /email/ ) {
         @Line = split ' ', $line;

         $mailuser = $Line[1];

         print "Mailing log - $mailsubject - $mailuser\n";

         $mailcmd = "$mailtool -s $mailsubject $mailuser < $maillog";
         open( MTL, "$mailcmd | ") or die "Can't execute mail command!\n";
         $dummy = <MTL>;
      }
      close(SBL);
   }
}


#
# Function to verify build success
#
sub VerifyBuild
{
   print "Verifying build ......\n";

   open( CHK, "$checkbuild | ") or die "Couldn't run verify build cmd!\n";

   $count = <CHK>;
   chop $count;
   # print "count = ", $count, "\n";

   if ( $count == 0 ) {
      $buildsuccess = 1;
   }
   else {
      $buildsuccess = 0;
   }
   close(CHK);
}


#
# Function to check in modified files from merge/build
#
sub CheckinFiles
{
   print "Checking in modified files ......\n";


}


#
# Function to append timing log to mail log
#
sub AppendTimingLog
{

}


#
# Function to append changes log to mail log
#
sub AppendChangesLog
{

}


#
# Function to handle merge/build succeeded
#
sub HandleSucceeded
{
   unless (open FRL, ">$maillog") {
      print "Couldn't open mail log file!\n";
      exit 1;
   }

   print FRL "Merge/Build Succeeded\n";
   print FRL "---------------------------------------\n";
   print FRL "Action       = $action\n";
   print FRL "Build view   = $viewname\n";
   print FRL "---------------------------------------\n";
   print FRL "\n";

   &AppendTimingLog;
   &AppendChangesLog;

   close(FRL);

   $mailsubject = "\"$viewname merge/build success\"";

   &SendMail;
}


#
# Function to handle build failed
#
sub HandleBuildFailed
{
   unless (open FRL, ">$maillog") {
      print "Couldn't open mail log file!\n";
      exit 1;
   }

   print FRL "Build Failed\n";
   print FRL "---------------------------------------\n";
   print FRL "Action       = $action\n";
   print FRL "Build view   = $viewname\n";
   print FRL "---------------------------------------\n";
   print FRL "\nPlease review $makelog for details.\n";
   print FRL "\n";

   close(FRL);

   $mailsubject = "\"$viewname build failed\"";

   &SendMail;
}


#
# Function to handle merge failed
#
sub HandleMergeFailed
{
   local( $conflict = 0 );
   local( $filepath );

   unless (open FRL, ">$maillog") {
      print "Couldn't open mail log file!\n";
      exit 1;
   }

   print FRL "Merge Failed\n";
   print FRL "---------------------------------------\n";
   print FRL "Action       = $action\n";
   print FRL "Merge view   = $viewname\n";
   print FRL "---------------------------------------\n";
   print FRL "\nFailed while merging from $fmbranch\n";
   print FRL "\nThe following files had merge conflicts:\n";

   unless (open FLF, $fmlogfile) {
      print "Couldn't open merge log file!\n";
      exit 1;
   }
   while ( $filepath = <FLF> ) {
      chop $filepath;

      unless ( $filepath =~ /#/ ) {
         @list = split ' ', $filepath;
         print FRL "   $list[2]\n";
         $conflict = 1;
      }
   }

   if ( $conflict == 1 ) {
      print FRL "\nReason for failure is file conflicts were detected.\n";
   }
   else {
      print FRL "\nReason for failure is couldn't execute the findmerge command.\n";
   }
   print FRL "\n";

   close(FRL);

   $mailsubject = "\"$viewname merge failed\"";

   &SendMail;
}


#
# Function to perform build action
#
sub BuildAction 
{
   print "Performing build ......\n";

   @Build = ($buildscript, $viewname, $target, $level);
   #         print "Build: \n@Build\n";

   system(@Build) == 0 or die "Can not execute build script!\n";

   print "Done build ......\n";
}


#
# Function to perform merge action
#
sub MergeAction
{
   print "Performing merge ......\n";

   if (@ARGV == 3) {
      print "Using source branch list - $listpath\n";
      unless (open SBL, $listpath) {
         print "Couldn't open source branch list file!\n";
         exit 1;
      }
      while ( $line = <SBL> ) {
         chop $line;

         if ( $line =~ /branch/ ) {
            @Line = split ' ', $line;

            $srcbranch = $Line[1];

            print "Merging from source branch - $srcbranch\n";

            $fmbranch = ".../$srcbranch/LATEST";
            $fmlogfile = "$hdmroot/$srcbranch.mergelog";

            @Merge = ($fmctl, $fmcmd, $fmvobs, $fmfver, $fmbranch, $fmnc, $fmlog, $fmlogfile, $fmmerge, $fmabort);
            #@Merge = ($fmctl, $fmcmd, $fmvobs, $fmfver, $fmbranch, $fmlog, $fmlogfile, $fmprint);
            #         print "Merge: \n@Merge\n";

            if ( system(@Merge) == 0 ) {
               $mergesuccess = 1;
            }
            else {
               $mergesuccess = 0;
               last;
            }
         }
      }
      close(SBL);
   }
   else {
      print "Not enough arguments for merge!\n";
      &Usage;
      exit 1;
   }

   print "Done merge ......\n";
}


# end of ccnightly.pl
