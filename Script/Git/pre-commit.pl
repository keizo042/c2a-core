#!/usr/bin/perl

print "pre-commit msg.\n";

my $DEBUG = 0;

### 不要なファイルのコミットを防止

my $err_flag = 0;

my @Targets = (
		"Examples/minimum_user_for_s2e/src/src_user/Settings/CmdTlm/DataBase/CMD_DB/SAMPLE_MOBC_CMD_DB.xlsm",
		"Examples/minimum_user_for_s2e/src/src_user/Settings/CmdTlm/DataBase/TLM_DB/SAMPLE_MOBC_TLM_DB.xlsm",
		"Examples/minimum_user_for_s2e/src/src_user/Settings/sils_define.h",
		"Examples/minimum_user_for_s2e/src/src_user/Settings/build_settings.h",
		"Examples/minimum_user_for_s2e/src/src_user/Library/git_revision.c"
	);

print "[] pwd\n" if $DEBUG;
print `pwd`, "\n" if $DEBUG;

# hookを自動更新
print "[] cp hook\n" if $DEBUG;
# my $cp_ret = `\cp -f  ./Script/Git/pre-commit.pl ./.git/hooks/pre-commit`;			# \つけたら動かん....？
my $cp_ret = `cp -f  ./Script/Git/pre-commit.pl ./.git/hooks/pre-commit`;
print $cp_ret, "\n" if $DEBUG;

# my $files = `git status|grep -e "modified" -e "new file"|sed "s/new file:\(.*\)/\1/g"|sed "s/modified:\(.*\)/\1/g"|cut -f 2`;
# my $files = `git status|grep -e "modified" -e "new file"`;
# ↑これだと，addされてないけど編集されたファイルがあるとコケてしまう...
my $files = `git status --short | grep '^[MARCD]'`;

print "[] git status input\n" if $DEBUG;
print $files if $DEBUG;

print "[] file list\n" if $DEBUG;
my @Files = split(/\n/, $files);
for (my $i=0; $i<=$#Files; $i++) {
	my $file = $Files[$i];
	$file = substr($file, 3);
	$file =~ s/^\s*(.*?)\s*$/$1/;
	$Files[$i] = $file;
	print "B:".$Files[$i], ":E\n" if $DEBUG;
}

print "[] check\n" if $DEBUG;
foreach my $file (@Files) {
	if (grep { $_ eq $file } @Targets) {
		print $file, "\n";
		$err_flag = 1;
	}
}

if ($err_flag) {
	print "The above files are forbidden to commit.\n";
	exit 1;
} else {
	exit 0;
}

