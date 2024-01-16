@echo off
color 2F
path %cd%\tools;%PATH%
if not defined blduser set blduser=x64efibld
set username=%blduser%
prompt [%computername%: %username%] $d$s$t$_$p$_$_$+$g
echo Current user is now %blduser%
goto :eof