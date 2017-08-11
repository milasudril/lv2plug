#!/bin/bash
PROJECT=lv2plug
PREFIX=/usr/local

for k in "$@"; do
	case "$k" in
		--prefix=*)
			PREFIX=( "${k#*=}" )
			shift
			;;
		*)
			echo Uknown options "$k"
			exit -1
	esac
done;

echo "Installing $PROJECT with PREFIX=$PREFIX"

declare -a rollback

function do_cleanup ()
	{
	for k in "${rollback[@]}"; do
		echo "$k"
		eval "$k"
	done
	}

function uninstall_cmds ()
	{
	echo "PREFIX="'"'"$PREFIX"'"'
	echo "PROJECT="'"'"$PROJECT"'"'
	for k in "${rollback[@]}"; do
		echo "$k"
	done
	}

trap '
if [ $? -ne 0 ]; then
	echo "Installation to $PREFIX failed"
	do_cleanup
fi
' 0

trap 'do_cleanup
exit 1' SIGINT SIGTERM

function transaction ()
	{
	echo "$1"
	eval "$1"
	rollback=("$2" "${rollback[@]}")
	return 0
	}

set -e
transaction 'mkdir -p "$PREFIX"/include/"$PROJECT"' \
	'rmdir "$PREFIX"/include/"$PROJECT" && rmdir "$PREFIX"/include && rmdir "$PREFIX"'
transaction 'cp __targets/*.hpp "$PREFIX"/include/"$PROJECT"' \
	'rm "$PREFIX"/include/"$PROJECT"/*.hpp'
transaction 'mkdir -p "$PREFIX"/lib' \
	'rmdir "$PREFIX"/lib'
transaction 'cp "__targets/lib$PROJECT.a" "$PREFIX/lib"' \
	'rm "$PREFIX"/lib/lib"$PROJECT".a'
transaction 'cp lv2spectohpp.php "$PREFIX/bin"' \
	'rm "$PREFIX/bin/lv2spectohpp.php"'
transaction 'cp lv2spectottl.php "$PREFIX/bin"' \
	'rm "$PREFIX/bin/lv2spectottl.php"'
transaction 'mkdir -p "$PREFIX/lib/maike"' \
	'rmdir "$PREFIX/lib/maike"'
transaction 'cp __targets/targetlv2spec.so "$PREFIX/lib/maike"' \
	'rm "$PREFIX/lib/maike/targetlv2spec.so"'
transaction 'cp __targets/liblv2plug_ui.a "$PREFIX/lib"' \
	'rm "$PREFIX/lib/liblv2plug_ui.a"' \

if [ "$(id -u)" == "0" ]; then
	chmod -R o+r "$PREFIX"/include
	chmod -R o+r "$PREFIX"/bin
	chmod -R o+r "$PREFIX"/lib
	chmod -R o+r "$PREFIX"/include/"$PROJECT"
	chmod o+x "$PREFIX"/bin/lv2spectohpp.php
	chmod o+x "$PREFIX"/bin/lv2spectottl.php
	chmod o+x "$PREFIX"/lib/maike/targetlv2spec.so
fi


uninstall_cmds > .uninstall.sh
chmod u+x .uninstall.sh

echo "$PROJECT has now been installed"

if ! [[ "$CPATH" == ?(*:)"$PREFIX/include"?(:*) ]];then
	echo " * If you wish to use lib$PROJECT, \
you may need to add $PREFIX/include to the CPATH variable."
fi

if ! [[ "$LIBRARY_PATH" == ?(*:)"$PREFIX/lib"?(:*) ]];then
	echo " * If you wish to use lib$PROJECT, \
you may need to add $PREFIX/lib to the LIBRARY_PATH variable."
fi

if ! [[ "$LD_LIBRARY_PATH" == ?(*:)"$PREFIX/lib"?(:*) ]];then
	echo " * If you wish to use lib$PROJECT you may need to add $PREFIX/lib to the LD_LIBRARY_PATH variable."
fi
