#!/usr/local/bin/perl

@commandsyntax = 
    ("ci [<options>] [<single filename>]",
     "Options are :",
     "[-f <filelisttocheckin>] -myco",
     "[-mr <MR#>] [-c[omment] \"one line description of fix\"]",
     "[-h[elp]] [-re[viewer] <name>] [-e[ffort] <days>]",
     "[-batchmode] [-complete | -incomplete]",
     " ",
     "Special MRs that can be used :",
     "MR# 1707  =>  For debug code.",
     "MR# 1556  =>  For use by Release Management only");

$, = "\n";

# understand the above flags
$myco = 'false';
$mailrecipients = 'hdm_software@3com.com';
#$mailrecipients = 'rameshwar_sundaresan@3com.com';
$nomail = 'false';

for ($ii = 0; $ii < int (@ARGV); $ii++) {
    
    $elem = $ARGV[$ii];
    if ($elem eq '-f') {
	$ii++;
	$elem = $ARGV[$ii];
	if ($elem =~ /-/ || !defined $elem) {
	    die "-f option needs a list of files to commit\n";
	}
	if ($myco eq 'true') {
	    print "Myco option given first : ignoring -f option\n";
	}
	else {
	    $filelisttocheckin = $ARGV[$ii];	    
	}
    }
    elsif ($elem eq '-myco') {
	if (defined $filelisttocheckin) {
	    print "File List given first : ignoring the -myco option\n";
	}
	else {
	    $myco = 'true';	    
	}
    }
    elsif ($elem eq '-mr') {
	$ii++;
	$elem = $ARGV[$ii];
	if ($elem =~ /-/ || !defined $elem) {
	    die "-mr needs an Modification Request # from tracker\n";
	}
	$mr = $elem;
    }
    elsif ($elem eq '-c' || $elem eq '-comment') {
	$ii++;
	$elem = $ARGV[$ii];
	if ($elem =~ /-/ || !defined $elem) {
	    die "-comment needs a string description\n";
	}
	$comment = $elem;
    }
    elsif ($elem eq '-re' || $elem eq '-reviewer') {
	$ii++;
	$elem = $ARGV[$ii];
	if ($elem =~ /-/ || !defined $elem) {
	    die "-reviewer needs a name\n";
	}
	$reviewer = $elem;
    }
    elsif ($elem eq '-effort' || $elem eq '-e') {
	$ii++;
	$elem = $ARGV[$ii];
	if (($elem =~ /-/) || (!($elem =~ /\A.\d*\..\d*\Z/) && 
	    !($elem =~ /\A.\d*\Z/)) || (!defined $elem)) {
	    die "-effort needs number of days effort (fraction allowed)\n";
	}
	$effort = $elem;
    }
    elsif ($elem eq '-h' || $elem eq '-help') {
	print @commandsyntax, "\n";
	exit;
    }

    elsif ($elem eq '-batchmode' || $elem eq '-ba') {
	$batchmode = 'true';
    }

    elsif ($elem eq '-complete') {
	if (defined $complete) {
	    die "-complete && -incomplete are mutually exclusive";
	}
	$complete = 'yes';
    }

    elsif ($elem eq '-incomplete') {
	if (defined $complete) {
	    die "-complete && -incomplete are mutually exclusive";
	}
	$complete = 'no';
    }

    elsif ($elem eq '-nomail') {
	$nomail = 'true';
    }
    
    elsif ($elem =~ '-') {
	print "cannot understand option $elem\n";
	print @commandsyntax, "\n";
	exit;
    }
    else {
	if (defined $filelisttocheckin || $myco eq 'true') {
	    print "Ignoring filename, file list got by other means\n";
	}
	$filename = $elem;
    }
}

# compulsary arguments

print "\nWelcome to the checkin tool\n\n" unless defined $batchmode;
print "usage ", @commandsyntax, "\n\nInteractive Mode\n\n" unless defined $batchmode;

#MR

getMR:
if (!defined $mr) {
    if (defined $batchmode) {
	print "You MUST enter an MR#\n";
	exit;
    }
    print "Please enter the MR # : ";
    $mr = int <STDIN>;
    print "\n";
}
if ($mr <= 0) {
    print "MR entered not a number, please enter a valid MR\n";
    exit if defined $batchmode;
    undef $mr;
    goto getMR;
}

# IS THE FIX FOR ABOVE MR COMPLETE OR NOT

getCOMPLETE:
if (!defined $complete) {
    if (defined $batchmode) {
	print "You MUST give one of -complete/-incomplete\n";
	exit;
    }
    print "Is the fix for MR# $mr Complete ? (yes/no) : ";
    $complete = <STDIN>;
    print "\n";
    chop $complete;
    unless (($complete eq 'yes') || ($complete eq 'no')) {
	print "You must give \'yes\' or \'no\'\n";
	undef $complete;
	goto getCOMPLETE;
    }
}

#Effort

getEffort:
if (!defined $effort) {
    if (defined $batchmode) {
	print "You MUST enter Effort in #days\n";
	exit;
    }
    print "Please enter the Effort #days (fractions permitted) : ";
    $effort = <STDIN>;
    chop $effort;
    print "\n";
}
unless (($effort =~ /\A.\d*\..\d*\Z/) || ($effort =~ /\A.\d*\Z/)) {
    print "Effort entered not a number, please enter a valid Effort in #days \n";
    exit if defined $batchmode;
    undef $effort;
    goto getEffort;
}

#comment

getcomment:
if (!defined $comment) {
    if (defined $batchmode) {
	print "You must enter a short description, option -comment\n";
	exit;
    }
    print "Please enter a short description of the fix : ";
    $comment = <STDIN>;
    chop $comment;
    print "\n";
}

unless (length ($comment) > 1) {
    print "You MUST enter a description, please try again\n";
    exit if defined $batchmode;
    undef $comment;
    goto getcomment;
}

#filename

getfilename:

@filelisttocheckin = ();
@rejected_filelist = ();
@accepted_filelist = ();

if (defined $filelisttocheckin) {
    open FILESTOCHECKIN, "<$filelisttocheckin";
    while (<FILESTOCHECKIN>) {
	chop;
	if (length ($_) > 1) {
	    push @filelisttocheckin, $_;
	}
    }
}
elsif ($myco eq 'true') {
    open FILESTOCHECKIN, "/usr/atria/bin/cleartool lsprivate -co -sh |";
    while (<FILESTOCHECKIN>) {
	chop;
	push @filelisttocheckin, $_;
    }
}
elsif (!defined $filename) {
    if (defined $batchmode) {
	print "You have not entered the file to commit\n";
	exit;
    }
    print "Give the file(s) to checkin : ";
    $filename = <STDIN>;
    chop $filename;
    if ($filename ne '') {
	@filelisttocheckin = split (/[ \t]/, $filename);
    }
}
else {
    push @filelisttocheckin, $filename;
}

foreach $filename (@filelisttocheckin) {
    $exfilname = `/usr/atria/bin/cleartool ls -s $filename`;
    @junklist = split ('/', $exfilname);
    $branch = $junklist[-2];
    $oldbranch = $branch unless defined $oldbranch; # initialise
    if (! -e $filename) {
	print "The given file \'$filename\' does not exist\n";
	exit if defined $batchmode;
	undef @filelisttocheckin;
	undef $filelisttocheckin;
	last;
    }
    chop $junklist[-1];
    if ($junklist[-1] ne "CHECKEDOUT") {
	print "The given file \'$filename\' is not checkedout\n";
	exit if defined $batchmode;
	undef @filelisttocheckin;
	undef $filelisttocheckin;
	last;
    }
    if ($oldbranch ne $branch) {
	print "Files seem to come from different branches\n";
	print "PLEASE ABORT && CONTACT RELEASE ENGINEER !\n";
	exit (-1);
    }
    print ('.') if ! defined $batchmode;
    
    $filediffs = `/usr/atria/bin/cleartool diff -pre -opt -headers_only $filename`;
    if ($filediffs =~ "Files are identical") {
	push @rejected_filelist, $filename;
    }
    else {
	push @accepted_filelist, $filename;
    }
}
if (!defined @filelisttocheckin) {
    undef $filename;
    goto getfilename;
}

print "\nNow all the following fields are optional\n" if !defined $batchmode;

# Person to Contact
# No option of giving a different developer's name compared to who
# is checking in
$developer = `whoami`;
chop $developer;

# reviewer
if (!defined $reviewer) {
    $reviewer = "none";
    if (! defined $batchmode) {
	print "Please enter the name of the reviewer : ";
	$reviewer = <STDIN>;
	chop ($reviewer);
	if ($reviewer eq '') {
	    $reviewer = "none";
	}
    }
}

if (!defined $batchmode) {
    print "\n\nThis is the information I have gathered from you\n\n";
    print "BRANCH         : $branch\n";
    print "MR#            : $mr\n";
    print "FIX COMPLETE ? : $complete\n";
    print "EFFORT (#days) : $effort\n";
    print "COMMENT        : $comment\n";
    print "DEVELOPER      : $developer\n";
    print "REVIEWER       : $reviewer\n";
    if (int @accepted_filelist > 0) {
	print "LIST OF FILES THAT WILL BE COMMITED\n";
	print @accepted_filelist, "\n";    
    }
    if (int @rejected_filelist > 0) {
	print "LIST OF FILES IDENTICAL TO PREDECESSOR\n";
	print "YOU WILL NEED TO UNCHECKOUT THESE FILES\n";
	print @rejected_filelist, "\n";
    }
    print "Proceed with commit (\'yes\' proceeds, anything else aborts) : ";
    $proceed = <STDIN>;
    chop $proceed;
    if ($proceed ne 'yes') {
	print "ABORTED BY YOU : EXITING\n";
	exit;
    }
}

if ($complete eq 'yes') {
    $complete = 'complete';
}
else {
    $complete = 'incomplete';
}

print "Committing : please wait\n" unless defined $batchmode;

foreach $filename (@accepted_filelist) {
    print "executing : /usr/atria/bin/cleartool ci -c \"MR# $mr; fix $complete; by $developer; reviewer $reviewer; effort $effort days; $comment\" $filename\n" unless defined $batchmode;
    `/usr/atria/bin/cleartool ci -c \"MR# $mr; fix $complete; by $developer; reviewer $reviewer; effort $effort days; $comment\" $filename`;
    if ($? != 0) {
	if (defined $batchmode) {
	    `echo ERROR | mailx -s \"clearcase error in commiting $filename
: $? \" $developer`;
	}
	else {
	    print "clearcase error commiting $filename : $?";
	}
    }
}

# $logfile = "/net/ice/users/hdmbuild/CHECKIN_LOGS/$branch.log";
# print "Logging into $logfile\n" unless defined $batchmode;

# open LOGFILE, ">>$logfile";

# print LOGFILE  "BRANCH         : $branch\n";
# print LOGFILE  "MR#            : $mr\n";
# print LOGFILE  "EFFORT #days   : $effort\n";
# print LOGFILE  "HEADER         : $header\n";
# print LOGFILE  "DEVELOPER      : $developer\n";
# print LOGFILE  "REVIEWER       : $reviewer\n";
# print LOGFILE  "TYPE OF COMMIT : $type_of_commit\n";
# print LOGFILE  "LIST OF FILES COMMITED\n";
# print LOGFILE  @filelisttocheckin, "\n";
# print LOGFILE  "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";

# close LOGFILE;

unless ($nomail eq 'true') {
    print "Mailing to $mailrecipients\n" unless defined $batchmode;
    open MAILTO, "| mailx -s \"Checkin to $branch by $developer for MR# $mr\" $mailrecipients";
    print MAILTO  "BRANCH         : $branch\n";
    print MAILTO  "MR#            : $mr\n";
    print MAILTO  "FIX COMPLETE ? : $complete\n";
    print MAILTO  "EFFORT #days   : $effort\n";
    print MAILTO  "COMMENT        : $comment\n";
    print MAILTO  "DEVELOPER      : $developer\n";
    print MAILTO  "REVIEWER       : $reviewer\n";
    print MAILTO  "LIST OF FILES CHECKED IN\n";
    print MAILTO  @accepted_filelist, "\n";
    close MAILTO;
}

print "Thank You\n\n" unless defined $batchmode;

