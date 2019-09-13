#!/usr/bin/bash
#
# nextgen.sh
#
# Copyright (C) 2019 madmurphy <madmurphy333@gmail.com>
#
# NExtGen is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# NExtGen is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. # See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <http://www.gnu.org/licenses/>.
#


###############
#  CONSTANTS  #
###############

# General settings
PROJECTS_DIR=~/'Nautilus-Projects'
DEFAULT_DESCRIPTION='(DESCRIPTION TO BE WRITTEN LATER)'

# Regular expressions
RE_DESCR_ALLOW='^[a-zA-Z0-9 _\-\.,:;!?/%&=+()]+$'
RE_VERSION_ALLOW='^[0-9]+\.[0-9]+\.[0-9]+$'
RE_AUTHOR_FORBID='[^a-zA-Z0-9 ]'
# From https://stackoverflow.com/a/2138832
RE_EMAIL_ALLOW="^[a-z0-9!#\$%&'*+/=?^_\`{|}~-]+(\.[a-z0-9!#$%&'*+/=?^_\`{|}~-]+)*@([a-z0-9]([a-z0-9-]*[a-z0-9])?\.)+[a-z0-9]([a-z0-9-]*[a-z0-9])?\$"
RE_USERNAME_FORBID='[^a-zA-Z0-9_\-]'
_RE_BLANK_='^\s*$'

# Other constants
_SCRIPT_PATH_="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"


###############
#   CHECKS    #
###############

# Syntax

_DIE_=0
_DONTASK_=0
_REALARGS_=()
_SKIPARGS_=()

for _ITER_; do

	case "${_ITER_}" in

		-h|--help)
			echo
			echo 'Usage:'
			echo
			echo "    ${0##*/} [options] [name] [description] [initial version] \\"
			echo '        [author'\''s full name] [author'\''s email] [author'\''s username]'
			echo
			echo 'Arguments:'
			echo
			echo '    name [required]'
			echo '        The extension name to be appended to the "nautilus-" prefix (e.g.'
			echo '        "bluetooth")'
			echo '    description [optional]'
			echo '        A short brief of what the extension does'
			echo '    initial version [optional]'
			echo '        The initial version (MAJOR.MINOR.REVISION), usually "0.1.0"'
			echo '    author'\''s full name [optional]'
			echo '        The author'\''s full name'
			echo '    author'\''s email [optional]'
			echo '        The author'\''s email address'
			echo '    author'\''s username [optional]'
			echo '        A public username that identifies the author online'
			echo
			echo 'Options:'
			echo	
			echo '    -h, --help          Show this help message and ignore all other arguments'
			echo '    -u, --unattended    Run this script in unattended mode'
			echo '    -v, --version       Print current version and ignore all other arguments'
			echo
			echo "Current version is $(cat "${_SCRIPT_PATH_}/VERSION")"
			echo
			exit 0
			;;

		-u|--unattended)

			_DONTASK_=1
			;;

		-v|--version)

			cat "${_SCRIPT_PATH_}/VERSION"
			exit 0
			;;

		-*)

			echo "Invalid option ${_ITER_}"
			exit 1
			;;

		*)

			[[ "${#_REALARGS_[@]}" -lt 6 ]] && _REALARGS_+=("${_ITER_}") || _SKIPARGS_+=("${_ITER_}")

			;;

	esac

done

if [[ "${_DONTASK_}" -ne 0 ]] && [[ "${#_REALARGS_[@]}" -lt 1 ]]; then

	echo 'Unable to run in unattended mode: not enough arguments.'
	echo 'You need to specify at least a name for the extension.'
	echo "See ${0##*/} --help for further information."
	exit 1

fi

if [[ "${#_SKIPARGS_[@]}" -gt 0 ]]; then

	echo "Warning: Too many arguments. Ignoring ${_SKIPARGS_[*]}..."

fi

# Semantics

_sanitize_extname_() {

	echo $(echo "${1}" | sed 's/[^[:alnum:]]\+/-/g' | sed 's/[A-Z]/\L&/g' | sed -E 's/^\-|\-[0-9]*$//g')

}

_sanitize_authname_() {

	echo $(echo "${1}" | sed 's/\s/ /g' | sed -E 's/^\s\+|\s\+$//g')

}

# Initial values in attended mode, or final values in unattended mode
_NEW_PKGNAME_=$(_sanitize_extname_ "${_REALARGS_[0]}")
_NEW_PKGDESCR_=$([[ "${_REALARGS_[1]}" =~ ${_RE_BLANK_} ]] && [[ "${_DONTASK_}" -ne 0 ]] && echo "${DEFAULT_DESCRIPTION}" || echo "${_REALARGS_[1]}")
_NEW_PKGVER_=$([[ "${_REALARGS_[2]}" =~ ${_RE_BLANK_} ]] && echo '0.1.0' || echo "${_REALARGS_[2]}")
_NEW_PKGAUTH_=$([[ "${_REALARGS_[3]}" =~ ${_RE_BLANK_} ]] && getent passwd "${LOGNAME}" | cut -d: -f5 | cut -d, -f1 || _sanitize_authname_ "${_REALARGS_[3]}")
_NEW_PKGEMAIL_=$([[ "${_REALARGS_[4]}" =~ ${_RE_BLANK_} ]] && echo "${USER}@$(hostname).localdomain" || echo "${_REALARGS_[4]}")
_NEW_PKGUSR_=$([[ "${_REALARGS_[5]}" =~ ${_RE_BLANK_} ]] && echo "${USER}" || echo "${_REALARGS_[5]}")

_show_summary_() {

	echo "Project's name: nautilus-${_NEW_PKGNAME_}"
	echo "Description: ${_NEW_PKGDESCR_}"
	echo "Version: ${_NEW_PKGVER_}"
	echo "Author's name: ${_NEW_PKGAUTH_}"
	echo "Author's e-mail: ${_NEW_PKGEMAIL_}"
	echo "Author's username: ${_NEW_PKGUSR_}"

}

if [[ "${_DONTASK_}" -ne 0 ]]; then

	if [[ "${_NEW_PKGNAME_}" =~ ${_RE_BLANK_} ]]; then echo 'Bad extension name'; _DIE_=1; fi
	if [[ "${_NEW_PKGDESCR_}" =~ ${_RE_BLANK_} ]] || ! [[ "${_NEW_PKGDESCR_}" =~ ${RE_DESCR_ALLOW} ]]; then echo 'Bad extension description'; _DIE_=1; fi
	if [[ "${_NEW_PKGVER_}" =~ ${_RE_BLANK_} ]] || ! [[ "${_NEW_PKGVER_}" =~ ${RE_VERSION_ALLOW} ]]; then echo 'Bad version number'; _DIE_=1; fi
	if [[ "${_NEW_PKGAUTH_}" =~ ${_RE_BLANK_} ]] || [[ "${_NEW_PKGAUTH_}" =~ ${RE_AUTHOR_FORBID} ]]; then echo 'Bad author'\''s name'; _DIE_=1; fi
	if [[ "${_NEW_PKGEMAIL_}" =~ ${_RE_BLANK_} ]] || ! [[ "${_NEW_PKGEMAIL_}" =~ ${RE_EMAIL_ALLOW} ]] ; then echo 'Bad e-mail address'; _DIE_=1; fi
	if [[ "${_NEW_PKGUSR_}" =~ ${_RE_BLANK_} ]] || [[ "${_NEW_PKGUSR_}" =~ ${RE_USERNAME_FORBID} ]]; then echo 'Bad public username'; _DIE_=1; fi

	if [[ "${_DIE_}" -ne 0 ]]; then

		echo 'Abort'
		exit 1

	fi

	echo 'Generating extension in unattended mode...'
	[[ "${#_REALARGS_[@]}" -lt 6 ]] && echo "See ${0##*/} --help for further options."
	echo
	_show_summary_

fi


###############
# QUESTIONARY #
###############

while [[ "${_DONTASK_}" -eq 0 ]]; do


	# Package name

	_GOOD_ANSWER_=0
	_TMPSTR_="${_NEW_PKGNAME_}"

	while [[ "${_GOOD_ANSWER_}" -eq 0 ]]; do

		echo
		echo '==> Project name (leave "nautilus-" to exit):'
		read -e -p 'nautilus-' -i "${_TMPSTR_}" _TMPSTR_
		[[ "${_TMPSTR_}" =~ ${_RE_BLANK_} ]] && exit 0
		_NEW_PKGNAME_=$(_sanitize_extname_ "${_TMPSTR_}")

		if [[ "${_TMPSTR_}" == "${_NEW_PKGNAME_}" ]]; then

			_GOOD_ANSWER_=1

		else

			echo
			echo 'Project name can contain only lower case letters, numbers and hyphens and must'
			echo 'end with a letter. The current choice will be automatically transformed into'
			read -p "\"nautilus-${_NEW_PKGNAME_}\". Do you wish to proceed? (y/N/q) " -n1 _ITER_
			[[ "${_ITER_}" == "${EOF}" ]] || echo
			[[ "${_ITER_,,}" == 'q' ]] && exit 0

			if [[ "${_ITER_,,}" == 'y' ]]; then

				_GOOD_ANSWER_=1

			fi

		fi

	done


	# Package description

	_GOOD_ANSWER_=0

	while [[ "${_GOOD_ANSWER_}" -eq 0 ]]; do

		echo
		read -e -p '==> Description (leave empty to exit):'$'\n' -i "${_NEW_PKGDESCR_}" _NEW_PKGDESCR_
		[[ "${_NEW_PKGDESCR_}" =~ ${_RE_BLANK_} ]] && exit 0

		if [[ "${_NEW_PKGDESCR_}" =~ ${RE_DESCR_ALLOW} ]]; then

			_GOOD_ANSWER_=1

		else

			echo
			echo 'Invalid description ([\w\s_-.,:;!?/%&=+()] only allowed)'

		fi

	done


	# Package initial version

	_GOOD_ANSWER_=0

	while [[ "${_GOOD_ANSWER_}" -eq 0 ]]; do

		echo
		read -e -p '==> Initial version (leave empty to exit):'$'\n' -i "${_NEW_PKGVER_}" _NEW_PKGVER_
		[[ "${_NEW_PKGVER_}" =~ ${_RE_BLANK_} ]] && exit 0

		if [[ "${_NEW_PKGVER_}" =~ ${RE_VERSION_ALLOW} ]]; then

			_GOOD_ANSWER_=1

		else

			echo
			echo 'Invalid version (MAJOR.MINOR.REVISION only allowed - numbers only)'

		fi

	done


	# Package author

	_GOOD_ANSWER_=0
	_TMPSTR_="${_NEW_PKGAUTH_}"

	while [[ "${_GOOD_ANSWER_}" -eq 0 ]]; do

		echo
		read -e -p '==> Author'\''s name (leave empty to exit):'$'\n' -i "${_TMPSTR_}" _TMPSTR_
		[[ "${_TMPSTR_}" =~ ${_RE_BLANK_} ]] && exit 0

		_NEW_PKGAUTH_=$(_sanitize_authname_ "${_TMPSTR_}")

		if [[ "${_NEW_PKGAUTH_}" =~ ${RE_AUTHOR_FORBID} ]]; then

			echo
			echo 'Invalid author name (alphanumeric and spaces only allowed)'

		else

			_GOOD_ANSWER_=1

		fi

	done


	# Package author's e-mail address

	_GOOD_ANSWER_=0

	while [[ "${_GOOD_ANSWER_}" -eq 0 ]]; do

		echo
		read -e -p '==> Author'\''s e-mail address (leave empty to exit):'$'\n' -i "${_NEW_PKGEMAIL_}" _NEW_PKGEMAIL_
		[[ "${_NEW_PKGEMAIL_}" =~ ${_RE_BLANK_} ]] && exit 0

		if [[ "${_NEW_PKGEMAIL_}" =~ ${RE_EMAIL_ALLOW} ]] ; then

			_GOOD_ANSWER_=1

		else

			echo
			echo 'Invalid e-mail address'

		fi

	done


	# Package author's public username

	_GOOD_ANSWER_=0

	while [[ "${_GOOD_ANSWER_}" -eq 0 ]]; do

		echo
		read -e -p 'Author'\''s public username (leave empty to exit):'$'\n' -i "${_NEW_PKGUSR_}" _NEW_PKGUSR_
		[[ "${_NEW_PKGUSR_}" =~ ${_RE_BLANK_} ]] && exit 0

		if [[ "${_NEW_PKGUSR_}" =~ ${RE_USERNAME_FORBID} ]]; then

			echo
			echo 'Invalid author name (alphanumeric, hyphen and underscore only allowed)'

		else

			_GOOD_ANSWER_=1

		fi

	done


	# Summary

	echo
	echo
	echo '                                    * * *'
	echo
	echo
	echo 'EXTENSION SUMMARY'
	echo
	_show_summary_
	echo
	read -p 'Is this correct? (Y/n/q) ' -n1 _ITER_
	[[ "${_ITER_}" == "${EOF}" ]] || echo
	[[ "${_ITER_,,}" == 'q' ]] && exit 0

	if ! [[ "${_ITER_,,}" == 'n' ]]; then

		_DONTASK_=1

	else

		echo
		echo 'Ok, let'\''s do it again...'

	fi

done


###############
#    BUILD    #
###############

_TITLECASE_PKGNAME_="$(echo ${_NEW_PKGNAME_} | sed -E 's/(^|\-)([a-z])/\U\2/g')"
_SNAKELCASE_PKGNAME_="$(echo ${_NEW_PKGNAME_} | sed 's/\-/_/g')"
_SNAKEUCASE_PKGNAME_="$(echo ${_SNAKELCASE_PKGNAME_} | sed 's/[a-z]/\U&/g')"
_PKGTARNAME_="nautilus-${_NEW_PKGNAME_}-${_NEW_PKGVER_}"
_TMPDIR_="$(mktemp -d)"

# Syntax: `recursed $OLDTEXT $NEWTEXT`
recursed() {

	grep --color=never -rl ${1} "${_TMPDIR_}" | xargs sed -i "s|${1}|${2}|g"

}

cp -r "${_SCRIPT_PATH_}/extension-template/package"/. "${_TMPDIR_}/${_PKGTARNAME_}"
cp "${_SCRIPT_PATH_}/extension-template/PKGBUILD" "${_TMPDIR_}/PKGBUILD"
mv "${_TMPDIR_}/${_PKGTARNAME_}/src/extension-template.c" "${_TMPDIR_}/${_PKGTARNAME_}/src/nautilus-${_NEW_PKGNAME_}.c"
recursed '__REPL_IDCASE_PACKAGENAME__' "${_NEW_PKGNAME_}"
recursed '__REPL_AUTHOR_NAME__' "${_NEW_PKGAUTH_}"
recursed '__REPL_AUTHOR_EMAIL__' "${_NEW_PKGEMAIL_}"
recursed '__REPL_PACKAGE_YEAR__' "$(date '+%Y')"
recursed '__REPL_TITLECASE_PACKAGENAME__' "${_TITLECASE_PKGNAME_}"
recursed '__REPL_LOWERCASE_PACKAGENAME__' "${_SNAKELCASE_PKGNAME_}"
recursed '__REPL_UPPERCASE_PACKAGENAME__' "${_SNAKEUCASE_PKGNAME_}"
recursed '__REPL_SHORT_PACKAGE_VERSION__' "$(echo ${_NEW_PKGVER_} | sed 's/\.[0-9]\+$//')"
recursed '__REPL_AUTHOR_NICKNAME__' "${_NEW_PKGUSR_}"
recursed '__REPL_LONG_PACKAGE_VERSION__' "${_NEW_PKGVER_}"
recursed '__REPL_PACKAGE_DESCRIPTION__' "${_NEW_PKGDESCR_}"

_PKGDIR_="${PROJECTS_DIR}/${_NEW_PKGNAME_}"

if [[ -d "${_PKGDIR_}" ]]; then

	_TMPSTR_='_'
	_ITER_=2

	while [[ -d "${PROJECTS_DIR}/${_NEW_PKGNAME_}${_TMPSTR_}${_ITER_}" ]]; do

		((_ITER_++))

	done

	_PKGDIR_="${_PKGDIR_}${_TMPSTR_}${_ITER_}"

fi

mkdir -p "${_PKGDIR_}"
(cd "${_TMPDIR_}" && tar -czvf "${_PKGDIR_}/${_PKGTARNAME_}.tar.gz" "${_PKGTARNAME_}" &> /dev/null)
_TMPSTR_=$(sha256sum "${_PKGDIR_}/${_PKGTARNAME_}.tar.gz")
sed -i "s|__REPL_PACKAGE_SHA256SUMS__|${_TMPSTR_%% *}|g" "${_TMPDIR_}/PKGBUILD"
mv "${_TMPDIR_}/PKGBUILD" "${_PKGDIR_}/PKGBUILD"
rm -R "${_TMPDIR_}"
echo
echo "Project has been created in ${_PKGDIR_}."
echo
echo "You can get started by hacking the function \`nautilus_${_SNAKELCASE_PKGNAME_}_helloworld()\`"
echo "in src/nautilus-${_NEW_PKGNAME_}.c. Good luck!"
echo


# EOF

