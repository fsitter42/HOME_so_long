# Set up the prompt

autoload -Uz promptinit
promptinit
prompt adam1

setopt histignorealldups sharehistory

# Use emacs keybindings even if our EDITOR is set to vi
bindkey -e

# Keep 1000 lines of history within the shell and save it to ~/.zsh_history:
HISTSIZE=1000
SAVEHIST=1000
HISTFILE=~/.zsh_history

# Use modern completion system
autoload -Uz compinit
compinit

zstyle ':completion:*' auto-description 'specify: %d'
zstyle ':completion:*' completer _expand _complete _correct _approximate
zstyle ':completion:*' format 'Completing %d'
zstyle ':completion:*' group-name ''
zstyle ':completion:*' menu select=2
eval "$(dircolors -b)"
zstyle ':completion:*:default' list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*' list-colors ''
zstyle ':completion:*' list-prompt %SAt %p: Hit TAB for more, or the character to insert%s
zstyle ':completion:*' matcher-list '' 'm:{a-z}={A-Z}' 'm:{a-zA-Z}={A-Za-z}' 'r:|[._-]=* r:|=* l:|=*'
zstyle ':completion:*' menu select=long
zstyle ':completion:*' select-prompt %SScrolling active: current selection at %p%s
zstyle ':completion:*' use-compctl false
zstyle ':completion:*' verbose true

zstyle ':completion:*:*:kill:*:processes' list-colors '=(#b) #([0-9]#)*=0=01;31'
zstyle ':completion:*:kill:*' command 'ps -u $USER -o pid,%cpu,tty,cputime,cmd'

export USER="fsitter"
export MAIL="fsitter@student.42vienna.com"
alias ll="ls -l"
alias gccw="gcc -Wall -Wextra -Werror"
alias ccw="cc -Wall -Wextra -Werror"
alias mini='~/mini-moulinette/mini-moul.sh'
#alias gitall="git add . && git commit -m \'600\' && git push"
alias sshome="ssh fsitter@89.58.7.133 -p 4242"
alias fzf="fzf --preview 'batcat --color=never --style=numbers {}'"
alias py="python3"
alias rmrm="rm -rf"
# Generated for envman. Do not edit.
[ -s "$HOME/.config/envman/load.sh" ] && source "$HOME/.config/envman/load.sh"
export PATH=/home/fsitter/.local/funcheck/host:$PATH
alias funcheck="echo funcheck is a bad programm that forces undefined behavior. we are not using such things."

r() {
	./"$1"
}
gitall() {
		git add .
		git commit -m "$1"
		git push
}

gitname() {
	git clone "$1" "$2"
	cd "$2"
}

gitgo() {
	git clone "$1" aa
	cd aa
	code .
}
gitmake() {
	git clone "$1" aa
	cd aa
	make
}
del() {
	cd ..
	rm -rf aa
}
zenmode() {
	python3 /home/fsitter/forkroyal/HOME_so_long/hello/so_long
}
