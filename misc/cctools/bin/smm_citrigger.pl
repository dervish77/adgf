#!/usr/local/bin/perl

# This script will parse the command used for the checkin. It will
# verify the exact syntax of the checkin, & ensure that it follows the
# standard. 

# The syntax being checked for is :

# "MR# <number>; fix [complete | incomplete]; by <name1 name2 ...>; reviewer <name1 name2 ...>;
# effort <#days>; Comments ... "

sub parse_comment {
    my $comment = pop (@_);
    my ($mr, $fix, $by, $reviewer, $effort, @ci_comment) = split (';', $comment);

    # start validating all the vars now
    # First MR#

    $_ = $mr;
    my ($a1, $a2, @a3) = split;
    if ($a1 ne 'MR#') {
	return "invalid_mr_head";
    }
    if (int $a2 <= 0) {
	return "invalid_mr";
    }
    if (defined @a3) {
	return "invalid_mr_tail";
    }

    # Second, Username
    $_ = $by;
    my ($b1, @b2) = split;
    if ($b1 ne 'by') {
	return ("invalid_by_head");
    }
    if (! defined @b2) {
	return ("invalid_by");
    }

    # Third, reviewer
    $_ = $reviewer;
    my ($c1, @c2) = split;
    if ($c1 ne 'reviewer') {
	return ("invalid_reviewer_head");
    }
    if (! defined @b2) {
	return ("invalid_reviewer");
    }

    # Fourth, Effort
    $_ = $effort;
    my ($d1, $d2, $d3, @d4) = split;
    if ($d1 ne 'effort') {
	return ("invalid_effort_head");
    }
    unless (($d2 =~ /\A.\d*\..\d*\Z/) || ($d2 =~ /\A.\d*\Z/)) {
	return ("invalid_effort");
    }
    if ($d3 ne 'days') {
	return ("invalid_effort_tail");
    }
    if (defined @d4) {
	return ("invalid_effort_tail");
    }

    #Last, Check existence of comment
    unless (scalar (@ci_comment) >= 1) {
	return ("invalid_comment");
    }

    # First Addition : Fix completion status
    $_ = $fix;
    my ($e1, $e2, @e3) = split;
    if ($e1 ne 'fix') {
	return "invalid_fix_head";
    }
    unless ($e2 eq 'complete' || $e2 eq 'incomplete') {
	return "invalid_fix";
    }
    if (defined @e3) {
	return "invalid_fix_tail";
    }
    

    # All OK Now !
    return ("valid_checkin");
}

print &parse_comment ($ARGV[0]), "\n";
